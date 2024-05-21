Fumiya Shinagawa 
2416455
shinagawa@chapman.edu
CPSC-350-01
Assignment 5

Lazily Balanced BST

Files:
DblList.h, Faculty.cpp, Faculty.h, LBBST.h, main.cpp, MainMenu.cpp, MainMenu.h, README.txt, runLog.txt, Student.cpp, Student.h

References:
https://www.w3schools.com/cpp/cpp_switch.asp
https://stackoverflow.com/questions/5455802/how-to-read-a-complete-line-from-the-user-using-cin

Struggles:
My initial struggles were during the making of the LBBST, implementing the lazily balanced section was a bit of a struggle to comprehend and 
to make it work, but not time consuming at all. Other than that, the Main Menu was very easily implemented, with the refernces used above 
needed for refreshers on switch statements and cin help. Other than that, the struggles with segmentation faults were solved pretty easily, 
with the issue being parameter issues and function calls. 

This application:
This application takes gives the user 11 options, 
1. Print all students and their information (sorted by ascending id #)
2. Print all faculty and their information (sorted by ascending id #)
3. Find and display student information given the student id
4. Find and display faculty information given the faculty id
5. Add a new student
6. Delete a student given the id
7. Add a new faculty member
8. Delete a faculty member given the id.
9. Change a student’s advisor given the student id and the new faculty id.
10. Remove an advisee from a faculty member given the ids
11. Exit
The user can choose any of these 11 options to print, add, delete from the student and faculty database. 
Once exited, all the students and faculty and their info is outputted into runLog.txt. Then the application closes. 
