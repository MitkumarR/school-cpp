#ifndef _DBHANDLER_H
#define _DBHANDLER_H

#include <iostream>
#include <sqlite3.h>
#include <string>

class DBHandler {
private:
    sqlite3* db;           // Pointer to SQLite database
    std::string dbName;    // Name of the database file
public:
    // Constructor
    DBHandler(const std::string& databaseName);

    // Destructor
    ~DBHandler();

    // Function to execute SQL commands
    bool executeSQL(const std::string& sql);

    // Function to handle errors
    std::string getErrorMessage() const;
};

#endif // !_LOG_H

