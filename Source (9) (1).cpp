//******************************************************************************************//
//*****************************    END SEMESTER PROJECT              ***********************//
//******************************************************************************************//
//*****************************          AIMEN MALIK                 ***********************//
//*****************************          KAYNAT SAJID                ***********************//
//******************************************************************************************//
//******************************************************************************************//

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;
class HashTable;
int index;

class Dictionary {
public:

    string word;
    string meaning;
    string example1, example2, example3, example4, example5, example6, example7, example8, example9, example10;

    Dictionary() {} //Default Constructor

    //constructor with parameters
    Dictionary(string word, string meaning, string example1, string example2, string example3, string example4,
        string example5, string example6, string example7, string example8, string example9, string example10) {
        this->word = word;
        this->meaning = meaning;
        this->example1 = example1;
        this->example2 = example2;
        this->example3 = example3;
        this->example4 = example4;
        this->example5 = example5;
        this->example6 = example6;
        this->example7 = example7;
        this->example8 = example8;
        this->example9 = example9;
        this->example10 = example10;
    }
};

class AvlNode {
public:
    Dictionary data;
    int height;
    AvlNode* leftChild;
    AvlNode* rightChild;
};

class AvlTree {
public:
    //root points to first node of tree
    AvlNode* root = NULL;
    //loc points to logical position of data
    AvlNode* loc = NULL;
    //loc points to logical predecessor of data
    AvlNode* ploc = NULL;

    //a boolean variable to check for duplicate insertion
    bool ifexists = false;

    
    bool isEmpty() {
       // if (root == NULL) then tree is empty
     return root == NULL;
    }

    //calculates the maximun of two numbers
    int max(int a, int b) {
        if (a > b)
            return a;
        else
            return b;
    }

    //Finds the minimun value in all leftchilds of tree
    AvlNode* MinimunValueNode(AvlNode* node) {
        AvlNode* temp = node;

        //loop continues till the end of tree.
        while (temp->leftChild != NULL) {
            temp = temp->leftChild;
        }
        return temp;
    }

    //recursive function to calculate height of tree
    int CalculateHeight(AvlNode* node) {
        if (node == NULL)
            return -1;
        else return max(CalculateHeight(node->leftChild), CalculateHeight(node->rightChild)) + 1;
    }

    //calculates balance factor of node
    int BalanceFactor(AvlNode* x) {
        if (x == NULL) {
            return 0;
        }
        else
        //returns difference of height of left and right child
        return CalculateHeight(x->leftChild) - CalculateHeight(x->rightChild);
    }

    //creatign a new node and updating data
    AvlNode* NewNode(Dictionary object) {
        AvlNode* temp = new AvlNode();
        temp->data = object;
        temp->leftChild = NULL;
        temp->rightChild = NULL;
        temp->height = 1;

        return temp;
    }

    //inserting into dictionary
    AvlNode* InsertNewNode(AvlNode* x, Dictionary object) {

        if (x == NULL) {
            return NewNode(object);
        }

        if (object.word < x->data.word) {
            x->leftChild = InsertNewNode(x->leftChild, object);
        }

        //inserton at right Child
        else if (object.word > x->data.word) {
            x->rightChild = InsertNewNode(x->rightChild, object);
        }

        //inserting duplicate values
        else {
           //cout << "Duplication not allowed" << endl;
            return x;
        }

        x->height = max(CalculateHeight(x->leftChild), CalculateHeight(x->rightChild)) + 1;

        int balancefactor = BalanceFactor(x);
        // cout << "balance factor is:   " << balancefactor << endl;

        //if balance factor is 1, 0 or -1 , then it is balanced. 
        if (balancefactor == 1 || balancefactor == 0 || balancefactor == -1) {
            return x;
        }
        //else performs respective rotations
        //left heavy
        else if (balancefactor > 1) {
            if (object.word < x->leftChild->data.word) {
                return RightRotate(x);
            }
            else if (object.word > x->leftChild->data.word) {
                return LeftRightRotate(x);
            }
        }
        //right heavy
        else if (balancefactor < -1) {
            if (object.word > x->rightChild->data.word) {
                return RotateLeft(x);
            }
            else if (object.word < x->rightChild->data.word) {
                return RightLeftRotate(x);
            }

        }
    }

