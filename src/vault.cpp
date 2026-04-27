#include "../include/vault.hpp"

Vault::Vault() : dbManager(std::make_unique<DatabaseManager>("Vault.db")) {
  dbManager->initialize();
}

void Vault::addNoteEntry(const std::string &title, const std::string &content) {
  dbManager->addNoteEntry(title, content);
}

bool Vault::deleteEntry(int id) { return dbManager->deleteEntry(id); }

void Vault::clear() { dbManager->clearAllEntries(); }
