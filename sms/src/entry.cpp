#include "../include/Student.h"
#include <iostream>

// Constructor Definition
Student::Student() {}
Student::Student(int regNo,
    const std::string& fName,
    const std::string& lName,
    const std::string& branch,
    int semester,
    const std::string& email,
    const std::vector<int>& date,
    const std::string& moNo)
    : regNo(regNo), fName(fName), lName(lName), branch(branch),
    semester(semester), email(email), date(date), moNo(moNo) {
}

// Destructor Definition
Student::~Student() {}

// Function: studentEntry
bool Student::studentEntry() {
    // SQL Insert Command
    std::string sql = "INSERT INTO students (reg_no, f_name, l_name, branch, semester, email, dob, mo_no) "
        "VALUES (" +
        std::to_string(regNo) + ", '" +
        fName + "', '" +
        lName + "', '" +
        branch + "', " +
        std::to_string(semester) + ", '" +
        email + "', '" +
        std::to_string(date[0]) + "-" + std::to_string(date[1]) + "-" + std::to_string(date[2]) + "', '" +
        moNo + "');";

    // Execute the SQL Command
    DBHandler db("sms.db"); // Database file
    if (db.executeSQL(sql)) {
        std::cout << "Student entry successful.\n";
        return true;
    }
    else {
        std::cerr << "Failed to add student to the database.\n";
        return false;
    }
}
