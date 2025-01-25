#include <iostream>
#include <limits>
#include <regex>

#include "../include/entry.h"
#include "../include/student.h"
#include "../include/utils.h"

// Helper function to clear invalid input


bool isDigits(const std::string& str) {
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

void studentEntry() {

    std::string regNo;
    std::string fName;
    std::string lName;
    std::string branch;
    int semester;
    std::string email;
    std::string moNo;
    std::vector<int> date(3); // Date: {day, month, year}

    std::regex regNoPattern("^U[0-9]{2}[A-Z]{2}[0-9]{3}$");

    // Prompt and validate inputs
    std::cout << "Enter Student Details\n";
    std::cout << "-----------------------\n";

    // Register Number
    while (true) {
        std::cout << "Register No.: ";
        std::cin >> regNo;

        // Check if input matches the pattern
        if (!std::regex_match(regNo, regNoPattern)) {
            std::cout << "Invalid register number. Format should be 'U20CS001'.\n";
            clearInput();
        }
        else {
            break; // Valid input, exit loop
        }
    }

    // First Name
    while (true) {
        std::cout << "First Name: ";
        std::cin >> fName;
        if (fName.empty()) {
            std::cout << "First name cannot be empty. Please try again.\n";
        }
        else {
            break;
        }
    }

    // Last Name
    while (true) {
        std::cout << "Last Name: ";
        std::cin >> lName;
        if (lName.empty()) {
            std::cout << "Last name cannot be empty. Please try again.\n";
        }
        else {
            break;
        }
    }

    // Branch
    while (true) {
        std::cout << "Branch: ";
        std::cin >> branch;
        if (branch.empty()) {
            std::cout << "Branch cannot be empty. Please try again.\n";
        }
        else {
            break;
        }
    }

    // Semester
    while (true) {
        std::cout << "Semester (1-8): ";
        std::cin >> semester;
        if (std::cin.fail() || semester < 1 || semester > 8) {
            std::cout << "Invalid semester. Please enter a number between 1 and 8.\n";
            clearInput();
        }
        else {
            break;
        }
    }

    // Email
    while (true) {
        std::cout << "Email: ";
        std::cin >> email;
        if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
            std::cout << "Invalid email format. Please enter a valid email address.\n";
        }
        else {
            break;
        }
    }

    // Date of Birth
    while (true) {
        std::cout << "Date of Birth (Day Month Year): ";
        std::cin >> date[0] >> date[1] >> date[2];
        if (std::cin.fail() || date[0] < 1 || date[0] > 31 || date[1] < 1 || date[1] > 12 || date[2] < 1900) {
            std::cout << "Invalid date. Please enter a valid day (1-31), month (1-12), and year (>1900).\n";
            clearInput();
        }
        else {
            break;
        }
    }

    // Mobile Number
    while (true) {
        std::cout << "Mobile No.: ";
        std::cin >> moNo;
        if (moNo.length() != 10 || !isDigits(moNo)) {
            std::cout << "Invalid mobile number. Please enter a 10-digit number.\n";
        }
        else {
            break;
        }
    }

    // Create Student Object and Insert into Database
    Student S(regNo, fName, lName, branch, semester, email, date, moNo);

    if (S.insert()) {
        std::cout << "Student entry successfully added to the database.\n";
    }
    else {
        std::cerr << "Failed to add student to the database.\n";
    }
}
