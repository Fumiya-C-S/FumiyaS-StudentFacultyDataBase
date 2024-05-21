#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

//Student class 
class Student{
    public:
        Student(); //default constructor
        Student(int stuID, string stuName, string stuGrade, string stuMajor, double stuGPA, int stuAdvisor); //overloaded constructor
        ~Student(); //default destructor

        //Student Class Variables
        int id; //Student ID
        string name; //Student's Name
        string grade; //Student's Grade 
        string major; //Student's Major
        double GPA; //Student's GPA
        int advisor; //Student's Advisor's ID
};

#endif