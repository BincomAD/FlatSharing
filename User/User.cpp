//
// Created by ero on 4/16/23.
//
#include "User.h"

User::User(size_t id, std::string login, std::string name, std::string password, std::string phoneNumber, std::string mail)
        :_id(id), _login(login), _name(name), _password(password), _phoneNumber(phoneNumber), _mail(mail) {};

boost::property_tree::ptree User::getJson() const {
    boost::property_tree::ptree user;

    user.put("id", _id);
    user.put("login", _login);
    user.put("password", _password);
    user.put("name", _name);
    user.put("number", _phoneNumber);
    user.put("email", _mail);

    return user;
}

void User::setAccess(std::string token) {
	_accessToken = token;
}

std::string User::getAccess() {
	return _accessToken;
}


std::string User::getLogin() const {
    return _login;
}

size_t User::getId() const {
    return _id;
}

User::User(size_t id, const std::string &login, const std::string &name, const std::string &mail) : _id(id),
                                                                                                    _login(login),
                                                                                                    _name(name),
                                                                                                    _mail(mail) {}

boost::property_tree::ptree User::getSafeJson() const {
    boost::property_tree::ptree user;

    user.put("id", _id);
    user.put("login", _login);
    user.put("name", _name);
    user.put("email", _mail);

    return user;
}
