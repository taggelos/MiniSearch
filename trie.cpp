//Function Definitions
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include "trie.h"

using namespace std;

Trie::Node::Node(char l, PostingList* p){
	letter = l;
	down = NULL;
	right = NULL;
	plist = p;
}

Trie::Trie(){
	//Head initialisation with null
	head = new Node('\0');
	//Only one node, the head
	numNodes = 1;
	//No words inside
	numWords = 0;
	maxLen = 0;
}

void Trie::add(const char* word, const int& lineNum){
	Node* temp = head;
	//Splitting word into letters
	//cout << "Splitting WORD "<< word << " into LETTERS" << endl;
	int len = (int)strlen(word);
	if (len > maxLen) maxLen = len;
	for (int i=0; i < len; i++){
		//Traverse same level Nodes
		//cout << " $$$$$ letter -> " << word[i]<<endl;
		while (temp->letter != word[i] && temp->right!=NULL){
			//cout << " TRAVERSING -> "<< temp->right->letter<<endl;
			temp = temp->right;
		}
		if(temp->letter != word[i]){
			//New right Node
			//cout << " NEW NODE RIGHT -> " << word[i]<<endl;
			temp->right=new Node(word[i]);
			if (i!=len-1){
				//cout << " NEW NODE RIGHT and DOWN -> " << word[i+1]<<endl;
				temp->right->down=new Node(word[i+1]);
				//cout << " NEXT to check -> " << word[i+1]<<endl;
				temp = temp->right->down;
			}
			//Last letter of word
			else {
				//cout << "Last letter of word " << word[i] << "-----"<< temp->right->letter<<"  :'("<<endl;
				//Initialize postingList
				if(temp->right->plist == NULL){
					//cout << "Mark LEAF with postinglist"<<endl;
					temp->right->plist = new PostingList(lineNum);
					temp->right->plist->print();
				}
				//Leaf node means we met an old word
				else{
					//cout << "met AN OLD FRIENDOULINO!" <<endl;
					temp->right->plist->add(lineNum);
				}
			}
			//Count the new Node we created
			numNodes++;
		}
		else {
			//Same letter means 2 things
			//cout << " Same letter -> " << word[i] << " and " << temp->letter<<endl;
			if ( i!=len-1){
				//We met an old Node or we create a new one
				//cout << " INSIDE same -> " << word[i]<<endl;
				if (temp->down==NULL) {
					//cout << "NEW NODE"<<endl;
					temp->down=new Node(word[i+1]);
				}
				else {
					//cout << "OLD NODE"<<endl;
				}
				temp=temp->down;
				//cout << " NEXT to check -> " << word[i+1]<<endl;
			}
			else{
				//Last letter of word
				//cout << "Last letter of word " << word[i] << "-----"<< temp->letter<<"  :'("<<endl;
				//Initialize postingList
				if(temp->plist == NULL){
					//cout << "Mark LEAF with postinglist"<<endl;
					temp -> plist = new PostingList(lineNum);
					temp->plist->print();
				}
				//Leaf node means we met an old word
				else{
					//cout << "met AN OLD FRIENDOULINO!" <<endl;
					temp->plist->add(lineNum);
				}
			}
		}
	}
	//Count the word we just added
	numWords++;
}

PostingList* Trie::search(const char* word){
	Node* temp = head;
	//Checking every letter of the word
	int len = (int)strlen(word);
	for (int i=0; i < len; i++){
		//Look up all nodes in same level till the end or if we find the one we want
		while (temp->letter != word[i] && temp->right!=NULL){
			//Traverse for same level
			temp = temp->right;
		}
		if(temp->letter != word[i]){
			//The word was not found
			return NULL;
		}
		else if (i!=len-1 && temp->down!=NULL){
				//Level down for next Letter
				temp=temp->down;
		}
		//Last letter will return NULL or the Posting List of the result		
	}
	return temp->plist;
}

void Trie::findAll(){
	Node* n = head;
	char* word = new char[maxLen+1];
	traverse(n,word,0);
	//cout << "ALL words-> " <<numWords<<endl;
	delete[] word;
}

void Trie::traverse(Node* n,char* word,int i){
	word[i] = n->letter;
	//Having a Posting List, means we have a word
	if(n->plist!=NULL){
		//Finish the word
		word[i+1] = '\0';
		//Get total times from its Posting List
		cout << word << " " << n->plist->getTotalTimes() <<endl;
	}
	//Traverse all Nodes Down and then Right
	if (n->down!=NULL) traverse(n->down,word,i+1);
	if (n->right!=NULL)	traverse(n->right,word,i);
}

Trie::Node::~Node(){
	//Delete the posting List of Leafs
	if (plist!=NULL) delete plist;
}

void Trie::traverseDel(Node* n){
	if (n->right!=NULL) traverseDel(n->right);
	if (n->down!=NULL) traverseDel(n->down);
	delete n;
}

Trie::~Trie(){
	Node* n = head;
	traverseDel(n);
}