//Function Definitions
#include "wordList.h"
using namespace std;

WordList::Node::Node(char* w){
	next = NULL;
	word = new char[strlen(w)+1];
	strcpy(word,w);
}

WordList::Node::~Node(){
	delete[] word;
}

WordList::WordList(){
	head = NULL;
	numNodes = 1;
}

void WordList::add(char* word){
	// O ( 1 ) insertion
	if (head==NULL){
		head = new Node(word);
		return;
	}
	Node * n = new Node(word);
	n->next = head;
	head = n;
	numNodes++;
}

void WordList::print(){
	Node* temp = head;
	while(temp!= NULL){
		cout << "node-> word: " << temp->word << " totalnodes->"<< numNodes<< endl;
		temp = temp->next;
	}
}

int countDigits(int n){
	int count = 1;
	while (n >9 ) {
		n = n / 10;
		++count;
	}
	return count;
}

void WordList::search(Trie* trie, const int& N, const int& K, char** documents, int* nwords){
	double bm25 [N]={};
	bool bm25flags [N]={};
	int avgdl = nwords[N] / N; // average number of words
	Node* temp = head;
	//char** words = new char*[numNodes+1];
	//int i=0;
	while(temp!= NULL){
		PostingList* plist = trie->search(temp->word);
		if (plist!=NULL){
			plist->score(bm25, bm25flags, avgdl, N, nwords);
		}
		//strcpy(words[i],temp->word);
		//i++;
		temp=temp->next;
	}
	Heap h(N);
	for (int i=0; i<N; i++){
		if (bm25flags[i]){
			h.add(i,bm25[i]);
		}
	}
	HeapNode* hn;
	for (int i=1; i<=K; i++){
		hn = h.popMax();
		if(hn==NULL) break;
		char *original = documents[hn->id];
		char *underline = createUnderLine(original);
		specialPrint(i,hn,underline,original);
		//cout << i << "."<<"("<< hn->id <<")"<< "[" << setprecision(4) << fixed << hn->score << "] " << documents[hn->id] <<endl;
		delete[] underline;
		cout << "testsss"<<endl;
		delete hn;
	}
}

char* WordList::fillWhiteSpace(char* line, size_t num){
	char* arr = new char[num+1];
	for (size_t i=0; i<num; i++)
		if(isspace(line[i])) arr[i] = line[i];
		else arr[i] =' ';
	arr[num] = '\0';
	return arr;
}

char* WordList::createUnderLine(char* original){
	size_t len = strlen(original);
	char *underline = fillWhiteSpace(original,len);
	Node* temp = head;
	while(temp!= NULL){
		replace(original,underline,temp->word);
		temp=temp->next;
	}
	return underline;
}

void WordList::replace(char* original, char* underline, char* word) {
	int len = (int)strlen(word);
	char* pch = strstr (original, word);
	while (pch != NULL) {
		int offset = (int)(pch-original);
		if (pch == original || original[offset-1] == ' ' || original[offset-1] == '\t') // word start
				if (pch[len] == ' ' || pch[len] == '\t' || pch[len] == '\0')// word end
					for (int i=offset; i<offset+len; i++)
						underline[i] = '^';
		pch += len;
		pch = strstr(pch, word);
	}
}

void WordList::printSpaces(int num){
	for (int i=0; i<num; i++) cout <<" ";
}

void WordList::specialPrint(int i, HeapNode* hn, char * underline, char* original){
	//strstr
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	cout << w.ws_col <<endl;

	//+5 for the dot and precision of number
	//+6 for extra characters in print like parentheses or dots
	int start = countDigits(i) + countDigits(hn->id) + countDigits((int)hn->score) + 5 + 6;
	if (hn->score<0) {
		start++;
	}
	int letters = w.ws_col - start;
	if(letters <= 0){
		cout << "Oops!" <<endl;
		return;
	}
	int lines = (int)strlen(original) / letters;
	if (strlen(original) % letters !=0) lines++;
	cout << " lines -> " << lines <<endl;
	//Start
	cout << i << ".("<< hn->id <<")[" << setprecision(4) << fixed << hn->score << "] ";
	for (int j=0;j<letters;j++){
		cout<< original[j];
	}
	cout << endl;
	printSpaces(start);
	for (int j=0;j<letters;j++){
		cout<< underline[j];
	}
	underline+=letters;
	original+=letters;
	//Rest
	for (int i=1;i<lines-1;i++){
		printSpaces(start);
		for (int j=0;j<letters;j++){
			cout<< original[j];
		}
		cout << endl;
		printSpaces(start);
		for (int j=0;j<letters;j++){
			cout<< underline[j];
		}
		underline+=letters;
		original+=letters;
		cout << endl;
	}
	//Last
	if(lines > 1){
		letters = strlen(original);
		printSpaces(start);
		for (int j=0;j<letters;j++){
			cout<< original[j];
		}
		cout << endl;
		printSpaces(start);
		for (int j=0;j<letters;j++){
			cout<< underline[j];
		}
		cout << endl;
	}
}

WordList::~WordList(){
	Node* temp = NULL;
	while(head!= NULL){
		temp = head;
		head = head->next;
		delete temp;
	}
}
