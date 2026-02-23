#include "database_manager.hpp"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string &path)
    : db_(path.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE),
      db_path_(path) {
  std::cout << "Database opened: " << path << std::endl;
}

bool DatabaseManager::initialize() {
  try {
    db_.exec("CREATE TABLE IF NOT EXISTS entries ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
             "type TEXT NOT NULL,"
             "title TEXT NOT NULL,"
             "content_data TEXT);");
    std::cout << "Table 'entries' ready" << std::endl;
    return true;
  } catch (const std::exception &e) {
    std::cerr << "SQL error: " << e.what() << std::endl;
    return false;
  }
}
