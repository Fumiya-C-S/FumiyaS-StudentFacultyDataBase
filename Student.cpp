#include "Student.h"

//default constructor
Student::Student(){
    //Default student parameters
    id = 0;
    name = "test";
    grade = "test";
    major = "none";
    GPA = 0.0;
    advisor = 0;  
}

//overloaded constructor
Student::Student(int stuID, string stuName, string stuGrade, string stuMajor, double stuGPA, int stuAdvisor){
    //assign student variables with passed in values
    id = stuID;
    name = stuName;
    grade = stuGrade;
    major = stuMajor;
    GPA = stuGPA;
    advisor = stuAdvisor;  
}

//destructor
Student::~Student(){}