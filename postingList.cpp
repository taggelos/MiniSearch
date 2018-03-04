//Function Definitions
#include <iostream>
#include "postingList.h"
using namespace std;

PostingList::PostingList(){
	head = NULL;
	numNodes = 0;
}

void PostingList::add(int line){
	Node* temp = head;
	bool found = false;
	while(temp!= NULL){
		if (temp->line == line) {
			found = true;
			break;
		}
		temp = temp->next;
	}
	if (found) temp->count++;
	else{
		Node* n = new Node;
		n->next = NULL;
		n->line= line;
		n->count= 1;	
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
		numNodes++;
	}
	totalTimes += 1;
}

int PostingList::countNodes(){
	return numNodes;
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
