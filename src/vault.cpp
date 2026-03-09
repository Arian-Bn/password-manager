#include "../include/vault.hpp"
#include <iostream>

Vault::Vault() : dbManager(std::make_unique<DatabaseManager>("Vault.db")) {
  dbManager->initialize();
}

void Vault::addPasswordEntry(const std::string &title,
                             const std::string &website,
                             const std::string &username,
                             const std::string &password) {
  dbManager->addPasswordEntry(title, website, username, password);
}

void Vault::addNoteEntry(const std::string &title, const std::string &content) {
  dbManager->addNoteEntry(title, content);
}

void Vault::displayAll() const {
  std::cout << "Display from DB - coming soon..." << std::endl;
}

void Vault::findByTitle(const std::string &title) const {
  std::cout << "Search in DB for '" << title << "' - coming soon..."
            << std::endl;
}

size_t Vault::getEntryCount() const { return 0; }

bool Vault::deleteEntry(size_t index) {
  std::cout << "Delete entry " << index << " from DB - coming soon..."
            << std::endl;
  return false;
}

void Vault::clear() { std::cout << "Clear DB - coming soon..." << std::endl; }
