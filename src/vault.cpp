#include "../include/vault.hpp"

Vault::Vault() : dbManager(std::make_unique<DatabaseManager>("Vault.db")) {
  dbManager->initialize();
}

void Vault::addNoteEntry(const std::string &title, const std::string &content,
                         const std::string &category) {
  dbManager->addNoteEntry(title, content, category);
}

bool Vault::deleteEntry(int id) { return dbManager->deleteEntry(id); }

void Vault::clear() { dbManager->clearAllEntries(); }

bool Vault::updateNoteEntry(int id, const std::string &title,
                            const std::string &content,
                            const std::string &category) {
  return dbManager->updateNoteEntry(id, title, content, category);
}
