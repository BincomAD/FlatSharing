//
// Created by nikita on 16.04.23.
//

#include "AbstractPage.h"

std::unordered_map<std::string, std::string>
AbstractPage::parseGetRequest(const std::shared_ptr<http::request<http::string_body>> request) {
    std::unordered_map<std::string, std::string> map;
    std::string uri{request->target()};
    std::string var, val;

    size_t startVariablePos{0};
    startVariablePos = uri.find_first_of('?');
    while (startVariablePos != std::string::npos) {
        startVariablePos++; //to skip '?'
        var = uri.substr(startVariablePos, uri.find_first_of("=", startVariablePos) - startVariablePos);
        size_t startValuePos{uri.find_first_of('=', startVariablePos) + 1};
        val = uri.substr(startValuePos, uri.find_first_of("&", startValuePos) - startValuePos);

        map.insert(std::make_pair(var, val));
        startVariablePos = uri.find_first_of('&', startVariablePos);
    }

    return map;
}

http::response<http::string_body> AbstractPage::getErrorResponse(const std::string& text, http::status status) {
    boost::beast::http::response<http::string_body> res {status, 11};
    res.body() = text;
    return res;
}

std::unordered_map<std::string, std::string>
AbstractPage::parsePostRequest(const std::shared_ptr<http::request<http::string_body>> request) {
    std::unordered_map<std::string, std::string> postParams;

    std::istringstream ss(request->body());
    std::string param;
    while (std::getline(ss, param, '&')) {
        std::size_t pos = param.find('=');
        if (pos != std::string::npos) {
            std::string key = param.substr(0, pos);
            std::string value = param.substr(pos + 1);
            postParams[key] = value;
        }
    }

    return postParams;
}

std::vector<std::string> AbstractPage::getMissingParams(std::unique_ptr<std::vector<std::string>> requiredParams) {

//    std::vector<std::string> requiredParams = {"login", "password"};
    std::vector<std::string> missingParams;

    for (const auto& param : (*requiredParams)) {
        if (_params.find(param) == _params.end()) {
            missingParams.push_back(param);
        }
    }

    return missingParams;
}
