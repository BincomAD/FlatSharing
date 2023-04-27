//
// Update by SashaD on 16.04.23.
//

#include "DBHelper.h"

DBHelper::DBHelper(std::string host, std::string port, std::string dbname,
                   std::string user, std::string password) {
    std::string connectionString{"host=" + host + " port=" + port + " dbname=" +
                                 dbname + " user=" + user + " password=" +
                                 password};
    _connection = new pqxx::connection(connectionString);
}

DBHelper::~DBHelper() {
    if(_connection) {
        delete _connection;
    }
}

void DBHelper::saveFlat(std::shared_ptr<FLat> flatItem) {
    boost::property_tree::ptree flatJson = flatItem->getJson();

    std::string price{std::to_string(flatJson.get<int>("price"))};
    std::string square{std::to_string(flatJson.get<int>("square"))};
    std::string address{flatJson.get<std::string>("address")};
    std::string description{flatJson.get<std::string>("description")};
    std::string ownerId{std::to_string(flatJson.get<int>("idUserOwner"))};

    pqxx::work txn(*_connection);
    txn.exec("INSERT INTO Flat (Price, Square, Address, Description, Owner_ID) VALUES ("
            + price + ", " + square + ", '" + address + "', '" + description + "', " + ownerId + ")");
    txn.commit();
    
}

FLat DBHelper::getFlat(size_t flatId) {
    std::string query{"SELECT Price, Square, Address, Description, Owner_ID FROM Flat WHERE ID = " + pqxx::to_string(flatId)};
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
    
    unsigned short price{0};
    unsigned short square{0};
    std::string address{"error"};
    std::string description{"error"};
    size_t owner_id{0};
    
    price = result[0]["Price"].as<unsigned short>();
    square = result[0]["Square"].as<unsigned short>();
    address = result[0]["Address"].as<std::string>();
    description = result[0]["Description"].as<std::string>();
    owner_id = result[0]["Owner_ID"].as<size_t>();
    
    FLat flatResult(price, square, flatId, owner_id, address, description);
    return flatResult;

}

