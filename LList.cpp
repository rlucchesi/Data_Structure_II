/*
*  Assignment #1, CPSC 2150
* Student Last Name: Teles Lazaro Lucchesi
* Student First Name: Rafael
* Student Number: 100273456
*/

#include "LList.h"

/*
 * Linked List Constructor.
 */
LList::LList() {
	head = nullptr;
	std::cout << "LList created" << std::endl;
}

/*
 * Linked List Copy Constructor.
 */
LList::LList(const LList& source) {
	this->head = copyAllI(source.head);
}

/*
 * Linked List Destructor.
 */
LList::~LList() {
	std::cerr << "Destructor invoked" << "\n";
	this->head = deleteAllI(this->head);
}

/*
 * Linked List Assignment operator overload.
 */
LList& LList::operator = (const LList& rtSide) {
	if (this != &rtSide) {
		this->head = deleteAllI(this->head);
		this->head = copyAllI(rtSide.head);
	}
	return *this;
}

/*
 * Returns TRUE if the Linked List is empty, FALSE otherwise.
 */
bool LList::isEmpty() const {
	return this->head == nullptr;
}

/*
 * Returns the number of Nodes of a Linked List.
 */
int LList::length() const {
	if (this->head == nullptr) {
		return 0;
	}
	
	Node* current = this->head;
	int output = 0;

	while (current != nullptr) {
		output++;
		current = current->next;
	}
	return output;
}

/*
 * Inserts a character at the beginning (at the front) of the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::cons(char ch) {
	try {
		this->head = cons(ch, this->head);
		return true;
	}
	catch (const std::bad_alloc&) {
		return false;
	}
}

/*
 * ITERATIVE: Inserts a character at the beginning (at the front) of the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::consI(char ch) {
	if (ch == '\0') {
		return false;
	}
	try {
		Node* data = new Node;
		data->item = ch;
		if (this->head == nullptr) {
			this->head = data;
			data->next = nullptr;
		}
		else {
			data->next = this->head;
			this->head = data;
		}
		return true;
	} catch (const std::bad_alloc&) {
		return false;
	}
}

/*
 * Appends a character to the end of the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::append(char ch) {
	try {
		this->head = append(ch, this->head);
		return true;
	}
	catch (const std::bad_alloc&) {
		return false;
	}
}

/*
 * ITERATIVE: Appends a character to the end of the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::appendI(char ch) {
	if (ch == '\0') {
		return false;
	}
	Node* current = this->head;
   
   while (this->head != nullptr && current->next != nullptr) {
      current = current->next;
   }
 	try {
		Node* data = new Node;
		data->item = ch;
		data->next = nullptr;
		current->next = data;
	}
   catch (const std::bad_alloc&) {
		return false;
	}
	return true;
}

/*
 * A recursive function that deletes the first occurence of a character in the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::remove(char ch) {
	if (this->head == nullptr || ch == '\0') {
		return false;
	}

	if (this->head->item == ch) {
		Node* nextNode = this->head->next;
		delete this->head;
		this->head = nextNode;
		return true;
	}

	return remove(ch, this->head);
}

/*
 * A helper function associated with the recursive function LList::remove(char).
 */
bool LList::remove(char ch, Node* current) {
	if (current == nullptr) {
		return false;
	}

	Node* nextNode = current->next;

	if (nextNode != nullptr && nextNode->item == ch) {
		Node* tmpPtr = nextNode->next;
		delete nextNode;
		current->next = tmpPtr;
		return true;
	}
	else {
		return remove(ch, nextNode);
	}
}

/*
 * ITERATIVE: Deletes the first occurence of a character in the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::removeI(char ch) {
	if (this->head == nullptr || ch == '\0') {
		return false;
	}

	Node* current = this->head;
	Node* previous;

	if (current->item == ch) {
		this->head = current->next;
		delete current;
	} else {
		do {
			previous = current;
			current = current->next;
		} while (current != nullptr && current->item != ch);

		if (current != nullptr) {
			previous->next = current->next;
			delete current;
		} else {
			return false;
		}
	}
	return true;
}


/*
 * A recursive function that searchs for a character in the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::found(char ch) const {
	if (ch == '\0') {
		return false;
	}
	return found(ch, this->head);
}

/*
 * A helper function associated with the recursive function LList::found(char).
 */
