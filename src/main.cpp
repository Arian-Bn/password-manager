#include "../include/CreditCardEntry.hpp"
#include "../include/PasswordEntry.hpp"
#include <iostream>

int main() {
  // 1. СОЗДАНИЕ объектов
  PasswordEntry password("GitHub", "myLogin", "myPassword123");
  CreditCardEntry card("4111111111111111", "IVAN IVANOV", "12/25", "123");

  // 2. ТЕСТИРОВАНИЕ методов
  std::cout << "Password encrypted: " << password.encrypt() << std::endl;
  std::cout << "Card encrypted: " << card.encrypt() << std::endl;

  // 3. Проверка геттеров (опционально)
  std::cout << "\nCard holder: " << card.getCardHolderName() << std::endl;
  std::cout << "Service: " << password.getService() << std::endl;

  return 0;
}
