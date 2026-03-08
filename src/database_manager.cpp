#include "database_manager.hpp"
#include <exception>
#include <iostream>
#include <memory>

const std::string DatabaseManager::CREATE_ENTRIES_TABLE =
    "CREATE TABLE IF NOT EXISTS entries ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "type TEXT NOT NULL CHECK(type IN ('password', 'note')),"
    "title TEXT NOT NULL,"
    "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
    ");";

const std::string DatabaseManager::CREATE_PASSWORDS_TABLE =
    "CREATE TABLE IF NOT EXISTS passwords ("
    "id INTEGER PRIMARY KEY,"
    "website TEXT NOT NULL,"
    "username TEXT NOT NULL,"
    "encrypted_password TEXT NOT NULL,"
    "FOREIGN KEY(id) REFERENCES entries(id) ON DELETE CASCADE"
    ");";

const std::string DatabaseManager::CREATE_NOTES_TABLE =
    "CREATE TABLE IF NOT EXISTS notes ("
    "id INTEGER PRIMARY KEY,"
    "content TEXT NOT NULL,"
    "FOREIGN KEY(id) REFERENCES entries(id) ON DELETE CASCADE"
    ");";

DatabaseManager::DatabaseManager(const std::string &path)
    : db_(path.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE),
      db_path_(path) {
  std::cout << "Database opened: " << path << std::endl;
}

bool DatabaseManager::initialize() {
  try {
    db_.exec(CREATE_ENTRIES_TABLE);
    db_.exec(CREATE_PASSWORDS_TABLE);
    db_.exec(CREATE_NOTES_TABLE);

    std::cout << "All tables created successfully" << std::endl;
    std::cout << " - entries table ready" << std::endl;
    std::cout << " - passwords table ready" << std::endl;
    std::cout << " - notes table ready" << std::endl;
    return true;

  } catch (const std::exception &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    return false;
  }
}

bool DatabaseManager::executeQuery(const std::string &query) {
  try {
    db_.exec(query);
    std::cout << "Query executed: " << query << std::endl;
    return true;
  } catch (const std::exception &e) {
    std::cout << "Query failed: " << e.what() << std::endl;
    return false;
  }
}
int DatabaseManager::addEntry(const std::string &type,
                              const std::string &title) {
  try {
    if (!insert_entry_stmt_) {
      insert_entry_stmt_ = std::make_unique<SQLite::Statement>(
          db_, "INSERT INTO entries (type, title) VALUES (?, ?)");
    }

    insert_entry_stmt_->bind(1, type);
    insert_entry_stmt_->bind(2, title);
    insert_entry_stmt_->exec();

    int newId = db_.getLastInsertRowid();

    insert_entry_stmt_->reset();
    std::cout << "Entry added with ID: " << newId << std::endl;
    return newId;

  } catch (const std::exception &e) {
    std::cerr << "Failed to add entry: " << e.what() << std::endl;
    return -1;
  }
}

void DatabaseManager::addPasswordDetails(int entryId,
                                         const std::string &website,
                                         const std::string &username,
                                         const std::string &encPassword) {
  try {
    if (!insert_password_stmt_) {
      insert_password_stmt_ = std::make_unique<SQLite::Statement>(
          db_, "INSERT INTO passwords (id, website, username, "
               "encrypted_password) VALUES (?, ?, ?, ?)");
    }

    insert_password_stmt_->bind(1, entryId);
    insert_password_stmt_->bind(2, website);
    insert_password_stmt_->bind(3, username);
    insert_password_stmt_->bind(4, encPassword);
    insert_password_stmt_->exec();

    insert_password_stmt_->reset();
  } catch (const std::exception &e) {
    std::cerr << "Failed to add entry: " << e.what() << std::endl;
  }
}

void DatabaseManager::addNoteDetails(int entryId, const std::string &content) {
  try {
    if (!insert_note_stmt_) {
      insert_note_stmt_ = std::make_unique<SQLite::Statement>(
          db_, "INSERT INTO notes (id, content) VALUES (?, ?)");
    }

    insert_note_stmt_->bind(1, entryId);
    insert_note_stmt_->bind(2, content);
    insert_note_stmt_->exec();

    insert_note_stmt_->reset();
  } catch (const std::exception &e) {
    std::cerr << "Failed to add entry: " << e.what() << std::endl;
  }
}
