// Header --> Functions Declarations
#include <iostream>
#include "postingList.h"

using namespace std;

#ifndef TRIE_H
#define TRIE_H

class Trie {
	//Letter
	struct Node {
		//Letter
		char letter;
		Node* down;
		Node* right;
		//Node* children;
		PostingList* plist;
		Node(char letter, PostingList* plist = NULL);
		~Node();
	};
	Node* head;
	int numNodes; //Node (Letter) counter with root node inside
	int numWords; //Word counter
	int maxLen; // Maximum length of word
public:
	Trie();
	void add(const char* word, const int& lineNum);
	PostingList* search(const char* word);
	void findAll();
	void traverse(Node* n,char* word,int i);
	void traverseDel(Node* n);
	~Trie();	
};

#endif
