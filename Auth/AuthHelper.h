//
// Created by ero on 5/14/23.
//

#ifndef BACKEND_CPP_AUTHHELPER_H
#define BACKEND_CPP_AUTHHELPER_H

#include <vector>
#include <memory>
#include "../DBHelper/DBHelper.h"
#include "../User/User.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iostream>
#include <pqxx/pqxx>

class AuthHelper {
private:
    DBHelper& _dbHelper;

    bool checkIfLoginExists(std::string login);

public:
    AuthHelper(DBHelper& dbHelper) : _dbHelper(dbHelper) {}

    bool registerUser(std::string login, std::string name, std::string password, std::string phoneNumber, std::string mail);

    std::string generateToken(int length);
};

#endif //BACKEND_CPP_AUTHHELPER_H
