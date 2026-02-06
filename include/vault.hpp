#pragma once
#include "entry.hpp"
#include <memory>
#include <string>
#include <vector>

class Vault {
public:
  Vault() = default;
  ~Vault() = default;

  void addPasswordEntry(const std::string &title, const std::string &website,
                        const std::string &username,
                        const std::string &password);
  void addNoteEntry(const std::string &title, const std::string &content);

  void displayAll() const;

  void findByTitle(const std::string &title) const;

  size_t getEntryCount() const { return entries_.size(); }

  bool deleteEntry(size_t index);

  void clear();

private:
  std::vector<std::unique_ptr<Entry>> entries_;
};
