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

LetterList::Node* LetterList::node(char l, PostingList* p){
	Node* kapos = new Node(l,p);	
	/*TODODELETE * temp = new TODODELETE;
	temp -> m = kapos;
	temp -> next = del;
	del = temp;*/
	return kapos;
}

LetterList::LetterList(){
	//head = NULL;
	cout<<"I AM CONSTRUCTING"<<endl;
	del = new TODODELETE;
	del -> m = new Node('\0');
	del -> next = NULL;
	head = new Node('\0');
	numNodes = 1;
	numWords = 0;
	cout << "MAH MAN-> "<<head->letter << endl;
}

void LetterList::add(char* word, int lineNum){
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
			cout << " NEW NODE RIGHT -> " << word[i]<<endl;
			temp->right=new Node(word[i]);
			if (i!=len-1){
				cout << " NEW NODE RIGHT and DOWN -> " << word[i+1]<<endl;
				temp->right->down=new Node(word[i+1]);
			}
			//temp->right->down = new Node('\0');
			cout << " NEXT to check -> " << word[i+1]<<endl;
			temp = temp->right->down;
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
				cout << "O FUCK "<<endl;
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

void LetterList::search(char* word){
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
			break;
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
			//Initialize postingList
			if(temp->plist == NULL){
				cout << "PROBLEM OF LEAF without postinglist"<<endl;
			}
			//Leaf node means we met an old word
			else{
				cout << "met AN OLD FRIENDOULINO! AXNE RE" <<endl;
			}
		}
	}
}


int LetterList::countNodes(){
	return numNodes;
}

void LetterList::printDown(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "node down-> Letter stored: " << temp->letter << endl;		
		temp = temp->down;
	}
}

void LetterList::printRight(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "node right-> Letter stored: " << temp->letter << endl;		
		temp = temp->right;
	}
}

void LetterList::print(){ //LATHOS
	cout << "LETS PRINT"<<endl;
	Node* temp = head;
	int level=1;
	while(temp->down!=NULL){		
		cout << " LETTER -- "<<temp->down->letter<<" -- and level-> "<< level<<endl;
		Node * temp2 = temp->down;
		while (temp2->right!=NULL){
			cout << " IN SAME LEVEL -- "<<level<<" -- :"<< temp2->letter<<endl;
			temp2 = temp2->right;
		}
		level++;
		temp=temp->down;
	}
}

void LetterList::printLeafs(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "sad " << temp->letter<<endl;
		if(temp->plist!=NULL) cout << "POSTING LIST IN -> " << temp->letter<<endl;	
		temp = temp->down;
	}
}

LetterList::Node::~Node(){
	if (plist!=NULL) delete plist;
}

LetterList::~LetterList(){
	/*Node* temp = NULL;
	while (del!=NULL){
		delete del->m;
		TODODELETE* temp = del;
		del = del->next;		
		delete temp;
	}*/
}


/*KXXXXXXX COMMENTS*/

	/*cout << " $$$$$here letter -> " << word[i]<<endl;
	if (head != NULL){
		//Same level search
		while (temp!=NULL && temp->letter != word[i]){
			if()
			temp=temp->right;
		}
		if (temp->down == NULL){
			cout << " new node with " << word[i]<<endl;		
			//Create new node
			Node* n = new Node;
			n->down = NULL;
			n->right = NULL;
			n->letter = word[i];
			n->plist = NULL;
			if(i!=strlen(word)-1){
				cout << "##Keep from the new letter!"<<endl;
				temp = n;
			}		
		}
		else if (temp->down->letter != word[i] ){
			if (temp->down->right == NULL){
				cout << " new RIGHTnode with " << word[i]<<endl;
				Node* n = new Node;
				n->down = NULL;
				n->right = NULL;
				n->letter = word[i];
				n->plist = NULL;
				if(i!=strlen(word)-1)
					temp = n;
			}
			else if(temp->down->right->letter == word[i]){
				cout << " Go RIGHT with same " << word[i]<<endl;
				temp=temp->right;				
			}
		}
		else {
			cout << " SAME node " << word[i] <<endl;
			//Traverse the trie if we have the character
			if (temp->down->letter == word[i]){
				temp = temp->down;
				cout << " GO down " << word[i]<<endl;
			}
			else {
				if (temp->right!=NULL){
					temp = temp->right;
					cout << " GO RIGHT " << word[i]<<endl;
				}
				else{
					Node* n = new Node;
					n->down = NULL;
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
				n->down = NULL;
				n->right = NULL;
				n->letter = word[i];
				n->plist= new PostingList;
				n->plist->add(lineNum);
				temp->down == n;
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
		n->down = NULL;
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
			temp = head;//NULL;//head->down;
		}
		numNodes++;
	}
}*/