#pragma once
#include "database_manager.hpp"
#include <memory>
#include <string>

class Vault {
public:
  Vault();
  ~Vault() = default;

  void addNoteEntry(const std::string &title, const std::string &content);
  bool deleteEntry(int id);
  void clear();

private:
  std::unique_ptr<DatabaseManager> dbManager;
};
