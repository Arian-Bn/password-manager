#pragma once
#include <SQLiteCpp/Database.h>
#include <memory>
#include <string>
#include <vector>

class DatabaseManager {
public:
  DatabaseManager(const std::string &db_path);
  bool initialize();
  bool executeQuery(const std::string &query);

  bool addPasswordEntry(const std::string &title, const std::string &website,
                        const std::string &username,
                        const std::string &encrypted_password);
  bool addNoteEntry(const std::string &title, const std::string &content);

  void beginTransaction();
  void commitTransaction();
  void rollbackTransaction();

  std::vector<std::tuple<int, std::string, std::string, std::string>>
  loadAllEntries() const;

private:
  SQLite::Database db_;
  std::string db_path_;
  std::unique_ptr<SQLite::Statement> test_stmt_;

  // SQL constants
  static const std::string CREATE_ENTRIES_TABLE;
  static const std::string CREATE_PASSWORDS_TABLE;
  static const std::string CREATE_NOTES_TABLE;
};
