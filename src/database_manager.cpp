#include "database_manager.hpp"
#include <exception>
#include <iostream>

const std::string DatabaseManager::CREATE_ENTRIES_TABLE =
    "CREATE TABLE IF NOT EXISTS entries ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "type TEXT NOT NULL CHECK(type IN ('note')),"
    "title TEXT NOT NULL,"
    "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
    ");";

const std::string DatabaseManager::CREATE_NOTES_TABLE =
    "CREATE TABLE IF NOT EXISTS notes ("
    "id INTEGER PRIMARY KEY,"
    "content TEXT NOT NULL,"
    "category TEXT,"
    "FOREIGN KEY(id) REFERENCES entries(id) ON DELETE CASCADE"
    ");";

DatabaseManager::DatabaseManager(const std::string &path)
    : db_(path.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE),
      db_path_(path) {}

bool DatabaseManager::initialize() {
  try {
    // Enable FOREIGN KEY support for ON DELETE CASCADE
    db_.exec("PRAGMA foreign_keys = ON;");
    db_.exec(CREATE_ENTRIES_TABLE);
    db_.exec(CREATE_NOTES_TABLE);

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

bool DatabaseManager::addNoteEntry(const std::string &title,
                                   const std::string &content,
                                   const std::string &category) {
  try {
    db_.exec("BEGIN TRANSACTION");

    SQLite::Statement insertEntry(
        db_, "INSERT INTO entries (type, title) VALUES (?, ?)");
    insertEntry.bind(1, "note");
    insertEntry.bind(2, title);
    insertEntry.exec();

    int entryId = db_.getLastInsertRowid();

    SQLite::Statement insertNote(
        db_, "INSERT INTO notes (id, content, category) VALUES (?, ?, ?)");
    insertNote.bind(1, entryId);
    insertNote.bind(2, content);
    insertNote.bind(3, category);
    insertNote.exec();

    db_.exec("COMMIT");
    return true;
  } catch (const std::exception &e) {
    db_.exec("ROLLBACK");
    std::cerr << "Failed to add entry: " << e.what() << std::endl;
    return false;
  }
}

std::vector<std::tuple<int, std::string, std::string>>
DatabaseManager::getAllEntries() const {
  std::vector<std::tuple<int, std::string, std::string>> entries;

  SQLite::Statement query(
      db_, "SELECT id, title, type FROM entries ORDER BY id DESC");

  while (query.executeStep()) {
    int id = query.getColumn(0);
    std::string title = query.getColumn(1);
    std::string type = query.getColumn(2);
    entries.push_back({id, title, type});
  }

  return entries;
}

bool DatabaseManager::clearAllEntries() {
  try {
    db_.exec("DELETE FROM entries");
    std::cout << "All entries cleared" << std::endl;
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Failed to clear: " << e.what() << std::endl;
    return false;
  }
}

bool DatabaseManager::deleteEntry(int id) {
  try {
    db_.exec("BEGIN  TRANSACTION");
    SQLite::Statement query(db_, "DELETE FROM entries WHERE id = ?");
    query.bind(1, id);
    query.exec();

    db_.exec("COMMIT");
    return true;
  } catch (const std::exception &e) {
    db_.exec("ROLLBACK");
    std::cerr << "Delete failed: " << e.what() << std::endl;
    return false;
  }
}

std::tuple<int, std::string, std::string, std::string>
DatabaseManager::getNoteEntry(int id) {
  SQLite::Statement query(
      db_, "SELECT e.id, e.title, n.content, n.category FROM entries e "
           "JOIN notes n ON e.id = n.id WHERE e.id = ?");

  query.bind(1, id);

  if (query.executeStep()) {
    return {query.getColumn(0), query.getColumn(1), query.getColumn(2),
            query.getColumn(3)};
  }

  return {0, "", "", ""};
}

std::vector<std::tuple<int, std::string, std::string>>
DatabaseManager::getEntriesFiltered(const std::string &title,
                                    const std::string &category) {
  std::vector<std::tuple<int, std::string, std::string>> entries;

  // Use LIKE for category so that empty string (from "All" filter) becomes '%'
  // a  nd matches all categories
  std::string searchCategory = category.empty() ? "%" : category;

  SQLite::Statement query(
      db_, "SELECT e.id, e.title, e.type FROM entries e JOIN notes n ON e.id = "
           "n.id WHERE e.title LIKE '%' || ? || '%' AND n.category LIKE ?");

  query.bind(1, title);
  query.bind(2, searchCategory);

  while (query.executeStep()) {
    int id = query.getColumn(0);
    std::string title = query.getColumn(1);
    std::string type = query.getColumn(2);
    entries.push_back({id, title, type});
  }

  return entries;
}

std::vector<std::string> DatabaseManager::getAllCategories() const {
  std::vector<std::string> categories;
  SQLite::Statement query(db_, "SELECT DISTINCT category FROM notes WHERE "
                               "category NOT NULL AND category != ''");

  while (query.executeStep()) {
    categories.push_back(query.getColumn(0));
  }

  return categories;
}

bool DatabaseManager::updateNoteEntry(int id, const std::string &title,
                                      const std::string &content,
                                      const std::string &category) {
  try {
    db_.exec("BEGIN TRANSACTION");

    SQLite::Statement updateEntry(db_,
                                  "UPDATE entries SET title = ? WHERE id = ?");
    updateEntry.bind(1, title);
    updateEntry.bind(2, id);
    updateEntry.exec();

    SQLite::Statement updateNote(
        db_, "UPDATE notes SET content = ?, category = ? WHERE id = ?");
    updateNote.bind(1, content);
    updateNote.bind(2, category);
    updateNote.bind(3, id);
    updateNote.exec();

    db_.exec("COMMIT");
    return true;
  } catch (const std::exception &e) {
    db_.exec("ROLLBACK");
    std::cerr << "Faild to update entry:" << e.what() << std::endl;
    return false;
  }
}
