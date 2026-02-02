#pragma once
#include "entry.hpp"
#include <string>

class NoteEntry : public Entry {
public:
  NoteEntry(const std::string &title, const std::string &content_);

  void display() const override;

  std::string getContent() const;

  void setContent(const std::string &content);

private:
  std::string content_;
};
