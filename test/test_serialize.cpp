#include "../include/entry.hpp"
#include "../include/note_entry.hpp"
#include "../include/password_entry.hpp"
#include <iostream>

int main() {
  // Test PasswordEntry
  PasswordEntry pass("Email", "gmail.com", "user", "pass123");
  std::string pass_str = pass.serialize();
  std::cout << "Serialized PasswordEntry: " << pass_str << std::endl;

  auto pass2 = Entry::deserialize(pass_str);
  if (pass2) {
    std::cout << "Deserialized successfully!" << std::endl;
    pass2->display();
  }

  NoteEntry note("Shopping", "Milk, Eggs");
  std::string note_string = note.serialize();
  std::cout << "Serialized NoteEntry: " << note_string << std::endl;

  auto note2 = Entry::deserialize(note_string);
  if (note2) {
    std::cout << "Deserialized successfully: " << std::endl;
    note2->display();
  }
  return 0;
}
