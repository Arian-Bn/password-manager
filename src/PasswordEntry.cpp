#include "../include/PasswordEntry.hpp"
#include <algorithm>

std::string PasswordEntry::encrypt() const {
  // Test!
  std::string encrypted = password;
  std::reverse(encrypted.begin(), encrypted.end());
  return encrypted;
}
