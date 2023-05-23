//
// Created by nikita on 18.05.23.
//

#ifndef BACKEND_CPP_REGISTRATIONPAGE_H
#define BACKEND_CPP_REGISTRATIONPAGE_H


#include "../AbstractPage.h"

class RegistrationPage : public AbstractPage {
public:
    http::response<http::string_body> getResponse() override;

    RegistrationPage(const std::shared_ptr<http::request<http::string_body>> &request);
};


#endif //BACKEND_CPP_REGISTRATIONPAGE_H
