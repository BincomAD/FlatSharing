//
// Created by nikita on 22.05.23.
//

#include "RentAFlatPage.h"
#include "../../DBHelper/DBHelper.h"

#define FLAT_IS_NOT_AVAILABLE "This flat has not been rented. Somebody have already took this flat"
#define WRONG_TOKEN "You dont have an access to rent this flat"
#define FLAT_WAS_NOT_FOUND "Flat was not found"

RentAFlatPage::RentAFlatPage(const std::shared_ptr<http::request<http::string_body>> &request) {
    _params = parsePostRequest(request);
}

http::response<http::string_body> RentAFlatPage::getResponse() {
    std::string flatId, clientId, beginDate, endDate, accessToken;
    if (_params.count("flat_id") &&
        _params.count("client_id") &&
        _params.count("begin_date") &&
        _params.count("end_date") &&
        _params.count("access_token")) {
        // Все ключи присутствуют
        flatId = _params.at("flat_id");
        clientId = _params.at("client_id");
        beginDate = _params.at("begin_date");
        endDate = _params.at("end_date");
        accessToken = _params.at("access_token");
    } else {
        std::string errorText = "Missing parameters: ";
        std::unique_ptr<std::vector<std::string>> reqParams = std::make_unique<std::vector<std::string>>();
        reqParams->push_back("flat_id");
        reqParams->push_back("client_id");
        reqParams->push_back("begin_date");
        reqParams->push_back("end_date");
        reqParams->push_back("access_token");
        auto mParams = getMissingParams(std::move(reqParams));
        for (auto i = mParams.begin(); i != mParams.end(); ++i) {
            errorText.append((*i));
            errorText.append(", ");
        }
        return getErrorResponse(errorText, http::status::bad_request);
    }

    DBHelper dbHelper;

    //todo: remove 123
    if(dbHelper.checkAccess(std::stoi(clientId), accessToken) || accessToken == "123"){
        bool wasFound {false};
        dbHelper.getFlat(std::stoi(flatId), &wasFound);
        if(!wasFound){
            return getErrorResponse(FLAT_WAS_NOT_FOUND, http::status::not_found);
        }
        bool isAvailable {dbHelper.checkFlatAvailability(std::stoi(flatId), beginDate, endDate)};
        if(isAvailable){
            dbHelper.rentAFlat(std::stoi(flatId), std::stoi(clientId), beginDate, endDate);
            boost::beast::http::response<http::string_body> res;
            res.result(http::status::ok);
            res.set(http::field::content_type, "text/html");
            res.body() = "success";
            return res;
        } else{
            return getErrorResponse(FLAT_IS_NOT_AVAILABLE, http::status::bad_request);
        }
    } else{
        return getErrorResponse(WRONG_TOKEN, http::status::forbidden);
    }
}
