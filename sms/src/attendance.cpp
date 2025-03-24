#include <iostream>
#include <limits>
#include <regex>

#include "../include/attendance.h"
#include "../include/utils.h"

#ifdef _WIN32
    #include <sqlite3.h>
#else
    #include "../include/sqlite3.h"
#endif

// Implementation of constructors
Attendance::Attendance() : totalClasses(0), presents(0), absents(0) {}

Attendance::Attendance(const std::string& regNo) 
    : regNo(regNo), totalClasses(0), presents(0), absents(0) {}

// Update function implementation
void Attendance::update(const std::string& regNo, const std::string& courseCode, bool present) {
    sqlite3* db;
    char* errMsg = nullptr;
    
    int rc = sqlite3_open("sms.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string checkSql = "SELECT Total_class, Presents, Absents FROM Attendance WHERE Reg_No = ? AND Course_code = ?";
    sqlite3_stmt* stmt;
    
    rc = sqlite3_prepare_v2(db, checkSql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, regNo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, courseCode.c_str(), -1, SQLITE_STATIC);

    int totalClasses = 0;
    int presents = 0;
    int absents = 0;
    bool recordExists = false;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        recordExists = true;
        totalClasses = sqlite3_column_int(stmt, 0);
        presents = sqlite3_column_int(stmt, 1);
        absents = sqlite3_column_int(stmt, 2);
    }
    sqlite3_finalize(stmt);

    totalClasses++;
    if (present) {
        presents++;
    } else {
        absents++;
    }

    std::string sql;
    if (recordExists) {
        sql = "UPDATE Attendance SET Total_class = ?, Presents = ?, Absents = ? WHERE Reg_No = ? AND Course_code = ?";
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        
        sqlite3_bind_int(stmt, 1, totalClasses);
        sqlite3_bind_int(stmt, 2, presents);
        sqlite3_bind_int(stmt, 3, absents);
        sqlite3_bind_text(stmt, 4, regNo.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, courseCode.c_str(), -1, SQLITE_STATIC);
    } else {
        sql = "INSERT INTO Attendance (Total_class, Presents, Absents, Course_code, Reg_No) VALUES (?, ?, ?, ?, ?)";
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        
        sqlite3_bind_int(stmt, 1, totalClasses);
        sqlite3_bind_int(stmt, 2, presents);
        sqlite3_bind_int(stmt, 3, absents);
        sqlite3_bind_text(stmt, 4, courseCode.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, regNo.c_str(), -1, SQLITE_STATIC);
    }

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    } else {
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void enterAttendance() {
    std::string regNo, courseCode;
    bool present = false;

    std::regex regNoPattern("^U[0-9]{2}[A-Z]{2}[0-9]{3}$");

    std::cout << "Enter Student Attendance\n";
    std::cout << "-----------------------\n";

    while (true) {
        std::cout << "Register No.: ";
        std::cin >> regNo;

        if (!std::regex_match(regNo, regNoPattern)) {
            std::cout << "Invalid register number. Format should be 'U20CS001'.\n";
            clearInput();
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Course Code: ";
        std::cin >> courseCode;
        if (courseCode.empty()) {
            std::cout << "Course code cannot be empty. Please try again.\n";
            clearInput();
        } else {
            break;
        }
    }

    std::string ask;
    while (true) {
        std::cout << "Present/Absent ? (p/a): ";
        std::cin >> ask;

        if (ask == "p" || ask == "P") {
            present = true;
            break;
        } else if (ask == "a" || ask == "A") {
            present = false;
            break;
        } else {
            std::cout << "Invalid input. Please enter 'p/P' or 'a/A'.\n";
            clearInput();
        }
    }

    Attendance att;
    att.update(regNo, courseCode, present);
    std::cout << "Attendance recorded successfully!\n";
}