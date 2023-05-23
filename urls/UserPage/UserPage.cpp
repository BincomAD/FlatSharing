//
// Created by nikita on 22.05.23.
//

#include "UserPage.h"
#include "../../DBHelper/DBHelper.h"

#define USER_NOT_FOUND "User with this login was not found"

UserPage::UserPage(const std::shared_ptr<http::request<http::string_body>> &request) {
    _params = parseGetRequest(request);
}

http::response<http::string_body> UserPage::getResponse() {
    std::string login;
    if (_params.count("login")){
        login = _params.at("login");
    } else{
        std::string errorText = "Missing login";
        return getErrorResponse(errorText, http::status::bad_request);
    }

    DBHelper dbHelper;
    bool wasFound;
    auto user {dbHelper.getUser(login, &wasFound)};
    if(wasFound){
        boost::property_tree::ptree jsonTree = user.getSafeJson();

        // JSON-tree to JSON
        std::ostringstream oss;
        boost::property_tree::write_json(oss, jsonTree);
        std::string jsonResponse = oss.str();

        // HTTP-creating (with JSON)
        http::response<http::string_body> response;
        response.body() = jsonResponse;
        response.set(http::field::content_type, "application/json");
        return response;
    } else{
        return getErrorResponse(USER_NOT_FOUND, boost::beast::http::status::not_found);
    }
}
