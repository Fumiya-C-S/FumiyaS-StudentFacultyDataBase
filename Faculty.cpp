#include "Faculty.h"

//default constructor
Faculty::Faculty(){
    //set default parameters
    id = 0;
    name = "test";
    position = "none";
    department = "none";
    advisees = new DblList<Student*>;
}

//overloaded constructor
Faculty::Faculty(int facID, string facName, string facPos, string facDep){
    //set paramteres to passed in values
    id = facID;
    name = facName;
    position = facPos;
    department = facDep;
    advisees = new DblList<Student*>;
}

//default destructor
Faculty::~Faculty(){
    delete advisees; //delete DblList of advisees
} 

//addADvisee
void Faculty::addAdvisee(Student *student){
    advisees->insertBack(student); //insert student to back of list
}

//removeAdvisee
void Faculty::removeAdvisee(Student *student){
    advisees->removeNode(student); //remove student from advisee list
}

//printAdvisees
void Faculty::printAdvisees(){
    ListNode<Student*> *current = advisees->front; 
    while (current != nullptr){ //print all advisees
        cout << current->key->name << " " << current->key->id << ", "; 
        current = current->next; //iterate
    }
}