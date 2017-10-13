/*
 *  Assignment #3, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: ********
 */


#include <iostream>
#include "Set.h"
// Author: G. and M. Monagan


//#define NDEBUG

// constructor 
Set::Set():list(nullptr) {
   // no body
}

Set::Set(Node* p) {
	this->list = p;
}

// Set operations
// test if the Set is empty by comparing the private variable list 
// to the nullptr
// one operation so regardless  of size of set  O(1)
// precondition:
//   p has been assigned a valid address or the nullptr
bool Set::isEmpty() const{ 
   return (list == nullptr); 
}

// return the number of elements in the Set i.e. the
// cardinality of the set
int Set::size() const {
	if (this->isEmpty()) {
		return 0;
	}
	int output = 1;
	Node* current = this->list;

	while (current->next != nullptr) {
		output++;
		current = this->list->next;
	}
	return output;
}

// insert x into the Set (in ascending order)
//  (if x is already in the Set, does nothing)
void Set::insert(int x) {
	if (this->isEmpty() || x < this->list->value) {
		this->list = cons(x, this->list);
	}
	else {
		Node* current = this->list->next;
		Node* previous = this->list;
		while (current != nullptr && current->value != x && x > current->value) {
			previous = current;
			current = current->next;
		}
		if (current == nullptr) {
			// insert at the last position
			Node* input = new Node;
			input->value = x;
			input->next = nullptr;
			previous->next = input;
		} else {
			if (current->value != x) {
				Node* input = new Node;
				input->value = x;
				input->next = current;
				previous->next = input;
			}
		}
	}
}

/*
 * Deletes the memory for the node with x in it.
 */
void Set::remove(int x) {
	if (this->isEmpty() || x < this->list->value) {
		return;
	}
	else {
		// x == first || [sec, rest] || not in list
		if (x == this->list->value) {
			Node* discard = this->list;
			this->list = this->list->next;
			delete discard;
		}
		else {
			Node* current = this->list->next;
			Node* previous = this->list;
			while (current != nullptr) {
				if (x == current->value) {
					Node* discard = current;
					previous->next = current->next;
					delete discard;
					return;
				}
				previous = current;
				current = current->next;
			}
		}
	}
}

// output onto out a list of the form { element0 element 1  ... elementn-1 }
// precondition:
//  Set s is a valid, well initialized Set
// complexity of printing the list is O(n) when there  are n elements in the Set s
std::ostream& operator<< (std::ostream& out, const Set& s) {
   out << "{ ";
   for (Set::Node* p = s.list; p != nullptr; p = p->next ) 
      out << p->value << " ";
   out << "}";
   return out;
}

// union of Set a and Set b
// use a type of "merge algorithm"
// a has m elements and b has n elements and both linked lists are sorted
// in the worse case, when the last value in both sets is the same, we need to go
// through both sets .... thus  union is O(m+n) (and this includes the reverse)
// precondition:
//  the lists in the Set a and in the Set b  are sorted in ascending order 
const Set operator +(const Set & a, const Set & b) {

   // you can change the code in this function

   Set::Node *p = a.list;  // pointer to help me traverse a
   Set::Node *q = b.list;  // pointer to help me traverse b
   Set::Node *result = nullptr;  // points to the resulting list from the merge
   
   while (p != nullptr && q != nullptr) {
	   // if p == q, p>q, p<q
	   if (p->value == q->value) {
		   result = Set::cons(p->value, result);
		   p = p->next;
		   q = q->next;
	   }
	   else if (p->value > q->value) {
		   result = Set::cons(q->value, result);
		   q = q->next;
	   } else {
		   result = Set::cons(p->value, result);
		   p = p->next;
	   }
   }
   while (p != nullptr) {
	   result = Set::cons(p->value, result);
	   p = p->next;
   }
   while (q != nullptr) {
	   result = Set::cons(q->value, result);
	   q = q->next;
   }

   return Set(Set::reverse(result));
}

