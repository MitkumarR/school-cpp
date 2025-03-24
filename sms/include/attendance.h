#ifndef _ATTENDANCE_H
#define _ATTENDANCE_H

#include <string>

class Attendance {
private:
    std::string regNo;
    std::string courseCode;
    int totalClasses;
    int presents;
    int absents;

public:
    Attendance();
    Attendance(const std::string& regNo);

    // Declaration of update function
    void update(const std::string& regNo, const std::string& courseCode, bool present);

    std::string getRegNo() const { return regNo; }
    std::string getCourseCode() const { return courseCode; }
};

void enterAttendance();
#endif // !_ATTENDANCE_H