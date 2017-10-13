/*
 *  Assignment #3, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: ********
 */

#ifndef SLIST_H
#define SLIST_H
// Build  a skip list
// CPSC 2150, Assignment #3, Fall 2017
// Gladys Monagan

#include <string>
#include <fstream>
#include <iostream>		// output

/*
* Two level Skip List that keeps the values in ascending order.
*/
class SList {
	public:
		/*
		 * Default Constructor
		 */
		SList();

		/*
		 * Insert an element in ascending order
		 * postcondition: the number of traversals done in this call to
		 * insert is added to the number of traversals so far
		 * Note: to get the number of traversals, including the 
		 * traversals needed when adjusting the pointers of the top list, 
		 * call getTraversals()
		 */
		void insert(int x);

		/*
		 * returns the TOTAL number of traversals done in order to build 
		 * the skip list so far
		 * the skip list is sorted in ascending order and the number of
		 * traversals continues increasing -- it is never reset
		 * the total number of traversals depends on the number of calls
		 * to the function insert and on how the top list is build and
		 * the pointers adjusted  
		 */
		int getTraversals() const;

		/*
		 * return true if x is found in the list, false otherwise
		 * postcondition: the number of comparisons done in this call to
		 * found is updated
		 * Note: if the number of comparisons made in found is needed,
		 * call getComparisons() after found is called
		 */
		bool found(int x);
   
		/*
		 * returns the number of comparisons done when found is called
		 * every time that found is called, the number of comparisons is 
		 * first reset to zero and the number comparisons is calculated
		 */
		int getComparisons() const;

		/*
		 * output all the elements of the list in order (i.e. in ascending order)
		 * separate the elements with the defined delimeter
		 * which currently has an intial value of "  \n" (may be changed)
		 */
		void printAllInOrder(std::ostream&) const;
   
		/*
		 * delimeter is used to separate the elements in printAllInOrder
		 */
		void setOutputDelimeter(std::string delimeter);
      
		/*
		 * return the number of elements in the skip list
		 */
		int numberOfElements() const;
      
		/*
		 * delete/deallocate the skip list and reset to the initial values
		 * of the instance variables
		 */
		void reset();
      
		/*
		 * overloaded assignment operator
		 */
		SList& operator = (const SList&);
      
		/*
		 * copy constructor
		 */
		SList(const SList&); 
      
		/* 
		 * destructor
		 */
		~SList();
      
		/*
		 * for debugging purpose, print the top list exclusively
		 * not part of a 'real skip list' but we want to debug our assignment
		 */
		void dumpTopList(std::ostream& out);
      
	private:
		int const INITIAL_COUNTER_VALUE = 0;
		std::string const INITIAL_DELIMITER = "  \n";

		struct Node {
			int item;				// stores item (int)
			Node* next;				// pointer to the next Node
			Node* lvlDown;			// pointer to go from l2 -> l1
		};
	   
		Node* l1;					// head of l1 (bottom list)
		Node* l2;					// head of l2 (top list)
		int l1Size;					// size of l1 (bottom list)
		int l2Size;					// size of l2 (top list)
		std::string myDelimeter;	// stores delimiter used in the printAllInOrder()

		unsigned numOfTraversals;		// stores # of Traversals
		unsigned numOfComparisons;		// stores # of Comparisons


		/*
		 * determine if the list is empty
		 */
		bool isEmpty();

		/*
		 * generates a new l2 (top List) based on a "factor" given as argument
		 * the factor determines how spread the items will be in the top List
		 */
		void generateL2(int factor);

		/*
	     * deletes the list passed as argument
		 */
		void deleteList(Node* aList);

		/*
		 * deletes the whole list
		 * parameters are a list and its size variable, which is set to
		 * the initial value (0)
		 */
		void deleteList(Node* aList, int& aSize);

		/*
		 * makes a copy of a SList based on another one
		 */
		void copyAll(const SList& rtSide);
};
#endif  // SLIST_H