    // A utility function to right rotate subtree rooted with x  
    AvlNode* RightRotate(AvlNode* x) {
        //cout << "*****Rotating Right:***** " << endl;
        AvlNode* y = x->leftChild;
        x->leftChild = y->rightChild;
        y->rightChild = x;
        x->height = max(CalculateHeight(x->leftChild), CalculateHeight(x->rightChild)) + 1;
        y->height = max(CalculateHeight(y->leftChild), CalculateHeight(y->rightChild)) + 1;
        return y;
    }

    // A utility function to left rotate subtree rooted with x 
    AvlNode* RotateLeft(AvlNode* x)
    {
        //cout << "*****Rotating Left*****" << endl;
        AvlNode* y = x->rightChild;
        x->rightChild = y->leftChild;		
        y->leftChild = x;
        x->height = max(CalculateHeight(x->leftChild), CalculateHeight(x->rightChild)) + 1;
        y->height = max(CalculateHeight(y->leftChild), CalculateHeight(y->rightChild)) + 1;
        return y;
    }

    // A utility function to LeftRight rotate subtree rooted with x 
    AvlNode* LeftRightRotate(AvlNode* x)
    {
        //cout << "****Rotating LeftRight*****" << endl;
        AvlNode* y = x->leftChild;
        x->leftChild = RotateLeft(y);
        AvlNode* node = RightRotate(x);
        return node;
    }

    // A utility function to RigthLeft rotate subtree rooted with x 
    AvlNode* RightLeftRotate(AvlNode* x)
    {
        //cout << "*****Rotating RightLeft*****" << endl;
        AvlNode* y = x->rightChild;
        x->rightChild = RightRotate(y);
        return RotateLeft(x);
    }

    void Find(AvlNode* root, string word)
    {
        loc = root;
        ploc = NULL;
        //Incase tree is empty
        if (loc == NULL) {
            cout << "\n\t\t\t\t\t\t\tThis word does not exists in Dictionary." << endl;
        }
        else {
            while (loc != NULL) {
                //if word is found
                if (loc->data.word == word) {
                    break;
                }
                //if word is in leftsub tree
                else if (word < loc->data.word)
                {
                    ploc = loc;
                    Find(loc->leftChild, word);
                }
                //if word is in right child
                else if (word > loc->data.word) {
                    ploc = loc;
                    Find(loc->rightChild, word);
                }
            }
        }
    }//ends Find function

