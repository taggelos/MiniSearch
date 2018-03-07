//Function Definitions
#include <iostream>
#include "postingList.h"
using namespace std;

PostingList::Node::Node(int l){
	next = NULL;
	line= l;
	count= 1;
}

PostingList::PostingList(int line){
	head = new Node(line);
	numNodes = 1;
	totalTimes = 1;
}

void PostingList::add(int line){
	Node* temp = head;
	bool found = false;
	while(temp!= NULL){
		if (temp->line == line) {
			found = true;
			temp->count++;
			break;
		}
		temp = temp->next;
	}
	if (!found){
		Node* n = new Node(line);
		temp = head;
		// O(1) to be changed
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = n;
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
	while(head!= NULL){
		temp = head;
		head = head->next;
		delete temp;
	}
}
