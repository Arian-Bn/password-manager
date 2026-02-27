#include "database_manager.hpp"
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
