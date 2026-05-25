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
  bool result = db->addNoteEntry("Test Title", "Test Content", "Test Category");
  EXPECT_TRUE(result);

  auto entries = db->getAllEntries();
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries[0]), "Test Title");
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