    //implements Search function to Find a word and its relative data in dictionary
    void Search(string newnode) {
        Find(root, newnode);
        
        //if loc!= NULL that means word is found, 
        //else word does not exists in our dictionary
        if (loc != NULL) {
            //prints all required data 

            if (loc->data.word.empty()) {
                loc->data.word = -1;
            }
            else
            {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Word:\n";
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t" << loc->data.word << endl;
                cout << "\t\t\t\t\t\tindex of word is   " << index << endl;
            }
            if (loc->data.meaning.empty()) {
                loc->data.meaning = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Meaning:\n";
                cout << "\n\t\t\t\t\t\t" << loc->data.meaning << endl;
            }
            if (loc->data.example1.empty()) {
                loc->data.example1 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 1:\n";
                cout << "\n\t\t\t\t\t\t" << loc->data.example1 << endl;
            }
            if (loc->data.example2.empty()) {
                loc->data.example2 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 2:\n";
                cout << "\n\t\t\t\t\t\t " << loc->data.example2 << endl;
            }
            if (loc->data.example3.empty()) {
                loc->data.example3 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 3:\n";
                cout << "\n\t\t\t\t\t\t" << loc->data.example3 << endl;
            }
            if (loc->data.example4.empty()) {
                loc->data.example4 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 4:\n";
                cout << "\n\t\t\t\t\t\t " << loc->data.example4 << endl;
            }
            if (loc->data.example5.empty()) {
                loc->data.example5 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 5:\n";
                cout << "\n\t\t\t\t\t\t" << loc->data.example5 << endl;
            }
            if (loc->data.example6.empty()) {
                loc->data.example6 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 6:\n" << endl;
                cout << "\n\t\t\t\t\t\t" << loc->data.example6 << endl;
            }
            if (loc->data.example7.empty()) {
                loc->data.example7 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 7:\n" << endl;
                cout << "\n\t\t\t\t\t\t" << loc->data.example7 << endl;
            }
            if (loc->data.example8.empty()) {
                loc->data.example8 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 8:\n" << endl;
                cout << "\n\t\t\t\t\t\t" << loc->data.example8 << endl;
            }
            if (loc->data.example9.empty()) {
                loc->data.example9 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 9:\n";
                cout << "\n\t\t\t\t\t\t" << loc->data.example9 << endl;
            }
            if (loc->data.example10.empty()) {
                loc->data.example10 = -1;
            }
            else {
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t   Example 10:\n";
                cout << "\n\t\t\t\t\t\t" << loc->data.example10 << endl;
            }
        }
    }

    //utility funtion to delete a word from dictionary
    void Deleting(string newnode) {
        Delete(root, newnode);
    }

    //utility funtion to insert data in dictionary
    void InsertNewNode(Dictionary object) {
        root = InsertNewNode(root, object);
    }

    //utility funtion to insert new word in dictionary
    void Inserting(string word) {
        addWord(root, word);
    }

