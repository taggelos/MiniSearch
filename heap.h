// Header --> Functions Declarations
#include <iostream>

using namespace std;

#ifndef HEAP_H
#define HEAP_H

struct HeapNode {
	//Number of file line
	int id;
	//Score
	int score;
};

class Heap {
	//Array to elements
	HeapNode** array;
	//Max size of the heap
	int size;
	//Number of Nodes
	int numNodes;
	int parent(int i);
	int left(int i);
	int right(int i);
	void swap(HeapNode** x, HeapNode** y);
public:
	Heap(int size);
	void add(int id, int score);
	HeapNode* popMax();
	int countNodes();
	~Heap();
};

#endif
