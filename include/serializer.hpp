#pragma once
#include "vault.hpp"
#include <string>

class Vault;

class Serializer {
public:
  static bool saveToFile(const Vault &vault, const std::string &filename);
  static bool loadFromFile(Vault &vault, const std::string &filename);

private:
  static std::unique_ptr<class Entry> deserializeEntry(const std::string &line);
};
