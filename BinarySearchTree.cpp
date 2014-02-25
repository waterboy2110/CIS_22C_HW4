// CIS_22C_HW4.cpp : BinarySearchTree.cpp
/***********************
James Agua
CIS 22C Deanza Winter
Binary Search Tree
Homework 4
***********************/

#include "BinarySearchTree.h"
#include "stdafx.h"


//*************************************
// Definition of method addNode
// Use interitive mode to find a leaf node in
// a left / right fasion. 
// Allows duplicate nodes (<=).
// Pre - a new student node.
// Returns a bool if successful.
//*************************************
bool BinarySearchTree::addNode(Node studentNode)
{
	bool success = false;
	Node *Pwalk;					// Pointer to walk the tree
	Node *parent = NULL;			// Pointer to the parent node
	Node *newNode = new Node;		// Create a new node for the tree
	*newNode = studentNode;			// Strange - only sorts correctly if I make this assignment
									// but I'm making the same assignment below in the if...
	

	if(root == NULL)				// First node to be saved is always the root
	{
		root = new Node;
		*root = studentNode;
	}
	else							// Walk the tree to find the next empty node
	{
		Pwalk = root;
		while(Pwalk)
		{
			parent = Pwalk;
			if(newNode->name <= Pwalk->name)
				Pwalk = Pwalk->left;
			else
				Pwalk = Pwalk->right;
		}
		
		if(newNode->name <= parent->name)
		{
			parent->left = newNode;
			*newNode = studentNode;
		}
		else
		{
			parent->right = newNode;
			*newNode = studentNode;
		}		
	}
	count++;
	return success;
}

// Definition of method search
// Use recrusion to find a node
// in a BST.
// Pre - The root of the tree
// and the target string and
// bool for success.
// Post - the node containing 
// the target.
Node* BinarySearchTree::search(Node *rootPtr, string student, bool& success)
{
	Node *targetNode;

	if(rootPtr == NULL)						// Node not found in root
		return NULL;
	
	if (rootPtr->name == student)			// Node found
	{
		return rootPtr;
		success = true;
	}

	else
	{
		targetNode = search(rootPtr->left, student, success);
		
		if(!success)						// No need to search the right tree
			targetNode = search(rootPtr->right, student, success);

		return targetNode;
	}
}

//*****************************
// Definition of function inOrderPrint.
// Recursively prints the BST in order.
// Pre - the root of the BST
// Post - sorted / printed tree
//*****************************
void BinarySearchTree::inOrderPrint(Node* root)
{
	if (root->left != NULL)
		inOrderPrint(root->left);
	cout << root->name << endl;
	if (root->right != NULL) 
		inOrderPrint(root->right);
}

//*****************************
// Definition of printAllLikeNodes
// Uses recursion to find all nodes
// that have the same target and print
// those nodes.
// Pre - A pointer to the root of the BST
// and the target string and a bool.
// Post - a printed output.
//*****************************
void BinarySearchTree::printAllLikeNodes(Node* rootPtr, string studentName, bool& success)
{
	success = false;

	if(rootPtr->left != NULL)
		printAllLikeNodes(rootPtr->left, studentName, success);
	if(rootPtr->name == studentName)
	{
		cout << "Student: " << rootPtr->pin << " " << rootPtr->name << endl;
		success = true;
	}
	if(rootPtr->right !=NULL)
		printAllLikeNodes(rootPtr->right, studentName, success);
}

//**************************************************
// Definition of fuction printLeaves
// Uses recrusion to find and print the leaves in 
// the tree.
// Pre - A pointer to the BST
// Post - The leaves of the tree printed.
//**************************************************
void BinarySearchTree::printLeaves(Node *rootPtr)
{
	if(rootPtr->left != NULL)
		printLeaves(rootPtr->left);
	if(rootPtr->left == NULL && rootPtr->right == NULL)
		cout << "Student: " << rootPtr->pin << " " << rootPtr->name << endl;
	if(rootPtr->right !=NULL)
		printLeaves(rootPtr->right);
}

//******************************
// Definition of funciton deleteLeaves
// Removes all leaves whose pointer (L / R)
// are null.
// Pre - A pointer to the root of the BST
// Post - All leaf nodes are deleted.
// TODO: use an iteritve approach to deleting the nodes
// unless the lessons show a good way. 
// The delete of a node must first set it's parent's L/R to null then delete the node
// A pWalk / parent solution may work.
//******************************
void BinarySearchTree::deleteLeaves(Node* rootPtr)
{
	if(rootPtr->left != NULL)
		deleteLeaves(rootPtr->left);

	if(rootPtr->left == NULL && rootPtr->right == NULL)
	{
		cout << "Deleting node: " << rootPtr->name << endl;
		// getting NPE when deleting. Should work
		//delete &rootPtr->name;
		//delete &rootPtr->gpa;
		//delete &rootPtr->pin;
		//delete &rootPtr;
	}

	if(rootPtr->right !=NULL)
		deleteLeaves(rootPtr->right);
}


//******************************
// Definition of function isEmpty
// Tests to see if root is null
// Pre - nothing
// Post - true if root is NULL
//******************************
bool BinarySearchTree::isEmpty() const
{
	if(root == NULL)
		return true;
}


//*****************************
// Constructor
//*****************************
BinarySearchTree::BinarySearchTree()
{
	root = NULL;
	count = 0;
}

// Definition of deleteTree.
// Deletes all the nodes of the tree
// in a post order traversal (L / R / root)
// Pre - A pointer to the root of the tree
// Post - tree is deleted
// TODO: This is pretty much out of the book
// and should work. 
void BinarySearchTree::clear(Node* rootPtr)
{
	if(rootPtr != NULL)
	{
		clear(rootPtr->left);
		clear(rootPtr->right);
		delete rootPtr;
	}
}

//*****************************
// Destructor
//*****************************
BinarySearchTree::~BinarySearchTree()
{
	cout << "DEBUG: in the destructor\n";

	Node *rootPtr = this->root;
	clear(rootPtr);
	
	if(isEmpty())
		cout << "Tree has been deleted.\n";
}
