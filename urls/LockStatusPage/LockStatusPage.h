//
// Created by nikita on 18.05.23.
//

#ifndef BACKEND_CPP_LOCKSTATUSPAGE_H
#define BACKEND_CPP_LOCKSTATUSPAGE_H


#include "../AbstractPage.h"

class LockStatusPage : public AbstractPage {
public:

    explicit LockStatusPage(const std::shared_ptr<http::request<http::string_body>> &request);

    http::response<http::string_body> getResponse() override;
};


#endif //BACKEND_CPP_LOCKSTATUSPAGE_H
