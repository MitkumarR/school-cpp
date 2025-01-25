/*
#include "../include/DBHandler.h"
#include <map>

DBHandler::DBHandler(const std::string& databaseName) : db(nullptr), dbName(databaseName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Database '" << dbName << "' opened successfully." << std::endl;
    }
}

// Destructor: Closes the database connection
DBHandler::~DBHandler() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Database '" << dbName << "' closed successfully." << std::endl;
    }
}
// Executes an SQL command
bool DBHandler::executeSQL(const std::string & sql){
    //code...
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);  // Free error message memory
        return false;
    }
    std::cout << "SQL executed successfully: " << std::endl;
    return true;
}

// Returns the last error message
std::string DBHandler::getErrorMessage() const {
    return sqlite3_errmsg(db);
}

*/