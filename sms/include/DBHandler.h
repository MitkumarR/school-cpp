#ifndef _DBHANDLER_H
#define _DBHANDLER_H

#include <iostream>
#include "../include/sqlite3.h"
#include <string>
#include <map>

class DBHandler {
private:
    sqlite3* db;           // Pointer to SQLite database
    std::string dbName;    // Name of the database file
public:
    // Constructor
    DBHandler(const std::string& databaseName) : db(nullptr), dbName(databaseName) {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "Database '" << dbName << "' opened successfully." << std::endl;
        }
    }
    // Destructor
    ~DBHandler() {
        if (db) {
            sqlite3_close(db);
            std::cout << "Database '" << dbName << "' closed successfully." << std::endl;
        }
    }
    // Function to execute SQL commands
    bool executeSQL(const std::string& sql) {
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
    // Function to handle errors
    std::string getErrorMessage() const {
        return sqlite3_errmsg(db);
    }
};

#endif // !_LOG_H

