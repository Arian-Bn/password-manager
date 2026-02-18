#pragma once
#include <sqlite3.h>
#include <string>

class DatabaseManager {
public:
  DatabaseManager(const std::string &db_path);
  ~DatabaseManager();
  bool initialize();

private:
  sqlite3 *db_;
  std::string db_path_;
};
