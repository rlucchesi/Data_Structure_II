/*
 *  Assignment #3, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: ********
 */

#include "SList.h"
#include <time.h>	// used as input for the srand function

const int NUM_TRIALS = 50;

/*
 * Test functions Prototypes
 */
// General Test of SList methods
int generalClassTest();
// Destructor Tester (and insertion of repeated items)
int destructorTest();

/*
 * Skiplist analysis using random, ascending and descending ordered items
 * Number of trials (constant) is used to get an average so that your data is more accurate
*/
unsigned skipListRandom(int numItems);
unsigned skipListAscending(int numItems);
unsigned skipListDescending(int numItems);

/*
 * General Test of SList methods
 */
int generalClassTest() {
	std::cerr << "\n\t ===== General Class Test =====\n\n";
	std::cerr << "SList a; \t\t\t-\tSkip List created\n";
	SList a;
	std::cerr << "a.setOutputDelimeter(\" \"); \t-\tDefine output Delimiter\n\n";
	a.setOutputDelimeter(" ");

	std::cerr << "a.dumpTopList(std::cerr); \t-\tPrint top List\n";
	a.dumpTopList(std::cerr);
	std::cerr << "\tExpected: [ ]\n\n";

	std::cerr << "a.printAllInOrder(std::cerr); \t-\tPrint bottom List\n";
	a.printAllInOrder(std::cerr);
	std::cerr << "\tExpected: [ ]\n\n";

	std::cerr << "a.getTraversals(); \t\t-\tPrint # traversals\n";
	std::cerr << "Traversals: " << a.getTraversals() << std::endl;
	std::cerr << "\tExpected: 0\n\n";

	std::cerr << "a.insert(7); \t\t\t-\tInsert 1 item\n";
	a.insert(7);
	a.dumpTopList(std::cerr);
	a.printAllInOrder(std::cerr);
	std::cerr << "\tExpected: [ 7 ] in both lists\n";
	std::cerr << "Traversals: " << a.getTraversals() << std::endl;
	std::cerr << "\tExpected: 1\n\n";

	std::cerr << "a.insert(3); a.insert(5); \t-\tInsert 2+ item (out of order)\n";
	a.insert(3);
	a.insert(5);
	a.dumpTopList(std::cerr);
	a.printAllInOrder(std::cerr);
	std::cerr << "\tExpected: top List [ 3 ]\n\t\tbottom List [ 3 5 7 ]\n";
	std::cerr << "Traversals: " << a.getTraversals() << std::endl;
	std::cerr << "\tExpected: 3\n\n";

	std::cerr << "a.found(5); \t\t\t-\tSearching for an item in the List\n";
	std::cerr << a.found(5) << std::endl;
	std::cerr << "\tExpected: 1 (TRUE)\n\n";
	std::cerr << "a.getComparisons(); \t\t-\tGetting the number of comparisons for the last search (found(5))\n";
	std::cerr << "Comparisons: " << a.getComparisons() << std::endl;
	std::cerr << "\tExpected: 5\n\n";

	std::cerr << "a.found(6); \t\t\t-\tSearching for an item not in the List\n";
	std::cerr << a.found(6) << std::endl;
	std::cerr << "\tExpected: 0 (FALSE)\n\n";
	std::cerr << "a.getComparisons(); \t\t-\tGetting the number of comparisons for the last search a.found(6)\n";
	std::cerr << "Comparisons: " << a.getComparisons() << std::endl;
	std::cerr << "\tExpected: 6\n\n";

	std::cerr << "a.insert(1); \t\t\t-\tInsert 1 item (to test how the top List grows)\n";
	a.insert(1);
	a.dumpTopList(std::cerr);
	a.printAllInOrder(std::cerr);
	std::cerr << "\tExpected: top List [ 1 5 ]\n\t\tbottom List [ 1 3 5 7 ]\n";
	std::cerr << "Traversals: " << a.getTraversals() << std::endl;
	std::cerr << "\tExpected: 7\n\n";

	std::cerr << "a.numberOfElements(); \t\t-\tNumber of elements in the skip list\n";
	std::cerr << "Number: " << a.numberOfElements() << std::endl;
	std::cerr << "\tExpected: 4\n\n";

	std::cerr << "SList b(a); \t\t\t-\tCopy Constructor Test\n";
	SList b(a);
	b.dumpTopList(std::cerr);
	b.printAllInOrder(std::cerr);
	std::cerr << "\tExpected: top List [ 1 5 ]\n\t\tbottom List [ 1 3 5 7 ]\n";
	std::cerr << "Number: " << b.numberOfElements() << std::endl;
	std::cerr << "\tExpected: 4\n\n";

	std::cerr << "c = a; \t\t\t\t-\tAssignment Operator Test\n";
	SList c;
	c = a;
	c.dumpTopList(std::cerr);
	c.printAllInOrder(std::cerr);
	std::cerr << "\tExpected: top List [ 1 5 ]\n\t\tbottom List [ 1 3 5 7 ]\n";
	std::cerr << "Number: " << b.numberOfElements() << std::endl;
	std::cerr << "\tExpected: 4\n\n";

	destructorTest();
	std::cerr << "\tExpected: called the Destructor+++++++++++++++\n\n";

	std::cerr << "c.reset(); \t\t\t-\tAssignment Operator Test\n";
	c.reset();
	c.dumpTopList(std::cerr);
	c.printAllInOrder(std::cerr);
	std::cerr << "\tExpected: top List [ ]\n\t\tbottom List [ ]\n";
	std::cerr << "Number: " << c.numberOfElements() << std::endl;
	std::cerr << "\tExpected: 0\n";
	std::cerr << "Traversals: " << c.getTraversals() << std::endl;
	std::cerr << "\tExpected: 0\n\n";

	std::cerr << "a.printAllInOrder(std::cerr); \t-\tBecause I did c = a and then c.reset(), I should see if a is as expected\n";
	a.dumpTopList(std::cerr);
	a.printAllInOrder(std::cerr);
	std::cerr << "\tExpected: top List [ 1 5 ]\n\t\tbottom List [ 1 3 5 7 ]\n\n";

	return 0;
}

