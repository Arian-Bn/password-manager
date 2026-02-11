#pragma once
#include <memory>
#include <string>

// Abstract base class for all entry types (passwords, notes, etc.)
class Entry {
public:
  Entry(const std::string &title);

  // Virtual destructor for pplymorphic deletion
  virtual ~Entry() = default;

  // Pure virtual - each entry type implements its own display
  virtual void display() const = 0;

  std::string getTitle() const;

  void setTitle(const std::string &new_title);

  void printBasicInfo() const;

  virtual std::string serialize() const = 0;

  static std::unique_ptr<Entry> deserialize(const std::string &data);

protected:
  std::string title_;
  std::string created_time_;

private:
  // Helper: returns current timestamp as string
  std::string getCurrentTimestamp() const;
};
