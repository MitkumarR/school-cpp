#include "../include/log.h"
#include "../include/DBHandler.h"

int main() {
	
	DBHandler dbHandler("sms.db");

	std::string createTableSQL = R"(
		    CREATE TABLE Student (
		    Reg_No INTEGER PRIMARY KEY,   
		    F_name TEXT NOT NULL,         
		    L_name TEXT NOT NULL,         
		    Branch TEXT NOT NULL,         
		    Semester INTEGER NOT NULL,    
		    Email TEXT UNIQUE NOT NULL,   
		    DOB DATE NOT NULL,            
		    Mo_No TEXT NOT NULL           
		);
    )";

	if (!dbHandler.executeSQL(createTableSQL)) {
		std::cerr << "Failed to create table. Error: " << dbHandler.getErrorMessage() << std::endl;
	}

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