//
// Created by nikita on 16.04.23.
//

#ifndef BACKEND_CPP_ABSTRACTPAGE_H
#define BACKEND_CPP_ABSTRACTPAGE_H

#include <boost/beast/core.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/string_body.hpp>

using namespace boost::beast;

class AbstractPage{
protected:
    std::unordered_map<std::string, std::string> _params;
    std::unordered_map<std::string, std::string> parseGetRequest(const std::shared_ptr<http::request<http::string_body>> request);
    std::unordered_map<std::string, std::string> parsePostRequest(const std::shared_ptr<http::request<http::string_body>> request);
public:

    //don`t forget to set status, content_type, and body.
    virtual http::response<http::string_body> getResponse() = 0;

    http::response<http::string_body> getErrorResponse(const std::string& text, http::status status);

    std::vector<std::string> getMissingParams(std::unique_ptr<std::vector<std::string>> requiredParams);
};


#endif //BACKEND_CPP_ABSTRACTPAGE_H
