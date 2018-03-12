// Header --> Functions Declarations
#include <iostream>
#include "postingList.h"
#include "letterList.h"
#include <math.h> //log //floor
#include <cstring> //strcpy

using namespace std;

#ifndef WORDLIST_H
#define WORDLIST_H

class WordList {
	struct Node {
		char* word;
		Node* next;
		Node(char* word);
		~Node();
	};
	Node* head;
	//Number of Nodes (Lines or Queries)
	int numNodes;	
public:
	WordList();
	void add(char* word);
	int countNodes();
	void print();
	void search(LetterList* llist, const int& N, int* nwords);
	~WordList();	
};

#endif
