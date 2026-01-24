#pragma once ////////////////
#include "Secret.hpp"
#include <string>

class PasswordEntry : public Secret {
private:
  std::string service;
  std::string login;
  std::string password;

public:
  PasswordEntry(std::string service, std::string login, std::string password)
      : service(service), login(login), password(password) {}
  virtual std::string encrypt() const override;

  std::string getService() const { return service; }

  std::string getLogin() const { return login; }

  std::string getPassword() const { return password; }
};
