//Function Definitions
#include <iostream>
#include "heap.h"
using namespace std;

Heap::Heap(int s){
	size = s;
	array = new HeapNode*[s];
	numNodes = 0;
}

void Heap::add(int id, int score){
	if(size==numNodes){
		cerr << "Heap failed!" <<endl;
		return;
	}
	HeapNode* n = new HeapNode;
	n->id = id;
	n->score = score;
	int i = numNodes;
	while (i!=0 && array[parent(i)]->score < n->score){
		array[i]=array[parent(i)];
		i=parent(i);
	}
	array[i]=n;
	numNodes++;
	cout << n << "<-array[0]"<<endl;
}

HeapNode* Heap::popMax(){
	HeapNode* root= array[0];
	HeapNode* last = array[numNodes-1];
	int i = 0; //parent
	int l = 1; //left
	numNodes--;
	while(l<numNodes){
		int r = l+1;
		int max = l;
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

void Heap::swap(HeapNode **x, HeapNode **y)
{
	HeapNode* temp = *x;
	*x = *y;
	*y = temp;
}

int Heap::countNodes(){
	return numNodes;
}

Heap::~Heap(){

}
