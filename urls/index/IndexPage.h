//
// Created by nikita on 16.04.23.
//

#ifndef BACKEND_CPP_INDEXPAGE_H
#define BACKEND_CPP_INDEXPAGE_H

#include "../AbstractPage.h"

class IndexPage : public AbstractPage {
private:
    std::shared_ptr<http::request<http::string_body>> _request;

public:

    explicit IndexPage(const std::shared_ptr<http::request<http::string_body>> &request);

    http::response<http::string_body> getResponse() override;

};


#endif //BACKEND_CPP_INDEXPAGE_H
