//
// Created by ero on 4/16/23.
//

#ifndef BACKEND_CPP_USER_H
#define BACKEND_CPP_USER_H

#include <string>
#include <vector>


class User {

private:
    size_t _id;
    std::string _nameUser, _secondName, _phoneNumber, _mail;

    std::vector<std::string> flatsHands();
    std::vector<std::string> flatsRent();

};

#endif //BACKEND_CPP_USER_H
