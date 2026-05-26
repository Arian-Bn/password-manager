#include "../include/database_manager.hpp"
#include <gtest/gtest.h>

class DatabaseTest : public ::testing::Test {
protected:
  void SetUp() override {
    db = std::make_unique<DatabaseManager>("test.db");
    db->initialize();
  }

  void TearDown() override {
    db.reset();
    std::remove("test.db");
  }

  std::unique_ptr<DatabaseManager> db;
};

TEST_F(DatabaseTest, AddNote) {
  bool results =
      db->addNoteEntry("Test Title", "Test Content", "Test Category");
  EXPECT_TRUE(results);

  auto entries = db->getAllEntries();
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries[0]), "Test Title");
}

TEST_F(DatabaseTest, DeleteNote) {
  db->addNoteEntry("To Delete", "Content", "Cat");

  auto before = db->getAllEntries();
  ASSERT_EQ(before.size(), 1);

  int id = std::get<0>(before[0]);
  bool results = db->deleteEntry(id);
  EXPECT_TRUE(results);

  auto after = db->getAllEntries();
  EXPECT_EQ(after.size(), 0);
}

TEST_F(DatabaseTest, SearchByTitle) {
  db->addNoteEntry("Apple", "Content1", "Fruit");
  db->addNoteEntry("Banana", "Content2", "Fruit");

  auto results = db->getEntriesFiltered("App", "");

  EXPECT_EQ(results.size(), 1);
  EXPECT_EQ(std::get<1>(results[0]), "Apple");
}

TEST_F(DatabaseTest, FilterByCategory) {
  db->addNoteEntry("Note 1", "Content1", "Work");
  db->addNoteEntry("Note 2", "Content2", "Personal");
  db->addNoteEntry("Note 3", "Content3", "Work");

  auto results = db->getEntriesFiltered("", "Work");
  EXPECT_EQ(results.size(), 2);

  for (const auto &entry : results) {
    int id = std::get<0>(entry);
    auto note = db->getNoteEntry(id);
    EXPECT_EQ(std::get<3>(note), "Work");
  }
}

TEST_F(DatabaseTest, UpdateNote) {
  db->addNoteEntry("Old Title", "Old Cotent", "Old Cat");

  auto entries = db->getAllEntries();
  ASSERT_EQ(entries.size(), 1);
  int id = std::get<0>(entries[0]);

  bool results = db->updateNoteEntry(id, "New Title", "New Content", "New Cat");
  EXPECT_TRUE(results);

  auto note = db->getNoteEntry(id);
  EXPECT_EQ(std::get<1>(note), "New Title");
  EXPECT_EQ(std::get<2>(note), "New Content");
  EXPECT_EQ(std::get<3>(note), "New Cat");
}

TEST_F(DatabaseTest, EmptyTitleFields) {
  bool results = db->addNoteEntry("", "Content", "Cat");
  EXPECT_FALSE(results);

  auto entries = db->getAllEntries();
  EXPECT_EQ(entries.size(), 0);
}

TEST_F(DatabaseTest, EmptyContentIsAllowed) {
  bool results = db->addNoteEntry("Title", "", "Cat");
  EXPECT_TRUE(results);

  auto entries = db->getAllEntries();
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries[0]), "Title");
}

TEST_F(DatabaseTest, VeryLongTitle) {
  std::string longTitle(1000, 'A');
  bool results = db->addNoteEntry(longTitle, "Content", "Cat");
  EXPECT_TRUE(results);

  auto entries = db->getAllEntries();
  EXPECT_EQ(entries.size(), 1);
}

TEST_F(DatabaseTest, SpecialCharacters) {
  bool results =
      db->addNoteEntry("Hello @#$%^&*())", "Content with <>&\"\'", "Cat");
  EXPECT_TRUE(results);

  auto entries = db->getAllEntries();
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries[0]), "Hello @#$%^&*())");
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
