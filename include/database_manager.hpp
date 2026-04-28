#pragma once
#include <SQLiteCpp/Database.h>
#include <string>
#include <vector>

class DatabaseManager {
public:
  DatabaseManager(const std::string &db_path);
  bool initialize();
  bool executeQuery(const std::string &query);

  bool addNoteEntry(const std::string &title, const std::string &content);
  std::vector<std::tuple<int, std::string, std::string>> getAllEntries() const;
  bool clearAllEntries();
  bool deleteEntry(int id);
  std::tuple<int, std::string, std::string> getNoteEntry(int id);

private:
  SQLite::Database db_;
  std::string db_path_;

  // SQL constants
  static const std::string CREATE_ENTRIES_TABLE;
  static const std::string CREATE_NOTES_TABLE;
};
