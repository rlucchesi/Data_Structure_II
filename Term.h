/*
 *  Assignment #4, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: 100273456
 * October 24th, 2017.
 */

#ifndef TERM_H
#define TERM_H

/*
 * C++ class for the Bivariate Polynomial Term
 */

class Term {
	public:
		/*
		 * Term Constructor
		 * Parameters: Polynomial Coefficient, Degree of X, Degree of Y
		 */
		Term(int, int, int);

		/*
		 * Coefficient getter
		 */
		int getCoefficient();

		/*
		 * Coefficient setter
		 */
		void setCoefficient(int);

		/*
		 * X Degree getter
		 */
		int getXDegree();

		/*
		 * X Degree setter
		 */
		void setXDegree(int);

		/*
		 * Y Degree getter
		 */
		int getYDegree();

		/*
		 * X Degree setter
		 */
		void setYDegree(int);

	private:
		int coeff;			// Polynomial Coefficient
		int xDegree;		// X Degree
		int yDegree;		// Y Degree
};

#endif