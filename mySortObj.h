/*
 *  Assignment #4, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: 100273456
 * October 24th, 2017.
 */

#ifndef MYSORTOBJ_H
#define MYSORTOBJ_H

#include "Term.h"

/*
 * Comparison function that is to be used in merge sort
 */
class mySortObj {
public:
	mySortObj();

	/*
	 * Overloaded operator() to make the object work as a function
	 */
	int operator()(Term*, Term*);

};

#endif