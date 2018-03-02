//Function Definitions
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include "letterList.h"
using namespace std;

LetterList::LetterList(){
	head = NULL;
	counter = 0;
}

void LetterList::add(char* word){
	cout << "Splitting WORD "<< word << " into LETTERS:" << endl;	
	for (int i=0; i < strlen(word) ; i++){
		Node* n = new Node;
		n->next = NULL;
		n->right = NULL;
		n->letter= word[i];
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
	}
}

int LetterList::count(){
	return counter;
}

void LetterList::printNext(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "node next-> Letter stored: " << temp->letter << endl;		
		temp = temp->next;
	}
}

void LetterList::printRight(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "node right-> Letter stored: " << temp->letter << endl;		
		temp = temp->right;
	}
}

LetterList::~LetterList(){
	Node* temp = NULL;
	while(head -> next != NULL){
		temp = head->next;
		delete head;
		head = temp;
	}
}
