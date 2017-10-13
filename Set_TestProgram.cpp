/*
 *  Assignment #3, CPSC 2150
 * Student Last Name: Teles Lazaro Lucchesi
 * Student First Name: Rafael
 * Student Number: ********
 */

// Author: G. and M. Monagan
#include "Set.h"
#include <iostream>
#include <cstdlib>

void f(Set a) {
   a.insert(19);
}

Set g() {
   Set a;
   a.insert(3);
   a.insert(2);
   a.insert(5);
   return a;
}

void h() {
   Set local;
   local.insert(1);
   local.insert(2);
   std::cout << "a local set has values " << local << "\n";
}
   
int main() {
    using std::cout;
    using std::endl;
    Set s, t;
    cout << "empty set: " <<  s << endl; 
    cout << "\t expecting: { }\n";
    cout << "|s|=" << s.size() << endl;
    cout << "\t expecting:|s|= 0\n";
    s.insert(3); s.insert(1); s.insert(9); s.insert(3); s.insert(7); s.insert(5);
    cout << "s = " << s << endl; 
    cout << "\t expecting: s = { 1 3 5 7 9 }\n";
    t.insert(3); t.insert(5); t.insert(4); 
    cout << "with insertions: t = "<< t << endl; 
    cout << "\t expecting: t = { 3 4 5 }\n";
    Set a = s + t;
    cout << "s union t = " << a << endl;
    cout << "\t expecting: s = { 1 3 4 5 7 9 }\n";
    Set b = s * t;
    cout << "s intersect t = " << b << endl;
    cout << "\t expecting: t = { 3 5 }\n";
	
	cout << "\n== Aditional Tests ==\n";
	Set p, q;
	cout << "Empty sets p and q generated. " << endl;
	cout << "Test: remove a item from an empty set; p.remove(1); p = "; p.remove(1);
	cout << p << endl;
	cout << "\t expecting: p = { }\n\n";
	
	p.insert(2); p.insert(3); q.insert(2); q.insert(3); q.insert(5);
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "p < q = " << (p < q) << endl;
	cout << "\t expecting: 1 (TRUE)\n\n";
	
	cout << "Test: remove items from sets; p.remove(3); q.remove(5);" << endl;
	p.remove(3); q.remove(5);
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "\t expecting: p = { 2 }\n\t\t    q = { 2 3 }\n\n";

	p.insert(4); q.insert(1); q.insert(4);
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "p < q = " << (p < q) << endl;
	cout << "\t expecting: 1 (TRUE)\n\n";
	p.insert(3); q.remove(1);
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "p < q = " << (p < q) << endl;
	cout << "\t expecting: 0 (FALSE)\n\n";
	p.remove(3); p.remove(4); q.remove(2); q.remove(3); q.remove(4);
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "p < q = " << (p < q) << endl;
	cout << "\t expecting: 0 (FALSE)\n\n";
	p.remove(2); q.insert(2);
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "p < q = " << (p < q) << endl;
	cout << "\t expecting: 1 (TRUE)\n\n";
	cout << "== Big three Tests == (NDEBUG must be on)\n" << endl;
	cout << " Assignment operator" << endl;
	cout << "s = " << s << endl;
	cout << "q = " << q << endl;
	cout << "q = s;" << endl;
	q = s;
	cout << "q = " << q << endl;
	cout << "\t expecting: q = " << s << "\n" << endl;

	cout << " Copy Constructor" << endl;
	Set c(q);
	cout << "Set c(q);" << endl;
	cout << "c = " << c << endl;
	cout << "\t expecting: c = " << q << "\n" << endl;

	cout << " Destructor" << endl;
	h();
	
	system("pause");
    return 0;
}
