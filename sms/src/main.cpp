#include "../include/log.h"
#include "../include/DBHandler.h"

int main() {
	
	
	DBHandler dbHandler("sms.db");

	/*std::string sql = R"(
		    CREATE TABLE Student (
		    Reg_No TEXT PRIMARY KEY,   
		    F_name TEXT NOT NULL,         
		    L_name TEXT NOT NULL,         
		    Branch TEXT NOT NULL,         
		    Semester INTEGER NOT NULL,    
		    Email TEXT UNIQUE NOT NULL,   
		    DOB DATE NOT NULL,            
		    Mo_No TEXT NOT NULL           
		);
    )";*/

	/*std::string sql = R"(
		CREATE TABLE Course (
			Course_code TEXT PRIMARY KEY,    -- Primary Key for the course
			Course_name TEXT NOT NULL,       -- Name of the course
			Credits INTEGER NOT NULL,        -- Number of credits for the course
			Course_semester INTEGER NOT NULL -- Semester in which the course is taught
		);
	)";*/

	/*std::string sql = R"(
		CREATE TABLE Attendance (
			Sr_No INTEGER PRIMARY KEY AUTOINCREMENT,  
			Total_class INTEGER NOT NULL,             
			Presents INTEGER NOT NULL,                
			Absents INTEGER NOT NULL,                 
			Course_code TEXT NOT NULL,                
			Reg_No TEXT NOT NULL,                     
			FOREIGN KEY (Course_code) REFERENCES Course(Course_code), 
			FOREIGN KEY (Reg_No) REFERENCES Student(Reg_No)           
		);
	)";*/

	//std::string sql = R"(
	//	CREATE TABLE Exam (
	//		Exam_Code TEXT PRIMARY KEY,        -- Primary Key for the exam
	//		Date DATE NOT NULL,                -- Date of the exam
	//		Grades TEXT NOT NULL,              -- Grade received (e.g., A, B, C, etc.)
	//		Exam_Credits INTEGER NOT NULL,     -- Credits assigned for the exam
	//		Course_code TEXT NOT NULL,         -- Foreign Key referencing the Course table
	//		Reg_No TEXT NOT NULL,              -- Foreign Key referencing the Student table
	//		FOREIGN KEY (Course_code) REFERENCES Course(Course_code), -- FK for Course
	//		FOREIGN KEY (Reg_No) REFERENCES Student(Reg_No)           -- FK for Student
	//	);
	//)";


	/*std::string sql = R"(
		INSERT INTO Course (Course_code, Course_name, Credits, Course_semester)
		VALUES 
		('CS001', 'Introduction to Programming', 4, 1),
		('CS002', 'Data Structures', 3, 2),
		('CS003', 'Computer Networks', 4, 3),
		('CS004', 'Database Management Systems', 3, 4),
		('CS005', 'Operating Systems', 5, 4),
		('CS006', 'Software Engineering', 3, 5),
		('CS007', 'Artificial Intelligence', 4, 5),
		('CS008', 'Machine Learning', 5, 6),
		('CS009', 'Computer Graphics', 3, 6),
		('CS010', 'Web Development', 4, 7),
		('CS011', 'Data Science', 5, 7),
		('CS012', 'Discrete Mathematics', 3, 2),
		('CS013', 'Digital Logic Design', 4, 3),
		('CS014', 'Theory of Computation', 3, 4),
		('CS015', 'Mobile App Development', 4, 5);
	)";
	*/
	/*
	if (!dbHandler.executeSQL(sql)) {
		std::cerr << "Failed to create table. Error: " << dbHandler.getErrorMessage() << std::endl;
	}
	*/

	std::string ask;

	while (true)
	{
		std::cout << "Do you want to exit ? y/n : ";
		std::cin >> ask;

		if (std::cin.fail()) {
			std::cin.clear();                      // Clear the error state
			std::cin.ignore(CHAR_MAX, '\n');        // Discard invalid input
			std::cout << "Invalid input.\n";
			continue;
		}

		if (ask == "y" || ask == "Y") break;
		else if (ask == "n" || ask == "N") log();
		else std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
	}
	
	return 0;
}