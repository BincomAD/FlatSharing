//
// Created by ero on 5/14/23.
//


#include <random>
#include "AuthHelper.h"


bool AuthHelper::registerUser(std::string login, std::string name, std::string password, std::string phoneNumber,
                              std::string mail) {
    if (checkIfLoginExists(login)) {
        return false;
    }

    size_t userId = _dbHelper.getUserId();
    std::unique_ptr<User> userItem = std::make_unique<User>(userId, login, name, password, phoneNumber, mail);

    _dbHelper.saveUser(std::move(userItem));

    return true;
}

bool AuthHelper::checkIfLoginExists(std::string login) {
    bool wasFound {false};
    _dbHelper.getUser(login, &wasFound);
    return wasFound;
}

std::string AuthHelper::generateToken(int length) {
    std::string token;

    std::random_device rd;
    std::mt19937 generator(rd());

    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    std::uniform_int_distribution<int> distribution(0, charset.size() - 1);
    auto randChar = [&distribution, &generator]() {
        return distribution(generator);
    };

    for (int i = 0; i < length; ++i) {
        token += charset[randChar()];
    }

    return token;
}