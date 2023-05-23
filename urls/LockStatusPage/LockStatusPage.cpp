//
// Created by nikita on 18.05.23.
//

#include "LockStatusPage.h"
#include "../../DBHelper/DBHelper.h"

#define ID_IS_MISSING "400 Bad Request: 'id' is missing. Please include the required 'id' parameter in your GET request"
#define LOCK_WAS_NOT_FOUND "404 Not found: Lock with this id wasn`t found"

LockStatusPage::LockStatusPage(const std::shared_ptr<http::request<http::string_body>> &request) {
    _params = parseGetRequest(request);
}

http::response<http::string_body> LockStatusPage::getResponse() {
    if(!_params.contains("id")){
       return getErrorResponse(ID_IS_MISSING, http::status::bad_request);
    }

    DBHelper dbHelper;
    bool wasFound {false};
    auto lock {dbHelper.getLock(std::stoul(_params.at("id")), &wasFound)};
    if(!wasFound){
        return getErrorResponse(LOCK_WAS_NOT_FOUND, http::status::not_found);
    }

    boost::property_tree::ptree pt;
    pt.put("is_open", lock.is_open());

    std::stringstream ss;
    boost::property_tree::write_json(ss, pt);

    boost::beast::http::response<http::string_body> res {http::status::ok, 11};
    res.body() = ss.str();
    res.set(http::field::content_type, "application/json");
    return res;
}
