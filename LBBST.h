#ifndef LBBST_H
#define LBBST_H

#include "Student.h"
#include "Faculty.h"
#include <iostream>
using namespace std;

//TreeNode Template Class
template <class T>
class TreeNode{

    public:
        TreeNode(); //default constructor
        TreeNode(T k); //overloaded constructor
        virtual ~TreeNode(); //default destructor

        T key; //key of TreeNode
        TreeNode<T> *left; //pointer to left node
        TreeNode<T> *right; //pointer to right node
    
    //private:
        int depthOfNode; //variable that holds the depth of this node
};

//default constructor
template <class T>
TreeNode<T>::TreeNode(){
    //set pointers to NULL
    left = NULL;
    right = NULL;
    key = NULL;
    depthOfNode = 0;
}

//overloaded constructor
template <class T>
TreeNode<T>::TreeNode(T k){
    //set pointers to NULL 
    left = NULL;
    right = NULL;
    key = k; //set key to passed in k
    depthOfNode = 0;
}

//default destructor
template <class T>
TreeNode<T>::~TreeNode(){
    //NULL out pointers
    left = NULL;
    right = NULL;
}

//LBBST implementation
template <class T>
class LBBST{

    public:
        LBBST(); //default constructor
        virtual ~LBBST(); //default destructor

        //core function
        void insert(T value); //insert node
        TreeNode<T>* contains(T value); //returns TreeNode<T> of passed in value
        bool containsID(int ID); //returns bool if passed in value is in tree
        bool deleteNode(T k); //delete node with passed in value
        TreeNode<T> *getSuccessor(TreeNode<T> *d); //gets the successor of node
        void rebalance(); //rebalances tree
        unsigned int getSize(); //returns size of tree
        void populateArray(TreeNode<T> *root, T* array); //populates array with tree nodes
        
        //other necessary functions
        void recursiveDestruction(TreeNode<T> *root); //recusrively destructs tree
        int returnMedian(int firstPos, int secondPos); //returns median of 2 values
        TreeNode<T>* recursiveConstruct(T* array, int start, int end); //recusrively constructs and returns new tree

        //helpers
        bool isEmpty();
        T* getMin();
        T* getMax();

        //printing function
        void printTree(); //aka print tree starting at the root
        void recPrint(TreeNode<T> *node, string order); //recusrive function of printing the Tree

        TreeNode<T> *root; //root node

    private:
        int leftSub; //integer of max left depth
        int rightSub; //integer of max right depth
        bool ifLeft; //bool if the entered node is on the left or right sub tree

        int currArrayPos; //integer holding current array position

        unsigned int size; //size of tree

        int parentPos; //parent position 
        int firstPos; //first position of array to find median
        int secondPos; //second position of array to find median
};

//default constructor
template <class T>
LBBST<T>::LBBST(){
    root = NULL; //creating empty tree
    leftSub = 0;
    rightSub = 0;
    size = 0;
}

//default destructor
template <class T>
LBBST<T>::~LBBST(){
    recursiveDestruction(root); //call recursivve destruct
    cout << "BST destructed" << endl;
}

//recursive destructor
template <class T>
void LBBST<T>::recursiveDestruction(TreeNode<T> *root){
    if (root == NULL){ //if empty return
        return;
    }
    recursiveDestruction(root->left); //iterate to left sub tree
    recursiveDestruction(root->right); //iterate to right sub tree
    cout << "Deleting " << root->key->id << endl; //print that the node is getting deleted
    delete root; //garbage collection
} 

//recusrive print function
template <class T>
void LBBST<T>::recPrint(TreeNode<T> *node, string order){
    if(node == NULL){ //if null return
        return;
    } 

    if (order == "pre"){ //if "pre", print in preorder
        cout << node->key->id << endl;
        recPrint(node->left, "pre");
        recPrint(node->right, "pre");
    } else if (order == "post"){ //if "post", print in postorder
        recPrint(node->left, "post");
        recPrint(node->right, "post");     
        cout << node->key->id << endl;   
    } else if (order == "in"){ //if "in", print inorder
        recPrint(node->left, "in");
        cout << node->key->id << endl;
        recPrint(node->right, "in");             
    }

}

