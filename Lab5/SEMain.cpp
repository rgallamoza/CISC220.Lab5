/*
 * SEMain.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: Debra
 */

#include "LLSE.hpp"
#include "Document.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

int main() {
	Document doc("Monet.txt");

	cout << "*****************************************************************" << endl;

	cout << "Test Cases" << endl;

	cout << "LLSE() and PrintLL():" << endl;

	cout << "Test 1:" << endl;
	LLSE ll1 = LLSE();
	ll1.printLL();

	cout << "Test 2:" << endl;
	LLSE ll2 = LLSE();
	ll2.printLL();

	cout << "Test 3:" << endl;
	LLSE ll3 = LLSE();
	ll3.printLL();				//Expecting LLSE to be empty

	cout << "*****************************************************************" << endl;

	cout << "addFirst(string x):" << endl;

	cout << "Test 1:" << endl;
	ll1.addFirst("hello");
	ll1.printLL();				//Expecting: hello:1, Size:1, Wordcount: 1

	cout << "Test 2:" << endl;
	ll2.addFirst("farewell");
	ll2.printLL();				//Expecting: farewell:1, Size:1, Wordcount: 1

	cout << "Test 3:" << endl;
	ll3.addFirst("bird");
	ll3.printLL();				//Expecting: bird:1, Size:1, Wordcount: 1

	cout << "*****************************************************************" << endl;

	cout << "addAtFirst(string x):" << endl;

	cout << "Test 1:" << endl;
	ll1.addAtFirst("bonjour");
	ll1.printLL();				//Expecting: bonjour:1, hello:1, Size:2, Wordcount:2

	cout << "Test 2:" << endl;
	ll2.addAtFirst("bye");
	ll2.printLL();				//Expecting: bye:1, farewell:1, Size:2, Wordcount:2

	cout << "Test 3:" << endl;
	ll3.addAtFirst("armadillo");
	ll3.printLL();				//Expecting: armadillo:1, bird:1, Size:2, Wordcount:2

	cout << "*****************************************************************" << endl;

	cout << "push(string x):" << endl;

	cout << "Test 1:" << endl;
	ll1.push("hola");
	ll1.printLL();				//Expecting: bonjour:1, hello:1, hola:1, Size: 3, Wordcount: 3

	cout << "Test 2:" << endl;
	ll2.push("salutations");
	ll2.printLL();				//Expecting: bye:1, farewell:1, salutations:1, Size: 3, Wordcount: 3

	cout << "Test 3:" << endl;
	ll3.push("crocodile");
	ll3.printLL();				//Expecting: armadillo:1, bird:1, crocodile:1, Size: 3, Wordcount: 3

	cout << "*****************************************************************" << endl;

	cout << "insertUnique(string x):" << endl;

	cout << "Test 1:" << endl;
	ll1.insertUnique("konnichiwa");
	ll1.printLL();				//Expecting: bonjour:1, hello:1, hola:1, konnichiwa:1, Size: 4, Wordcount: 4

	cout << "Test 2:" << endl;
	ll1.insertUnique("konnichiwa");
	ll1.printLL();				//Expecting: bonjour:1, hello:1, hola:1, konnichiwa:2, Size: 4, Wordcount: 5

	cout << "Test 3:" << endl;
	ll2.insertUnique("goodbye");
	ll2.printLL();				//Expecting: bye:1, farewell:1, goodbye:1, salutations:1, Size: 4, Wordcount: 4

	cout << "Test 4:" << endl;
	ll2.insertUnique("goodbye");
	ll2.printLL();				//Expecting: bye:1, farewell:1, goodbye:2, salutations:1, Size: 4, Wordcount: 5

	cout << "Test 5:" << endl;
	ll3.insertUnique("ant");
	ll3.printLL();				//Expecting: ant:1, armadillo:1, bird:1, crocodile:1, Size: 4, Wordcount: 4

	cout << "Test 6:" << endl;
	ll3.insertUnique("ant");
	ll3.printLL();				//Expecting: ant:2, armadillo:1, bird:1, crocodile:1, Size: 4, Wordcount: 5

	cout << "*****************************************************************" << endl;

	cout << "findInsert(string x):" << endl;

	cout << "Test 1:" << endl;
	Node *tmp1 = ll1.findInsert("bonjour");
	cout << (tmp1 == NULL) << endl;			//Expecting true (1)

	cout << "Test 2:" << endl;
	Node *tmp2 = ll2.findInsert("howdy");
	cout << (tmp2 == NULL) << endl;			//Expecting false (0)
	//cout << tmp2->word << endl;				//Expecting goodbye

	cout << "Test 3:" << endl;
	Node *tmp3 = ll3.findInsert("cow");
	cout << (tmp3 == NULL) << endl;			//Expecting false (0)
	//cout << tmp3->word << endl;				//Expecting bird

	cout << "*****************************************************************" << endl;

	cout << "remFirst():" << endl;

	cout << "Test 1:" << endl;
	ll1.remFirst();
	ll1.printLL();				//Expecting: hello:1, hola:1, konnichiwa:2, Size: 3, Wordcount: 4

	cout << "Test 2:" << endl;
	ll2.remFirst();
	ll2.printLL();				//Expecting: farewell:1, goodbye:2, salutations:1, Size: 3, Wordcount: 4

	cout << "Test 3:" << endl;
	ll3.remFirst();
	ll3.printLL();				//Expecting: armadillo:1, bird:1, crocodile:1, Size: 3, Wordcount: 3


	cout << "*****************************************************************" << endl;

	cout << "pop():" << endl;

	cout << "Test 1:" << endl;
	ll1.pop();
	ll1.printLL();				//Expecting: hello:1, hola:1, Size: 2, Wordcount: 2

	cout << "Test 2:" << endl;
	ll2.pop();
	ll2.printLL();				//Expecting: farewell:1, goodbye:2, Size: 2, Wordcount: 3

	cout << "Test 3:" << endl;
	ll3.pop();
	ll3.printLL();				//Expecting: armadillo:1, bird:1, Size: 2, Wordcount: 2

	cout << "*****************************************************************" << endl;

	cout << "normalizeCounts() and eliminateLowWords():" << endl;

	cout << "Test 1:" << endl;
	for(int i=0;i<298;i++){
		ll1.insertUnique("hello");
	}
	ll1.normalizeCounts();
	ll1.eliminateLowWords();
	ll1.printLL();				//Expecting: hello:~0.99, Size: 1, Wordcount: 299

	cout << "Test 2:" << endl;
	for(int i=0;i<297;i++){
		ll2.insertUnique("goodbye");
	}
	ll2.normalizeCounts();
	ll2.eliminateLowWords();
	ll2.printLL();				//Expecting: goodbye:~0.99, Size: 1, Wordcount: 299

	cout << "Test 3:" << endl;
	for(int i=0;i<298;i++){
		ll3.insertUnique("armadillo");
	}
	ll3.normalizeCounts();
	ll3.eliminateLowWords();
	ll3.printLL();				//Expecting: armadillo:~0.99, Size: 1, Wordcount: 299

	return 0;
}
