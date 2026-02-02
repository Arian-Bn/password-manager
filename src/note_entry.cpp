#include "../include/note_entry.hpp"
#include <iostream>

NoteEntry::NoteEntry(const std::string &title, const std::string &content)
    : Entry(title), content_(content) {
  std::cout << "NoteEntry created: " << title << std::endl;
}

void NoteEntry::display() const {
  Entry::printBasicInfo();
  std::cout << "Type: Note" << std::endl;
  std::cout << "Content: " << content_ << std::endl;
}

std::string NoteEntry::getContent() const { return content_; }

void NoteEntry::setContent(const std::string &content) { content_ = content; }
