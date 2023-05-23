//
// Created by nikita on 21.05.23.
//

#include "LoginPage.h"
#include "../../DBHelper/DBHelper.h"

#define ERROR_USER_NOT_FOUND "Wrong login or password"

LoginPage::LoginPage(const std::shared_ptr<http::request<http::string_body>> &request) {
    _params = parsePostRequest(request);
}

http::response<http::string_body> LoginPage::getResponse() {
    std::string login, password;
    if (_params.count("login") &&
        _params.count("password")) {
        // Все ключи присутствуют
        login = _params.at("login");
        password = _params.at("password");
    } else{
        std::string errorText = "Missing parameters: ";
        std::unique_ptr<std::vector<std::string>> reqParams = std::make_unique<std::vector<std::string>>();
        reqParams->push_back("login");
        reqParams->push_back("password");
        auto mParams = getMissingParams(std::move(reqParams));
        for (auto i = mParams.begin(); i != mParams.end(); ++i) {
            errorText.append((*i));
            errorText.append(", ");
        }
        return getErrorResponse(errorText, http::status::bad_request);
    }

    DBHelper dbHelper;
    auto jsonTree {dbHelper.getUserTokens(login, password)};
    if(jsonTree.empty()){
        return getErrorResponse(ERROR_USER_NOT_FOUND, http::status::forbidden);
    }
    std::ostringstream oss;
    boost::property_tree::write_json(oss, jsonTree);
    std::string jsonResponse {oss.str()};

    http::response<http::string_body> res;
    res.result(http::status::ok);
    res.set(http::field::content_type, "application/json");
    res.body() = jsonResponse;
    return res;
}
