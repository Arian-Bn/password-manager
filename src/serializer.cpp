#include "../include/serializer.hpp"
#include "../include/vault.hpp"
#include <fstream>
#include <iostream>

bool Serializer::saveToFile(const Vault &vault, const std::string &filename) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    std::cout << "ERROR: Cannot open file for writing: " << filename
              << std::endl;
    return false;
  }

  int count = 0;
  // for (const auto &entry : vault.getAllEntries()) {
  //   file << entry->serialize() << "\n";
  //   count++;
  // }
  //
  file.close();
  std::cout << "Saved " << count << " entries to " << filename << std::endl;
  return true;
}

bool Serializer::loadFromFile(Vault &vault, const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "ERROR: Cannot open file or for reading: " << filename
              << std::endl;
    return false;
  }

  vault.clear();

  std::string line;
  int count = 0;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    //   auto entry = deserializeEntry(line);
    //   if (entry) {
    //     vault.addEntry(std::move(entry));
    //     count++;
    //   }
    // }

    file.close();
    std::cout << "Loaded " << count << " entries from " << filename
              << std::endl;
    return true;
  }

  // std::unique_ptr<Entry> Serializer::deserializeEntry(const std::string
  // &line) {
  //   return Entry::deserialize(line);
  // }
}
