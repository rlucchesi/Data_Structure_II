/*
 *  Assignment #3, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: 100273456
 */

#include "SList.h"

/*
 * Default Constructor
 */
SList::SList() {
	#ifndef NDEBUG
	std::cerr << "called the Constructor+++++++++++++++\n\n";
	#endif

	this->numOfTraversals = INITIAL_COUNTER_VALUE;
	this->numOfComparisons = INITIAL_COUNTER_VALUE;
	this->l1 = nullptr;
	this->l2 = nullptr;
	this->l1Size = INITIAL_COUNTER_VALUE;
	this->l2Size = INITIAL_COUNTER_VALUE;
	this->myDelimeter = INITIAL_DELIMITER;
}


/*
 * Insert an element in ascending order
 * postcondition: the number of traversals done in this call to
 * insert is added to the number of traversals so far
 * Note: to get the number of traversals, including the
 * traversals needed when adjusting the pointers of the top list,
 * call getTraversals()
 */
void SList::insert(int x) {
	Node* input = new Node;
	input->item = x;
	input->lvlDown = nullptr;

	if (this->isEmpty()) {
		// List is empty
		input->next = nullptr;
		this->l1 = input;
		
	} else if (x <= this->l1->item) {
		// List is not empty
		// item will replace the List's head
		input->next = this->l1;
		this->l1 = input;
			
		if (((this->l2Size + 1) * (this->l2Size + 1)) != l1Size + 1) {
			// needed because the head of top List is != from the head of the bottom List
			// the test is done to avoid rearranging the list twice since
			// generateL2 will be called again, if needed, at the end of this method
			deleteList(this->l2);
			generateL2(this->l2Size + 1);
		}
	} else {
		// item goes somewhere else in the list 
		// search for the right position to insert new item using l2 (top List), then L1 (bottom List)
		Node* current = this->l2->next;	// *current is in top List**
		Node* previous = this->l2;
		while (current != nullptr && x > current->item) {
			previous = current;
			current = current->next;
		}
		if (current == nullptr || x < current->item) {
			current = previous->lvlDown;	// *current is in bottom List from now on**
			while (current != nullptr && x > current->item) {
				previous = current;
				current = current->next;
			}
		} else {
			// found position... insert here!
			previous = previous->lvlDown;
			current = previous->next;
		}
		input->next = current;
		previous->next = input;
	}
	this->l1Size++;

	if (((this->l2Size + 1) * (this->l2Size + 1)) == l1Size) {
		//keep the ratio between two lists.. time to rearrange!
		deleteList(this->l2);
		generateL2(++this->l2Size); // update l2Size
	}
}


/*
 * returns the TOTAL number of traversals done in order to build
 * the skip list so far
 * the skip list is sorted in ascending order and the number of
 * traversals continues increasing -- it is never reset
 * the total number of traversals depends on the number of calls
 * to the function insert and on how the top list is build and
 * the pointers adjusted
 */
int SList::getTraversals() const {
	return this->numOfTraversals;
}


/*
 * return true if x is found in the list, false otherwise
 * postcondition: the number of comparisons done in this call to
 * found is updated
 * Note: if the number of comparisons made in found is needed,
 * call getComparisons() after found is called
 */
bool SList::found(int x) {
	Node* current = this->l2;	// *current is in top List**
	Node* previous;
	this->numOfComparisons = INITIAL_COUNTER_VALUE;

	this->numOfComparisons++;
	if (x < current->item) {
		return false;
	}
	else if (x == current->item) {
		return true;
	}
	else {
		while (current != nullptr && x > current->item) {
			this->numOfComparisons++;
			previous = current;
			current = current->next;
		}
		this->numOfComparisons++;
		if (current == nullptr || x < current->item) {
			current = previous->lvlDown;	// *current is in bottom List from now on**
			while (current != nullptr && x > current->item) {
				this->numOfComparisons++;
				current = current->next;
			}
			this->numOfComparisons++;
			if (current == nullptr) {
				return false;
			}
			this->numOfComparisons++;
			return (x == current->item);
		}
		else {
			// item found in L2
			return true;
		}
	}
}


/*
 * returns the number of comparisons done when found is called
 * every time that found is called, the number of comparisons is
 * first reset to zero and the number comparisons is calculated
 */
int SList::getComparisons() const {
	return this->numOfComparisons;
}


/*
 * output all the elements of the list in order (i.e. in ascending order)
 * separate the elements with the defined delimeter
 * which currently has an intial value of "  \n" (may be changed)
 */
void SList::printAllInOrder(std::ostream& out) const {
	std::string result = "bottom List [ ";
	Node* current = this->l1;

	while (current != nullptr) {
		result += std::to_string(current->item) + this->myDelimeter;
		current = current->next;
	}
	result += "]\n";
	out << result;
}


/*
 * delimeter is used to separate the elements in printAllInOrder
 */
