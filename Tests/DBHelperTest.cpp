#include <gtest/gtest.h>
#include <pqxx/pqxx>
#include <memory>
#include <string>
#include <vector>
#include "../DBHelper/DBHelper.h"
#include "../Flat/Flat.h"
#include "../SmartLock/SmartLock.h"
#include "../User/User.h"

TEST(DBHelperTest, GetFlatTest) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);
  std::unique_ptr<FLat> flatItem = std::make_unique<FLat>(1000, 50, db_helper.getFlatId(), 5, "Test Address", "Test Description");
  db_helper.saveFlat(std::move(flatItem));

  std::unique_ptr<FLat> flatItemNew = std::make_unique<FLat>(1000, 50, db_helper.getFlatId()-1, 5, "Test Address", "Test Description");
  // Act
  FLat resultFlat = db_helper.getFlat(db_helper.getFlatId()-1);

  boost::property_tree::ptree actualJson = resultFlat.getJson();
  EXPECT_EQ(flatItemNew->getJson(), actualJson);
}

TEST(DBHelperTest, FlatUpdate) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);
  std::unique_ptr<FLat> flatItem = std::make_unique<FLat>(1000, 50, 1112, 5, "Test Address", "Test Description");
  db_helper.saveFlat(std::move(flatItem));
  size_t index = db_helper.getFlatId() - 1;

  std::unique_ptr<FLat> flatItemUp = std::make_unique<FLat>(3000, 50, 1112, 5, "Test Address", "Test Description");
  db_helper.updateFlat(index, std::move(flatItemUp));

  std::unique_ptr<FLat> flatItemUpNew = std::make_unique<FLat>(3000, 50, index, 5, "Test Address", "Test Description");
  // Act
  FLat resultFlat = db_helper.getFlat(index);

  boost::property_tree::ptree actualJson = resultFlat.getJson();
  EXPECT_EQ(flatItemUpNew->getJson(), actualJson);
}

TEST(DBHelperTest, GetFlatsListTest) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);
  std::vector<std::unique_ptr<FLat>> result;
  std::vector<std::unique_ptr<FLat>> flatItems;
  size_t index = db_helper.getFlatId();
  for (int i = 1; i <= 10; ++i) {
    std::unique_ptr<FLat> flatItem = std::make_unique<FLat>(i * 1000, index+i-1, index+i-1, 5, "Test Address " + std::to_string(i), "Test Description " + std::to_string(i));
    flatItems.push_back(std::make_unique<FLat>(*flatItem));  // Создаем новый уникальный указатель
    result.push_back(std::make_unique<FLat>(*flatItem));     // Создаем новый уникальный указатель
  }


  for (auto& flatItem : flatItems) {
    db_helper.saveFlat(std::move(flatItem));
  }

  // Act
  std::vector<FLat> resultFlats = db_helper.getFlatsList(index, 5);

  // Assert
  EXPECT_EQ(resultFlats.size(), 5);
  for (int i = index; i < index + 5; ++i) {
    EXPECT_EQ(resultFlats[i - index].getJson(), result[i - index]->getJson());
  }
}

TEST(DBHelperTest, GetLock) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);

  // Add a SmartLock to the database
  std::unique_ptr<SmartLock> lockItem = std::make_unique<SmartLock>(db_helper.getLockId(), 14, false);
  db_helper.saveLock(std::move(lockItem));

  // Act
  SmartLock retrievedLock = db_helper.getLock(db_helper.getLockId()-1);
  // Assert
  EXPECT_EQ(retrievedLock.is_open(), false);
}

TEST(DBHelperTest, updateLock) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);

  // Add a SmartLock to the database
  std::unique_ptr<SmartLock> lockItem = std::make_unique<SmartLock>(db_helper.getLockId(), 14, false);
  std::unique_ptr<SmartLock> lockItemUp = std::make_unique<SmartLock>(db_helper.getLockId(), 14, false);
  db_helper.saveLock(std::move(lockItem));
  db_helper.updateLock(db_helper.getLockId()-1, std::move(lockItemUp));
  // Act
  SmartLock retrievedLock = db_helper.getLock(db_helper.getLockId()-1);



  std::unique_ptr<SmartLock> lockItemUpN = std::make_unique<SmartLock>(db_helper.getLockId(), 14, false);
  // Assert
  EXPECT_EQ(retrievedLock.is_open(), lockItemUpN->is_open());
}

TEST(DBHelperTest, GetUser) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);

  // Add a User to the database
  std::unique_ptr<User> userItem = std::make_unique<User>(db_helper.getUserId(), "John", "Doe", "zxc123", "123456789", "johndoe@mail.ru");
  db_helper.saveUser(std::move(userItem));
  std::unique_ptr<User> userItemUp = std::make_unique<User>(db_helper.getUserId()-1, "John", "Doe", "zxc123", "123456789", "johndoe@mail.ru");
  // Act
  User retrievedUser = db_helper.getUser(db_helper.getUserId()-1);
  // Assert
  EXPECT_EQ(retrievedUser.getJson(), userItemUp->getJson());
}

TEST(DBHelperTest, UpdateUser) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);

  // Add a User to the database
  std::unique_ptr<User> userItem = std::make_unique<User>(db_helper.getUserId(), "John", "Doe", "zxc123", "123456789", "johndoe@mail.ru");
  db_helper.saveUser(std::move(userItem));

  //Update User
  std::unique_ptr<User> userItemUp = std::make_unique<User>(db_helper.getUserId()-1, "Sasha", "Qwe", "zxc123", "123456789", "johndoe@mail.ru");
  db_helper.updateUser(db_helper.getUserId()-1, std::move(userItemUp));
  // Act
    
  std::unique_ptr<User> userItemUpN = std::make_unique<User>(db_helper.getUserId()-1, "Sasha", "Qwe", "zxc123", "123456789", "johndoe@mail.ru");
  User retrievedUser = db_helper.getUser(db_helper.getUserId()-1);
  // Assert
  EXPECT_EQ(retrievedUser.getJson(), userItemUpN->getJson());
}

TEST(DBHelperTest, AccessTokken) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);

  // Add a User to the database
  std::unique_ptr<User> userItem = std::make_unique<User>(4, "John", "Doe", "zxc123", "123456789", "johndoe@mail.ru");
  db_helper.saveUser(std::move(userItem));
    
  db_helper.setAccess(db_helper.getUserId()-1, "321");
  bool result = db_helper.checkAccess(db_helper.getUserId()-1, "321");
  
  // Assert
  EXPECT_EQ(result, true);
}




