#ifndef _STUDENT_H
#define _STUDENT_H

#include <vector>
#include <string>
#include "../include/DBHandler.h"

class Student {
private:
    int regNo;
    std::string fName;
    std::string lName;
    std::string branch;
    int semester;
    std::string email;
    std::vector<int> date; // Format: {day, month, year}
    std::string moNo;

public:
    // Constructor
    Student();
    Student(int regNo,
        const std::string& fName,
        const std::string& lName,
        const std::string& branch,
        int semester,
        const std::string& email,
        const std::vector<int>& date = { 0, 0, 0 },
        const std::string& moNo = "");

    // Destructor
    ~Student();

    // Methods
    bool studentEntry();
};

#endif // !_STUDENT_H