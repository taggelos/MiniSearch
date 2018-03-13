//Function Definitions
#include <iostream>
#include "heap.h"
using namespace std;

Heap::Heap(int s){
	size = s;
	array = new HeapNode*[s];
	numNodes = 0;
}

void Heap::add(int id, double score){
	if(size==numNodes){
		cerr << "Heap failed!" <<endl;
		return;
	}
	HeapNode* n = new HeapNode;
	n->id = id;
	n->score = score;
	int i = numNodes;
	//finding max
	while (i!=0 && array[parent(i)]->score < n->score){
		array[i]=array[parent(i)];
		i=parent(i);
	}
	array[i]=n;
	numNodes++;
}

HeapNode* Heap::popMax(){
	if(numNodes==0) return NULL;
	HeapNode* root= array[0];
	HeapNode* last = array[numNodes-1];
	//parent
	int i = 0;
	//left
	int l = 1;
	numNodes--;
	while(l<numNodes){
		int r = l+1;
		int max = l;
		//Find max value
		if(r<numNodes && array[r]->score > array[l]->score){
			max = r;
		}
		if (array[max]->score > last->score){
			array[i] = array[max];
			i = max;
			l = left(i);
		}
		else break;
	}
	array[i] = last;
	return root;
}

int Heap::parent(int i){
	return (i-1)/2;
}

int Heap::left(int i){
	return (2*i + 1);
}

int Heap::right(int i){
	return (2*i + 2);
}

Heap::~Heap(){
	for (int i=0; i < numNodes ; i++){
		delete array[i];
	}
	delete[] array;
}