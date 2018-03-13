// Header --> Functions Declarations
#include <iostream>
#include "postingList.h"
#include "trie.h"
#include <math.h> //log //floor
#include <cstring> //strcpy
#include <iomanip> //precision

//ioctl
#include <cstdio>
#include <sys/ioctl.h>

#include "heap.h"

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
	void search(Trie* trie, const int& N, const int& K, char** documents, int* nwords);
	~WordList();	
};

#endif
