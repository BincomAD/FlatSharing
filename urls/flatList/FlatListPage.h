//
// Created by nikita on 15.05.23.
//

#ifndef BACKEND_CPP_FLATLISTPAGE_H
#define BACKEND_CPP_FLATLISTPAGE_H


#include "../AbstractPage.h"
#include "../../Flat/Flat.h"

class FlatListPage : public AbstractPage{
private:
    std::unordered_map<std::string, std::string> _params;

    std::vector<FLat> getFlatsJson(size_t offset, size_t amount);

public:

    explicit FlatListPage(const std::shared_ptr<http::request<http::string_body>> &request);

    http::response<http::string_body> getResponse() override;


};


#endif //BACKEND_CPP_FLATLISTPAGE_H
