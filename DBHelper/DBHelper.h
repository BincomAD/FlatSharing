//
// Update by SashaD on 16.04.23.
//

#ifndef BACKEND_CPP_DBHELPER_H
#define BACKEND_CPP_DBHELPER_H
#include <vector>
#include <memory>
#include "../Flat/Flat.h"
#include "../SmartLock/SmartLock.h"
#include "../User/User.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iostream>
#include <pqxx/pqxx>

#define HOST "localhost"
#define PORT "5432"
#define DBNAME "FlatSharingDB"
#define USER "flat"
#define PASSWORD "123"

class DBHelper {
 private:
  pqxx::connection* _connection;

 public:
  DBHelper(std::string host = HOST, std::string port = PORT, std::string dbname = DBNAME,
           std::string user = USER, std::string password = PASSWORD);

  ~DBHelper();

  void saveFlat(std::unique_ptr<FLat> flatItem);
  void updateFlat(size_t flatId, std::unique_ptr<FLat> flatItemUp);
  FLat getFlat(size_t flatId, bool* wasFound);
  void removeFlat(size_t flatId);
  std::vector<FLat> getFlatsList(size_t offset, size_t amount);
  void saveLock(std::unique_ptr<SmartLock> lockItem);
  void removeLock(size_t lockId); 
  SmartLock getLock(size_t lockId, bool* wasFound);
  void updateLock(size_t lockId, std::unique_ptr<SmartLock> slItem);
  User getUser(size_t userId);
  User getUser(std::string userLogin, bool* wasFound);
  void saveUser(std::unique_ptr<User> userItem);
  void removeUser(size_t userId);
  void updateUser(size_t userId, std::unique_ptr<User> userItemUp);
  void setAccess(size_t userId, std::string token);
  bool checkAccess(size_t userId, std::string token);
  bool checkRefresh(size_t userId, std::string token);
  void setRefresh(size_t userId, std::string token);
  boost::property_tree::ptree getUserTokens(const std::string& login, const std::string& password);
  bool checkFlatAvailability(int flatId, const std::string& startDate, const std::string& endDate);
  void rentAFlat(int flatId, int clientId, const std::string& beginDate, const std::string& endDate);

  size_t getFlatId();
  size_t getLockId();
  size_t getUserId();
  
};

#endif  // BACKEND_CPP_DBHELPER_H
