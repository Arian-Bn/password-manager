#pragma once
#include "Secret.hpp"
#include <string>

class CreditCardEntry : public Secret {
private:
  std::string numberCard;
  std::string cardHolderName;
  std::string expiryDate;
  std::string cvv;

public:
  CreditCardEntry(std::string numberCard, std::string cardHolderName,
                  std::string expiryDate, std::string cvv)
      : numberCard(numberCard), cardHolderName(cardHolderName),
        expiryDate(expiryDate), cvv(cvv) {}
  virtual std::string encrypt() const override;
  std::string getNumberCard() const { return numberCard; }
  std::string getCardHolderName() const { return cardHolderName; }
  std::string getExpiryDate() const { return expiryDate; }
  std::string getCvv() const { return cvv; }
};
