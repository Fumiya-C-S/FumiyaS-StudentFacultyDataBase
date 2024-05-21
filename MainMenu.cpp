#include "MainMenu.h"

//default constructor
MainMenu::MainMenu(){
    //initialize student and faculty LBBST
    studentBST = new LBBST<Student*>;
    facultyBST = new LBBST<Faculty*>;
    exit = true;
}

//default destructor
MainMenu::~MainMenu(){
    //garbage collect student and faculty LBBST 
    delete studentBST;
    delete facultyBST;
}

//MainMenuPrompt Function
void MainMenu::mainMenuPrompt(){

    //keep printing until user says exit
    while(exit){
        //Print list of all possible actions
        cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
        cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
        cout << "3. Find and display student information given the student id" << endl;
        cout << "4. Find and display faculty information given the faculty id" << endl;
        cout << "5. Add a new student" << endl;
        cout << "6. Delete a student given the id" << endl;
        cout << "7. Add a new faculty member" << endl;
        cout << "8. Delete a faculty member given the id." << endl;
        cout << "9. Change a student’s advisor given the student id and the new faculty id." << endl;
        cout << "10. Remove an advisee from a faculty member given the ids" << endl;
        cout << "11. Exit" << endl;

        cout << "What would you like to do? (1-11): ";
        cin >> userNum;
        cout << endl;

        //switch statement for whatever user wants to do 
        switch(userNum){
            case 1: //Print All Student
                cout << "Printing All Students" << endl;
                printStudents(studentBST->root);
                cout << endl;
                break; 
            case 2: //Print All Faculty
                cout << "Printing All Faculty" << endl;
                printFaculty(facultyBST->root);
                cout << endl;
                break;
            case 3: //Print Specific Student
                cout << "Which student would you like to display? ";
                cin >> userStudentID; 
                printSpecificStudent(userStudentID);
                break;
            case 4: //Print Specific Faculty
                cout << "Which faculty would you like to display? ";
                cin >> userFacultyID; 
                printSpecificFaculty(userFacultyID);
                break;
            case 5: //Add Student to LBBST
                addStudent();
                cout << endl;
                break;
            case 6: //Delete Student from LBBST
                cout << "Enter Student ID you want to delete: ";
                cin >> userStudentID;
                deleteSpecificStudent(userStudentID);
                break;
            case 7: //Add Faculty to LBBST
                addFaculty();
                cout << endl;
                break;
            case 8: //Delete Faculty from LBBST
                cout << "Enter Faculty ID you want to delete: ";
                cin >> userFacultyID;
                deleteSpecificFaculty(userFacultyID);
                break;
            case 9: //Change Student's Advisor
                cout << "Enter the Student ID to change their Advisor: ";
                cin >> userStudentID;
                cout << "Enter the Faculty ID to switch to: ";
                cin >> userFacultyID;
                changeStudentAdvisor(userStudentID, userFacultyID);
                break;
            case 10: //Delete Advisee from Faculty
                cout << "Enter the Faculty ID to remove an advisee: ";
                cin >> userFacultyID;
                cout << "Enter the Student ID to delete: ";
                cin >> userStudentID;
                removeAdvisee(userStudentID, userFacultyID);
                break;
            case 11: //Exit the program
                cout << "Exiting" << endl;
                runLog();
                exit = false;
                break;
            default: //If user inputs number that is not 1-11
                cout << "Invalid Number Inputted, Please Try Again" << endl;
                break;
        }

    }
}

//printStudents function
void MainMenu::printStudents(TreeNode<Student*> *root){
    if(root == NULL){ //if node is empty return
        return;
    }

    printStudents(root->left); //recusrively call print on left subtree
    //print student and their info (inorder)
    cout << "Student ID: " << root->key->id << " Name: " << root->key->name << " Major: " << root->key->major << " Grade: " << root->key->grade << " GPA: " << root->key->GPA << " Advisor: " << root->key->advisor << endl;
    printStudents(root->right); //recusrivly call print on right subtree
}

