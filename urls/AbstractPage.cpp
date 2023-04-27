//
// Created by nikita on 16.04.23.
//

#include "AbstractPage.h"

std::unordered_map<std::string, std::string>
AbstractPage::parseGetRequest(std::shared_ptr<http::request<http::string_body>> request) {
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
