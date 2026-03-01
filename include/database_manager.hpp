#pragma once
#include <SQLiteCpp/Database.h>
#include <memory>
#include <string>

class DatabaseManager {
public:
  DatabaseManager(const std::string &db_path);

  bool initialize();
  bool executeQuery(const std::string &query);

  int addEntry(const std::string &type, const std::string &title);
  void addPasswordDetails(int entryId, const std::string &website,
                          const std::string &username,
                          const std::string &encPassword);
  void addNoteDetails(int entryId, const std::string &content);

  void beginTransaction();
  void commitTransaction();
  void rollbackTransaction();

private:
  SQLite::Database db_;
  std::string db_path_;
  std::unique_ptr<SQLite::Statement> test_stmt_;

  std::unique_ptr<SQLite::Statement> insert_entry_stmt_;
  std::unique_ptr<SQLite::Statement> insert_password_stmt_;
  std::unique_ptr<SQLite::Statement> insert_note_stmt_;

  // SQL constants
  static const std::string CREATE_ENTRIES_TABLE;
  static const std::string CREATE_PASSWORDS_TABLE;
  static const std::string CREATE_NOTES_TABLE;
};
