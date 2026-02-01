#pragma once
#include "entry.hpp"
#include <string>

class PasswordEntry : public Entry {
public:
  PasswordEntry(const std::string &title, const std::string &website,
                const std::string &username, const std::string &password);

  void display() const override;

  std::string getWebsite() const;
  std::string getUsername() const;

  void setWebsite(const std::string &website);
  void setUsername(const std::string &username);

private:
  std::string website_;
  std::string username_;
  std::string password_;
};