/*
 * Destructor Tester (and insertion of repeated items)
 */
int destructorTest() {
	SList z;
	z.setOutputDelimeter(" ");
	z.insert(100);
	z.insert(900);
	z.insert(300);
	z.insert(400);
	z.insert(500);
	z.insert(500);
	z.insert(900);
	z.insert(500);
	z.insert(800);
	std::cerr << "SList z; \t\t\t-\tDestructor Test (debug mode must be on) AND insertion of repeated items\n";
	z.dumpTopList(std::cerr);
	z.printAllInOrder(std::cerr);
	return 0;
}

/*
 * Insertion of randomly generated items
 * The number of items to be inserted is defined as a parameter
 */
unsigned skipListRandom(int numItems) {
	srand(time(0));
	unsigned sum = 0;
	SList r;

	for (int trials = 0; trials < NUM_TRIALS; trials++) {
		r.reset();
		for (int i = 0; i < numItems; i++) {
			r.insert(rand() % numItems);
		}
		sum += r.getTraversals();
	}

	std::cerr << "RANDOM TEST (last trial): n = " + std::to_string(numItems) + "\n";
	r.found(numItems / 4);
	std::cerr << "Searching: " + std::to_string(numItems / 4) + ". Comparisons: "
		+ std::to_string(r.getComparisons()) + "\n";
	r.found(numItems / 2);
	std::cerr << "Searching: " + std::to_string(numItems / 2) + ". Comparisons: "
		+ std::to_string(r.getComparisons()) + "\n";
	r.found((numItems / 4) * 3);
	std::cerr << "Searching: " + std::to_string((numItems / 4) * 3) + ". Comparisons: "
		+ std::to_string(r.getComparisons()) + "\n";
	r.found(numItems + 1);
	std::cerr << "Searching (not in List): " + std::to_string(numItems + 1) + ". Comparisons: "
		+ std::to_string(r.getComparisons()) + "\n\n";

	return (double)(sum / NUM_TRIALS);
}

