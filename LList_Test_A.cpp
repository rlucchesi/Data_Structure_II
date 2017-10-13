/*
 *  Assignment #1, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: *********
 */

#include "LList.h"
#include <fstream>

//Prototypes
void destructorTest();
int generalClassTest();
void heapSizeTest();

void destructorTest() {
	std::cerr << "12- Destructor Test. Expected: 'Destructor invoked' at the end of the function call" << std::endl;

	// Create a new LList
	LList destructorTest;

	// Insert two letters at the beginning of the list is successful.
	std::cerr << "12- destructorTest.cons('F'). Expected: TRUE\t--\t" << destructorTest.cons('F') << std::endl;
	std::cerr << "12- destructorTest.cons('E'). Expected: TRUE\t--\t" << destructorTest.cons('E') << std::endl;
	std::cerr << "12- destructorTest.print(). Expected: [EF]\t--\t"; destructorTest.print();
}

int generalClassTest() {
	// Create a new LList
	std::cerr << "0- LList myLList; Expected: display 'LList created'\t--\t"; LList myLList;
	
	// Check and see if the new list is empty.
	std::cerr << "1- myLList.isEmpty(). Expected: TRUE\t--\t" << myLList.isEmpty() << std::endl;
	
	// Check and see the size of the list.
	std::cerr << "2- myLList.length(). Expected: 0\t--\t" << myLList.length() << std::endl;
	
	// Check and see if insertion at the beginning of the list is successful.
	std::cerr << "3- [ARRAY] before inserting the first ch. Expected: []\t--\t"; myLList.print();
	std::cerr << "3- myLList.cons('A'). Expected: TRUE\t--\t" << myLList.cons('A') << std::endl;
	std::cerr << "3- [ARRAY] after inserting the first ch. Expected: [A]\t--\t"; myLList.print();
	std::cerr << "3- myLList.cons('B'). Expected: TRUE\t--\t" << myLList.cons('B') << std::endl;
	std::cerr << "3- [ARRAY] after inserting the second ch. Expected: [BA]\t--\t"; myLList.print();

	// Check and see if characters are appended at the end of the list.
	std::cerr << "4- [ARRAY] before appending a ch. Expected: [BA]\t--\t"; myLList.print();
	std::cerr << "4- myLList.append('C'). Expected: TRUE\t--\t" << myLList.append('C') << std::endl;
	std::cerr << "4- [ARRAY] after appending a ch. Expected: [BAC]\t--\t"; myLList.print();
	std::cerr << "4- myLList.append('D'). Expected: TRUE\t--\t" << myLList.append('D') << std::endl;
	std::cerr << "4- [ARRAY] after appending a ch. Expected: [BACD]\t--\t"; myLList.print();
	std::cerr << "4- myLList.append('E'). Expected: TRUE\t--\t" << myLList.append('E') << std::endl;
	std::cerr << "4- [ARRAY] after appending the third ch. Expected: [BACDE]\t--\t"; myLList.print();

	// Check and see if the list is empty and its size.
	std::cerr << "5- myLList.isEmpty(). Expected: FALSE\t--\t" << myLList.isEmpty() << std::endl;
	std::cerr << "5- myLList.length(). Expected: 5\t--\t" << myLList.length() << std::endl;

	// Check and see the removal of a character not in the list.
	std::cerr << "6- [ARRAY] before an attempt to remove a character not in the list. Expected: [BACDE]\t--\t"; myLList.print();
	std::cerr << "6- myLList.remove('Z'). Expected: FALSE\t--\t" << myLList.remove('Z') << std::endl;

	// Check and see the removal of a character in the list.
	std::cerr << "6- myLList.remove('B'). Expected: TRUE\t--\t" << myLList.remove('B') << std::endl;
	std::cerr << "6- [ARRAY] after removing a ch in the list. Expected: [ACDE]\t--\t"; myLList.print();

	// Check and see if a ch is in the list.
	std::cerr << "8- [ARRAY] before finding characters in the list. Expected: [ACDE]\t--\t"; myLList.print();
	std::cerr << "8- myLList.found('Z'). Expected: FALSE\t--\t" << myLList.found('Z') << std::endl;
	std::cerr << "8- myLList.found('C'). Expected: TRUE\t--\t" << myLList.found('C') << std::endl;

	// Check and see the first character and the boolean value in each possible case.
	bool isThereFirst = true;
	LList emptyLList;
	std::cerr << "9- myLList.getFirst(isThereFirst). Expected: TRUE - A\t--\t" << isThereFirst << " - " << myLList.getFirst(isThereFirst) << std::endl;
	std::cerr << "9- emptyLList.getFirst(isThereFirst). Expected: FALSE - (blank)\t--\t" << isThereFirst << " - " << emptyLList.getFirst(isThereFirst) << std::endl;

	// Check and see if the list is reversed.
	std::cerr << "10- [ARRAY] before reversing its order. Expected: [ACDE]\t--\t"; myLList.print();
	std::cerr << "10- myLList.reverse() invoked." << std::endl; myLList.reverse();
	std::cerr << "10- [ARRAY] after reversing its order. Expected: [EDCA]\t--\t"; myLList.print();

	// Check and see if the copy constructor works.
	std::cerr << "11- Copy Constructor Test. LList myOtherLList(myLList); myOtherLList.print(). Expected: [EDCA] (same as 10)\t--\t";
	LList myOtherLList(myLList); myOtherLList.print();

	// Check and see if the destructor works.
	destructorTest();

	// Check and see if the assignment operator and copyAll() work.
	std::cerr << "13- Assignment operator, deleteAll() and copyAll() Test (within the assignment operator implementation)" << std::endl;
	emptyLList = myLList;
	std::cerr << "13- emptyLList = myLList; emptyLList.print(). Expected: [EDCA] (same as 10)\t--\t"; emptyLList.print();
	
	return 0;
}

/* == PART B ==
Once you have Part A running properly, write another test program that determines
what the longest possible linked list is. (You will be testing the heap size). You can do
this since both append and cons are defined to return true if successful and false
otherwise.
Write a new version of the implementation file of your class because you will want to
rewrite some functions to make them iterative to prevent your program from
crashing.
*/

void heapSizeTest() {
	LList* myList = new LList();
	unsigned nodesAllocated = 0;

	// Once the Heap is exhausted, an exception is thrown inside LList::cons(ch) and it returns false, thus exiting the loop
	while (myList->cons('A')) {
		nodesAllocated++;
	}

	std::cerr << "***cons exhausts the heap with " << nodesAllocated << " nodes\n\n";
}

int main() {
	generalClassTest();
	system("pause");

	heapSizeTest();

	system("pause");
	return 0;
}