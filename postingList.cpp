//Function Definitions
#include <iostream>
#include "postingList.h"
using namespace std;

PostingList::PostingList(){
	head = NULL;
	counter = 0;
}

void PostingList::add(int line,int count){
	Node* n = new Node;
	n->next = NULL;
	n->line= line;
	n->count= count;	
	if (head != NULL){
		Node* temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = n;
	}
	else {
		head = n;
	}
	counter++;
	totalTimes += count;
}

int PostingList::count(){
	return counter;
}

void PostingList::print(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "node-> Number of line: " << temp->line << " Times found: "<< temp->count<< endl;		
		temp = temp->next;
	}
	cout << "~ totalTimes found: "<< totalTimes << " ~"<< endl;
}

PostingList::~PostingList(){
	Node* temp = NULL;
	while(head -> next != NULL){
		temp = head->next;
		delete head;
		head = temp;
	}
}
