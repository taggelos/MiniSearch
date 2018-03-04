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
		Node* left;
		Node* right;
		PostingList* plist;
	};
	Node* head;
	int numNodes; //Node (Letter) counter
	int numWords; //Word counter
	PostingList * p; //Hashtable for end nodes of words?
public:
	LetterList();
	void add(char* word, int lineNum);
	int countNodes();
	void printLeft();
	void printRight();
	void printLeafs();
	~LetterList();	
};

#endif
