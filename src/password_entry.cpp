#include "../include/password_entry.hpp"
#include <iostream>

PasswordEntry::PasswordEntry(const std::string &title,
                             const std::string &website,
                             const std::string &username,
                             const std::string &password)
    : Entry(title), website_(website), username_(username),
      password_(password) {
  std::cout << "PasswordEntry created: " << title << std::endl;
}

void PasswordEntry::display() const {
  printBasicInfo();

  std::cout << "Type: Password" << std::endl;
  std::cout << "Website: " << website_ << std::endl;
  std::cout << "Username: " << username_ << std::endl;
  std::cout << "Password: " << password_ << std::endl;
}

std::string PasswordEntry::getWebsite() const { return website_; }

std::string PasswordEntry::getUsername() const { return username_; }

void PasswordEntry::setWebsite(const std::string &website) {
  website_ = website;
}

void PasswordEntry::setUsername(const std::string &username) {
  username_ = username;
}

std::string PasswordEntry::serialize() const {
  return "password|" + title_ + "|" + website_ + "|" + username_ + "|" +
         password_;
}
