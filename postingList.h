// Header --> Functions Declarations
#include <iostream>

using namespace std;

#ifndef POSTINGLIST_H
#define POSTINGLIST_H

class PostingList {
	struct Node {
		//Number of document line
		int line;
		//Times the word was found
		int count; 
		Node* next;
	};
	Node* head;
	int counter;
	//Total times the word was found
	int totalTimes;
public:
	PostingList();
	void add(int line, int count);
	int count();
	void print();
	~PostingList();	
};

#endif
