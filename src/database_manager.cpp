#include "database_manager.hpp"
#include <SQLiteCpp/Statement.h>
#include <exception>
#include <iostream>

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

bool DatabaseManager::addPasswordEntry(const std::string &title,
                                       const std::string &website,
                                       const std::string &username,
                                       const std::string &encrypted_password) {
  try {
    db_.exec("BEGIN TRANSACTION");
    SQLite::Statement insertEntry(
        db_, "INSERT INTO entries (type, title) VALUES (?, ?)");
    insertEntry.bind(1, "password");
    insertEntry.bind(2, title);
    insertEntry.exec();

    int entryId = db_.getLastInsertRowid();

    SQLite::Statement insertPass(
        db_, "INSERT INTO passwords (id, website, username, "
             "encrypted_password) VALUES (?, ?, ?, ?)");
    insertPass.bind(1, entryId);
    insertPass.bind(2, website);
    insertPass.bind(3, username);
    insertPass.bind(4, encrypted_password);
    insertPass.exec();

    db_.exec("COMMIT");
    std::cout << "Password entry added with ID: " << entryId << std::endl;
    return true;

  } catch (const std::exception &e) {
    db_.exec("ROLLBACK");
    std::cerr << "Failed to add entry: " << e.what() << std::endl;
    return false;
  }
}

bool DatabaseManager::addNoteEntry(const std::string &title,
                                   const std::string &content) {
  try {
    db_.exec("BEGIN TRANSACTION");

    SQLite::Statement insertEntry(
        db_, "INSERT INTO entries (type, title) VALUES (?, ?)");
    insertEntry.bind(1, "note");
    insertEntry.bind(2, title);
    insertEntry.exec();

    int entryId = db_.getLastInsertRowid();

    SQLite::Statement insertNote(
        db_, "INSERT INTO notes (id, content) VALUES (?, ?)");
    insertNote.bind(1, entryId);
    insertNote.bind(2, content);
    insertNote.exec();

    db_.exec("COMMIT");
    std::cout << "Note entry added with ID: " << entryId << std::endl;
    return true;
  } catch (const std::exception &e) {
    db_.exec("ROLLBACK");
    std::cerr << "Failed to add entry: " << e.what() << std::endl;
    return false;
  }
}

std::vector<std::tuple<int, std::string, std::string>>
DatabaseManager::getAllEntries() const {
  std::vector<std::tuple<int, std::string, std::string>> entries;

  SQLite::Statement query(
      db_, "SELECT id, title, type FROM entries ORDER BY ID DESC");

  while (query.executeStep()) {
    int id = query.getColumn(0);
    std::string title = query.getColumn(1);
    std::string type = query.getColumn(2);
    entries.push_back({id, title, type});
  }

  return entries;
}

bool DatabaseManager::clearAllEntries() {
  try {
    db_.exec("DELETE FROM entries");
    std::cout << "All entries cleared" << std::endl;
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Failed to clear: " << e.what() << std::endl;
    return false;
  }
}
