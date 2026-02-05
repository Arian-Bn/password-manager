#include "../include/vault.hpp"
#include <iostream>
#include <limits>
#include <string>

void printMenu() {
  std::cout << "\n=== PASSWORD MANAGER ===\n";
  std::cout << "1. Add Password Entry\n";
  std::cout << "2. Add Note Entry\n";
  std::cout << "3. View All Entries\n";
  std::cout << "4. Search by Title\n";
  std::cout << "5. Clear All Entries\n";
  std::cout << "6. Show Entry Count\n";
  std::cout << "0. Exit\n";
  std::cout << "Chois: ";
}

void ClearInputBuffer() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
  Vault vault;
  int choice = -1;

  std::cout << "Welcome to Password Manager!\n";

  while (choice != 0) {
    printMenu();
    std::cin >> choice;
    ClearInputBuffer();

    switch (choice) {
    case 1: { // Add Password
      std::string title, website, username, password;

      std::cout << "Title: ";
      std::getline(std::cin, title);

      std::cout << "Website: ";
      std::getline(std::cin, website);

      std::cout << "Username: ";
      std::getline(std::cin, username);

      std::cout << "Password: ";
      std::getline(std::cin, password);

      vault.addPasswordEntry(title, website, username, password);
      break;
    }

    case 2: { // Add Note
      std::string title, content;

      std::cout << "Title: ";
      std::getline(std::cin, title);

      std::cout << "Content: ";
      std::getline(std::cin, content);

      vault.addNoteEntry(title, content);
      break;
    }

    case 3: { // View All
      vault.displayAll();
      break;
    }

    case 4: { // Search
      std::string searchTerm;

      std::cout << "Search term: ";
      std::getline(std::cin, searchTerm);

      vault.findByTitle(searchTerm);
      break;
    }

    case 5: // Clear All
      vault.clear();
      break;

    case 6: // Count
      std::cout << "Total entries: " << vault.getEntryCount() << std::endl;
      break;

    case 0: // Exit
      std::cout << "Goodbye!\n";
      break;

    default:
      std::cout << "Invalid choice. Tye again.\n";
    }
  }

  return 0;
}
