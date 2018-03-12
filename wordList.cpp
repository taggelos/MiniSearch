//Function Definitions
#include <iostream>
#include "wordList.h"
using namespace std;

WordList::Node::Node(char* w){
	next = NULL;
	word = new char[strlen(w)+1];
	strcpy(word,w);
}

WordList::Node::~Node(){
	delete[] word;
}

WordList::WordList(){
	head = NULL;
	numNodes = 1;
}

void WordList::add(char* word){
	// O ( 1 ) insertion
	if (head==NULL){
		head = new Node(word);
		return;
	}
	Node * n = new Node(word);
	n->next = head;
	head = n;
	numNodes++;
}

void WordList::print(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "node-> word: " << temp->word << "  totalnodes->"<< numNodes<< endl;		
		temp = temp->next;
	}
}

void WordList::search(LetterList* llist, const int& N, int* nwords){
	double bm25 [N]={};
	int avgdl = nwords[N] / N; // average number of words
	Node* temp = head;
	while(temp!= NULL){
		cout<<"~~~~SEARCHING "<< " red "<<"~~~~"<<endl;
		PostingList* plist = llist->search(temp->word);
		if (plist!=NULL){		
			plist->score(bm25, avgdl, N, nwords);
		}
		temp=temp->next;
	}
	//insert in heap
	//for (int i =0; i<N; i++){
}

int WordList::countNodes(){
	return numNodes;
}

WordList::~WordList(){
	Node* temp = NULL;
	while(head!= NULL){
		temp = head;
		head = head->next;
		delete temp;
	}
}
