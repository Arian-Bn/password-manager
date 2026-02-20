#pragma once
#include <SQLiteCpp/Database.h>
#include <string>

class DatabaseManager {
public:
  DatabaseManager(const std::string &db_path);
  bool initialize();

private:
  SQLite::Database db_;
  std::string db_path_;
};
