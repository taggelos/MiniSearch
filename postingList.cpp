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
	while(1){
		if (temp->line == line) {
			temp->count++;
			break;
		}
		if (temp->next==NULL){
			Node* n = new Node(line);
			temp->next = n;
			numNodes++;
			break;
		}
		temp = temp->next;
	}
	totalTimes += 1;
}

void PostingList::print(){
	Node* temp = head;
	while(temp!= NULL){
		//cout << "node-> Number of line: " << temp->line << " Times found: "<< temp->count<< endl;
		temp = temp->next;
	}
	//cout << "~ totalTimes found: "<< totalTimes << " ~"<< endl;
}

int PostingList::getTotalTimes(){
	return totalTimes;
}

void PostingList::score(double* bm25, bool* flags, int avgdl, int N, int* nwords){
	int D=0;
	//IDF
	double curIdf;
	Node* temp = head;
	while(temp!= NULL){
		curIdf= idf(N,numNodes);
		//number of words in a document -> |D|
		D = nwords[temp->line];
		// term frequency is temp->count
		bm25[temp->line]+=fscore(curIdf,temp->count,avgdl,D);
		flags[temp->line] = true;
		temp = temp->next;
	}

}

double PostingList::idf(const int& N, const int& nqi ){
	return log((N - nqi + 0.5)/(nqi + 0.5));
}

double PostingList::fscore(const double& idf, const int& tf, const int& avgdl, const int& D, const double& k1, const double& b){
	//return only 4 digits after comma
	return idf * (tf * (k1 + 1)) / (tf + k1 * (1 - b + b * D/avgdl));
}

int PostingList::tf(int line){
	Node* temp = head;
	while(temp!= NULL){
		if (temp->line == line){
			return temp->count;
		}
		temp = temp->next;
	}
	return 0;
}

PostingList::~PostingList(){
	Node* temp = NULL;
	while(head!= NULL){
		temp = head;
		head = head->next;
		delete temp;
	}
}