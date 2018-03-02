// Header --> Functions Declarations
#include <iostream>
#include "postingList.h"

using namespace std;

#ifndef LETTERLIST_H
#define LETTERLIST_H

class LetterList {
	struct Node {
		//Letter
		char letter;
		Node* next;
		Node* right;
		PostingList* plist;
	};
	Node* head;
	int counter;
	PostingList * p;
public:
	LetterList();
	void add(char* word);
	int count();
	//void print();
	void printNext();
	void printRight();
	~LetterList();	
};

#endif
