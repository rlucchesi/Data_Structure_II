/*
 *  Assignment #4, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: 100273456
 * October 24th, 2017.
 */

#include "BiVarPolynomial.h"
#include <fstream>

/*
 * Test Program ment to be used with an input file (polys.txt)
 */
int main() {
	int numTerms;
	int inputArr[3];
	BiVarPolynomial a;
	BiVarPolynomial b;
	
	while (std::cin >> numTerms) {
		for (int i = 0; i < numTerms; i++) {
			std::cin >> inputArr[0];
			std::cin >> inputArr[1];
			std::cin >> inputArr[2];
			a.addTerm(inputArr[0], inputArr[1], inputArr[2]);
		}

		std::cin >> numTerms;
		for (int i = 0; i < numTerms; i++) {
			std::cin >> inputArr[0];
			std::cin >> inputArr[1];
			std::cin >> inputArr[2];
			b.addTerm(inputArr[0], inputArr[1], inputArr[2]);
		}

		std::cout << "===================================\nunsorted\npoly1: ";
		std::cout << a;
		std::cout << "\npoly2: ";
		std::cout << b;
		std::cout << "\nsorted\na: ";
		a.sort();
		std::cout << a;
		std::cout << "\nb: ";
		b.sort();
		std::cout << b;
		std::cout << "\na + b: ";
		std::cout << a + b;
		std::cout << "\na * b: ";
		std::cout << a * b;
		std::cout << "\nda/dx: ";
		std::cout << a.differentiate('x');
		std::cout << "\nda/dy: ";
		std::cout << a.differentiate('y');
		std::cout << "\ndb/dx: ";
		std::cout << b.differentiate('x');
		std::cout << "\ndb/dy: ";
		std::cout << b.differentiate('y');
		std::cout << "\n===================================\n\n";
		a.reset();
		b.reset();
	}
	
	return 0;
}