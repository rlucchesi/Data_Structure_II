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

#include "BiVarPolynomial.h"

 /*
  * Bivariate Polynomial Constructor
  */
BiVarPolynomial::BiVarPolynomial() {
	this->head = nullptr;
}

/*
 * Bivariate Polynomial Destructor
 */
BiVarPolynomial::~BiVarPolynomial() {
	this->deleteAll();
}

/*
 * Bivariate Polynomial Copy Constructor
 * Parameter: another instance of a Bivariate Polynomial
 */
BiVarPolynomial::BiVarPolynomial(const BiVarPolynomial& aSource) {
	this->copyAll(aSource);
}

/*
 * Overloaded assignment operator
 */
BiVarPolynomial& BiVarPolynomial::operator=(const BiVarPolynomial& aSource) {
	if (this != &aSource) {
		this->deleteAll();
		this->copyAll(aSource);
	}
	return *this;
}

/*
 * Overloaded + to be used in the addition of two Bivariate Polynomials
 */
BiVarPolynomial& operator+(const BiVarPolynomial& A, const BiVarPolynomial& B) {
	BiVarPolynomial* output = new BiVarPolynomial;
	int newCoeff, Ax, Ay, Bx, By;

	BiVarPolynomial::Node* iteratorA = A.head;
	BiVarPolynomial::Node* iteratorB = B.head;

	while (iteratorA != nullptr && iteratorB != nullptr) {
		Ax = iteratorA->data->getXDegree();
		Bx = iteratorB->data->getXDegree();
		Ay = iteratorA->data->getYDegree();
		By = iteratorB->data->getYDegree();

		if (Ax > Bx) {
			output->addTerm(iteratorB->data->getCoefficient(), iteratorB->data->getXDegree(), iteratorB->data->getYDegree());
			iteratorB = iteratorB->next;
		} else if (Ax < Bx) {
			output->addTerm(iteratorA->data->getCoefficient(), iteratorA->data->getXDegree(), iteratorA->data->getYDegree());
			iteratorA = iteratorA->next;
		} else { // Ax == Bx
			if (Ay > By) {
				output->addTerm(iteratorB->data->getCoefficient(), iteratorB->data->getXDegree(), iteratorB->data->getYDegree());
				iteratorB = iteratorB->next;
			} else if (Ay < By) {
				output->addTerm(iteratorA->data->getCoefficient(), iteratorA->data->getXDegree(), iteratorA->data->getYDegree());
				iteratorA = iteratorA->next;
			} else { // Ay == By
				newCoeff = iteratorA->data->getCoefficient() + iteratorB->data->getCoefficient();
				if (newCoeff != 0) {
					output->addTerm(newCoeff, iteratorA->data->getXDegree(), iteratorA->data->getYDegree());
				}
				iteratorA = iteratorA->next;
				iteratorB = iteratorB->next;
			}
		}
	}

	while (iteratorA != nullptr) {
		output->addTerm(iteratorA->data->getCoefficient(), iteratorA->data->getXDegree(), iteratorA->data->getYDegree());
		iteratorA = iteratorA->next;
	}
	while (iteratorB != nullptr) {
		output->addTerm(iteratorB->data->getCoefficient(), iteratorB->data->getXDegree(), iteratorB->data->getYDegree());
		iteratorB = iteratorB->next;
	}

	output->sort();
	return *output;
}

/*
 * Overloaded * to be used in the multiplication of two Bivariate Polynomials
 */
BiVarPolynomial& operator*(const BiVarPolynomial& A, const BiVarPolynomial& B) {
	BiVarPolynomial* output = new BiVarPolynomial;
	
	BiVarPolynomial::Node* iteratorA = A.head;
	BiVarPolynomial::Node* iteratorB = B.head;

	// Iterate through both polynomials, combininig the terms to generate the output
	while (iteratorA != nullptr) {
		while (iteratorB != nullptr) {
			output->addTerm(iteratorA->data->getCoefficient() * iteratorB->data->getCoefficient(),
				iteratorA->data->getXDegree() + iteratorB->data->getXDegree(),
				iteratorA->data->getYDegree() + iteratorB->data->getYDegree());
			iteratorB = iteratorB->next;
		}
		iteratorA = iteratorA->next;
		iteratorB = B.head;
	}
	return *output;
}

/*
 * Overload stream insertion
 */
std::ostream& operator<<(std::ostream& output, const BiVarPolynomial& aSource) {
	BiVarPolynomial::Node* current = aSource.head;
	std::string result = "";

	while (current != nullptr) {
		if (current->data->getCoefficient()	> 0) {
			result += "+";
		}
		result += std::to_string(current->data->getCoefficient()) + "x^" + std::to_string(current->data->getXDegree()) +
			"y^" + std::to_string(current->data->getYDegree()) + " ";
		current = current->next;
	}

	output << result;
	return output;
}

/*
 * Function to check wether the Polynomial is empty
 * Returns true if empty, false otherwise
 */
bool BiVarPolynomial::isEmpty() {
	return (this->head == nullptr);
}

/*
 * Add Term Method. Add a term to the front of the polynomial
 * Parameters: Coefficient, degree of X, degree of Y
 */
void BiVarPolynomial::addTerm(int aCoeff, int aXDeg, int aYDeg) {
	if (aCoeff != 0) {
		this->head = cons(new Term(aCoeff, aXDeg, aYDeg), this->head);
	}
}

/*
 * Differentiates the polynomial with respect to an specified variable
 * If the differentiation results in a negative X/Y degree, the term
 * is removed from the output
 * Parameters: 'x' or 'y', ignoring any other character
 */
