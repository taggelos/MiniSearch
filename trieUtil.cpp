//Function Definitions
#include "trieUtil.h"

Trie* insertTrie(char** documents, const int& lineNum, int* nwords){
	Trie* trie = new Trie;
	char * word;
	//So as not to change original
	char * templine;
	//For each sentence we add the words
	for (int i=0; i<lineNum ; i++){
		//cout << "Splitting LINE "<< documents[i] << " into WORDS:" << endl;
		templine = new char [strlen(documents[i])+1];
		strcpy(templine,documents[i]);
		word = strtok(templine," \t");
		while (word != NULL){
			nwords[i]++;
			//cout << "------------------------------------"<<numberLen(atoi(word))<<endl;
			trie->add(word,i);
			word = strtok(NULL, " \t");
		}
		//1 more cell for sum of all cells
		nwords[lineNum]+=nwords[i];
		delete[] templine;
	}	
	return trie;
}

void search(Trie* trie, const int& lineNum, const int& K, char** documents, int* nwords){
	char * q = strtok(NULL, " \t");
	//number of queries
	int n=0;
	WordList wlist;
	while(q != NULL && n<10){
		wlist.add(q);
		q = strtok(NULL, " \t");
		n++;
	}
	if (n==0) cerr << "Provide at least 1 argument for search!" <<endl;
	else wlist.search(trie,lineNum, K, documents, nwords);
}

void df(Trie* trie){
	char * q = strtok(NULL, " \t");
	int n=0;
	char* param=NULL;
	//take 0 or 1 arguments
	while(q != NULL && n<=1){
		if(n==0){
			param = new char[strlen(q)+1];
			strcpy(param,q);
		}		
		q = strtok(NULL, " \t");
		n++;
	}
	if (n==2) cerr << "Provide at most 1 argument to search!" <<endl;
	else {
		if (param!=NULL){
			PostingList* plist = trie->search(param);
			if (plist!=NULL) cout << param << " " << plist->getTotalTimes() <<endl;
			else cout << "The word was not found." <<endl;
		}
		else trie->findAll();
	}
	delete[] param;
}

void tf(Trie* trie, int lineNum){
	char * q = strtok(NULL, " \t");
	//number of parameters (id,word)
	int n=0; 
	char** params = new char*[2];
	while(q != NULL && n<=2){
		//Do not violate allocated array with more arguments
		if (n!=2) {
			params[n] = new char[strlen(q)+1];
			strcpy(params[n],q);
		}
		q = strtok(NULL, " \t");
		n++;
	}
	switch (n){
		case 0: 
			cerr << "2 arguments needed, 0 provided!" << endl;
			delete[] params;
			break;
		case 1:	
			cerr << "Need 1 more argument!" << endl;
			delete[] params[0];
			delete[] params;
			break;
		case 3:	
			cerr << "Provide no more than 2 arguments for search!" << endl;
			free2D(params,2);
			break;
		default: 
			if(!numberCheck(params[0]))	{
				cerr << "1st argument must be an integer!" << endl;
				free2D(params,2);
				break;
			}
			int argLine  = atoi(params[0]);
			if(argLine >= lineNum || argLine < 0 ) cerr << "Not a valid line number!" << endl;
			else cout << params[0] << " " << params[1] << " " << tf(trie,argLine,params[1]) << endl;
			free2D(params,2);
	}
}

int tf(Trie* trie, const int& id, const char* word){
	PostingList* plist = trie->search(word);
	if (plist!=NULL) return plist->tf(id);
	return 0;
}