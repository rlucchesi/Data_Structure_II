/*
 *  Assignment #4, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: 100273456
 * October 24th, 2017.
 */

#include "Term.h"
#include "mySortObj.h"

/*
 * mySortObj Constructor
 */
mySortObj::mySortObj() {}

/*
 * Overloaded operator() to make the object work as a function
 */
int mySortObj::operator()(Term* a, Term* b) {
	if (a->getXDegree() < b->getXDegree()) {
		return -1;
	}
	else if (a->getXDegree() > b->getXDegree()) {
		return 1;
	}
	else {
		if (a->getYDegree() < b->getYDegree()) {
			return -1;
		}
		else if (a->getYDegree() > b->getYDegree()) {
			return 1;
		}
		else {
			return 0;
		}
	}
}
