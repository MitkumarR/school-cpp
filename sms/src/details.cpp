#include "../include/details.h"
#include "../include/student.h"
#include "../include/utils.h"
#include <regex>

void studentDetails()
{
    std::string regNo;
    std::regex regNoPattern("^U[0-9]{2}[A-Z]{2}[0-9]{3}$");
    

    while (true) {
        std::cout << "Register No.: ";
        std::cin >> regNo;

        // Check if input matches the pattern
        if (!std::regex_match(regNo, regNoPattern)) {
            std::cout << "Invalid register number. Format should be like 'U20CS001'.\n";
            clearInput();
        }
        else {
            break; // Valid input, exit loop
        }
    }

    Student S;
    if (S.search(regNo)) {
        std::cout << "\n" << std::endl;
        S.get(); // Display student details
        std::cout << "\n" << std::endl;
    }
    else {
        std::cout << "No student found with Register No.: " << regNo << std::endl;
    }
}

