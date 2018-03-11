//Function Definitions
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include "letterList.h"
//#include "postingList.h"
using namespace std;

LetterList::Node::Node(char l, PostingList* p){
	letter = l;
	down = NULL;
	right = NULL;
	plist = p;	
}

LetterList::LetterList(){
	//head = NULL;
	cout<<"I AM CONSTRUCTING"<<endl;
	head = new Node('\0');
	numNodes = 1;
	numWords = 0;
	maxLen = 0;
	cout << "MAH MAN-> "<<head->letter << endl;
}

void LetterList::add(const char* word, const int& lineNum){
	Node* temp = head;
	cout << "Splitting WORD "<< word << " into LETTERS" << endl;
	int len = (int)strlen(word);
	if (len > maxLen) maxLen = len;
	for (int i=0; i < len; i++){
		cout << " $$$$$ letter -> " << word[i]<<endl;
		while (temp->letter != word[i] && temp->right!=NULL){
			cout << " TRAVERSING -> "<< temp->right->letter<<endl;
			temp = temp->right;
		}
		if(temp->letter != word[i]){
			cout << " NEW NODE RIGHT -> " << word[i]<<endl;
			temp->right=new Node(word[i]);
			if (i!=len-1){
				cout << " NEW NODE RIGHT and DOWN -> " << word[i+1]<<endl;
				temp->right->down=new Node(word[i+1]);
				//temp->right->down = new Node('\0');
				cout << " NEXT to check -> " << word[i+1]<<endl;
				temp = temp->right->down;
			}
			else {
				cout << "Last letter of word " << word[i] << "-----"<< temp->right->letter<<"  :'("<<endl;
				//Initialize postingList
				if(temp->right->plist == NULL){
					cout << "Mark LEAF with postinglist"<<endl;
					temp->right -> plist = new PostingList(lineNum);
					temp->right->plist->print();
				}
				//Leaf node means we met an old word
				else{
					cout << "met AN OLD FRIENDOULINO!" <<endl;
					temp->right->plist->add(lineNum);
				}
			}
			numNodes++;
		}
		else {//if (temp->letter == word[i]){
			cout << " Same letter -> " << word[i] << " and " << temp->letter<<endl;
			if ( i!=len-1){// && temp->down==NULL){				
				cout << " INSIDE same -> " << word[i]<<endl;
				if (temp->down==NULL) {
					cout << "NEW NODE"<<endl;
					temp->down=new Node(word[i+1]);
				}
				else {
					cout << "OLD NODE"<<endl;
				}
				temp=temp->down;
				cout << " NEXT to check -> " << word[i+1]<<endl;
			}
			else{
				cout << "Last letter of word " << word[i] << "-----"<< temp->letter<<"  :'("<<endl;
				//Initialize postingList
				if(temp->plist == NULL){
					cout << "Mark LEAF with postinglist"<<endl;
					temp -> plist = new PostingList(lineNum);
					//temp = new Node(word[i],new PostingList(lineNum));
					temp->plist->print();
					//temp=n; 
					////numNodes++;
				}
				//Leaf node means we met an old word
				else{
					cout << "met AN OLD FRIENDOULINO!" <<endl;
					temp->plist->add(lineNum);
				}
			}
		}
	}
	//temp->plist->print();
	numWords++;
}

PostingList* LetterList::search(const char* word){
	Node* temp = head;
	cout << "Splitting WORD "<< word << " into LETTERS" << endl;
	int len = (int)strlen(word);
	for (int i=0; i < len; i++){
		cout << " $$$$$ letter -> " << word[i]<<endl;
		while (temp->letter != word[i] && temp->right!=NULL){
			cout << " TRAVERSING -> "<< temp->right->letter<<endl;
			temp = temp->right;
		}
		if(temp->letter != word[i]){
			cout << " NOT found NODE -> " << word[i]<<endl;
			return NULL;
		}
		else {//if (temp->letter == word[i]){
			cout << " Same letter -> " << word[i]<<endl;
			if (i!=len-1 && temp->down!=NULL){
				//Node* n = node(word[i+1]);
				cout << " LETS SEE " <<endl;
				temp=temp->down;
			}	
		}
		cout << " AXNE -> " << word[i]<<endl;
		if(i==len-1){
			cout << "Last letter of word " << word[i] << "----- "<< temp->letter << "   :'("<<endl;
			if(temp->plist == NULL){
				cout << "PROBLEM OF LEAF without postinglist or ALMOST the word"<<endl;
			}
			//Leaf node means we met an old word
			else{
				cout << "met AN OLD FRIENDOULINO! AXNE RE" <<endl;
			}
		}
	}
	return temp->plist;
}

void LetterList::findAll(){
	Node* n = head;
	char* word = new char[maxLen+1];
	traverse(n,word,0);
	cout << "ALL words-> " <<numWords<<endl;
	delete[] word;
}

void LetterList::traverse(Node* n,char* word,int i){
	word[i] = n->letter;
	if(n->plist!=NULL){
		word[i+1] = '\0';
		cout << word << " " << n->plist->getTotalTimes() <<endl;
	}
	if (n->down!=NULL) traverse(n->down,word,i+1);
	if (n->right!=NULL)	traverse(n->right,word,i);
}


int LetterList::countNodes(){
	return numNodes;
}

LetterList::Node::~Node(){
	if (plist!=NULL) delete plist;
}

void LetterList::traverseDel(Node* n){
	if(n->plist!=NULL){
		cout << " Here word's last letter-> "<<n->letter<<endl;
	}
	else cout << n->letter;
	if (n->right!=NULL) traverseDel(n->right);
	if (n->down!=NULL) traverseDel(n->down);
}

LetterList::~LetterList(){
	Node* n = head;
	traverseDel(n);
}