    void addWord(AvlNode* x, string word) {
        int choice;
        int cont;
        string meaning;
        string example1, example2, example3, example4, example5, example6, example7, example8, example9, example10;
        
        Find(x,word);
        //if loc== NULL that means value is not found in Dictionary, ifexists = false
        //if loc!= NULL that means value is  found in Dictionary, ifexists = true
        if (loc != NULL) {
            ifexists = true;
            cout << "\t\t\t\t\tDuplication not allowed.\n\t\t\t\t\tWord already exists" << endl;\
            //if value already exists , funtion returns
            return;
        }
        else ifexists = false;
        
       

        cout << "\n\t\t\t\t\t\t\tMeaning:\n";
        cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
        cout << "\n\t\t\t\t\t\t\t\t";
        getline(cin, meaning);

        cout << "\n\t\t\t\t\t\tHow many Example do you want to insert:" << endl;
        cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
        cout << "\n\t\t\t\t\t\t\t\t";
        cin >> choice;
        string newline;
        getline(cin, newline);
        switch (choice) {
        case 1:
            cout << "\n\t\t\t\t\t\t\t   Example 1:";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            break;
        case 2:
            cout << "\n\t\t\t\t\t\t\t   Example 1:";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            cout << "\n\t\t\t\t\t\t\t   Example 2:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example2);
            break;
        case 3:
            cout << "\n\t\t\t\t\t\t\t   Example 1:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            cout << "\n\t\t\t\t\t\t\t   Example 2:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example3);
            cout << "\n\t\t\t\t\t\t\t   Example 3:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example3);
            break;
        case 4:
            cout << "\n\t\t\t\t\t\t\t   Example 1:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            cout << "\n\t\t\t\t\t\t\t   Example 2:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example2);
            cout << "\n\t\t\t\t\t\t\t   Example 3:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example3);
            cout << "\n\t\t\t\t\t\t\t   Example 4:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example4);
            break;
        case 5:
            cout << "\n\t\t\t\t\t\t\t   Example 1:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            cout << "\n\t\t\t\t\t\t\t   Example 2:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example2);
            cout << "\n\t\t\t\t\t\t\t   Example 3:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example3);
            cout << "\n\t\t\t\t\t\t\t   Example 4:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example4);
            cout << "\n\t\t\t\t\t\t\t   Example 5:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example5);
            break;
        case 6:
            cout << "\n\t\t\t\t\t\t\t   Example 1:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            cout << "\n\t\t\t\t\t\t\t   Example 2:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example2);
            cout << "\n\t\t\t\t\t\t\t   Example 3:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example3);
            cout << "\n\t\t\t\t\t\t\t   Example 4:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example4);
            cout << "\n\t\t\t\t\t\t\t   Example 5:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example5);
            cout << "\n\t\t\t\t\t\t\t   Example 6:\n";
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example6);
            break;
        case 7:
            cout << "\n\t\t\t\t\t\t\t   Example 1:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            cout << "\n\t\t\t\t\t\t\t   Example 2:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example2);
            cout << "\n\t\t\t\t\t\t\t   Example 3:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example3);
            cout << "\n\t\t\t\t\t\t\t   Example 4:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example4);
            cout << "\n\t\t\t\t\t\t\t   Example 5:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example5);
            cout << "\n\t\t\t\t\t\t\t   Example 6:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example6);
            cout << "\n\t\t\t\t\t\t\t   Example 7:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example7);
            break;
        case 8:
            cout << "\n\t\t\t\t\t\t\t   Example 1:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            cout << "\n\t\t\t\t\t\t\t   Example 2:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t";
            getline(cin, example2);
            cout << "\n\t\t\t\t\t\t\t   Example 3:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example3);
            cout << "\n\t\t\t\t\t\t\t   Example 4:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example4);
            cout << "\n\t\t\t\t\t\t\t   Example 5:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example5);
            cout << "\n\t\t\t\t\t\t\t   Example 6:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example6);
            cout << "\n\t\t\t\t\t\t\t   Example 7:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example7);
            cout << "\n\t\t\t\t\t\t\t   Example 8:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example8);
            break;
        case 9:
            cout << "\n\t\t\t\t\t\t\t   Example 1:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            cout << "\n\t\t\t\t\t\t\t   Example 2:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example2);
            cout << "\n\t\t\t\t\t\t\t   Example 3:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example3);
            cout << "\n\t\t\t\t\t\t\t   Example 4:\n";
            cout << "\n\t\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example4);
            cout << "\n\t\t\t\t\t\t\t   Example 5:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example5);
            cout << "\n\t\t\t\t\t\t\t   Example 6:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example6);
            cout << "\n\t\t\t\t\t\t\t   Example 7:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example7);
            cout << "\n\t\t\t\t\t\t\t   Example 8:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example8);
            cout << "\n\t\t\t\t\t\t\t   Example 9:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example9);
            break;
        case 10:
            cout << "\n\t\t\t\t\t\t\t   Example 1:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example1);
            cout << "\n\t\t\t\t\t\t\t   Example 2:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example2);
            cout << "\n\t\t\t\t\t\t\t   Example 3:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example3);
            cout << "\n\t\t\t\t\t\t\t   Example 4:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example4);
            cout << "\n\t\t\t\t\t\t\t   Example 5:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example5);
            cout << "\n\t\t\t\t\t\t\t   Example 6:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example6);
            cout << "\n\t\t\t\t\t\t\t   Example 7:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example7);
            cout << "\n\t\t\t\t\t\t\t   Example 8:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example8);
            cout << "\n\t\t\t\t\t\t\t   Example 9:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example9);
            cout << "\n\t\t\t\t\t\t\t   Example 10:\n";
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t";
            getline(cin, example10);
            break;
        }

        Dictionary* obj = new Dictionary(word, meaning, example1, example2, example3, example4,
            example5, example6, example7, example8, example9, example10);

        root = InsertNewNode(root, *obj);
        cout << "\n\t\t\t\t\t\t\t   Word Inserted" << endl;
    }

    void ViewTree(AvlNode* x) {
        //if tree is empty, then returns
        if (x == NULL)
            return;
        else {
            
            cout << "\nWord:\t" << x->data.word << endl;
            if (x->data.meaning.empty())
            {
                x->data.meaning = -1;
            }
            else {
                cout << "Meaning:\t" << x->data.meaning << endl;
            }
            if (x->data.example1.empty())
            {
                x->data.example1 = -1;
            }
            else {
                cout << "Example 1:\t" << x->data.example1 << endl;
            }
            if (x->data.example2.empty())
            {
                x->data.example2 = -1;
            }
            else {
                cout << "Example 2:\t " << x->data.example2 << endl;
            }
            if (x->data.example3.empty())
            {
                x->data.example3 = -1;
            }
            else {
                cout << "Example 3:\t" << x->data.example3 << endl;
            }
            if (x->data.example4.empty())
            {
                x->data.example4 = -1;
            }
            else {
                cout << "Example 4:\t " << x->data.example4 << endl;
            }
            if (x->data.example5.empty())
            {
                x->data.example5 = -1;
            }
            else {
                cout << "Example 5:\t" << x->data.example5 << endl;
            }

            if (x->data.example6.empty())
            {
                x->data.example6 = -1;
            }
            else {
                cout << "Example 6:\t" << x->data.example6 << endl;
            }
            if (x->data.example7.empty())
            {
                x->data.example7 = -1;
            }
            else {
                cout << "Example 7:\t" << x->data.example7 << endl;
            }

            if (x->data.example8.empty())
            {
                x->data.example8 = -1;
            }
            else {
                cout << "Example 8:\t" << x->data.example8 << endl;
            }
            if (x->data.example9.empty())
            {
                x->data.example9 = -1;
            }
            else {
                cout << "Example 9:\t" << x->data.example9 << endl;
            }
            if (x->data.example10.empty())
            {
                x->data.example10 = -1;
            }
            else {

                cout << "Example 10:\t" << x->data.example10 << endl;
            }

            ViewTree(x->leftChild);
            ViewTree(x->rightChild);
        }

    }

    AvlNode* Delete(AvlNode* x, string word) {

        if (x == NULL) {
            cout << "\n\t\t\t\t\t\t\tThis word does not exists in Dictionary." << endl;
            return  x;
        }

        //if value is in left subtree
        else if (word < x->data.word) {
            x->leftChild = Delete(x->leftChild, word);
        }
        //if value is in right subtree
        else if (word > x->data.word) {
            x->rightChild = Delete(x->rightChild, word);
        }
        else {

            //there are two cases.
                //case 1: node with 1 or no child
            if (x->leftChild == NULL || x->rightChild == NULL) {

                //initializing temp with one existing child
                AvlNode* temp;
                if (x->leftChild) {
                    temp = x->leftChild;
                }
                else {
                    temp = x->rightChild;
                }
                //now deleting nodes

                //no child case
                if (temp == NULL) {
                    temp = x;
                    x = NULL;
                }
                //1 child case
                else {
                    *x = *temp;
                }
                //free the temp pointer
                delete temp;
                cout << "\n\t\t\t\t\t\t\tWORD IS DELETED SUCCESSFULLY." << endl;

            }//ends case 1

            //case 2: node with 2 childs
            else {
                AvlNode* temp = MinimunValueNode(x->rightChild);
                x->data = temp->data;
                x->rightChild = Delete(x->rightChild, temp->data.word);
            }

        }//ends else

        if (x == NULL) {
            return x;
        }
        //update height
        x->height = max(CalculateHeight(x->leftChild), CalculateHeight(x->rightChild)) + 1;

        //check balance factor
        int balancefactor = BalanceFactor(x);
        //cout << "balance factor = " << balancefactor << endl;
        //there are 2 possible ways when balancefactor <-1 or >1

        //case 1:
        //left heavy
        if (balancefactor > 1) {

            //Left Left Case
            if ((BalanceFactor(x->leftChild)) >= 0) {
                return RightRotate(x);
            }
            //Left Right CAse
            else
                return LeftRightRotate(x);
        }

        //case 2
        //right heavy
        if (balancefactor < -1) {
            //right right case
            if (x->rightChild <= 0) {
                return RotateLeft(x);
            }
            //right left case
            else {
                return RightLeftRotate(x);
            }
        }
        return x;
    }//ends delete fun
  
           
        void swap(string* a, string* b)
        {
            string t = *a;
            *a = *b;
            *b = t;
        }
     
        int partition(string arr[], int low, int high)
        {
            string pivot = arr[high]; // pivot  
            int i = (low - 1); // Index of smaller element  

            for (int j = low; j <= high - 1; j++)
            {
                // If current element is smaller than the pivot  
                if (arr[j] < pivot)
                {
                    i++; // increment index of smaller element  
                    swap(&arr[i], &arr[j]);
                }
            }
            swap(&arr[i + 1], &arr[high]);
            return (i + 1);
        }

    void quickSort(string A[], int left, int right) {
        if (left < right) {
            /* pi is partitioning index, arr[p] is now
          at right place */
            int pivot = partition(A, left, right);
         // Separately sort elements before 
        // partition and after partition 
            quickSort(A, left, pivot - 1);
            quickSort(A, pivot + 1, right);
        }
    }

};//ends AvlTree class

