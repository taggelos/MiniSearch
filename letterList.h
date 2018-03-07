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
		Node* down;
		Node* right;
		//Node* children;
		PostingList* plist;
		Node(char letter, PostingList* plist = NULL);
		~Node();
	};
	Node* head;
	int numNodes; //Node (Letter) counter with root node inside
	int numWords; //Word counter
	//PostingList * p; //Hashlist for end nodes of words?
	//TODODELETE
	struct TODODELETE{
		Node* m;
		TODODELETE* next;
	};
	Node* node(char letter, PostingList* plist = NULL);
	TODODELETE* del;
public:
	LetterList();
	void add(char* word, int lineNum);
	void search(char* word);
	int countNodes();
	void print();
	void printDown();
	void printRight();
	void printLeafs();
	~LetterList();	
};

#endif
