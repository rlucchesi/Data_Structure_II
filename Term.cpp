/*
 *  Assignment #4, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: 100273456
 * October 24th, 2017.
 */


#include "Term.h"

 /*
  * Term Constructor
  * Parameters: Polynomial Coefficient, Degree of X, Degree of Y
  */
Term::Term(int aCoeff, int aXDeg, int aYDeg) {
	this->coeff = aCoeff;
	this->xDegree = aXDeg;
	this->yDegree = aYDeg;
}

/*
 * Coefficient getter
 */
int Term::getCoefficient() {
	return this->coeff;
}

/*
 * Coefficient setter
 */
void Term::setCoefficient(int aCoeff) {
	this->coeff = aCoeff;
}

/*
 * X Degree getter
 */
int Term::getXDegree() {
	return this->xDegree;
}

/*
 * X Degree setter
 */
void Term::setXDegree(int aXDeg) {
	this->xDegree = aXDeg;
}

/*
 * Y Degree getter
 */
int Term::getYDegree() {
	return this->yDegree;
}

/*
 * X Degree setter
 */
void Term::setYDegree(int aYDeg) {
	this->yDegree = aYDeg;
}