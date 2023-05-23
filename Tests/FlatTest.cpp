//
// Created by nikita on 01.05.23.
//
#include <gtest/gtest.h>
#include <boost/property_tree/json_parser.hpp>
#include "../Flat/Flat.h"

TEST(FlatTest, GetJsonReturnsCorrectJson) {
    FLat flat(100, 50, 1, 2, "123 Main St", "A nice flat");
    boost::property_tree::ptree expectedJson;
    expectedJson.put("price", 100);
    expectedJson.put("square", 50);
    expectedJson.put("idFlat", 1);
    expectedJson.put("idUserOwner", 2);
    expectedJson.put("address", "123 Main St");
    expectedJson.put("isTaken", "false");
    expectedJson.put("description", "A nice flat");

    boost::property_tree::ptree actualJson = flat.getJson();

    EXPECT_EQ(expectedJson, actualJson);
}