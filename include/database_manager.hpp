#pragma once
#include <QString>
#include <SQLiteCpp/Database.h>
#include <string>
#include <vector>

class DatabaseManager {
public:
  DatabaseManager(const std::string &db_path);
  bool initialize();
  bool executeQuery(const std::string &query);

  bool addNoteEntry(const std::string &title, const std::string &content,
                    const std::string &category);
  std::vector<std::tuple<int, std::string, std::string>> getAllEntries() const;
  bool clearAllEntries();
  bool deleteEntry(int id);
  std::tuple<int, std::string, std::string, std::string> getNoteEntry(int id);
  std::vector<std::tuple<int, std::string, std::string>>
  getEntriesFiltered(const std::string &title, const std::string &category);
  std::vector<std::string> getAllCategories() const;
  bool updateNoteEntry(int id, const std::string &title,
                       const std::string &content, const std::string &category);

private:
  SQLite::Database db_;
  std::string db_path_;

  // SQL constants
  static const std::string CREATE_ENTRIES_TABLE;
  static const std::string CREATE_NOTES_TABLE;
};
