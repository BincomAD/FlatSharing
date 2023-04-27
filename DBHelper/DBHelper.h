//
// Update by SashaD on 16.04.23.
//

#ifndef BACKEND_CPP_DBHELPER_H
#define BACKEND_CPP_DBHELPER_H
#include <vector>
#include <memory>
#include "../Flat/Flat.h"
#include "../SmartLock/SmartLock.h"
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
s
class DBHelper {
 private:
  pqxx::connection* _connection;

 public:
  DBHelper(std::string host, std::string port, std::string dbname,
           std::string user, std::string password);

  ~DBHelper();

  void saveFlat(std::shared_ptr<FLat> flatItem);
  FLat getFlat(size_t flatId);
  std::vector<FLat> getFlatsList(size_t offset, size_t amount);
  SmartLock getLock(size_t lockId);
  void updateLock(std::shared_ptr<SmartLock> slItem);
};

#endif  // BACKEND_CPP_DBHELPER_H