bool LList::found(char ch, Node* current) const {
	if (current == nullptr) {
		return false;
	}
	if (current->item == ch) {
		return true;
	}
	else {
		return found(ch, current->next);
	}
}

/*
 * ITERATIVE: Searchs for a character in the Linked List.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool LList::foundI(char ch) const {
	if (ch == '\0' || this->head == nullptr) {
		return false;
	}

	Node* current = this->head;

	while (current != nullptr) {
		if (current->item == ch) {
			return true;
		}
		current = current->next;
	}
	return false;
}

/*
 * The function returns the first element of the Linked List and sets
 * its boolean parameter to TRUE. If the list is empty, the function returns
 * the character '\0' and sets its boolean parameter to FALSE.
 */
char LList::getFirst(bool& hasFirst) const {
	if (this->head == nullptr) {
		hasFirst = false;
		return '\0';
	}
	else {
		hasFirst = true;
		return this->head->item;
	}
}

/* 
 * Reverses the linked list.
 * The function does not take arguments nor does it return a value.
 */
void LList::reverse() {
	bool headSaved = false;
	Node* current;
	Node* previous;
	Node* headPtr;

	while (this->head->next != nullptr) {
		current = this->head;
		while (current->next != nullptr) {
			previous = current;
			current = current->next;
		}
		current->next = previous;
		previous->next = nullptr;
		if (!headSaved) {
			headSaved = true;
			headPtr = current;
		}
	}
	this->head = headPtr;
}

/*
 * Prints the linked list to standard output (from beginning to end).
 * The output starts with a '[' and finishes with a ']' followed by an end-of-line.
 */
void LList::print() const {
	Node* current = this->head;
	std::string output = "";
	for (int i = 0; i < this->length(); i++) {
		output += current->item;
		current = current->next;
	}

	std::cout << "[" << output << "]" << std::endl;
}

/*
 * A recursive function that deletes the complete linked list.
 */
LList::Node* LList::deleteAll(Node* current) {
	if (current == nullptr) {
		return nullptr;
	}
	Node* nextPtr = current->next;
	delete current;
	return deleteAll(nextPtr);
}

/*
 * ITERATIVE: Deletes the whole Linked List.
 */
LList::Node* LList::deleteAllI(Node* input) {
	Node* discard;
   while (input != nullptr) {
	  	discard = input;
	  	input = input->next;
	  	delete discard;
	}
	return input;
}


/*
 * A recursive function that copies the complete linked list (making a copy with nodes in the same order).
 */
LList::Node* LList::copyAll(Node* p) {
	if (p == nullptr) {
      return nullptr;
   }
	return cons(p->item, copyAll(p->next));
}

/*
 * ITERATIVE: Copies the whole Linked List by
 * making a copy with nodes in the same order.
 */
LList::Node* LList::copyAllI(Node* input) {
	Node* output = nullptr;
   if (input != nullptr) {
      // at least one node exists
      output = new Node;
      output->item = input->item;
      output->next = nullptr;
      input = input->next;

      while (input != nullptr) {
         // while more elements exists
	   	output->next = new Node;
         output = output->next;
         output->item = input->item;
         output->next = nullptr;
		   input = input->next;
	   }
   }
	return output;
}

/*
 * STATIC PRIVATE FUNCTIONS
 */

/*
 * Returns the number of Nodes in a Linked List.
 */
int LList::length(Node *p) {
	if (p == nullptr) {
		return 0;
	}

	Node* current = p;
	int output = 0;

	while (current != nullptr) {
		output++;
		current = current->next;
	}
	return output;
}

/*
 * Inserts a character at the beginning (at the front)
 * of the Linked List and returns a pointer to a Node.
 */
LList::Node* LList::cons(char ch, Node* current) {
	Node* data = new Node;
	data->item = ch;
	data->next = current;
	return data;
}

/*
 * Recursive: appends a character to the end of the Linked List.
 * and returns TRUE if successful, FALSE otherwise.
 */
LList::Node* LList::append(char ch, Node* current) {
	if (current == nullptr) {
		return cons(ch, current);
	}
	else {
		current->next = append(ch, current->next);
		return current;
	}
}

