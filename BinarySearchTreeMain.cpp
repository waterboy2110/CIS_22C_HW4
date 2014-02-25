// CIS_22C_HW4.cpp : main project file.
/***********************
James Agua
CIS 22C Deanza Winter
Binary Search Tree
Homework 4
***********************/

#include "stdafx.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace System;

// Constants for the menu choices
const char SEARCH_BY_NAME				= 'A',	// Search the tree by student name
           PRINT_SORTED					= 'B',	// Print the list sorted by student name
		   PRINT_LEVEL					= 'C',	// Print by level (queue)
		   PRINT_TREE_LIST				= 'D',	// Print the tree as an indented list
		   PRINT_LEAVES					= 'E',	// Print the leaves of the tree
		   DELETE_LEAF_NODES			= 'F',	// Delete the leaves in the tree
		   SHOW_MENU					= 'M',	// Display this menu
           QUIT_CHOICE					= 'Q';	// End the program

// Menu Display
const string MENU = 
	"A\tSearch the tree by student name.\n"
	"B\tPrint the list sorted by student name.\n"
	"C\tPrint the tree by level.\n"
	"D\tPrint the tree as an indented list.\n"
	"E\tPrint the leaves of the tree.\n"
	"F\tDelete the leaves of the tree.\n"
	"M\tThis menu\n"
	"Q\tEnd the program\n\n";

// Function Prototypes
string getUserChoice();									// Menu choices
void printMenu();										// Menu options
bool processFile(BinarySearchTree *);					// Open and process the input file
string removeTrailingWhiteSpace(string);				// Clean up student name string of trailing junk
void printSortedManager(BinarySearchTree *);			// Manage the sorted print
void searchManager(BinarySearchTree *);					// Get users input to search the tree
void printLeavesManager(BinarySearchTree *);			// Interface for the printLeaves function
void deleteLeavesManager(BinarySearchTree *);			// Interface for the delete leaves function

int main(array<System::String ^> ^args)
{
   string choice;			// hold a menu choice
   bool success = false;	// User menu success
   bool status = false;		// File read status


   // Define a pointer to a BinarySearchTree object and allocate.
   BinarySearchTree *ptrBinSearchTree = new BinarySearchTree;
   
   // Add the file data to the node
   if(!processFile(ptrBinSearchTree))
	   return 1;
   
   cout << "Type M for the menu\n";
   
    while (!success)
    {
		choice = getUserChoice(); // will need the string to carry the args
        switch (toupper(choice[0]))
        {
           case SEARCH_BY_NAME:
                searchManager(ptrBinSearchTree);
                break;
           case PRINT_SORTED:
                printSortedManager(ptrBinSearchTree);
				break;
		   case PRINT_LEVEL:
			    cout << "Not Implemented\n";
				break;
		   case PRINT_TREE_LIST:
			   cout << "Not Implemented\n";
			   break;
		   case PRINT_LEAVES:
			   printLeavesManager(ptrBinSearchTree);
			   break;
		   case DELETE_LEAF_NODES:
			   deleteLeavesManager(ptrBinSearchTree);
			   break;
		   case SHOW_MENU:
			   cout << MENU;
			   break;
		   case QUIT_CHOICE:
			  success = true;
			  break;
		   default:
			  cout << "Type M for the menu.\n";
			  status = false;
        }
    }

   delete ptrBinSearchTree;
   return 0;
}

/**~*~*
   This function takes input from the user.
   If the input is not valid (a valid menu choice) it
   prompts the user to type H for help until a vailid input
   is entered.
*~**/
string getUserChoice()
{
	cout << ">";
    string userChoice;
    bool success;
	success = cin >> userChoice;
    cin.clear();			// to clear the error flag
	cin.ignore(80, '\n');	// to discard the unwanted input from the input buffer
    return userChoice;
}

//*************************
// Definition of printMenu
// Prints the choices available
// for the menu.
//*************************
void printMenu()
{
	cout << "\nHelp Menu\n" << SHOW_MENU;
}

//**************************************************
// Defintion of printSortedManager
// Calls inOrderPrint and passes in the root of the
// tree.
// Pre - the BST
// Post - void
//**************************************************
void printSortedManager(BinarySearchTree *tree)
{
	Node rootPtr = tree->getRoot();
	tree->inOrderPrint(&rootPtr);
}

//**************************************************
// Definition of searchManager
// Searches the BST for nodes by name.
// Prints all names found (duplicates)
// Pre - A pointer to the BST
// Post - Prints to console nodes name attribute
//**************************************************
void searchManager(BinarySearchTree *tree)
{
	Node root = tree->getRoot();
	Node *targetPtr = &root;
	string studentName;
	bool success;

	cout << "Student Name?\n>";
	getline(cin, studentName);

	tree->printAllLikeNodes(targetPtr, studentName, success);

	if(!success)
		cout << "Student not found.\n";
}

//**************************************************
// Definition of fuction printLeaveManager
// Calls the printLeaves function 
// Pre - A pointer to the BST
// Post - None
//**************************************************
void printLeavesManager(BinarySearchTree *tree)
{
	Node root = tree->getRoot();
	Node *rootPtr = &root;
	cout << "Leaf nodes:\n";
	tree->printLeaves(rootPtr);
}

//*************************************************
// Definition of functon deleteLeavesManager
// Calls the deleteLeaves funtion.
// Pre - a pointer to the BST
// Post - None
//*************************************************
void deleteLeavesManager(BinarySearchTree *tree)
{
	Node root = tree->getRoot();
	Node *rootPtr = &root;
	tree->deleteLeaves(rootPtr);
}
//**************************************************
// Definition of function processFile.
// This function will read all the data from
// the file and call addNode to build the bin tree.
//**************************************************
bool processFile(BinarySearchTree *tree)
{
   ifstream inFile;
   string readStr;
   string fileName;
   bool empty = true;
   fileName = "gpa.txt";
   Node node;

// Open file to read, if couldn't open, display error
   // and exit with false
   inFile.open(fileName);
   if (!inFile)
   {
      cout << "Error opening " << fileName << "!\n";
      return false;
   }
	// Process each string in the file beginnging with students PIN
  while (getline(inFile, readStr, ' '))
  {
	   node.pin = atoi(readStr.c_str());		// Finish processing the students PIN

	   getline(inFile, readStr, ';');			// Process the students name
	   node.name = removeTrailingWhiteSpace(readStr);

	   getline(inFile, readStr);				// Process the students gpa
	   node.gpa = atof(readStr.c_str());

	   cout << "DEBUG node data: " << node.pin << " " << node.name << " " << node.gpa << endl;
	   
	   tree->addNode(node);						// Add the node to the tree
	   empty = false;
   }

   inFile.close();
 
   if (empty)
      return false;

   return true;
}

//**************************************************
// Definition of function removeTrailingWhiteSpace.
// This function removes trailing white spaces at
// the back of the string, str, and returns the new
// string. Removes trailing tabs, line feeds,
// spaces, and carriage returns.
//**************************************************
string removeTrailingWhiteSpace(string str)
{
   int i = str.length() - 1;  // zero based
   while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ' || str[i] == '\r')
   {
      str.erase(i, 1);
      i--;
   }
   return str;
}