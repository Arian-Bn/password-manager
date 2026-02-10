#include "../include/serializer.hpp"
#include "../include/note_entry.hpp"
#include "../include/password_entry.hpp"
#include "../include/vault.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

bool Serialize::saveToFile(const Vault &vault, const std::string &filename) {
  std::cout << "TODO: Implement saveToFile()" << std::endl;

  (void)vault;
  (void)filename;

  return true;
}

bool Serialize::loadFromFile(Vault &vault, const std::string &filename) {
  std::cout << "TODO: Implement loadFromFile()" << std::endl;

  (void)vault;
  (void)filename;

  return true;
}
