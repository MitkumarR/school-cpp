#ifndef _STUDENT_H
#define _STUDENT_H

#include <vector>
#include <string>
#include <sstream>

#include "../include/DBHandler.h"

class Student {
private:
    std::string regNo, fName, lName, branch, email, moNo;
    std::vector<int> date;
    int semester = 0;

public:

    Student(){};
    // Constructor
    Student(
        const std::string& regNo,
        const std::string& fName,
        const std::string& lName,
        const std::string& branch,
        const int semester,
        const std::string& email,
        const std::vector<int>& date,
        const std::string& moNo)
        : regNo(regNo), fName(fName), lName(lName), branch(branch),
        semester(semester), email(email), date(date), moNo(moNo) {
    };


    // Destructor
    ~Student() {};

    // Methods
    bool insert()
    {
        std::string sql = "INSERT INTO Student (Reg_No, F_name, L_name, Branch, Semester, Email, DOB, Mo_No) "
            "VALUES ('" +
            regNo + "', '" +
            fName + "', '" +
            lName + "', '" +
            branch + "', " +
            std::to_string(semester) + ", '" +
            email + "', '" +
            std::to_string(date[0]) + "-" + std::to_string(date[1]) + "-" + std::to_string(date[2]) + "', '" +
            moNo + "');";

        // Execute the SQL Command
        DBHandler db("sms.db"); // Database file
        if (!db.executeSQL(sql)) return false;

        return true;
    }

    bool search(std::string& pk)
    {
        std::string sql = "SELECT * FROM Student WHERE Reg_No = ?";

        // Database handler object
        sqlite3* db;
        sqlite3_stmt* stmt;

        // Open the database
        if (sqlite3_open("sms.db", &db) != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        // Prepare the SQL query
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return false;
        }

        // Bind the primary key (Reg_No) to the query
        if (sqlite3_bind_text(stmt, 1, pk.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
            std::cerr << "Error binding parameter: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return false;
        }

        // Execute the query and fetch the result
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            // Extract values from the current row
            regNo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            fName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            lName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            branch = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            semester = sqlite3_column_int(stmt, 4);
            email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            std::string dob = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            std::stringstream ss(dob);
            std::string token;

            date.clear();
            while (std::getline(ss, token, '-')) {
                date.push_back(std::stoi(token));
            }

            moNo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));

            // Extract and parse the DOB

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return true;
        }

        // No record found
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    void get()
    {

        std::cout << "\tStudent Details:\n";
        std::cout << "\t-----------------\n";
        std::cout << "Registration No.: " << regNo << "\n";
        std::cout << "First Name: " << fName << "\n";
        std::cout << "Last Name: " << lName << "\n";
        std::cout << "Branch: " << branch << "\n";
        std::cout << "Semester: " << semester << "\n";
        std::cout << "Email: " << email << "\n";
        std::cout << "Mobile No.: " << moNo << "\n";
        std::cout << "Date of Birth: " << date[0] << "-" << date[1] << "-" << date[2] << "\n";
    }
};

#endif // !_STUDENT_H