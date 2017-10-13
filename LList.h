#ifndef LLIST_H
#define LLIST_H
/* 
 *  Assignment #2, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: *********
 */

#include <iostream> // used in LList.cpp
#include <string>	// used in LList.cpp

// when we do NOT want to debug, we do #define
// #define NDEBUG
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
		char getFirst(bool&) const;

		// reverses the list, the original list is mutated 
		void reverse();

		// print the list to standard output started with a  '[' and finished 
		// with a ']' followed by an end-of-line  
		// dumps the array when NDEBUG is defined
		void print() const;
      
		// copy constructor
		LList(const LList&);

		// destructor 
		~LList(); 

		// overloaded assignment operator 
		LList& operator = (const LList& rtSide);

	private:
		static const int INITIAL_CAPACITY = 4;
		static const int END = -1;
	   	   	   
		struct Node {
			char item;	// Holds the character in the Linked List
			int next;	// Points the index of the next item of the List
		};

		Node* data;		// Pointer to the array of Nodes
		int capacity;	// Holds the current capacity of the Array
		int head;		// Index of the head of the Linked List
		int free;		// Index of the head of the Free Linked List
      
		// get the length of the list p
		int length(int p) const;

	  
		// duplicates the size of the Array holding the Linked List.
		// the function might throw bad_alloc exception; however, it will only
		// be called inside a try catch block.
		Node* duplicateSize();
	  
		// makes a copy of a linked list (with nodes in the same order)
		// based on a existing one(argument).
		void copyAll(const LList&);
	  
		// deletes the complete linked list.
		void deleteAll();
	
	  
		#ifndef NDEBUG
		// dump the array 
		void dumpNodesArray() const;
		// possibly other code
		#endif      

};
#endif
