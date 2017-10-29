/*
 * LLSE.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: ryan
 */

#include "LLSE.hpp"
#include <string>
using namespace std;

LLSE::LLSE(){
	first = NULL;
	last = NULL;
	size = 0;
	wordcount = 0;
}

LLSE::~LLSE(){
	Node *tmp;

	while (first != NULL){
		tmp = first->next;
		delete first;
		first = tmp;
	}
}

void LLSE::printLL(){
	Node *tmp = first;

	while (tmp != NULL){
		cout << tmp->word << ":" << tmp->count << ",";
		tmp = tmp->next;
	}

	cout << endl;
}

void LLSE::addFirst(string x){
	Node *newnode = new Node(x);

	first = newnode;
	last = newnode;

	size++;
	wordcount++;
}

void LLSE::addAtFirst(string x){
	Node *tmp = first;
	Node *newfirst = new Node(x);

	tmp->prev = newfirst;
	newfirst->next = tmp;
	first = newfirst;

	size++;
	wordcount++;
}

void LLSE::push(string x){
	Node *tmp = last;
	Node *newlast = new Node(x);

	tmp->next = newlast;
	newlast->prev = tmp;
	last = newlast;

	size++;
	wordcount++;
}

void LLSE::insertUnique(string x){

	if(first == NULL){
		addFirst(x);
	}
	else if(x < first->word){
		addAtFirst(x);
	}
	else if(x > last->word){
		push(x);
	}
	else{
		Node *insert = findInsert(x);

		if(insert != NULL){
			Node *newnode = new Node(x);
			/*
			if(insert->next == NULL){ 	// if insert->next == NULL then insert is last node
				insert->next = newnode;
				last = newnode;
			}
			*/
			Node *tmp = insert->next;
			insert->next = newnode;
			tmp->prev = newnode;

			size++;
			wordcount++;
		}
	}
}

Node *LLSE::findInsert(string x){
	Node *tmp = first;
	Node *insert;

	while(tmp != NULL){
		tmp = tmp->next;
		if(tmp->word == x){
			tmp->count++;
			wordcount++;

			insert = NULL;
			break;
		}
		else if(tmp->word > x){
			insert = tmp->prev;
			break;
		}
		else if(tmp->next == NULL){
			insert = tmp;
			break;
		}
	}

	return insert;
}

void LLSE::normalizeCounts(){
	Node *tmp = first;

	while(tmp != NULL){
		tmp->count /= wordcount;
		tmp = tmp->next;
	}
}

string LLSE::remFirst(){
	Node *tmp = first->next;

	size--;
	wordcount -= first->count;

	return first->word;

	tmp->prev = NULL;
	delete first;
	first = tmp;
}

string LLSE::pop(){
	Node *tmp = last->prev;

	size--;
	wordcount -= last->count;

	return last->word;

	tmp->next = NULL;
	delete last;
	last = tmp;
}

string LLSE::remNext(Node *n){
	Node *tmp = n->next;

	if(tmp->next == NULL){ 		// if tmp->next == NULL then tmp is last node
		size--;
		wordcount -= tmp->count;

		return tmp->word;

		n->next = NULL;
		delete tmp;
		last = n;
	}
	else{
		size--;
		wordcount -= tmp->count;

		return tmp->word;

		n->next = tmp->next;
		tmp->next->prev = n;
		delete tmp;
	}
}

void LLSE::eliminateLowWords(){
	while(first->count < .004){
		remFirst();
	}
	while(last->count < .004){
		pop();
	}

	Node *tmp = first;

	while(tmp->next != NULL){
		if(tmp->next->count < .004){
			remNext(tmp);
		}
		tmp = tmp->next;
	}
}
