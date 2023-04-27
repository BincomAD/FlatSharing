//
// Created by nikita on 16.04.23.
//

#include "Flat.h"


FLat::FLat(unsigned short priceFlat, unsigned short squareFlat, size_t idFlat, size_t idUserOwner, std::string address, std::string description)
            : _priceFlat(priceFlat), _squareFlat(squareFlat), _idFlat(idFlat), _idUserOwner(idUserOwner), _address(address), _description(description) {}

boost::property_tree::ptree FLat::getJson() const {
    boost::property_tree::ptree flat;

    flat.put("price", _priceFlat);
    flat.put("square", _squareFlat);
    flat.put("idFlat", _idFlat);
    flat.put("idUserOwner", _idUserOwner);
    flat.put("address", _address);
    flat.put("smartLock", isTaken());
    flat.put("description", _description);


    return flat;

}
