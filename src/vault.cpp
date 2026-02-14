#include "../include/vault.hpp"
#include "../include/note_entry.hpp"
#include "../include/password_entry.hpp"
#include <iostream>

void Vault::addPasswordEntry(const std::string &title,
                             const std::string &website,
                             const std::string &username,
                             const std::string &password) {
  entries_.push_back(
      std::make_unique<PasswordEntry>(title, website, username, password));

  std::cout << "Password entry added: " << title << std::endl;
}

void Vault::addNoteEntry(const std::string &title, const std::string &content) {
  entries_.push_back(std::make_unique<NoteEntry>(title, content));
  std::cout << "Note entry added: " << title << std::endl;
}

void Vault::displayAll() const {
  if (entries_.empty()) {
    std::cout << "\nVault is empty. Add some entries first!\n" << std::endl;
    return;
  }

  std::cout << "\n=== VAULT CONTENTS (" << entries_.size()
            << ") ===" << std::endl;
  for (size_t i = 0; i < entries_.size(); i++) {
    std::cout << "[" << i + 1 << "] ";
    entries_[i]->display();
    if (i != entries_.size() - 1) {
      std::cout << "---" << std::endl;
    }
  }
  std::cout << "\n=== END OF VAULT ===\n" << std::endl;
}

void Vault::findByTitle(const std::string &title) const {
  bool found = false;

  for (const auto &entry : entries_) {
    if (entry->getTitle().find(title) != std::string::npos) {
      if (!found) {
        std::cout << "\nSearch results for \"" << title << "\":" << std::endl;
        found = true;
      }
      entry->display();
      std::cout << "---" << std::endl;
    }
  }

  if (!found) {
    std::cout << "No entries found with title containing: " << title
              << std::endl;
  }
}

bool Vault::deleteEntry(size_t index) {
  if (index == 0 || index > entries_.size()) {
    return false;
  }

  std::string title = entries_[index - 1]->getTitle();
  entries_.erase(entries_.begin() + index - 1);
  return true;
}

void Vault::clear() {
  entries_.clear();
  std::cout << "Vault cleared. All entries removed." << std::endl;
}
