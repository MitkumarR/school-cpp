### Student Info System

This project is a simple C++ application for managing student information, including student details, courses, exam grades, and attendance. It uses SQLite as the database to store and retrieve data, and it is developed using Visual Studio.

### Features

- **Student Information**: View details like registration number, name, branch, semester, email, date of birth, and mobile number.
- **Courses**: Display courses a student is enrolled in based on their semester.
- **Grades**: Manage and view exam results, including exam code, course code, grades, and credits.
- **Attendance**: Track attendance for each course, including total classes, presents, absents, and percentage.

### Development Environment
- **Visual Studio**: This project is developed using Visual Studio (recommended: Visual Studio 2019 or later with C++ workload installed).
- **C++ Compiler**: Ensure you have a C++17 compatible compiler (Visual Studio includes this by default).
- **Git**: For cloning the vcpkg repository.

### Dependencies
This project uses the following libraries:
- **SQLite3**: For database operations.
  - **Header File**: `sqlite3.h`
  - **Library File**: `sqlite3.lib` (Windows) or `libsqlite3.a` (Linux/Mac)

### Installing SQLite3
**Using vcpkg**:
   - vcpkg will automatically download and build SQLite3 for your platform.
   - Follow the vcpkg setup instructions below to install SQLite3.

### Place SQLite3 Header (If Not Using vcpkg)
If you manually installed SQLite3, ensure `sqlite3.h` is placed in the `include/` directory of your project:
```
StudentManagementSystem/include/sqlite3.h
```

### In Visual Studio
1. Open the solution in Visual Studio.
2. Set the build configuration to `Debug` or `Release` and the platform to `x64` (or `x86` if you installed 32-bit SQLite).
3. Build the solution: Build > Build Solution (or press `F5` to build and run).
4. The program will create an `sms.db` file in the project directory to store the database.

### Troubleshooting
- **SQLite3 Not Found**:
  - Ensure `sqlite3.h` is in the `include/` directory.
  - If using vcpkg, verify the integration step was successful.
  - If manually installed, ensure `sqlite3.lib` is linked correctly.
- **Linker Errors**:
  - Ensure there is only one `main` function in your project (in `main.cpp`).
  - Check that all source files are correctly added to the project.
- **Database Errors**:
  - Ensure the program has write permissions to create `sms.db` in the project directory.

### Contributing
Feel free to fork this repository, make improvements, and submit pull requests. For major changes, please open an issue first to discuss the proposed changes.


