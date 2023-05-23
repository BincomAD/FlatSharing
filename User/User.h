//
// Created by ero on 4/16/23.
//

#ifndef BACKEND_CPP_USER_H
#define BACKEND_CPP_USER_H

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class User {
public:
    User(size_t id, const std::string &login, const std::string &name, const std::string &mail);

    User(size_t id, std::string login, std::string name, std::string password, std::string phoneNumber, std::string mail);
    boost::property_tree::ptree getJson() const;
    boost::property_tree::ptree getSafeJson() const;
    void setAccess(std::string token);
    std::string getLogin() const;
private:
    size_t _id;
    std::string _login, _name, _password, _phoneNumber, _mail, _accessToken;

    std::vector<std::string> flatsHands();
    std::vector<std::string> flatsRent();
    std::string getAccess();

public:
    size_t getId() const;
};

#endif //BACKEND_CPP_USER_H
