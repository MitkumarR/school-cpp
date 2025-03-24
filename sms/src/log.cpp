#include <iostream>

#include "../include/log.h"
#include "../include/details.h"
#include "../include/info.h"
#include "../include/entry.h"
#include "../include/grades.h"
#include "../include/attendance.h"
#include "../include/student.h"

void log()
{
	int menuOption;

	std::cout << "\n\t===== School Management System =====" << std::endl;
	

	std::cout << "1. Show Student Details" << std::endl;
	std::cout << "2. Show Student Information" << std::endl;
	std::cout << "3. Student's Entry" << std::endl;
	std::cout << "4. Enter Student's Grades" << std::endl;
	std::cout << "5. Enter Student's Attendance" << std::endl;

menu:
	std::cout << "choice : ";
	std::cin >> menuOption;

	// Handle invalid input
	if (std::cin.fail()) 
	{
		std::cin.clear();                      // Clear the error state
		std::cin.ignore(INT_MAX, '\n');        // Discard invalid input
		std::cout << "Invalid input. Please enter a valid number.\n";
		goto menu;                             // Go back to the menu
	}

	try
	{
		
		switch (menuOption)
		{
	
		case 1: studentDetails();
			break;	
		case 2: studentInfo();
			break;	
		case 3: studentEntry();
			break;
		case 4: enterGrades();
			break;
		case 5: enterAttendance();
			break;
	
		default: 
			std::cout << "Please select valid option ! ";
			goto menu;
	
			break;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
	}
}