BiVarPolynomial BiVarPolynomial::differentiate(char ch) {
	BiVarPolynomial output(*this);
	BiVarPolynomial::Node* iterator = output.head;
	BiVarPolynomial::Node* previous = iterator;

	if (ch == 'x' || ch == 'X') {
		while (iterator != nullptr) {
			if (iterator->data->getXDegree() - 1 >= 0) {
				iterator->data->setCoefficient(iterator->data->getCoefficient() * iterator->data->getXDegree());
				iterator->data->setXDegree(iterator->data->getXDegree() - 1);
				previous = iterator;
			}
			else {
				previous->next = iterator->next;
				delete iterator;
				iterator = previous;
			}
			iterator = iterator->next;
		}
	}
	else if (ch == 'y' || ch == 'Y') {
		while (iterator != nullptr) {
			if (iterator->data->getYDegree() - 1 >= 0) {
				iterator->data->setCoefficient(iterator->data->getCoefficient() * iterator->data->getYDegree());
				iterator->data->setYDegree(iterator->data->getYDegree() - 1);
				previous = iterator;
			}
			else {
				previous->next = iterator->next;
				delete iterator;
				iterator = previous;
			}
			iterator = iterator->next;
		}
	}
	return output;
}

/*
 * Method used to trigger the merge sort algorithm
 */
void BiVarPolynomial::sort() {
	if (this->head != nullptr) {
		BiVarPolynomial::mergeSort(&this->head);
	}
}

/*
 * Method used to reset a Polynomial (== new Object)
 */
void BiVarPolynomial::reset() {
	deleteAll();
}

// ---- Private Methods ----

/*
 * Node Constructor
 * Parameters: A Polynomial Term, a reference to which the Node will point to
 */
BiVarPolynomial::Node* BiVarPolynomial::cons(Term* newTerm, Node* aNext) {
	Node* input = new Node;
	input->data = newTerm;
	input->next = aNext;
	return input;
}

/*
 * Helper function to delete the contents of the Polynomial
 */
void BiVarPolynomial::deleteAll() {
	Node* discardNode;
	Term* discardTerm;
	while (this->head != nullptr) {
		discardNode = this->head;
		discardTerm = this->head->data;
		this->head = this->head->next;
		delete discardTerm;			// delete the Term pointed by the Node
		delete discardNode;			// and then deletes the Node
	}
}

/*
 * Helper function to make a copy of a Polynomial based on an existing object instance.
 */
void BiVarPolynomial::copyAll(const BiVarPolynomial& aSource) {
	Node* source = aSource.head;
	Node* iterator = this->head = nullptr;
	
	while (source != nullptr) {
		if (iterator == nullptr) {
			// first Node
			this->head = new Node;
			iterator = this->head;
		} else {
			iterator->next = new Node;
			iterator = iterator->next;
		}
		iterator->data = new Term(source->data->getCoefficient(), source->data->getXDegree(),
			source->data->getYDegree());
		iterator->next = nullptr;

		source = source->next;
	}
}

/*
 * Recursive mergeSort used to manage the split and merge stages of the algorithm
 * Parameter: A reference to a Linked List (Node)
 */
void BiVarPolynomial::mergeSort(Node** aHead) {
	Node* head = *aHead;
	
	// basecase
	if (aHead == nullptr || head->next == nullptr) {
		return;
	}

	//split
	Node* a;
	Node* b;
	BiVarPolynomial::split(&a, &b, head);

	// recursive call on halves
	BiVarPolynomial::mergeSort(&a);
	BiVarPolynomial::mergeSort(&b);

	// merge halves
	mySortObj sortObj;
	*aHead = BiVarPolynomial::merge(a, b, sortObj);

}

/*
 * Divides a Linked List in two halves using the slow/fast technique, and returns both halves through the arguments
 * Parameters: reference to the first Half, reference to the second Half,
 *   pointer to the Head of the Linked List to be divided
 */
void BiVarPolynomial::split(Node** A, Node** B, Node* aHead) {
	Node* lastOfA = nullptr;
	Node* middle = nullptr;
	Node* end = aHead;

	if (end == nullptr || end->next == nullptr) {
		*A = aHead;
		*B = nullptr;
	}
	else {
		middle = aHead;
		while (end != nullptr) {
			end = end->next;
			lastOfA = middle;
			middle = middle->next;
			if (end != nullptr) {
				end = end->next;
			}
		}
		lastOfA->next = nullptr;		// closes the first half (making it 'finite' linked list)
		*A = aHead;
		*B = middle;
	}
}

/*
 * Merges two Linked Lists into one, using a functor to determine under which
 *   criterion the merge will take place
 * Parameters: Pointer to a Linked List A, pointer to a Linked List B, a functor object
 */
BiVarPolynomial::Node* BiVarPolynomial::merge(Node* A, Node* B, mySortObj sortObj) {
	if (A == nullptr)
		return B;
	if (B == nullptr)
		return A;
		
	switch (sortObj(A->data, B->data)) {
		case 1:
			A->next = merge(A->next, B, sortObj);
			return A;
		case 0:
			if (A->data->getCoefficient() + B->data->getCoefficient() != 0) {
				A->data->setCoefficient(A->data->getCoefficient() + B->data->getCoefficient());
			}
			A->next = merge(A->next, B->next, sortObj);
			return A;
		case -1:
			B->next = merge(A, B->next, sortObj);
			return B;
	}
}