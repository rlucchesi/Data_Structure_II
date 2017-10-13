/*
 *  Assignment #3, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: ********
 */

#ifndef SET_H
#define SET_H

// header file for the class Set
// Author: G. and M. Monagan
#include <iostream>

class Set {
   public:
      // constructs the empty Set
      Set(); 
      // returns true if the Set is empty, false otherwise
      bool isEmpty() const; 
      // return the number of elements in the Set i.e. the
      // cardinality of the set
      int size() const; 
      // insert x into the Set (in ascending order)
      //  (if x is already in the Set, does nothing)
      void insert(int x); 

	  // Deletes the memory for the node with x in it.
	  void remove(int x);

      // return the union of a and b
      // note that neither the Set a nor the Set b are changed
      friend const Set operator +(const Set & a, const Set & b); 

      // return the intersection of a and b
      // note that neither the Set a nor the Set b are changed
      friend const Set operator *(const Set & a, const Set & b); 

	  // Proper subset operator
	  // Returns true if P has all the elements in Q;
      //   and Q has at least one element that is not in P.
	  friend bool operator <(const Set & a, const Set & b);

      // output a set in the form { element0 element 1  ... elementn-1 }
      friend std::ostream& operator<< (std::ostream&, const Set&);

      // copy constructor
      Set(const Set&); 
      // destructor 
      // implementation detail: return all the memory of the linked list 
      ~Set(); 
      // overloaded assignment operator so that one set can be assigned to another
      Set& operator = (const Set& rtSide); 
      
   private:
      struct Node {
         int value;
         Node* next;
      };
      // The linked list is sorted in ascending order so that the 
      // Set operations union and intersect can be done in linear time using merging. 
      //  The insert operation needs to insert in order and if x is already there, 
      // it doesn't do anything. 
      // So the list is always sorted and never has duplicates.
      Node* list;
      
      // suggested constructor:
      // constructor that takes p and sets the list to p
      // no copies of the nodes of p are made
	  Set(Node* p);

      // make a new node with the value x and the link set to p
      // return a pointer to the new node
      // we want to access cons in friend functions so make it static
      static Node * cons(int x, Node* p );


      // reverse in linear time the list pointed to by p
      // the reverse is destructive so the list returned are the
      // original nodes
      // we want to access reverse in friend functions so make it static
      static Node * reverse(Node * p);

	  // Makes a copy of a Set based on a existing one (argument).
	  Node* copyAll(const Node*);
	  
	  // Deletes the whole set.
	  Node* deleteAll();
	 } ;

#endif