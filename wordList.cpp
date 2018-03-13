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

int countDigits(int n){
	int count = 0;
	while (n != 0) {
		n = n / 10;
		++count;
	}
	return count;
}

void printSpaces(int num){
	for (int i=0; i<num; i++) cout <<" ";
}

void specialPrint(int i, HeapNode* hn, char** documents){
	//strstr
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	int start = countDigits(i) + countDigits(hn->id) + countDigits((int)hn->score) + 5 + 6;
	if (hn->score<0) {
		start+=1;
		cout << "+1"<<endl;
	}
	printSpaces(start);
	cout << "<-"<<start <<endl;
	cout << i << "."<<"("<< hn->id <<")"<< "[" << setprecision(4) << fixed << hn->score << "] " << documents[hn->id] <<endl;
}

void WordList::search(Trie* trie, const int& N, const int& K, char** documents, int* nwords){
	double bm25 [N]={};
	int avgdl = nwords[N] / N; // average number of words
	Node* temp = head;
	while(temp!= NULL){
		PostingList* plist = trie->search(temp->word);
		if (plist!=NULL){
			plist->score(bm25, avgdl, N, nwords);
		}
		temp=temp->next;
	}
	Heap h(N);
	for (int i=0; i<N; i++){
		if (bm25[i]!=0){
			h.add(i,bm25[i]);
		}
	}
	HeapNode* hn;
	for (int i=1; i<=K; i++){
		hn = h.popMax();
		if(hn==NULL) break;
		specialPrint(i,hn,documents);
		//cout << i << "."<<"("<< hn->id <<")"<< "[" << setprecision(4) << fixed << hn->score << "] " << documents[hn->id] <<endl;
		delete hn;
	}
	if(hn==NULL) cout << "yoloooo\n";
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