//defauly print tree (preorder)
template <class T>
void LBBST<T>::printTree(){
    recPrint(root, "pre");
}

//isEmpty()
template <class T>
bool LBBST<T>::isEmpty(){
    return (root == NULL); //returns if empty or not
}

//getMin function
template <class T>
T* LBBST<T>::getMin(){
    if(isEmpty()){ //if empty return nothing
        return NULL;
    }

    TreeNode<T> *current = root; 
    while(current->left != NULL){ //go to the leftmost node in tree
        current = current->left;
    }

    return &(current->key); //return the node 
}

//getMax function
template <class T>
T* LBBST<T>::getMax(){
    if(isEmpty()){ //if empty return nothing
        return NULL;
    }

    TreeNode<T> *current = root;
    while(current->right != NULL){ //go to the rightmost node in tree
        current = current->right;
    }

    return &(current->key); //return the node
}

//insert function
template <class T>
void LBBST<T>::insert(T value){
    TreeNode<T> *node = new TreeNode<T>(value);

    if (isEmpty()){ //if Tree is empty
        root = node; //set inserted node to root
        size++;
    } else {
        //tree was not empty
        TreeNode<T> *current = root;
        TreeNode<T> *parent = root;
        int i = 0; //counter for depth
        
        while(true){
            parent = current; //iterate through tree
            ++i; //increase depth counter

            if(value->id < current->key->id){ //if id is less than current id
                //we go left
                current = current->left;
                if (i == 1){ //if the counter for depth at 1, this means that this ndoe is being inserted on the left sub tree
                    ifLeft = true;
                }
                if(current == NULL){
                    //we found the insertion point
                    node->depthOfNode = i; //udpate depth of node of this node
                    cout << "This node's height (left) is: " << i << "." << endl;
                    parent->left = node;
                    size++;
                    if (i > leftSub){ //if the new inserted node is the deepest, update lestSub depth
                        leftSub = i;
                    }
                    rebalance(); //rebalance if needed
                    break;
                }
            } else { //if id is larger than current id
                //we go right
                current = current->right;
                if (i == 1){ //if counter for depth at 1, this means that this node is inserted in right Subtree
                    ifLeft = false;
                }
                if(current == NULL){
                    //we found the insertion point
                    node->depthOfNode = i; //update depth of node of node
                    cout << "This node's height (right) is: " << i << "." << endl;
                    parent->right = node;
                    size++;
                    if (i > rightSub){
                        rightSub = i; //if the depth of this node is the deepest, update right subtree depth
                    }
                    rebalance(); //rebalance if needed
                    break;
                }
            }
        }
        if (ifLeft){ //updates leftSub depth to the new lowest depth
            if (i > leftSub){
                leftSub = i;
            }
        } else { //updates rightSub depth to the new lowest depth
            if (i > rightSub){
                rightSub = i;
            }
        }
    }
}

//contains function returning TreeNode
template <class T>
TreeNode<T>* LBBST<T>::contains(T value){
    if(isEmpty()){ //if empty return nullptr
        return nullptr;
    } 

    TreeNode<T> *current = root;
    while(current->key->id != value){ //iterate through the tree
        if(value < current->key->id){
            current = current->left;
        } else {
            current = current->right;
        }

        if(current == NULL){
            return NULL; //if not found return null
        }
    }
    return current; //if here, the tree contains node with passed in value, return the TreeNode
}

