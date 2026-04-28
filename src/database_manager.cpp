#include "database_manager.hpp"
#include <SQLiteCpp/Statement.h>
#include <exception>
#include <iostream>

const std::string DatabaseManager::CREATE_ENTRIES_TABLE =
    "CREATE TABLE IF NOT EXISTS entries ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "type TEXT NOT NULL CHECK(type IN ('note')),"
    "title TEXT NOT NULL,"
    "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
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
    db_.exec(CREATE_NOTES_TABLE);

    std::cout << "All tables created successfully" << std::endl;
    std::cout << " - entries table ready" << std::endl;
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

bool DatabaseManager::deleteEntry(int id) {
  try {
    db_.exec("BEGIN  TRANSACTION");
    SQLite::Statement query(db_, "DELETE FROM entries WHERE id = ?");
    query.bind(1, id);
    query.exec();

    db_.exec("COMMIT");
    std::cout << "Entry " << id << " deleted" << std::endl;
    return true;
  } catch (const std::exception &e) {
    db_.exec("ROLLBACK");
    std::cerr << "Delete failed: " << e.what() << std::endl;
    return false;
  }
}

std::tuple<int, std::string, std::string>
DatabaseManager::getNoteEntry(int id) {
  SQLite::Statement query(db_, "SELECT e.id, e.title, n.content FROM entries e "
                               "JOIN notes n ON e.id = n.id WHERE e.id = ?");

  query.bind(1, id);

  if (query.executeStep()) {
    return {query.getColumn(0), query.getColumn(1), query.getColumn(2)};
  }

  return {0, "", ""};
}
