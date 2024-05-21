#ifndef MAINMENU_H
#define MAINMENU_H

#include "LBBST.h"
#include "Student.h"
#include "Faculty.h"
#include <iostream>
#include <exception>
#include <fstream>
using namespace std;

//MainMenu class
class MainMenu{

    public:
        MainMenu(); //default constructor
        ~MainMenu(); //default destructor

        //core functions
        void mainMenuPrompt(); //prints out options

        //functions from prompt
        void printStudents(TreeNode<Student*> *root); //prints all students
        void printFaculty(TreeNode<Faculty*> *root); //prints all faculty
        void printSpecificStudent(int studentID); //prints specific student given ID
        void printSpecificFaculty(int facultyID); //prints specific faculty given ID 
        void deleteSpecificStudent(int studentID); //deletes specific student given ID
        void deleteSpecificFaculty(int facultyID); //deletes specific faculty given ID
        void addStudent(); //adds a student
        void addFaculty(); //adds a faculty
        void changeStudentAdvisor(int studentID, int facutlyID); //changes a student's advisor
        void removeAdvisee(int studentID, int facultyID); //removes an advisees from faculty

        void checkAdvisor(TreeNode<Student*> *root, int facultyID); //check if student still has advisor (after faculty deletion)
        void runLog(); //prints all student and faculty into text file
        void printToFileStudent(TreeNode<Student*> *root, ofstream& outputFile); //prints all students to file
        void printToFileFaculty(TreeNode<Faculty*> *root, ofstream& outputFile); //prints all faculty to file


    private:
        LBBST<Student*> *studentBST; //Tree storing all students
        LBBST<Faculty*> *facultyBST; //Tree sotring all faculty

        Student *foundStudent;

        //user inputted variables
        int userStudentID; 
        int userFacultyID;
        int userNum;

        bool exit; //if program should stop or not

        //user Input Student Info
        int studentID;
        string name;
        string grade;
        string major;
        double GPA;
        int advisor;

        //user Input Faculty Info
        int facultyID;
        string facName;
        string position;
        string department;

};

#endif