#include "../include/entry.hpp"
#include <iostream>

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
