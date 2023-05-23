//
// Created by nikita on 16.05.23.
//

#include "CurrentFlatPage.h"
#include "../../DBHelper/DBHelper.h"

#define ID_IS_MISSING "400 Bad Request: 'id' is missing. Please include the required 'id' parameter in your GET request"
#define FLAT_WAS_NOT_FOUND "404 Not found: Flat with this id wasn`t found"

CurrentFlatPage::CurrentFlatPage(const std::shared_ptr<http::request<http::string_body>> &request) {
    _params = parseGetRequest(request);
}

http::response<http::string_body> CurrentFlatPage::getResponse() {
    if(!_params.contains("id")){
        return getErrorResponse(ID_IS_MISSING, http::status::bad_request);
    }

    DBHelper dbHelper;
    bool wasFound {false};
    auto flat = dbHelper.getFlat(std::stoul(_params.at("id")), &wasFound);
    if(!wasFound){
        return getErrorResponse(FLAT_WAS_NOT_FOUND, http::status::not_found);
    }
    boost::property_tree::ptree jsonTree = flat.getJson();

    // JSON-tree to JSON
    std::ostringstream oss;
    boost::property_tree::write_json(oss, jsonTree);
    std::string jsonResponse = oss.str();

    // HTTP-creating (with JSON)
    http::response<http::string_body> response;
    response.body() = jsonResponse;
    response.set(http::field::content_type, "application/json");

    return response;
}