/*
 * Insertion of ascending ordered items
 * The number of items to be inserted is defined as a parameter
 */
unsigned skipListAscending(int numItems) {
	unsigned sum = 0;
	SList a;
	
	for (int trials = 0; trials < NUM_TRIALS; trials++) {
		a.reset();
		for (int i = 0; i < numItems; i++) {
			a.insert(i);
		}
		sum += a.getTraversals();
	}

	std::cerr << "ASCENDING TEST (last trial): n = " + std::to_string(numItems) + "\n";
	a.found(numItems / 4);
	std::cerr << "Searching: " + std::to_string(numItems / 4) + ". Comparisons: "
		+ std::to_string(a.getComparisons()) + "\n";
	a.found(numItems / 2);
	std::cerr << "Searching: " + std::to_string(numItems / 2) + ". Comparisons: "
		+ std::to_string(a.getComparisons()) + "\n";
	a.found((numItems / 4) * 3);
	std::cerr << "Searching: " + std::to_string((numItems / 4) * 3) + ". Comparisons: "
		+ std::to_string(a.getComparisons()) + "\n";
	a.found(numItems + 1);
	std::cerr << "Searching (not in List): " + std::to_string(numItems + 1) + ". Comparisons: "
		+ std::to_string(a.getComparisons()) + "\n\n";

	return (double)(sum / NUM_TRIALS);
}

/*
 * Insertion of descending ordered items
 * The number of items to be inserted is defined as a parameter
 */
unsigned skipListDescending(int numItems) {
	unsigned sum = 0;
	SList d;

	for (int trials = 0; trials < NUM_TRIALS; trials++) {
		d.reset();
		for (int i = numItems; i > 0; i--) {
			d.insert(i);
		}
		sum += d.getTraversals();
	}

	std::cerr << "DESCENDING TEST (last trial): n = " + std::to_string(numItems) + "\n";
	d.found(numItems / 4);
	std::cerr << "Searching: " + std::to_string(numItems / 4) + ". Comparisons: "
		+ std::to_string(d.getComparisons()) + "\n";
	d.found(numItems / 2);
	std::cerr << "Searching: " + std::to_string(numItems / 2) + ". Comparisons: "
		+ std::to_string(d.getComparisons()) + "\n";
	d.found((numItems / 4) * 3);
	std::cerr << "Searching: " + std::to_string((numItems / 4) * 3) + ". Comparisons: "
		+ std::to_string(d.getComparisons()) + "\n";
	d.found(numItems + 1);
	std::cerr << "Searching (not in List): " + std::to_string(numItems + 1) + ". Comparisons: "
		+ std::to_string(d.getComparisons()) + "\n\n";

	return (double) (sum / NUM_TRIALS);
}



int main() {
	generalClassTest();
	
	std::cerr << "\t ===== Traversals and Comparisons =====\n\n";

	unsigned random[] = { skipListRandom(1250), skipListRandom(2500), skipListRandom(5000),
		skipListRandom(10000) };
	unsigned ascending[] = { skipListAscending(1250), skipListAscending(2500), skipListAscending(5000),
		skipListAscending(10000) };
	unsigned descending[] = { skipListDescending(1250), skipListDescending(2500), skipListDescending(5000),
		skipListDescending(10000) };

	printf("Type \\ N\t%10d\t%10d\t%10d\t%10d\tRatio (10000 / 5000)\n", 1250, 2500, 5000, 10000);
	printf("Random\t\t%10d\t%10d\t%10d\t%10d\t%10f\n", random[0], random[1], random[2], random[3], (double) random[3] / random[2]);
	printf("Ascending\t%10d\t%10d\t%10d\t%10d\t%10f\n", ascending[0], ascending[1], ascending[2], ascending[3], (double) ascending[3] / ascending[2]);
	printf("Descending\t%10d\t%10d\t%10d\t%10d\t%10f\n\n", descending[0], descending[1], descending[2], descending[3], (double) descending[3] / descending[2]);
	printf("Number of trials for each N: %d\n\n", NUM_TRIALS);
	
	system("pause");
	return 0;
}
