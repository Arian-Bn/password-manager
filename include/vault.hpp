#pragma once
#include "../include/entry.hpp"
#include "../include/note_entry.hpp"
#include "../include/password_entry.hpp"
#include <memory>
#include <string>
#include <vector>

class Vault {
public:
  Vault() = default;
  ~Vault() = default;

  void addPasswordEntry(const std::string &title, const std::string &websit,
                        const std::string &usrtname,
                        const std::string &password);
  void addNoteEntry(const std::string &title, const std::string &content);

  void displayAll() const;

  void findByTitle(const std::string &title) const;

  size_t getEntryCout() const { return entries_.size(); }

  void clear();

private:
  std::vector<std::unique_ptr<Entry>> entries_;
};