class HashTable {
public:
    //size of our hash table
    int size = 16000;
    //array to store Dictionary words
    string* array = new string[16000];

    //this pointer stores the address of all AvlTree nodes
    AvlTree* ht;

    //constructor to initialize the array size
    HashTable() {
        ht = new AvlTree[size];
    }

    //hash function takes word and returns the index
    //wordsum=sum of each character of word.
    //index=wordSum % size of hash table
    int HashFunction(string word)
    {
        int wordSum = 0;
       for (int i = 0;i < word.length();i++)
        {
            wordSum =  wordSum + word[i];
        }
        index = wordSum % size;
        //returning absolute value of index to ignore the negative ones   
        return abs(index);
    }

    //for insert in Dictionary
    void HashInsert(string word, Dictionary obj) {
        int index = HashFunction(word);
        ht[index].InsertNewNode(obj);

    }

    //function for user to delete a word
    void HashDelete(string word) {
        int index = HashFunction(word);
        ht[index].Deleting(word);

    }
    //function for user to Search a word
    void HashSearch(string word) {
        int index = HashFunction(word);
        ht[index].Search(word);
    }
    //inserting a new word by user
    void HashInserting(string word, HashTable* HT) {
        int index = HashFunction(word);
        ht[index].Inserting(word);
    }