void SList::setOutputDelimeter(std::string delimeter) {
	this->myDelimeter = delimeter;
}


/*
 * return the number of elements in the skip list
 */
int SList::numberOfElements() const {
	return this->l1Size;
}


/*
 * delete/deallocate the skip list and reset to the initial values
 * of the instance variables
 */
void SList::reset() {
	deleteList(this->l1, this->l1Size);
	deleteList(this->l2, this->l2Size);
	this->l1 = nullptr;
	this->l2 = nullptr;
	this->numOfTraversals = INITIAL_COUNTER_VALUE;
	this->numOfComparisons = INITIAL_COUNTER_VALUE;
}


/*
 * overloaded assignment operator
 */
SList& SList::operator = (const SList& rtSide) {
	#ifndef NDEBUG
	std::cout << "called the assignment operator+++++++++++++++\n\n";
	#endif
	
	if (this != &rtSide) {
		//deleteAll
		deleteList(this->l1, this->l1Size);
		deleteList(this->l2, this->l2Size);
		this->l1 = nullptr;
		this->l2 = nullptr;
		//CopyAll
		copyAll(rtSide);
	}
	return *this;
}


/*
 * copy constructor
 */
SList::SList(const SList& rtSide) {
	#ifndef NDEBUG
	std::cout << "called the Copy Constructor+++++++++++++++\n\n";
	#endif

	copyAll(rtSide);
}


/*
 * destructor
 */
SList::~SList() {
	#ifndef NDEBUG
	std::cout << "called the Destructor+++++++++++++++\n\n";
	#endif

	deleteList(this->l1, this->l1Size);
	deleteList(this->l2, this->l2Size);
	this->l1 = nullptr;
	this->l2 = nullptr;
}


/*
 * for debugging purpose, print the top list exclusively
 * not part of a 'real skip list' but we want to debug our assignment
 */
void SList::dumpTopList(std::ostream& out) {
	std::string result = "top List [ ";
	Node* current = this->l2;

	while (current != nullptr) {
		result += std::to_string(current->item ) + this->myDelimeter;
		current = current->next;
	}
	result += "]\n";
	out << result;
}


// --------------------- Private Methods ---------------------

/*
 * determine if the list is empty
 */
bool SList::isEmpty() {
	return this->l1 == nullptr;
}


/*
 * generates a new l2 (top list) based on the current l1
 */
void SList::generateL2(int factor) {
	//delete current L2
	//update l2Length
	//create new L2 with updated nodes
	//(set l2, nested for loop to get new nodes based on l2Length)

	bool isHeadAssigned = false;
	int i = INITIAL_COUNTER_VALUE;
	Node* l1Iterator = this->l1;
	Node* l2Previous = nullptr;

	do {
		Node* tmp = new Node;
		tmp->next = nullptr;
		if (!isHeadAssigned) {
			this->l2 = tmp;
			isHeadAssigned = true;
		}
		tmp->lvlDown = l1Iterator;
		tmp->item = l1Iterator->item;
		for (int j = 0; j < factor && l1Iterator != nullptr; j++) {
			l1Iterator = l1Iterator->next;
			this->numOfTraversals++;
		}
		if (l2Previous != nullptr) {
			l2Previous->next = tmp;
		}
		l2Previous = tmp;
		i += factor;
	} while (i < this->l1Size);
}


/*
 * deletes the list passed as argument
 */
void SList::deleteList(Node* aList) {
	Node* current = aList;
	Node* discard;
	while (current != nullptr) {
		discard = current;
		current = current->next;
		delete discard;
	}
}


/*
 * deletes the whole list
 * parameters are a list and its size variable, which is set to
 * the initial value (0)
 */
void SList::deleteList(Node* aList, int& aSize) {
	Node* current = aList;
	Node* discard;
	while (current != nullptr) {
		discard = current;
		current = current->next;
		delete discard;
	}
	aSize = INITIAL_COUNTER_VALUE;
}



void SList::copyAll(const SList& rtSide) {
	// copy private variables
	this->myDelimeter = rtSide.myDelimeter;
	this->numOfTraversals = rtSide.numOfTraversals;
	this->numOfComparisons = rtSide.numOfComparisons;
	this->l1Size = rtSide.l1Size;
	this->l2Size = rtSide.l2Size;
	
	// copy L1
	Node* rtIterator = rtSide.l1;
	Node* ltPrevious = nullptr;

	while (rtIterator != nullptr) {
		Node* input = new Node;
		input->item = rtIterator->item;
		input->lvlDown = rtIterator->lvlDown;
		input->next = nullptr; //LINK TO THE NEXT NODE (node created yet)
		if (ltPrevious != nullptr) {
			ltPrevious->next = input;
		}
		else {
			this->l1 = input;
		}
		ltPrevious = input;
		rtIterator = rtIterator->next;
	}

	// copy L2
	generateL2(this->l2Size); // This way I can keep the links from L2 -> L1 consistent
}


