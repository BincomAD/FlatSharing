//
// Created by nikita on 16.04.23.
//
#include "IndexPage.h"

http::response<http::string_body>
IndexPage::getResponse() {
    http::response<http::string_body> response;
    response.result(http::status::ok);
    response.body() = "Hello, World!!!";
    response.set(http::field::content_type, "text/plain");
    return response;
}

IndexPage::IndexPage(const std::shared_ptr<http::request<http::string_body>> &request) {
    _request = request;
}