    //this function prints Dictionary in sorted manner
    void PrintDictionaryWords() {
        //greeting message
        cout << "\n\t\t\t\t\t*********************************************************************************" << endl;
        cout << "\n\t\t\t\t\t\t\t      Dictionary" << endl;
        cout << "\n\t\t\t\t\t*********************************************************************************" << endl;
  
            //calling quicksort function to sort the array conatining Dictionary words
            ht->quickSort(array, 0, size-1);
            cout << "after sorting" << endl;
            //printing after sorting the array
            for (int i = 0;i < size;i++) {
                if (array[i] == "")
                    continue;
                cout << array[i] << endl;
            }
            cout << endl;
    }

    void PrintAllDictionary() 
    {
        for (int i = 0;i < size;i++)
        {
            //if the root at index i is empty, it doesn't print
            if (ht[i].root == NULL) {
                continue;
            }
            ht[i].ViewTree(ht[i].root);
            cout << endl;
        }
    }//PrintAllDictionary ends

    //parser function for reading data from file
    void read() {
        
        int i = 0;
        string word;
        string meaning;
        string example1, example2, example3, example4, example5, example6, example7, example8, example9, example10;


        ifstream file("word-meaning-examples1.csv");

        char count = 0;
        string line;
        //opens file for reading
        if (file.good()) {
            cout << "\n\n\t\t\t\t\t\t\t   *****FILE IS READ SUCCESSFULLY*****" << endl;

            getline(file, line);
            while (!file.eof())
            {

                getline(file, word, ',');
                getline(file, meaning, ',');
                getline(file, example1, ',');
                getline(file, example2, ',');
                getline(file, example3, ',');
                getline(file, example4, ',');
                getline(file, example5, ',');
                getline(file, example6, ',');
                getline(file, example7, ',');
                getline(file, example8, ',');
                getline(file, example9, ',');
                getline(file, example10, '\n');

                //converting word to lower case
                std::for_each(word.begin(), word.end(), [](char& c) {

                    c = ::tolower(c);
                    });
                const char* c = word.c_str();
                
                //stores words in array to be sorted
                array[i] = word;
                i++;

                //makes an object of Dictionary class and uses constructor to initialize it with file contents
                Dictionary* obj = new Dictionary(word, meaning, example1, example2, example3, example4,
                    example5, example6, example7, example8, example9, example10);

                //inserting object in hash table.
                HashInsert(c, *obj);
            }
            file.close();
        }
        //if file fails to open
        else cout << "\n\n\t\t\t\t\t\t\t***FILE CANNOT BE OPENED.***" << endl;
    }//ends read function

};//ends hashtable class

