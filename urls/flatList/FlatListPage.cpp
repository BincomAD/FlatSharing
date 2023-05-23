//
// Created by nikita on 15.05.23.
//

#include "FlatListPage.h"
#include "../../DBHelper/DBHelper.h"

http::response<http::string_body> FlatListPage::getResponse() {
    size_t amount {20}, offset {0};
    if(_params.contains("amount")){
        amount = std::stoul(_params["amount"]);
        if(amount > 20){
            amount = 20;
        }
    }
    if(_params.contains("offset")){
        offset = std::stoul(_params["offset"]);
    }


    // Получение списка квартир
    auto flats {getFlatsJson(offset, amount)};

    // Создание JSON объекта
    boost::property_tree::ptree pt;
    boost::property_tree::ptree flats_ptree;

    // Итерация по списку квартир и добавление их в JSON
    for(const auto& flat : flats) {
        boost::property_tree::ptree flat_ptree;
        flat_ptree = flat.getJson();
        flats_ptree.push_back(std::make_pair("", flat_ptree));
    }

    pt.put("total", std::to_string(flats.size()));
    pt.add_child("params", flats_ptree);

    // Преобразование JSON объекта в строку
    std::stringstream ss;
    boost::property_tree::write_json(ss, pt);
    std::string json = ss.str();

    // Создание HTTP ответа с JSON в качестве тела
    http::response<http::string_body> res { http::status::ok, 11};
    res.set(http::field::content_type, "application/json");
    res.set(http::field::access_control_allow_origin, "*");
    res.body() = json;
    res.prepare_payload();

    return res;
}


FlatListPage::FlatListPage(const std::shared_ptr<http::request<http::string_body>> &request) {
    _params = parseGetRequest(request);
}

std::vector<FLat> FlatListPage::getFlatsJson(size_t offset, size_t amount) {
    DBHelper dbHelper;
    auto flats {dbHelper.getFlatsList(offset, amount)};
    return flats;
}
