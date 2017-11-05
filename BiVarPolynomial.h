/*
 *  Assignment #4, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: 100273456
 * October 24th, 2017.
 */

/*
 * Implement a C++ class to sort a bivariate polynomial, to add two bivariate polynomials,
 * and to differentiate the bivariate polynomial with respect to each of the variables.
 * 
 * You are required to implement the polynomial using a linked list of pointers to terms.
 */

#ifndef BIVARPOLYNOMIAL_H
#define BIVARPOLYNOMIAL_H

#include "Term.h"
#include "mySortObj.h"
#include <iostream>
#include <string>

/*
 * C++ Bivariate Polynomial class
 */
class BiVarPolynomial {
	/*
	 * Overload stream insertion
	 */
	friend std::ostream& operator<< (std::ostream&, const BiVarPolynomial&);
	
	/*
	 * Overloaded + to be used in the addition of two Bivariate Polynomials
	*/
	friend BiVarPolynomial& operator+(const BiVarPolynomial&, const BiVarPolynomial&);

	/*
	* Overloaded * to be used in the multiplication of two Bivariate Polynomials
	*/
	friend BiVarPolynomial& operator*(const BiVarPolynomial&, const BiVarPolynomial&);

	public:
		/*
		 * Class Constructor
		 */
		BiVarPolynomial();

		/*
		 * Class Destructor
		 */
		~BiVarPolynomial();
		
		/*
		 * Copy Constructor
		 */
		BiVarPolynomial(const BiVarPolynomial&);

		/*
		 * Overloaded assignment operator
		 */
		BiVarPolynomial& operator=(const BiVarPolynomial&);

		/*
		 * Function to check wether the Polynomial is empty
		 * Returns true if empty, false otherwise
		 */
		bool isEmpty();
		
		/*
		 * Add Term Method. Add a term to the front of the polynomial
		 * Parameters: Coefficient, degree of X, degree of Y
		 */
		void addTerm(int, int, int);

		/*
		 * Differentiates the polynomial with respect to an specified variable
		 * If the differentiation results in a negative X/Y degree, the term
		 * is removed from the output
		 * Parameters: 'x' or 'y', ignoring any other character
		 */
		BiVarPolynomial differentiate(char);

		/*
		 * Method used to trigger the merge sort algorithm
		 */
		void sort();

		/*
		 * Method used to reset a Polynomial (== new Object)
		 */
		void reset();

	private:
		/*
		 * Struct of the Linked List of pointers to Terms
		 */
		struct Node {
			Term* data;
			Node* next;
		};

		Node* head;		// head of the Linked List
		
		/*
		 * Node Constructor
		 * Parameters: A Polynomial Term, a reference to which the Node will point to
		 */
		Node* cons(Term*, Node*);

		/*
		 * Helper function to delete the contents of the Polynomial
		*/
		void deleteAll();

		/*
		 * Helper function to make a copy of a Polynomial based on an existing object instance.
		 */
		void copyAll(const BiVarPolynomial&);

		/*
		 * Recursive mergeSort used to manage the split and merge stages of the algorithm
		 */
		static void mergeSort(Node**);
		
		/*
		 * Divides a Linked List in two halves, returning them through its arguments
		 * Parameters: First Half, Second Half, Head of the Node to be divided
		 */
		static void split(Node**, Node**, Node*);

		/*
		 * Merges two Linked Lists into one, using a functor to determine under which criterion
		 * Parameters: Linked List A, Linked List B, functor object
		*/
		static Node* merge(Node*, Node*, mySortObj);
};

#endif