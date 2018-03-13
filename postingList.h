// Header --> Functions Declarations
#include <iostream>
#include <cmath> //log //floor

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
	double idf(const int& n, const int& nqi);
	double fscore(const double& idf, const int& tf, const int& avgdl, const int& D, const double& k1 = 1.2, const double& b = 0.75);
public:
	PostingList(int line);
	void add(int line);
	int getTotalTimes();
	//int countNodes();
	void score(double* bm25, int avgdl, int N, int* nwords);
	//term frequency function
	int tf(int line);
	void print();
	~PostingList();	
};

#endif
