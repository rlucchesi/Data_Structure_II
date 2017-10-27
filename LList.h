/*
 *  Assignment #1, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: 100273456
 */

#ifndef LLIST_H
#define LLIST_H

#include <iostream> // used in LList.cpp
#include <string>	// used in LList.cpp

// when we do NOT want to debug, we do #define
//#define NDEBUG
// we comment out #define NDEBUG when we do not want debug statements

class  LList {
public:
	// build a list
	LList();
	// determine if the list is empty
	bool isEmpty() const;
	// give length of list
	int length() const;
	// insert ch at the beginning (at the front) of the linked list
	// return true if successful, false otherwise
	bool cons(char ch);
	// append ch to the end of the linked list
	// return true if successful, false otherwise
	bool append(char ch);
	// delete the first occurence of ch in the list 
	// if the deletion happens, return true,  false otherwise
	bool remove(char ch);
	// search ch in the list, return true if found, false otherwise
	bool found(char ch) const;
	// if the list is empty,  getFirst is set to false and the character '\0' 
	// is returned, otherwise it returns the first character of the list and 
	// hasFirst is set to true
	char getFirst(bool& hasFirst) const;
	// reverses the list, the original list is mutated 
	void reverse();
	// print the list to standard output started with a  '[' and finished 
	// with a ']' followed by an end-of-line  
	void print() const;


	// copy constructor
	LList(const LList&);
	// destructor 
	~LList();
	// overloaded assignment operator 
	LList& operator = (const LList& rtSide);

	/*
	 * Iterative Methods
	 */
	bool consI(char);
	bool appendI(char);
	bool removeI(char);
	bool foundI(char) const;

private:
	struct Node {
		char item;
		Node* next;
	};

	// pointer to the linked list
	Node* head;

	// for the assignment, you are NOT allowed to have a tail pointer
	// i.e. one that points to the last node of the list

	// get the length of the list p
	static int length(Node *p);
   
	// Inserts a character at the beginning (at the front)
	// of the Linked List and returns a pointer to a Node
	static Node* cons(char, Node*);
   
	// Appends a character to the end of the Linked List
	// and returns TRUE if successful, FALSE otherwise
	static Node* append(char, Node*);

	// A helper function associated with the recursive function LList::remove(char)
	bool remove(char, Node*);

	// A helper function associated with the recursive function LList::found(char)
	bool found(char, Node*) const;

	// A recursive function that deletes the complete linked list
	Node* deleteAll(Node*);

	// A recursive function that copies the complete linked list (making a copy with nodes in the same order)
	Node* copyAll(Node*);

	/*
	* Iterative Methods
	*/
	Node* deleteAllI(Node*);
	Node* copyAllI(Node*);
};
#endif
