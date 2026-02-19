#include "../include/database_manager.hpp"
#include <iostream>
#include <sqlite3.h>

DatabaseManager::DatabaseManager(const std::string &path)
    : db_(nullptr), db_path_(path) {}

DatabaseManager::~DatabaseManager() {
  if (db_)
    sqlite3_close(db_);
}

bool DatabaseManager::initialize() {
  int rc = sqlite3_open(db_path_.c_str(), &db_);

  if (rc != SQLITE_OK) {
    std::cout << "Cannot open database: " << sqlite3_errmsg(db_) << std::endl;
    sqlite3_close(db_);
    return false;
  }
  std::cout << "opened database successfully: " << db_path_ << std::endl;

  std::string sql = "CREATE TABLE IF NOT EXISTS entries ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "type TEXT NOT NULL,"
                    "title TEXT NOT NULL,"
                    "content_data TEXT);";

  char *errMsg = nullptr;
  rc = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errMsg);

  if (rc != SQLITE_OK) {
    std::cout << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return false;
  }

  std::cout << "Table 'entries' created or alreade exists." << std::endl;
  return true;
}
