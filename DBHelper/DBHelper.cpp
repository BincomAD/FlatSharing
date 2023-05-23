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

void DBHelper::saveFlat(std::unique_ptr<FLat> flatItem) {
    boost::property_tree::ptree flatJson = flatItem->getJson();
    
    std::string id{std::to_string(flatJson.get<int>("idFlat"))};
    std::string price{std::to_string(flatJson.get<int>("price"))};
    std::string square{std::to_string(flatJson.get<int>("square"))};
    std::string address{flatJson.get<std::string>("address")};
    std::string description{flatJson.get<std::string>("description")};
    std::string ownerId{std::to_string(flatJson.get<int>("idUserOwner"))};

    pqxx::work txn(*_connection);
    txn.exec("INSERT INTO Flat (price, square, address, description, owner_id) VALUES ("
             + price + ", " + square + ", '" + address + "', '" + description + "', " + ownerId + ")");
    txn.commit();
    
    
}

//wasFound is return value
FLat DBHelper::getFlat(size_t flatId, bool* wasFound) {
    std::string query{"SELECT price, square, address, description, owner_id FROM Flat WHERE id = " + pqxx::to_string(flatId)};
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
  
    unsigned short price{0};
    unsigned short square{0};
    std::string address{"error"};
    std::string description{"error"};
    size_t owner_id{0};
    
    if (result.size() > 0) {
        price = result[0]["Price"].as<unsigned short>();
    	square = result[0]["Square"].as<unsigned short>();
    	address = result[0]["Address"].as<std::string>();
    	description = result[0]["Description"].as<std::string>();
    	owner_id = result[0]["Owner_ID"].as<size_t>();
        (*wasFound) = true;
    } else{
        (*wasFound) = false;
    }

    
    FLat flatResult(price, square, flatId, owner_id, address, description);
    return flatResult;

}

void DBHelper::removeFlat(size_t flatId) {
    std::string query{"DELETE FROM Flat WHERE id = " + pqxx::to_string(flatId)};
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
    txn.commit();
 
}

void DBHelper::updateFlat(size_t flatId, std::unique_ptr<FLat> flatItemUp) {
    boost::property_tree::ptree flatJson = flatItemUp->getJson();
    
    std::string id{std::to_string(flatJson.get<int>("idFlat"))};
    std::string price{std::to_string(flatJson.get<int>("price"))};
    std::string square{std::to_string(flatJson.get<int>("square"))};
    std::string address{flatJson.get<std::string>("address")};
    std::string description{flatJson.get<std::string>("description")};
    std::string ownerId{std::to_string(flatJson.get<int>("idUserOwner"))};
    
    pqxx::work txn(*_connection);
    txn.exec("UPDATE Flat SET price = " + price + ", square = " + square + ", address = '" + address + "', description = '" + description + "', owner_id = " + ownerId + " WHERE id = " + pqxx::to_string(flatId));
    txn.commit();
}


std::vector<FLat> DBHelper::getFlatsList(size_t offset, size_t amount) {
    std::vector<FLat> result;

    pqxx::work txn(*_connection);

    // Выполняем запрос с использованием смещения и количества
    std::string query = "SELECT * FROM Flat WHERE id >= " + std::to_string(offset) + " AND id < " + std::to_string(offset + amount);
    pqxx::result queryResult = txn.exec(query);

    // Обрабатываем результат запроса
    for (const auto& row : queryResult) {
        unsigned short price = row["Price"].is_null() ? 0 : row["Price"].as<unsigned short>();
        unsigned short square = row["Square"].is_null() ? 0 : row["Square"].as<unsigned short>();
        std::string address = row["Address"].is_null() ? "" : row["Address"].as<std::string>();
        std::string description = row["Description"].is_null() ? "" : row["Description"].as<std::string>();
        size_t owner_id = row["Owner_ID"].is_null() ? 0 : row["Owner_ID"].as<size_t>();
        size_t flatId = row["id"].is_null() ? 0 : row["id"].as<size_t>();
        FLat flatResult(price, square, flatId, owner_id, address, description);
        result.push_back(flatResult);
    }

    txn.commit();

    return result;
}


