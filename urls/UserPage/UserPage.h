//
// Created by nikita on 22.05.23.
//

#ifndef BACKEND_CPP_USERPAGE_H
#define BACKEND_CPP_USERPAGE_H


#include "../AbstractPage.h"

class UserPage : public AbstractPage{
public:
    UserPage(const std::shared_ptr<http::request<http::string_body>> &request);
    http::response<http::string_body> getResponse() override;
};


#endif //BACKEND_CPP_USERPAGE_H