// intersection  ... a type of merge algorithm
// traverse both lists a and b until the values of both lists are equal
// and then make a Node with that value and add it to the list pointed to by result
// complexity:
// if a has m elements and b has n elements and both linked lists are sorted,
// in the worse case their intersection takes O(m+n)
// reverse is done in linear time and we know that reverse takes at most
// minimum(n,m) 
// precondition:
//  the lists in the Set a and in the Set b  are sorted in ascending order 
const Set operator *(const Set& a, const Set& b) {

   // you can change the code in this function

   Set::Node *p = a.list;  // pointer to help me traverse a
   Set::Node *q = b.list;  // pointer to help me traverse b
   Set::Node *result = nullptr;  // points to the resulting list from the merge

   while (p != nullptr && q != nullptr) {
	   // if p == q, p>q, p<q
	   if (p->value == q->value) {
		   result = Set::cons(q->value, result);
		   p = p->next;
		   q = q->next;
	   }
	   else if (p->value > q->value) {
		   q = q->next;
	   }
	   else {
		   p = p->next;
	   }
   }
      
   Set c;
   c.list = Set::reverse(result);
   return c;
}

/*
 * Proper subset operator
 * Returns true if P has all the elements in Q;
 *	and Q has at least one element that is not in P.
 */
bool operator <(const Set & a, const Set & b) {
	Set::Node *p = a.list;  // pointer to help me traverse a
	Set::Node *q = b.list;  // pointer to help me traverse b
	bool isProperSubset = false;

	while (p != nullptr && q != nullptr) {
		// if p == q, p>q, p<q
		if (p->value == q->value) {
			p = p->next;
			q = q->next;
		}
		else if (p->value > q->value) {
			q = q->next;
			isProperSubset = true;
		}
		else {
			return false;
		}
	}
	if (p == nullptr && q == nullptr) {
		return isProperSubset;
	} else if (q != nullptr) {
		return true;
	} else {
		return false;
	}
}


// copy constructor  
Set::Set(const Set& otherSet) {
	this->list = this->copyAll(otherSet.list);
	#ifndef NDEBUG
	std::cout << "&&&&&&&&&& copy constructor called &&&&&&&&&&&\n";
	#endif
}

// destructor
// postcondition: 
//    every Node in the list is deleted and the list is set to nullptr
Set::~Set(){
	this->list = this->deleteAll();
	#ifndef NDEBUG
	std::cout << "called the destructor+++++++++++++++\n";
	#endif
}

// overload the assignment operator
Set& Set::operator = (const Set& otherSet) {
	if (this != &otherSet) {
		this->list = this->deleteAll();
		this->list = this->copyAll(otherSet.list);
	}
	#ifndef NDEBUG
	std::cout << "!!!!!!!!!!!!!!!!!!! called the overloaded = operator\n";
	#endif
	return *this;
}

// make a new node and put in the value field x and in the next field p
// precondition: none
// postcondition:
//   a pointer to the newly created Node is returned
// complexity: O(1)
Set::Node * Set::cons( int x, Node * p ) {
   Node * q;
   q = new Node;
   q->value = x;
   q->next = p;
   return q;
}
 
// reverse in linear time the list pointed to by p
// the reverse is destructive so the list returned are the
// original nodes
// we want to access reverse in friend functions so make it static
Set::Node * Set::reverse(Node * p) {
	if (p == nullptr) {
		return nullptr;
	}
	Node* output = nullptr;
	do {
		output = Set::cons(p->value, output);
		p = p->next;
	} while (p != nullptr);
	
	return output;
}

/*
 * Makes a copy of a Set based on a existing one (argument).
 */
Set::Node* Set::copyAll(const Node* source) {
	Set::Node* output = nullptr;
	if (source == nullptr) {
		return output;
	}
	else {
		do {
			output = Set::cons(source->value, output);
			source = source->next;
		} while (source != nullptr);
	}
	return Set::reverse(output);
}

/*
 * Deletes the whole set.
 */
Set::Node* Set::deleteAll() {
	Node* current = this->list;
	Node* discard;

	while (current != nullptr) {
		discard = current;
		current = current->next;
		delete discard;
	}

	return current;
}