/*
 *  Assignment #2, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: *********
 */

#include "LList.h"

/*
 * Linked List Constructor.
 */
LList::LList() {
	this->capacity = INITIAL_CAPACITY;
	this->head = END;
	this->free = 0;
	this->data = new Node[this->capacity];

	int i;
	for (i = this->free; i < this->capacity - 1; i++) {
		this->data[i].item = '#';
		this->data[i].next = i + 1;
	}
	this->data[i].item = '#';
	this->data[i].next = END;
	std::cerr << "LList created\n";
}

/*
 * Linked List Copy Constructor.
 */
LList::LList(const LList& source) {
	this->head = source.head;
	this->capacity = source.capacity;
	this->free = source.free;
	this->data = new Node[source.capacity];

	for (int i = 0; i < this->capacity; i++) {
		this->data[i].item = source.data[i].item;
		this->data[i].next = source.data[i].next;
	}
}

/*
 * Linked List Destructor.
 */
LList::~LList() {
	delete[] this->data;
	this->head = END;
	std::cerr << "Destructor invoked\n";
}

/*
 * Overloaded Assignment operator.
 */
LList& LList::operator = (const LList& rtSide) {
	if (this != &rtSide) {
		this->deleteAll();
		this->copyAll(rtSide);
	}
	return *this;
}

/*
 * Determines if the linked list is empty.
 */
bool LList::isEmpty() const {
	return this->head == END;
}

/*
 * Returns the number of Nodes in the linked list.
 */
int LList::length() const {
	if (this->isEmpty()) {
		return 0;
	}
	int output = 1;
	int current = this->head;

	while (this->data[current].next != END) {
		output++;
		current = this->data[current].next;
	}

	return output;
}

/*
 * Returns the number of Nodes in a linked list from a certain
 * Node p (index).
 */
int LList::length(int p) const {
	int current = p, output = 1;

	while (this->data[current].next != END) {
		output++;
		current = this->data[current].next;
	}
	
	return output;
}

/*
 * Inserts a character at the beginning (at the front) of the
 * Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::cons(char ch) {
	try {
		if (this->free == END) {
			this->data = this->duplicateSize();
		}
		// create a variable to work with
		int current = this->free;
		// Update Free index
		this->free = this->data[current].next;
		// Actual insertion of data
		this->data[current].item = ch;
		this->data[current].next = this->head;
		// Update Head index
		this->head = current;
	}
	catch (...) {
		return false;
	}
	return true;
}

/*
 * Appends a character to the end of the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::append(char ch) {
	try {
		if (this->free == END) {
			this->data = this->duplicateSize();
		}
		// create a variable to work with
		int current = this->head;
		
		// Find the last item and update its next field
		while (this->data[current].next != END) {
			current = this->data[current].next;
		}
		this->data[current].next = this->free;
		
		// Work on the new Node (previously a Free node)
		current = this->free;
		// Update Free index
		this->free = this->data[this->free].next;

		// Actual insertion of data
		this->data[current].item = ch;
		this->data[current].next = END;
	} catch (...) {
		return false;
	}
	return true;
}

/*
 * Deletes the first occurence of a character in the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::remove(char ch) {
	if (this->isEmpty()) {
		return false;
	}
	
	// variables to work with
	int previous, current;
	current = this->head;

	// search for the item to be removed
	while (current != END && this->data[current].item != ch) {
		previous = current;
		current = this->data[current].next;
	}

	// item not found
	if (current == END) {
		return false;
	}

	// item found. Update head and free indices accordingly
	if (current == this->head) {
		this->head = this->data[current].next;
		this->data[current].next = this->free;
		this->free = current;
		this->data[current].item = '#';
	} else {
		this->data[previous].next = this->data[current].next;
		this->data[current].next = this->free;
		this->data[current].item = '#';
		this->free = current;
	}
	return true;
}

/*
 * Searchs for a character in the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::found(char ch) const {
	if (this->isEmpty()) {
		return false;
	}

	int current = this->head;

	while (current != END) {
		if (this->data[current].item == ch) {
			return true;
		}
		current = this->data[current].next;
	}
	return false;
}

/*
 * Returns the first element of the Linked List and sets its boolean
 * parameter to TRUE. If the list is empty, the function returns
 * the character '\0' and sets its boolean parameter to FALSE.
 */
char LList::getFirst(bool &hasFirst) const {
	if (this->isEmpty()) {
		hasFirst = false;
		return '\0';
	}
	hasFirst = true;
	return this->data[this->head].item;
}

/* 
 * Reverses the linked list.
 */
void LList::reverse() {
	if (this->isEmpty()) {
		return;
	}
	bool headSaved = false;
	int current, previous, headIndex;

	while (this->data[this->head].next != END) {
		current = this->head;
		while (this->data[current].next != END) {
			previous = current;
			current = this->data[current].next;
		}
		this->data[current].next = previous;
		this->data[previous].next = END;
		if (!headSaved) {
			headSaved = true;
			headIndex = current;
		}
	}
	this->head = headIndex;
}

/*
 * Prints the linked list to standard output (from beginning to end).
 * The output starts with a '[' and finishes with a ']' followed by
 * an end-of-line.
 */
void LList::print() const {
	if (this->isEmpty()) {
		std::cerr << "[]" << std::endl;
	} else {
		std::string output = "";
		int current = this->head;

		do {
			output += this->data[current].item;
			current = this->data[current].next;
		} while (current != END);

		std::cerr << "[" << output << "]" << std::endl;
	}
	#ifndef NDEBUG
	this->dumpNodesArray();
	#endif
}

/*
 * Duplicates the size of the Array holding the Linked List.
 * The function might throw bad_alloc exception; however, it will only
 * be called inside a try catch block.
 */
LList::Node* LList::duplicateSize() {
	// create output array
	Node* output = new Node[this->capacity * 2];

	// after making sure there is enough memory to hold the new array
	// update free array index
	this->free = this->capacity;
	// update capacity variable
	this->capacity = this->capacity * 2;

	// copy the contents
	for (int i = 0; i < this->free; i++) {
		output[i].item = this->data[i].item;
		output[i].next = this->data[i].next;
	}

	// delete previous array
	delete [] this->data;

	// Organize the array of free Nodes
	int i;
	for (i = this->free; i < this->capacity - 1; i++) {
		output[i].item = '#';
		output[i].next = i + 1;
	}
	output[i].item = '#';
	output[i].next = END;

	return output;
}

/*
 * Makes a copy of a linked list (with nodes in the same order)
 * based on a existing one (argument).
 */
void LList::copyAll(const LList& source) {
	this->head = source.head;
	this->capacity = source.capacity;
	this->free = source.free;
	this->data = new Node[source.capacity];

	for (int i = 0; i < this->capacity; i++) {
		this->data[i].item = source.data[i].item;
		this->data[i].next = source.data[i].next;
	}

	
}

/*
 * Deletes the complete linked list.
 */
void LList::deleteAll() {
	delete [] this->data;
	this->head = END;
}

#ifndef NDEBUG
/*
 * Dumps the array
 */
void LList::dumpNodesArray() const {
	// print upper part of table and indecies values
	printf("\n\tindex\titem\tnext\t\tHead: %2d\tFree: %2d", this->head, this->free);
	printf("\n\t----\t---\t----");

	// print each line (for loop)
	for (int i = 0; i < this->capacity; i++) {
		printf("\n\t %2d\t %c\t %2d", i, this->data[i].item, this->data[i].next);
	}
	
	// print bottom line
	printf("\n\t----\t---\t----\n\n");
}
#endif