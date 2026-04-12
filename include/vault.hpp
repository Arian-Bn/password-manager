#pragma once
#include "database_manager.hpp"
#include <memory>
#include <string>

class Vault {
public:
  Vault();
  ~Vault() = default;

  void addPasswordEntry(const std::string &title, const std::string &website,
                        const std::string &username,
                        const std::string &password);
  void addNoteEntry(const std::string &title, const std::string &content);

  void displayAll() const;
  void findByTitle(const std::string &title) const;

  size_t getEntryCount() const;
  bool deleteEntry(int id);
  void clear();

private:
  std::unique_ptr<DatabaseManager> dbManager;
};
