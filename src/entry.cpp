#include "../include/entry.hpp"
#include "../include/note_entry.hpp"
#include "../include/password_entry.hpp"
#include <iostream>
#include <sstream>

Entry::Entry(const std::string &title)
    : title_(title), created_time_("2026-02-01 00:00:00") {
  std::cout << "Entry created: " << title_ << std::endl;
}

std::string Entry::getTitle() const { return title_; }

void Entry::setTitle(const std::string &new_title) { title_ = new_title; }

void Entry::printBasicInfo() const {
  std::cout << "Title: " << title_ << "\nCreated: " << created_time_
            << std::endl;
}

std::string Entry::getCurrentTimestamp() const { return "2026-02-07 00:00:00"; }

std::unique_ptr<Entry> Entry::deserialize(const std::string &data) {
  std::istringstream iss(data);
  std::string type;
  std::getline(iss, type, '|');

  if (type == "password") {
    std::string title, website, username, password;
    std::getline(iss, title, '|');
    std::getline(iss, website, '|');
    std::getline(iss, username, '|');
    std::getline(iss, password);

    return std::make_unique<PasswordEntry>(title, website, username, password);
  } else if (type == "note") {
    std::string title, content;
    std::getline(iss, title, '|');
    std::getline(iss, content);

    return std::make_unique<NoteEntry>(title, content);
  }

  return nullptr;
}
