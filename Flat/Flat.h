//
// Created by nikita on 16.04.23.
//


#ifndef BACKEND_CPP_FLAT_H
#define BACKEND_CPP_FLAT_H
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class FLat {
private:
    unsigned short _priceFlat;
    unsigned short _squareFlat;

    size_t _idFlat;
    size_t _idUserOwner;
    std::string _address;

    std::string _description;

    bool isTaken() const;

public:
    FLat(unsigned short priceFlat, unsigned short squareFlat, size_t idFlat, size_t idUserOwner, std::string address, std::string description);

    boost::property_tree::ptree getJson() const;

};


#endif //BACKEND_CPP_FLAT_H