class StackNode {
public:
    string  wordSearched;
    StackNode* next;
};

class Stack {
private:
    //size of stack
    int size;
    //pointer to access most recent stack element
    StackNode* top;
public:
    //constructor to initialize 
    Stack() {
        size = 0;
        top = NULL;
    }
    bool isEmpty() {
        return (top == NULL);
    }
    //implementing push funtion 
    void push(string word) {
        StackNode* temp = new StackNode();

        //if stack is empty, then temp points to NULL
        if (isEmpty()) {
            temp->next = NULL;
        }
        //else temp points to top
        else {
            temp->next = top;
        }
        //stores word and update top and size of stack
        temp->wordSearched = word;
        top = temp;
        size++;
    }
    //to print all Searches
    void PrintHistory() {
        cout << "\n\t\t\t\t\t*********************************************************************************" << endl;
        cout << "\n\t\t\t\t\t\t\t      SHOWING HISTORY" << endl;
        cout << "\n\t\t\t\t\t*********************************************************************************" << endl;
        cout << "\n\t\t\t\t\t\t\tUser History:" << endl;
        StackNode* temp = new StackNode();
        temp = top;
        if (isEmpty()) {
            cout << "\n\t\t\t\t\t\t\t\tNo History Found" << endl;
        }
        else {
            int i = 0;
            cout << "\n\t\t\t\t\t\t\tHistory:" << endl;
            while (temp) {
                cout << ++i << "\n\t\t\t\t\t\t\t\t. " << temp->wordSearched << endl;
                temp = temp->next;
            }
        }
    }
};//ends Stack class

void display() {
    int choice;
    cout << "\n\t\t\t\t\t *********************************************************************************" << endl;
    cout << "\n\t\t\t\t\t\t\t      WELCOME TO ONLINE Dictionary" << endl;
    cout << "\n\t\t\t\t\t *********************************************************************************" << endl;
    cout << "\n\t\t\t\t\t\t\t   ****INSTRUCTIONS ARE AS FOLLOWS****" << endl;
    cout << "\n\n\t\t\t\t\t\t1. ENTER 1 TO Search A WORD , ITS MEANING AND EXAMPLES." << endl;
    cout << "\n\t\t\t\t\t\t2. ENTER 2 TO INSERT A WORD , ITS MEANING AND EXAMPLES OT YOUR OWN CHOICE." << endl;
    cout << "\n\t\t\t\t\t\t3. ENTER 3 TO DELETE AND WORD IN A DICTONARY." << endl;
    cout << "\n\t\t\t\t\t\t4. ENTER 4 TO VIEW  YOUR HISTORY. " << endl;
    cout << "\n\t\t\t\t\t\t5. ENTER 5 TO VIEW ALL THE WORDS IN A Dictionary." << endl;
    cout << "\n\t\t\t\t\t\t6. ENTER 7 TO EXIT." << endl;
    cout << "\n\t\t\t\t\t\t7. ENTER ANY KEY TO CONTINUE." << endl;
    cout << "\n\t\t\t\t\t\t8. ENTER WORD IN ANY CASE YOU WANT TO." << endl;
    cout << "\n\t\t\t\t\t*********************************************************************************" << endl;
    cout << "\n\t\t\t\t\t\t\t\t   STARTING..." << endl;
    cout << "\n\t\t\t\t\t*********************************************************************************" << endl; 
};

