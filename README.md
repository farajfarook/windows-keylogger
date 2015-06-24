# Windows Keylogger
Windows Key Logger application for educational purposes

This application will capture all your keyboard key press events and save it in a file in the background.!

**disclaimer** *This application is created with no warranty or neither I would take any responsibilities for any sort of threats imposed by any individual or a group of individuals towards anyone. This application is developed soley for educational purposes of learning how Windows C++ API works in global keyboard hooks*

##Getting started
####Steps to build
1. Clone the repository to your local PC
2. Open the solution with visual studio with C++
3. Build the project

####Steps to execute/kill

1. Get the executables from the build folder, and execute the `keylogger.exe`
2. To kill the process you have to open up the `task manager` and search the process and kill it.

##More information
Application is designed to write a file with the name `keylogger.txt` which contains all the key press done in the windows host where this application is running. This file is created along with the `exe` file which is excuted. You can change this file name from the `stdafx.h` file's line: `#define LOGFILE "keylogger.txt"`

In the debug mode application is written to write back to the log output window. 

Application is **Unicode enabled.** So if the keyboard input has some extraordinary characters those will also get logged in the file.

  - Update me with the bug as posting new issues in the github.
  - Feel free to fork the project and fix any bugs that you find.
  - have fun!
