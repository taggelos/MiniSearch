//Function Definitions
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include "letterList.h"
#include "postingList.h"
using namespace std;

LetterList::LetterList(){
	head = NULL;
	numNodes = 0;
	numWords = 0;
}

void LetterList::add(char* word, int lineNum){
	Node* temp = head;
	cout << "Splitting WORD "<< word << " into LETTERS" << endl;
	for (int i=0; i < strlen(word) ; i++){
		cout << " $$$$$here letter -> " << word[i]<<endl;
		if (head != NULL){
			/*//Same level search
			while (temp!=NULL && temp->letter != word[i]){
				if()
				temp=temp->right;
			}*/
			if (temp->left == NULL){
				cout << " new node with " << word[i]<<endl;		
				//Create new node
				Node* n = new Node;
				n->left = NULL;
				n->right = NULL;
				n->letter = word[i];
				n->plist = NULL;
				if(i!=strlen(word)-1){
					cout << "##Keep from the new letter!"<<endl;
					temp = n;
				}		
			}
			else if (temp->left->letter != word[i] ){
				if (temp->left->right == NULL){
					cout << " new RIGHTnode with " << word[i]<<endl;
					Node* n = new Node;
					n->left = NULL;
					n->right = NULL;
					n->letter = word[i];
					n->plist = NULL;
					if(i!=strlen(word)-1)
						temp = n;
				}
				else if(temp->left->right->letter == word[i]){
					cout << " Go RIGHT with same " << word[i]<<endl;
					temp=temp->right;				
				}
			}
			else {
				cout << " SAME node " << word[i] <<endl;
				//Traverse the trie if we have the character
				if (temp->left->letter == word[i]){
					temp = temp->left;
					cout << " GO LEFT " << word[i]<<endl;
				}
				else {
					if (temp->right!=NULL){
						temp = temp->right;
						cout << " GO RIGHT " << word[i]<<endl;
					}
					else{
						Node* n = new Node;
						n->left = NULL;
						n->right = NULL;
						n->letter = word[i];
						n->plist = NULL;
						if(i!=strlen(word)-1)
							temp = n;
					}
				}
			}
			//Last Node of word
			if(i==strlen(word)-1){
				cout << "Last letter of word " << word[i] << "   :'("<<endl;
				//Initialize postingList
				if(temp->plist == NULL){
					cout << "Mark LEAF with postinglist"<<endl;
					Node* n = new Node;
					n->left = NULL;
					n->right = NULL;
					n->letter = word[i];
					n->plist= new PostingList;
					n->plist->add(lineNum);
					temp->left == n;
					numNodes++;
				}
				//Leaf node means we met an old word
				else{
					cout << "met AN OLD FRIENDOULINO! " <<endl;
					temp->plist->add(lineNum);
				}
			}
		}
		else {
			cout << " here 1st node -> " << word[i]<<endl;
			Node* n = new Node;
			n->left = NULL;
			n->right = NULL;
			n->letter = word[i];
			n->plist = NULL;
			head = n;
			//One character word
			if(i==strlen(word)-1){
				cout << " one word one char!!!! what a luck!" <<endl;			
				n->plist= new PostingList;
				n->plist->add(lineNum);
			}
			//If the word continues
			else{
				cout << "the word goes on!"<<endl;
				temp = head;//NULL;//head->left;
			}
			numNodes++;
		}
	}
	numWords++;
}

int LetterList::countNodes(){
	return numNodes;
}

void LetterList::printLeft(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "node left-> Letter stored: " << temp->letter << endl;		
		temp = temp->left;
	}
}

void LetterList::printRight(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "node right-> Letter stored: " << temp->letter << endl;		
		temp = temp->right;
	}
}

void LetterList::printLeafs(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "sad " << temp->letter<<endl;
		if(temp->plist!=NULL) cout << "POSTING LIST IN -> " << temp->letter<<endl;	
		temp = temp->left;
	}
}

LetterList::~LetterList(){
	Node* temp = NULL;
	while(head -> left != NULL){
		temp = head->left;
		delete head;
		head = temp;
	}
}
