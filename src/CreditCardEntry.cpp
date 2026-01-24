#include "../include/CreditCardEntry.hpp"
#include <algorithm>

std::string CreditCardEntry::encrypt() const {
  // Test!
  std::string result = numberCard;
  std::reverse(result.begin(), result.end());
  return result;
}
