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

	cout << "Size: " << size << endl;
	cout << "Wordcount: " << wordcount << endl;
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

			Node *tmp = insert->next;
			insert->next = newnode;
			newnode->prev = insert;
			tmp->prev = newnode;
			newnode->next = tmp;

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
	Node *target = first;
	Node *tmp = first->next;
	string word = target->word;

	size--;
	wordcount -= target->count;

	tmp->prev = NULL;
	first = tmp;

	delete target;

	return word;
}

string LLSE::pop(){
	Node *target = last;
	Node *tmp = last->prev;
	string word = target->word;

	size--;
	wordcount -= target->count;

	tmp->next = NULL;
	last = tmp;

	delete target;

	return word;
}

string LLSE::remNext(Node *n){
	Node *target = n->next;
	Node *tmp = n->next->next;
	string word = target->word;

	size--;
	wordcount -= target->count;

	n->next = tmp;
	tmp->prev = n;

	delete target;

	return word;
}

void LLSE::eliminateLowWords(){
	while(first->count < .004){
		cout << "removing " << remFirst() << endl;
	}
	while(last->count < .004){
		cout << "removing " << pop() << endl;
	}

	Node *tmp = first;

	while(tmp->next != NULL){
		remove:
		if(tmp->next->count < .004){
			cout << "removing " << remNext(tmp) << endl;
			goto remove;
		}
		tmp = tmp->next;
	}
}