//printFaculty function
void MainMenu::printFaculty(TreeNode<Faculty*> *root){
    if(root == NULL){ //in node is empty return
        return;
    }

    printFaculty(root->left); //recusrive call on left subtree
    //print Faculty and their info
    cout << "Faculty ID: " << root->key->id << " Name: " << root->key->name << " Position: " << root->key->position << " Department: " << root->key->department << endl; 
    //print the Faculty's Advisees
    cout << root->key->name << "'s Advisees: "; 
    root->key->printAdvisees();
    cout << endl;
    printFaculty(root->right); //recursive call on right subtree
}

//printSpecificStudent function
void MainMenu::printSpecificStudent(int studentID){
    TreeNode<Student*> *current = studentBST->root;
    while(current->key->id != studentID){ //iterate through tree
        if(studentID < current->key->id){
            current = current->left;
        } else {
            current = current->right;
        }

        if(current == NULL){ //if student is not found
            cout << "That Student Does Not Exist." << endl;
            return;
        }
    }
    //print the student with the given specific ID
    cout << "Student ID: " << current->key->id << " Name: " << current->key->name << " Major: " << current->key->major << " Grade: " << current->key->grade << " GPA: " << current->key->GPA << " Advisor: " << current->key->advisor << endl;
    cout << endl;
    delete current;
}

//printSpecificFaculty function
void MainMenu::printSpecificFaculty(int facultyID){
    TreeNode<Faculty*> *current = facultyBST->root;
    while(current->key->id != facultyID){ //iterate through the tree
        if(facultyID < current->key->id){ 
            current = current->left;
        } else {
            current = current->right;
        }

        if(current == NULL){ //if student not found
            cout << "That Faculty Member Does Not Exist." << endl;
            return;
        }
    }
    //print the faculty with the given specific ID
    cout << "Faculty ID: " << current->key->id << " Name: " << current->key->name << " Position: " << current->key->position << " Department: " << current->key->department << endl;
    cout << current->key->name << "'s Advisees: "; 
    current->key->printAdvisees();
    cout << endl;
    delete current;
}

//Add Student function
void MainMenu::addStudent(){
    if (facultyBST->getSize() == 0){ //if there is no faculty, ask user to create faculty member first
        cout << "Please Create a Faculty Member First" << endl;
        return;
    }

    //Obtain the new student's information
    cout << "Adding a new student to database, please provided the necessary information: " << endl;
    cout << "What is the student's ID? ";
    cin.ignore();
    cin >> studentID;
    cin.ignore();
    cout << "What is the student's name? ";
    getline(cin, name);
    cout << "What is the student major? ";
    getline(cin, major);
    cout << "What is the student grade? ";
    getline(cin, grade);
    cout << "What is the student GPA? ";
    cin >> GPA;
    cout << "Who is the student's advisor (Faculty ID)? " << endl;;
    cout << "List of Available Advisors: " << endl;
    printFaculty(facultyBST->root);
    cin >> advisor;
    while (true){ //make sure the inputted Advisor is an advisor that is already registered in the system
        if (facultyBST->containsID(advisor)){
            break;
        }
        cout << "Advisor does not exist." << endl;
        cin >> advisor;
    }

    Student *newStudent = new Student(studentID, name, major, grade, GPA, advisor); //create new student object
    TreeNode<Faculty*> *current = facultyBST->root;
    while(current->key->id != facultyID){ //look for advisor node
        if(facultyID < current->key->id){
            current = current->left;
        } else {
            current = current->right;
        } 
    }
    current->key->advisees->insertBack(newStudent); //insert new student as advisee
    studentBST->insert(newStudent); //insert student into tree
    cout << "New Student Added" << endl;
}

