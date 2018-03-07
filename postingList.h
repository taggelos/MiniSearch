// Header --> Functions Declarations
#include <iostream>

using namespace std;

#ifndef POSTINGLIST_H
#define POSTINGLIST_H

class PostingList {
	struct Node {
		//Number of document line
		int line;
		//Times the word was found in a sentence
		int count; 
		Node* next;
		Node(int line);
	};
	Node* head;
	//Number of Nodes
	int numNodes;
	//Total times the word was found
	int totalTimes;
public:
	PostingList(int line);
	void add(int line);
	//int getCount(int line);
	int getTotalTimes();
	int getNumNodes();
	int countNodes();
	void print();
	~PostingList();	
};

#endif
