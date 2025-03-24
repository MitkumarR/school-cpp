#include <iostream>
#include <string>
#include <sqlite3.h>
#include <regex>
#include "../include/grades.h"
#include "../include/utils.h"

std::string generateExamCode(const std::string& examDate,
    const std::string& regNo,
    const std::string& courseCode) {
    // Extract components
    std::string year = examDate.substr(2, 2);  // Last 2 digits of year (e.g., "25" from "2025")
    std::string month = examDate.substr(5, 2); // Month (e.g., "03")
    char studentType = regNo[0];              // 'U' or 'P' from reg no

    // Generate exam code
    return year + month + studentType + courseCode; // e.g., "2503U001"
}

void enterGrades()
{
    std::string examDate;
    std::string grades;
    int examCredits;
    std::string courseCode;
    std::string regNo;
    std::string examCode; // Will be generated automatically

    std::cout << "\nEnter Student's Grades\n";
    std::cout << "-----------------------\n";

    // Course Code (e.g., CS001)
    std::regex courseCodePattern("^CS\\d{3}$");
    while (true) {
        std::cout << "Enter Course Code (e.g., CSXXX): ";
        std::getline(std::cin, courseCode);
        if (!std::regex_match(courseCode, courseCodePattern)) {
            std::cout << "Invalid format. Must be 'CS' followed by 3 digits (e.g., CS001).\n";
        }
        else {
            break;
        }
    }

    // Exam Date
    std::regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
    while (true) {
        std::cout << "Enter Exam Date (YYYY-MM-DD): ";
        std::getline(std::cin, examDate);
        if (!std::regex_match(examDate, datePattern)) {
            std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
        }
        else {
            // Additional validation for valid date ranges
            int year = std::stoi(examDate.substr(0, 4));
            int month = std::stoi(examDate.substr(5, 2));
            int day = std::stoi(examDate.substr(8, 2));
            if (year < 2000 || month < 1 || month > 12 || day < 1 || day > 31) {
                std::cout << "Invalid date values. Use year >= 2000, month 1-12, day 1-31.\n";
            }
            else {
                break;
            }
        }
    }

    // Registration Number (e.g., U22CS070 or P22CS076)
    std::regex regNoPattern("^[UP]\\d{2}CS\\d{3}$");
    while (true) {
        std::cout << "Enter Registration Number (e.g., U22CS070 or P22CS076): ";
        std::getline(std::cin, regNo);
        if (!std::regex_match(regNo, regNoPattern)) {
            std::cout << "Invalid format. Must be 'U' or 'P', 2 digits, 'CS', then 3 digits.\n";
        }
        else {
            break;
        }
    }

    // Generate Exam Code automatically
    examCode = generateExamCode(examDate, regNo, courseCode);
    std::cout << "Exam Code: " << examCode << std::endl;

    // Grades
    while (true) {
        std::cout << "Enter Grade (A, B, C, D, F): ";
        std::getline(std::cin, grades);
        if (grades.length() != 1 ||
            (grades != "A" && grades != "B" && grades != "C" &&
                grades != "D" && grades != "F")) {
            std::cout << "Invalid grade. Please enter A, B, C, D, or F.\n";
        }
        else {
            break;
        }
    }

    // Exam Credits
    while (true) {
        std::cout << "Enter Exam Credits (1-10): ";
        std::cin >> examCredits;
        if (std::cin.fail() || examCredits < 1 || examCredits > 10) {
            std::cout << "Invalid credits. Please enter a number between 1 and 10.\n";
            clearInput();
        }
        else {
            clearInput();
            break;
        }
    }

    // Database operations
    sqlite3* db;
    int rc = sqlite3_open("sms.db", &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    const char* sql = "INSERT INTO Exam (Exam_Code, Date, Grades, Exam_Credits, Course_code, Reg_No) "
        "VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Bind values
    sqlite3_bind_text(stmt, 1, examCode.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, examDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, grades.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, examCredits);
    sqlite3_bind_text(stmt, 5, courseCode.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, regNo.c_str(), -1, SQLITE_STATIC);

    // Execute
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::cout << "Grade successfully entered into database!" << std::endl;
}