//deleteNode function
template <class T>
bool LBBST<T>::deleteNode(T k){
    if(isEmpty()){ //if empty return false
        return false;
    }

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    while(current->key->id != k->id){ //iterate through the tree
        parent = current;

        if(k->id < current->key->id){
            isLeft = true;
            current = current->left;
        } else {
            isLeft = false;
            current = current->right;
        }

        if(current == NULL){ //if not found then return false
            return false;
        }
    }

    //we found the node that needs to be deleted, now lets proceed delete
    
    //Case 1: No Children, It's a Leaf
    if (current->left == NULL && current->right == NULL){
        if (current == root){
            root = NULL;
        } else if (isLeft){
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } 
    //Case 2: Node Has 1 Child
    //Child on Left
    else if (current->right == NULL){
        if(current == root){
            root = current->left;
        } else if (isLeft){
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    } 
    //Child on Right
    else if (current->left == NULL){
        if(current == root){
            root = current->right;
        } else if (isLeft){
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    } 
    //Case 3: Node Has 2 Childrenf
    else {
        TreeNode<T> *successor = getSuccessor(current); //get successor of node being deleted

        if(current == root){
            root = successor;
        } else if (isLeft){
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }
    delete current;
    size--; //decrement size
    rebalance(); //rebalance if needed
    return true; //return true that node was deleted
} 

//getSuccessor function
template <class T>
TreeNode<T>* LBBST<T>::getSuccessor(TreeNode<T> *d){

    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;

    //iterate through the tree to find successor
    while(current != NULL){
        sp = successor;
        successor = current;
        current = current->left;
    }

    //we found the successor but we need to check if the successor is a descendant of the right child
    if (successor != d->right){ //update pointers to successor
         sp->left = successor->right;
         successor->right = d->right;
    }

    return successor; //return successor
}

//getSize function
template <class T>
unsigned int LBBST<T>::getSize(){
    return size; //returns size
}

//populate array function
template <class T>
void LBBST<T>::populateArray(TreeNode<T> *node, T* array){
    if (node == NULL){ //if node is null then return
        return;
    }

    populateArray(node->left, array); //recursive call on left sub tree
    array[currArrayPos] = node->key; //add node to array inorder
    currArrayPos++;
    populateArray(node->right, array); //recursive call on right sub tree

}

//rebalance function
template <class T>
void LBBST<T>::rebalance(){
    if ((leftSub == 1 && rightSub == 1) || (leftSub == 0 && rightSub == 1) || (leftSub == 1 && rightSub == 0)){ //if the left sub and right sub are both 1, or either right or left sub is at 1 and the other is at 0
        return; //return
    }

    if (leftSub * 1.5 < rightSub || rightSub * 1.5 < leftSub){ //if the left sub or right sub is 1.5 times the opposite sub tree
        cout << "RESIZING" << endl;
        cout << "Size: " << size << endl;
        T array[size]; //create new array
        currArrayPos = 0;
        populateArray(root, array); //populate the array

        //print out the array
        for (int i = 0; i < size; ++i){
            cout << array[i] << endl;
        }
        currArrayPos = 0;

        //set integers to find median
        firstPos = 0;
        secondPos = size - 1;

        cout << endl;
        cout << "NEW LBBST: " << endl;
        root = recursiveConstruct(array, firstPos, secondPos); //recursively construct the array
        return;

    }

    return;
}

//recursive construct function
template <class T>
TreeNode<T>* LBBST<T>::recursiveConstruct(T* array, int start, int end){
    if (start > end){ //if the start value is bigger than end value
        return nullptr;  //return
    }

    int medianIndex = (start + end) / 2; //get median of start and end
    TreeNode<T> *node = new TreeNode<T>(array[medianIndex]); //create new node

    //recusrive call the left subtree and construct left subtree
    node->left = recursiveConstruct(array, start, medianIndex - 1);

    //recursive call the right subtree and construct right subtree
    node->right = recursiveConstruct(array, medianIndex + 1, end);

    return node; //return the node
}

//return median
template <class T> 
int LBBST<T>::returnMedian(int firstPos, int secondPos){
    int median = (firstPos + secondPos) / 2;
    return median; //returns the median position from given 2 positions
} 

//containsID bool return version 
template <class T>
bool LBBST<T>::containsID(int ID){
    if(isEmpty()){ //if empty return false
        cout << "No Students/Faculty in Database" << endl;
        return false;
    } 

    TreeNode<T> *current = root;
    while(current->key->id != ID){ //iterate through the tree
        if(ID < current->key->id){
            current = current->left;
        } else {
            current = current->right;
        }

        if(current == NULL){
            return false; //if not found return false
        }
    }
    return true; //else return true since node with ID was found
}


#endif