int main() {

    HashTable* HT = new HashTable();

    Stack history;
    string word;
    HT->read();
    char cont = 0;
    
    display();
    while (1) {
        string line;

        int choice = 0;
        cout << "\n\n\t\t\t\t\t\t\tEnter the operation you want to perform:" << endl;
        cout << "\n\t\t\t\t\t\t\t\t1.Search\n\t\t\t\t\t\t\t\t2.Insert\n\t\t\t\t\t\t\t\t3.Delete\n\t\t\t\t\t\t\t\t4.History\n\t\t\t\t\t\t\t\t5.View Dictionary Words\n\t\t\t\t\t\t\t\t6.View All Dictionary \n\t\t\t\t\t\t\t\t7.Exit" << endl;
        cout << "\n\t\t\t\t\t\t\t\t";
        cin >>  choice;
        string newline;
        getline(cin, newline);
        switch (choice) {
        case 1:
            cout << "\n\t\t\t\t\t *********************************************************************************" << endl;
            cout << "\n\t\t\t\t\t\t\t      FEEL FREE TO Search" << endl;
            cout << "\n\t\t\t\t\t *********************************************************************************" << endl;
            cout << "\n\t\t\t\t\t\t\tEnter Word To Search:" << endl;
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t\t";
            getline(cin, word);
            std::for_each(word.begin(), word.end(), [](char& c)
                {
                    c = ::tolower(c);
                });
            HT->HashSearch(word);
            history.push(word);
            break;

        case 2:
            cout << "\n\t\t\t\t\t*********************************************************************************" << endl;
            cout << "\n\t\t\t\t\t\t\t      FEEL FREE TO INSERT" << endl;
            cout << "\n\t\t\t\t\t*********************************************************************************" << endl;
            cout << "\n\t\t\t\t\t\t\tEnter word you want to insert:" << endl;
            cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t\t\t\t\t\t";
            getline(cin, word);
            std::for_each(word.begin(), word.end(), [](char& c)
                {
                    c = ::tolower(c);
                });
            HT->HashInserting(word, HT);
            history.push(word); //push history in stack
            break;

            case 3:
                cout << "\n\t\t\t\t\t*********************************************************************************" << endl;
                cout << "\n\t\t\t\t\t\t\t      FEEL FREE TO DELETE" << endl;
                cout << "\n\t\t\t\t\t*********************************************************************************" << endl;
                cout << "\n\t\t\t\t\t\t\tEnter Word To Delete:" << endl;
                cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
                cout << "\n\t\t\t\t\t\t\t\t";
                getline(cin, word);
                std::for_each(word.begin(), word.end(), [](char& c)
                    {
                        c = ::tolower(c);
                    });
                HT->HashDelete(word);
                history.push(word); //push history in stack
               break;
 
        case 4:
            history.PrintHistory();
            break;

        case 5:
            HT->PrintDictionaryWords();
            break;

        case 6:
            HT->PrintAllDictionary();
            break;

        case 7:
            exit(0);
            break;

        default:
            cout << "\n\t\t\t\t\t\t\tInvalid choice." << endl;
            break;

        }
        cout << "\n\n\t\t\t\t\t\t\tPress any key to continue" << endl;
        cout << "\n\t\t\t\t\t------------------------------------------------------------------------------------" << endl;
        cout << "\n\t\t\t\t\t\t\t";
        cin >> cont;
    }

    return 0;
};