//deleteSpecificStudent function
void MainMenu::deleteSpecificStudent(int studentID){

    if (studentBST->isEmpty()) { //if Tree is empty
        cout << "The student database is empty." << endl;
        return;
    }

    TreeNode<Student*> *current = studentBST->root;
    TreeNode<Student*> *parent = nullptr;

    while (current != nullptr && current->key->id != studentID) { //iterate through the student tree
        parent = current;
        if (studentID < current->key->id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) { //if student not found
        cout << "A student with ID: " << studentID << " does not exist." << endl;
        return;
    }

    //iterate through the faculty tree
    TreeNode<Faculty*> *facCurr = facultyBST->root;
    TreeNode<Faculty*> *facParent = nullptr;
    while (facCurr != nullptr && facCurr->key->id != current->key->advisor) {
        facParent = facCurr;
        if (current->key->advisor < current->key->id) {
            facCurr = facCurr->left;
        } else {
            facCurr = facCurr->right;
        }
    }
    
    //remove Student from Advisee list
    facCurr->key->removeAdvisee(current->key);

    //delete Node from tree
    // Case 1: Node to be deleted has no children
    if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {
            studentBST->root = nullptr; // Update root if current is the root
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
    }
    // Case 2: Node to be deleted has one child
    else if (current->left == nullptr) {
        if (parent == nullptr) {
            studentBST->root = current->right; // Update root if current is the root
        } else if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        delete current;
    } else if (current->right == nullptr) {
        if (parent == nullptr) {
            studentBST->root = current->left; // Update root if current is the root
        } else if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        delete current;
    }
    // Case 3: Node to be deleted has two children
    else {
        TreeNode<Student*> *successor = studentBST->getSuccessor(current);
        if (parent == nullptr) {
            studentBST->root = successor; // Update root if current is the root
        } else if (parent->left == current) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = current->left;
        delete current;
    }

    //Garbage Collection
    delete facCurr;
    delete facParent;
    delete parent;
}

//delete specific Faculty function
void MainMenu::deleteSpecificFaculty(int facultyID){
    if (facultyBST->getSize() == 1 && studentBST->getSize() > 0){ //if there is a student registered, and only 1 faculty member, you can't delete 
        cout << "If this advisor is deleted, student(s) will not have an advisor, please create another faculty member before deleting." << endl;
        return;
    }

    if (facultyBST->isEmpty()) { //if facutly tree is empty
        cout << "The faculty database is empty." << endl;
        return;
    }

    TreeNode<Faculty*> *current = facultyBST->root;
    TreeNode<Faculty*> *parent = nullptr;
    //iterate through the faculty bst to look for faculty with given id
    while (current != nullptr && current->key->id != facultyID) {
        parent = current;
        if (facultyID < current->key->id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) { //if faculty not found
        cout << "A faculty with ID: " << facultyID << " does not exist." << endl;
        return;
    }

    //iterate through student tree
    TreeNode<Student*> *stuCurrent = studentBST->root;
    if(stuCurrent->key->advisor == facultyID){ //if the current student has the faculty member that is being deleted as their advisor
        cout << "You Must Change " << stuCurrent->key->name << " (" << stuCurrent->key->id << ")'s advisor: "; //you must change their advisro
        int newAdvisor;
        cin >> newAdvisor;
        while(true){ //reask for advisor until they enter a valid number
            if (facultyBST->containsID(newAdvisor)){
                break;
            } else {
                cout << "Invalid Faculty, please reenter: ";
                cin >> newAdvisor;
            }
        }
        stuCurrent->key->advisor = newAdvisor;
    }

    //delete node
    // Case 1: Node to be deleted has no children
    if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {
            facultyBST->root = nullptr; // Update root if current is the root
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
    }
    // Case 2: Node to be deleted has one child
    else if (current->left == nullptr) {
        if (parent == nullptr) {
            facultyBST->root = current->right; // Update root if current is the root
        } else if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        delete current;
    } else if (current->right == nullptr) {
        if (parent == nullptr) {
            facultyBST->root = current->left; // Update root if current is the root
        } else if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        delete current;
    }
    // Case 3: Node to be deleted has two children
    else {
        TreeNode<Faculty*> *successor = facultyBST->getSuccessor(current);
        if (parent == nullptr) {
            facultyBST->root = successor; // Update root if current is the root
        } else if (parent->left == current) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = current->left;
        delete current;
    }
}

//add faculty function
void MainMenu::addFaculty(){
    //ask user for necessary information
    cout << "Adding a new faculty to database, please provided the necessary information: " << endl;
    cout << "What is the faculty's ID? ";
    cin.ignore();
    cin >> facultyID;
    cin.ignore();
    cout << "What is the faculty's name? ";
    getline(cin, facName);
    cout << "What is the faculty's position? ";
    getline(cin, position);
    cout << "What is the faculty's department? ";
    getline(cin, department);

    //Create new faculty object
    Faculty *newFaculty = new Faculty(facultyID, facName, position, department);
    facultyBST->insert(newFaculty); //insert faculty into faculty BST
    cout << "New Faculty Added" << endl;
}

//changeStudentAdvisor function
void MainMenu::changeStudentAdvisor(int studentID, int facultyID){
    if (studentBST->containsID(studentID) && facultyBST->containsID(facultyID)){ //if the inputted StudentID and FacultyID exists
        //iterate through student tree
        TreeNode<Student*> *current = studentBST->root;
        while(current->key->id != studentID){
            if(studentID < current->key->id){
                current = current->left;
            } else {
                current = current->right;
            }
        }
        int prevFacID = current->key->advisor; 
        current->key->advisor = facultyID; //change the advisor to new advisor

        //iterate through faculty tree
        TreeNode<Faculty*> *facCurrent = facultyBST->root;
        while(facCurrent->key->id != facultyID){
            if(facultyID < facCurrent->key->id){
                facCurrent = facCurrent->left;
            } else {
                facCurrent = facCurrent->right;
            }
        }
        facCurrent->key->advisees->insertBack(current->key); //add the student as a new advisee

        //iterate through faculty tree again
        facCurrent = facultyBST->root;
        while(facCurrent->key->id != prevFacID){
            if(prevFacID < facCurrent->key->id){
                facCurrent = facCurrent->left;
            } else {
                facCurrent = facCurrent->right;
            }
        }
        facCurrent->key->advisees->removeNode(current->key); //remove the old student from advisees list
 

        cout << "Changed student: " << studentID << "'s advisor to: " << facultyID << "." << endl;
    } else {
        cout << "Entered Student ID or Faculty ID does not exist." << endl;
    }
}

//remove Advisee function
void MainMenu::removeAdvisee(int studentID, int facultyID){
    if (studentBST->containsID(studentID) && facultyBST->containsID(facultyID)){ //if the studentID and facultyID exists
        //iterate through student tree
        TreeNode<Student*> *stuCurrent = studentBST->root;
        while(stuCurrent->key->id != studentID){
            if(studentID < stuCurrent->key->id){
                stuCurrent = stuCurrent->left;
            } else {
                stuCurrent = stuCurrent->right;
            }
        }

        //iterate through faculty tree
        TreeNode<Faculty*> *facCurrent = facultyBST->root;
        while(facCurrent->key->id != facultyID){
            if(facultyID < facCurrent->key->id){
                facCurrent = facCurrent->left;
            } else {
                facCurrent = facCurrent->right;
            }
        }
        
        facCurrent->key->removeAdvisee(stuCurrent->key); //remove the student from faculty advisees list
        cout << "Removed student: " << studentID << "from " << facultyID << "'s advisee list." << endl;

        cout << "Who will the student's new advisor be? "; //ask user for student's new advisor
        cin >> userFacultyID;
        while(true){
            if (studentBST->containsID(studentID) && facultyBST->containsID(userFacultyID)){ //if studentID and facultyID both exist
                //iterate through the student tree
                TreeNode<Student*> *current = studentBST->root;
                while(current->key->id != studentID){
                    if(studentID < current->key->id){
                        current = current->left;
                    } else {
                        current = current->right;
                    }
                }
                current->key->advisor = userFacultyID; //update the student's advisor
                //iterate through faculty tree
                TreeNode<Faculty*> *facCurrent = facultyBST->root;
                while(facCurrent->key->id != userFacultyID){
                    if(userFacultyID < facCurrent->key->id){
                        facCurrent = facCurrent->left;
                    } else {
                        facCurrent = facCurrent->right;
                    }
                }
                facCurrent->key->advisees->insertBack(current->key); //add student to advisees list
                break; 
            } else { //user will keep reentering the Faculty ID until they submit a value ID
                cout << "Reenter faculty ID: ";
                cin >> userFacultyID;
            }
        }

    } else {
        cout << "Entered Student ID or Faculty ID does not exist." << endl;
    }
}

//checkAdvisor function
void MainMenu::checkAdvisor(TreeNode<Student*> *root, int facultyID){
    //iterates through all of the students and changes all the students with a specific advisor to change (due to that advisor being deleted)
    if(root->key->advisor == facultyID){ //if inputted Student has an specific advisor
        //those with that advisor must change advisor
        cout << "You Must Change " << root->key->name << " (" << root->key->id << ")'s advisor: ";
        int newAdvisor;
        cin >> newAdvisor;
        while(true){ //user will have to reeneter their new FacultyID until a valid ID
            if (facultyBST->containsID(newAdvisor)){
                break;
            } else {
                cout << "Invalid Faculty, please reenter: ";
                cin >> newAdvisor;
            }
        }
        root->key->advisor = newAdvisor;
    }
    checkAdvisor(root->left, facultyID); //recursive function on left subtree
    checkAdvisor(root->right, facultyID); //recusrive function of right subtree
}

//runLog Function
void MainMenu::runLog(){
    ofstream outputFile("runLog.txt"); //open output file stream to "runLog.txt"

    if (!outputFile.is_open()){ //if the file isn't open somehow
        cout << "File is not open" << endl;
        return;
    }

    //start printing students to text file
    outputFile << "Students: " << endl;
    TreeNode<Student*> *stuRoot = studentBST->root;
    printToFileStudent(stuRoot, outputFile); //recursive call of printing students to text file

    outputFile << endl;

    //start printing faculty to text file
    outputFile << "Faculty: " << endl;
    TreeNode<Faculty*> *facRoot = facultyBST->root;
    printToFileFaculty(facRoot, outputFile); //recusrive call of printing faculty to textfile
}

//printToFileStudent recursive function
void MainMenu::printToFileStudent(TreeNode<Student*> *stuRoot, ofstream& outputFile){
    if (stuRoot == nullptr) { //if node is NULL return
        return; 
    }
 
    printToFileStudent(stuRoot->left, outputFile); //recusrively call on left Subtree
    //print all students in ascending ID order
    outputFile << "Student ID: " << stuRoot->key->id << " Name: " << stuRoot->key->name << " Major: " << stuRoot->key->major << " Grade: " << stuRoot->key->grade << " GPA: " << stuRoot->key->GPA << " Advisor: " << stuRoot->key->advisor << endl;
    printToFileStudent(stuRoot->right, outputFile); //recursively call on right Subtree
}


void MainMenu::printToFileFaculty(TreeNode<Faculty*> *facRoot, ofstream& outputFile){
    if (facRoot == nullptr) { //if node is NULL return
        return;
    }

    printToFileFaculty(facRoot->left, outputFile); //recusrive call on left Subtree
    //print all faculty and their info ascending ID order
    outputFile << "Faculty ID: " << facRoot->key->id << " Name: " << facRoot->key->name << " Position: " << facRoot->key->position << " Department: " << facRoot->key->department << endl; 
    outputFile << facRoot->key->name << "'s Advisees: "; 
    ListNode<Student*> *current = facRoot->key->advisees->front;
    while (current != nullptr){
        outputFile << current->key->name << " " << current->key->id << ", "; 
        current = current->next;
    }
    cout << endl;
    printToFileFaculty(facRoot->right, outputFile); //recursive call on right subtree
}