void DBHelper::saveLock(std::unique_ptr<SmartLock> lockItem) {
    
    
    std::string id{std::to_string(lockItem->getId())};
    std::string isOpen{std::to_string(lockItem->is_open())};
    std::string flatId{std::to_string(lockItem->getFlatId())};

    pqxx::work txn(*_connection);
    txn.exec("INSERT INTO smartlock (isopen, flat_id) VALUES ('"
            + isOpen + "', " + flatId + ")");
    txn.commit();
    
    
}

void DBHelper::removeLock(size_t lockId) {
    std::string query{"DELETE FROM smartlock WHERE id = " + pqxx::to_string(lockId)};
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
    txn.commit();
}


//wasFound is return value
SmartLock DBHelper::getLock(size_t lockId, bool* wasFound) {
    std::string query{"SELECT isopen, flat_id FROM smartlock WHERE id = " + pqxx::to_string(lockId)};
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
  
    size_t flatId{999};
    bool isOpen{0};
    
    if (result.size() > 0) {
        flatId = result[0]["flat_id"].as<size_t>();
    	isOpen = result[0]["isopen"].as<bool>();
        (*wasFound) = true;
    } else{
        (*wasFound) = false;
    }
    
    SmartLock lockResult(lockId, flatId, isOpen);
    return lockResult;

}

void DBHelper::updateLock(size_t lockId, std::unique_ptr<SmartLock> slItem) {
        
    std::string isOpen{std::to_string(slItem->is_open())};
    std::string flatId{std::to_string(slItem->getFlatId())};

    pqxx::work txn(*_connection);
    txn.exec("UPDATE smartlock SET isopen = '" + isOpen + "', flat_id = " + flatId + " WHERE Id = " + pqxx::to_string(lockId));
    txn.commit();
}

User DBHelper::getUser(size_t userId) {
    std::string query{"SELECT name, email, number, login, password FROM profile WHERE id = " + pqxx::to_string(userId)};
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
  
    std::string name{"error"};
    std::string email{"error"};
    std::string number{"error"};
    std::string login{"error"};
    std::string password{"error"};
    
    if (result.size() > 0) {
        name = result[0]["name"].as<std::string>();
    	email = result[0]["email"].as<std::string>();
    	number = result[0]["number"].as<std::string>();
    	login = result[0]["login"].as<std::string>();
    	password = result[0]["password"].as<std::string>();
    }

    
    User userResult(userId, login, name, password, number, email);
    return userResult;

}

void DBHelper::saveUser(std::unique_ptr<User> userItem) {
    boost::property_tree::ptree userJson = userItem->getJson();
    
//    std::string id{std::to_string(userJson.get<size_t>("id"))};
    std::string login{userJson.get<std::string>("login")};
    std::string name{userJson.get<std::string>("name")};
    std::string phone{userJson.get<std::string>("number")};
    std::string mail{userJson.get<std::string>("email")};
    std::string password{userJson.get<std::string>("password")};

    pqxx::work txn(*_connection);
    txn.exec("INSERT INTO profile (name, email, number, login, password) VALUES ('"
             + name + "', '" + mail + "', '" + phone + "', '" + login + "', '" + password + "')");
    txn.commit();
    
}

void DBHelper::removeUser(size_t userId) {
    std::string query{"DELETE FROM profile WHERE Id = " + pqxx::to_string(userId)};
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
    txn.commit();
 
}

void DBHelper::updateUser(size_t userId, std::unique_ptr<User> userItemUp) {
    boost::property_tree::ptree userJson = userItemUp->getJson();
    
    std::string login{userJson.get<std::string>("login")};
    std::string name{userJson.get<std::string>("name")};
    std::string phone{userJson.get<std::string>("phoneNumber")};
    std::string mail{userJson.get<std::string>("mail")};
    std::string password{userJson.get<std::string>("password")};
    
    pqxx::work txn(*_connection);
    txn.exec("UPDATE profile SET login = '" + login + "', name = '" + name + "', email = '" + mail + "', password = '" + password + "', number = '" + phone + "' WHERE id = " + pqxx::to_string(userId));
    txn.commit(); 
}

void DBHelper::setAccess(size_t userId, std::string token) {
    pqxx::work txn(*_connection);
    txn.exec("UPDATE profile SET accesstoken = '" + token + "' WHERE id = " + pqxx::to_string(userId));
    txn.commit(); 
}

