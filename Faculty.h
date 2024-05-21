#ifndef FACULTY_H
#define FACULTY_H

#include "DblList.h"
#include "Student.h"
#include "LBBST.h"
#include <iostream>
using namespace std;

//Faculty class
class Faculty{
    public:
        Faculty(); //default constructor
        Faculty(int facID, string facName, string facPos, string facDep); //overloaded constructor
        ~Faculty(); //default destructor

        //Faculty Core Variables
        int id; //Faculty's ID number
        string name; //Faculty's name
        string position; //Faculty's position
        string department; //Faculty's department
        DblList<Student*> *advisees; //Faculty's advisees

        //Core Functions
        void addAdvisee(Student *student); //add advisee to list
        void removeAdvisee(Student *student); //remove advisee from list
        void printAdvisees(); //print all advisees

};

#endif