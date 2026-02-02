#include "../include/entry.hpp"
#include "../include/note_entry.hpp"
#include "../include/password_entry.hpp"
#include <iostream>
#include <memory>
#include <vector>

int main() {
  std::cout << "=== Testing PasswordEntry and NoteEntry ===\n" << std::endl;

  // Test 1: Create instances of both entry types
  PasswordEntry password("Gmail", "gmail.com", "user", "secret123");
  NoteEntry note("Shoping List", "Milk, Eggs, Bread");

  std::cout << "\n=== Direct calls ===" << std::endl;
  password.display();
  std::cout << std::endl;
  note.display();

  // Test 2: Demonstrate polymorphism
  // Store different entry types in a single vector using base class pointers
  std::cout << "\n=== Polymorphism test ===" << std::endl;
  std::vector<std::unique_ptr<Entry>> entries;

  // Add PasswordEntry to vector (as Entry pointer)
  entries.push_back(std::make_unique<PasswordEntry>("GitHub", "github.com",
                                                    "dev", "github_pass"));

  // Add NoteEntry to same vector (as Entry pointer)
  entries.push_back(
      std::make_unique<NoteEntry>("Ideas", "Add encryption, database, GUI"));

  // Add another PasswordEntry
  entries.push_back(std::make_unique<PasswordEntry>("Netflix", "netflix.com",
                                                    "family_user", "movie123"));

  for (const auto &entry : entries) {
    entry->display();
    std::cout << std::endl;
  }

  // Test 3: Verify getters and setters work correctly

  std::cout << "\n=== Getters/Setters test ===" << std::endl;
  PasswordEntry testPass("Test", "test.com", "old", "pass");
  std::cout << "Original website: " << testPass.getWebsite() << std::endl;
  testPass.setWebsite("new-website.com");
  std::cout << "Updated website: " << testPass.getWebsite() << std::endl;

  return 0;
}
