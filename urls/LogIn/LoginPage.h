//
// Created by nikita on 21.05.23.
//

#ifndef BACKEND_CPP_LOGINPAGE_H
#define BACKEND_CPP_LOGINPAGE_H


#include "../AbstractPage.h"

class LoginPage : public AbstractPage {
private:
public:
    LoginPage(const std::shared_ptr<http::request<http::string_body>> &request);

    http::response<http::string_body> getResponse() override;
};


#endif //BACKEND_CPP_LOGINPAGE_H
