//
// Created by nikita on 18.05.23.
//

#include "RegistrationPage.h"
#include "../../Auth/AuthHelper.h"

#define DEFAULT_TOKEN_SIZE 255
#define USER_EXISTS "Auth failed. User with this login already exists"

//getErrorResponse(LOGIN_IS_MISSING, http::status::bad_request);
http::response<http::string_body> RegistrationPage::getResponse() {
    std::string login, name, password, phoneNumber, mail;
    if (_params.count("login") && _params.count("name") &&
        _params.count("password") && _params.count("phoneNumber") &&
        _params.count("email")) {
        // Все ключи присутствуют
        login = _params.at("login");
        name = _params.at("name");
        password = _params.at("password");
        phoneNumber = _params.at("phoneNumber");
        mail = _params.at("email");
    } else{
        std::string errorText = "Missing parameters: ";
        std::unique_ptr<std::vector<std::string>> reqParams = std::make_unique<std::vector<std::string>>();
        reqParams->push_back("login");
        reqParams->push_back("name");
        reqParams->push_back("password");
        reqParams->push_back("phoneNumber");
        reqParams->push_back("email");
        auto mParams = getMissingParams(std::move(reqParams));
        for (auto i = mParams.begin(); i != mParams.end(); ++i) {
            errorText.append((*i));
            errorText.append(", ");
        }
        return getErrorResponse(errorText, http::status::bad_request);
    }

    DBHelper dbHelper;
    AuthHelper authHelper(dbHelper);

    boost::beast::http::response<http::string_body> res;

    if (authHelper.registerUser(login, name, password, phoneNumber, mail)) {
        // Auth successful
        bool wasAdded {false};
        auto uId {dbHelper.getUser(login, &wasAdded).getId()};
        dbHelper.setRefresh(uId,
                            authHelper.generateToken(DEFAULT_TOKEN_SIZE));
        dbHelper.setAccess(uId, authHelper.generateToken(DEFAULT_TOKEN_SIZE));

        //return tokens
        auto jsonTree {dbHelper.getUserTokens(login, password)};

        std::ostringstream oss;
        boost::property_tree::write_json(oss, jsonTree);
        std::string jsonResponse {oss.str()};

        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = jsonResponse;
    } else {
        // Auth failed
        return getErrorResponse(USER_EXISTS, http::status::bad_request);
    }

    return res;
}

RegistrationPage::RegistrationPage(const std::shared_ptr<http::request<http::string_body>> &request) {
    _params = parsePostRequest(request);
}


