#pragma once
#include <SQLiteCpp/Database.h>
#include <memory>
#include <string>

class DatabaseManager {
public:
  DatabaseManager(const std::string &db_path);
  bool initialize();
  bool executeQuery(const std::string &query);

private:
  SQLite::Database db_;
  std::string db_path_;
  std::unique_ptr<SQLite::Statement> test_stmt_;

  // SQL constants
  static const std::string CREATE_ENTRIES_TABLE;
  static const std::string CREATE_PASSWORDS_TABLE;
  static const std::string CREATE_NOTES_TABLE;
};
