#include <iostream>
#include <string>
#include <sqlite3.h>
#include <iomanip>
#include <regex>
#include "../include/info.h"
#include "../include/utils.h"

// Callback function for SQLite queries (generic display)
static int displayCallback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << std::setw(20) << std::left << azColName[i] << ": "
            << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << "------------------------" << std::endl;
    return 0;
}

// Display all student details
void displayStudentDetails(sqlite3* db, const std::string& regNo) {
    std::string sql = "SELECT * FROM Student WHERE Reg_No = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, regNo.c_str(), -1, SQLITE_STATIC);

        std::cout << "\nStudent Details:\n";
        std::cout << "----------------\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            for (int i = 0; i < sqlite3_column_count(stmt); i++) {
                std::cout << std::setw(20) << std::left << sqlite3_column_name(stmt, i)
                    << ": " << sqlite3_column_text(stmt, i) << std::endl;
            }
        }
        sqlite3_finalize(stmt);
    }
}

// Display courses based on student's semester
void displayStudentCourses(sqlite3* db, const std::string& regNo) {
    std::string sql = R"(
        SELECT c.Course_code, c.Course_name, c.Credits, c.Course_semester
        FROM Course c
        JOIN Student s ON c.Course_semester = s.Semester
        WHERE s.Reg_No = ?;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, regNo.c_str(), -1, SQLITE_STATIC);

        std::cout << "\nStudent's Courses:\n";
        std::cout << "----------------\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << "Course Code: " << sqlite3_column_text(stmt, 0) << "\n"
                << "Course Name: " << sqlite3_column_text(stmt, 1) << "\n"
                << "Credits: " << sqlite3_column_int(stmt, 2) << "\n"
                << "Semester: " << sqlite3_column_int(stmt, 3) << "\n"
                << "------------------------\n";
        }
        sqlite3_finalize(stmt);
    }
}

// Display exam results
void displayStudentResults(sqlite3* db, const std::string& regNo) {
    std::string sql = "SELECT Exam_Code, Course_code, Grades, Exam_Credits "
        "FROM Exam WHERE Reg_No = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, regNo.c_str(), -1, SQLITE_STATIC);

        std::cout << "\nStudent Results:\n";
        std::cout << "----------------\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << "Exam Code: " << sqlite3_column_text(stmt, 0) << "\n"
                << "Course Code: " << sqlite3_column_text(stmt, 1) << "\n"
                << "Grade: " << sqlite3_column_text(stmt, 2) << "\n"
                << "Credits Gained: " << sqlite3_column_int(stmt, 3) << "\n"
                << "------------------------\n";
        }
        sqlite3_finalize(stmt);
    }
}

// Display attendance
void displayStudentAttendance(sqlite3* db, const std::string& regNo) {
    std::string sql = "SELECT Course_code, Total_class, Presents, Absents "
        "FROM Attendance WHERE Reg_No = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, regNo.c_str(), -1, SQLITE_STATIC);

        std::cout << "\nStudent Attendance:\n";
        std::cout << "----------------\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int total = sqlite3_column_int(stmt, 1);
            int present = sqlite3_column_int(stmt, 2);
            float percentage = (total > 0) ? (static_cast<float>(present) / total * 100) : 0;

            std::cout << "Course Code: " << sqlite3_column_text(stmt, 0) << "\n"
                << "Total Classes: " << total << "\n"
                << "Present: " << present << "\n"
                << "Absent: " << sqlite3_column_int(stmt, 3) << "\n"
                << "Percentage: " << std::fixed << std::setprecision(2)
                << percentage << "%\n"
                << "------------------------\n";
        }
        sqlite3_finalize(stmt);
    }
}

void studentInfo()
{
    sqlite3* db;
    std::string regNo;

    // Open database
    if (sqlite3_open("sms.db", &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Get student registration number
    std::cout << "\nStudent Information System\n";
    std::cout << "--------------------------\n";
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

    // Verify student exists
    std::string checkSql = "SELECT COUNT(*) FROM Student WHERE Reg_No = ?;";
    sqlite3_stmt* checkStmt;
    if (sqlite3_prepare_v2(db, checkSql.c_str(), -1, &checkStmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(checkStmt, 1, regNo.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(checkStmt) == SQLITE_ROW && sqlite3_column_int(checkStmt, 0) == 0) {
            std::cout << "Student with Registration Number " << regNo << " not found!\n";
            sqlite3_finalize(checkStmt);
            sqlite3_close(db);
            return;
        }
        sqlite3_finalize(checkStmt);
    }

    // Menu loop
    while (true) {
        std::cout << "\nStudent Information Menu\n";
        std::cout << "------------------------\n";
        std::cout << "1. View Student Details\n";
        std::cout << "2. View Student Courses\n";
        std::cout << "3. View Student Results\n";
        std::cout << "4. View Student Attendance\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1-5): ";

        int choice;
        std::cin >> choice;
        clearInput();

        switch (choice) {
        case 1:
            displayStudentDetails(db, regNo);
            break;
        case 2:
            displayStudentCourses(db, regNo);
            break;
        case 3:
            displayStudentResults(db, regNo);
            break;
        case 4:
            displayStudentAttendance(db, regNo);
            break;
        case 5:
            std::cout << "Exiting Student Information System\n";
            sqlite3_close(db);
            return;
        default:
            std::cout << "Invalid choice! Please enter a number between 1 and 5.\n";
        }
    }

    sqlite3_close(db);
}
