#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

/*~*~*************************
* The Node struct creates a node
* that holds the database items
* for the BSTs data:
* (pin – an integer, name – a string, gpa – a double).
~*~***************************/

#include <string>

using namespace std;

struct Node
{
	int pin;			// Students PIN
	string name;		// Students name
	double gpa;			// Students GPA
	Node *left;			// Pointer to the left node
	Node *right;		// Pointer to the right node

	// Constructor
	Node(){pin = 0; name = ""; gpa = 0.0; left = NULL; right = NULL;} 
};

/*~*~****************************
* BinarySearchTree class
~*~*****************************/
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	// Binary Search Tree Operations
	bool addNode(Node);									// Add a Node
	void deleteLeaves(Node*);							// Delete all leaf nodes
	bool deleteNode(Node&) const;						// Delete a Node *NOT DEFINED*
	bool isEmpty() const;								// Determine if tree is empty
    void clear(Node*);									// Delete all items in the tree
	void inOrderPrint(Node*); const						// Traverse the tree and print ordered results
	int getCount() const {return count;}				// Returns the count of all nodes in the BST
	Node getRoot() const {return *root;}				// Returns the root of the BST
	Node* search(Node*, string, bool&);					// Search for a node
	void printAllLikeNodes(Node*, string, bool&);		// Prints all nodes that have the same string
	void printLeaves(Node*);							// Prints the leaves of the tree


private:
	Node *root;											// Pointer to the root of the Binary Search Tree
	int count;
};

#endif