bool DBHelper::checkAccess(size_t userId, std::string token) {
    std::string query{"SELECT accesstoken FROM profile WHERE id = " + pqxx::to_string(userId)};
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
    
    std::string accessToken{result[0]["accesstoken"].as<std::string>()};
    
    return accessToken == token;
}

size_t DBHelper::getFlatId() {
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec("SELECT MAX(id) FROM Flat"));

    size_t maxId = 0;
    if (!result[0][0].is_null()) {
        maxId = result[0][0].as<size_t>();
    }

    txn.commit();

    return maxId + 1;
}

size_t DBHelper::getLockId() {
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec("SELECT MAX(id) FROM smartlock"));

    size_t maxId = 0;
    if (!result[0][0].is_null()) {
        maxId = result[0][0].as<size_t>();
    }

    txn.commit();

    return maxId + 1;
}

size_t DBHelper::getUserId() {
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec("SELECT MAX(id) FROM profile"));

    size_t maxId = 0;
    if (!result[0][0].is_null()) {
        maxId = result[0][0].as<size_t>();
    }

    txn.commit();

    return maxId + 1;
}

//wasFound is return value
User DBHelper::getUser(std::string userLogin, bool* wasFound) {
    std::string query{"SELECT id, name, email FROM profile WHERE login = '" + pqxx::to_string(userLogin) + "'"};

    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
    size_t id{0};
    std::string name{"error"};
    std::string email{"error"};
    std::string login{"error"};

    if (result.size() > 0) {
        id = result[0]["id"].as<size_t>();
        name = result[0]["name"].as<std::string>();
    	email = result[0]["email"].as<std::string>();
    	login = userLogin;
        (*wasFound) = true;
    } else{
        (*wasFound) = false;
    }

    
    User userResult(id, login, name, email);
    return userResult;

}

void DBHelper::setRefresh(size_t userId, std::string token) {
    pqxx::work txn(*_connection);
    txn.exec("UPDATE profile SET refresh_token = '" + token + "' WHERE id = " + pqxx::to_string(userId));
    txn.commit(); 
}

bool DBHelper::checkRefresh(size_t userId, std::string token) {
    std::string query{"SELECT refresh_token FROM profile WHERE id = " + pqxx::to_string(userId)};
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
    
    std::string accessToken{result[0]["refresh_token"].as<std::string>()};
    
    return accessToken == token;
}

boost::property_tree::ptree DBHelper::getUserTokens(const std::string& login, const std::string& password) {
    std::string query = "SELECT password, accesstoken, refresh_token FROM profile WHERE login = '" + login + "'";
    
    pqxx::work txn(*_connection);
    pqxx::result result(txn.exec(query));
    
    boost::property_tree::ptree response;
    
    if (result.size() > 0) {
        std::string storedPassword = result[0]["password"].as<std::string>();
        if (storedPassword == password) {
            std::string accessToken = result[0]["accesstoken"].as<std::string>();
            std::string refreshToken = result[0]["refresh_token"].as<std::string>();;
            
            response.put("access_token", accessToken);
            response.put("refresh_token", refreshToken);
        }
    }
    
    return response;
}

bool DBHelper::checkFlatAvailability(int flatId, const std::string& startDate, const std::string& endDate) {
    std::string query = "SELECT COUNT(*) FROM rents WHERE flat_id = " + std::to_string(flatId)
                        + " AND (('"+ startDate + "' BETWEEN begin_date AND end_date) OR ('" + endDate + "' BETWEEN begin_date AND end_date)"
                        + " OR (begin_date BETWEEN '" + startDate + "' AND '" + endDate + "') OR (end_date BETWEEN '" + startDate + "' AND '" + endDate + "'))";

    pqxx::nontransaction txn(*_connection);
    pqxx::result result = txn.exec(query);

    // Получаем значение COUNT(*) из результата запроса
    int count = result[0][0].as<int>();

    // Если count больше 0, значит квартира занята в указанный период
    return count == 0;
}

void DBHelper::rentAFlat(int flatId, int clientId, const std::string& beginDate, const std::string& endDate) {
    std::string query = "INSERT INTO rents (client_id, begin_date, end_date, flat_id) VALUES ("
                        + std::to_string(clientId) + ", '"
                        + beginDate + "', '"
                        + endDate + "', "
                        + std::to_string(flatId) + ")";

    pqxx::work txn(*_connection);
    txn.exec(query);
    txn.commit();
}



