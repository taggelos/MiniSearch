//Function Definitions
#include "functions.h"

void paramError(char * programName ,const char * reason){
	//Display the problem
	cerr << reason << ", please try again." << endl;
	//Show the usage and exit.
	cerr << "Usage : " << programName << " [-i <DOCUMENT>][-k <NUMBER OF RESULTS GREATER THAN ZERO>]" << endl; 
	exit(1);
}

void commandError(){
	cerr << "##############################################################"<<endl;
	cerr << "#Invalid command!" <<endl;
	cerr << "#Available commands :\t/search <q1> <q2> <q3> <q4> ... <q10>" << endl;
	cerr << "#\t\t\t" << "/df or /df <word>" << endl << "#\t\t\t" << "/tf <integer> <word>" << endl << "#\t\t\t" << "/exit" << endl;			
	cerr << "##############################################################"<<endl;
}

bool numberCheck(char *str){
	int len = (int)strlen(str);
	//In case there is a letter with the number and atoi clears it
	for (int j=0; j<len; j++)
		if (!isdigit(str[j])) return false;
	return true;
}

char** readFile(char* myFile, int &lines){
	FILE * file;
	lines = 0;

	file = fopen (myFile, "r");
	if (file == NULL){
		cerr << "Error opening file" << endl;
		exit(2);
	}
	else {
		while(!feof(file)) if(fgetc(file) == '\n') lines++;
		char ** documents = new char*[lines];
		rewind(file);
		char * mystring;
		size_t n;
		//First Line
		mystring = NULL;
		n = 0;
		getline(&mystring, &n, file);
		documents[0] = new char[strlen(mystring)+1];
		strcpy(documents[0],mystring);
		char *token =strtok(mystring," \t\n");
		if (mystring[0] != '0' || (token!=NULL && !numberCheck(token))) {
			cerr << "Invalid first line of file" <<endl;
			exit(3);
		}
		//Rest of Lines
		for (int i=1; i<lines;i++){
			//Reinitialize
			char * mystring = NULL;
			n = 0;
			getline(&mystring, &n, file);
			documents[i] = new char[strlen(mystring)+1];
			strcpy(documents[i],mystring);
			char *token =strtok(mystring," \t\n");
			//For first character of first line we check without using atoi
			if (atoi(mystring)!=i || (token!=NULL && !numberCheck(token))) {
				cerr <<"Invalid number close in line "<< i+1 << " of file" <<endl;
				exit(4);
			}
			free(mystring);
		}
		free(mystring);
		fclose (file);
		return documents;
	}
}

void inputCheck(int argc, char* argv[], char*& inputFile, int& topK){
	if (argc == 3){
		if (strcmp(argv[1],"-i")) {
			paramError(argv[0], "You need to provide input file");
		}
		inputFile = argv[2];
	}
	else if (argc== 5) {
		if (!strcmp(argv[1],"-i") && !strcmp(argv[3],"-k")){
			inputFile = argv[2];
			if (numberCheck(argv[4])) topK = atoi(argv[4]);
			else topK = 0;
			//Invalid for negative or zero result
			if (topK <=0) paramError(argv[0], "This is not an appropriate number");
		}
		else if (!strcmp(argv[3],"-i") && !strcmp(argv[1],"-k")){
			inputFile = argv[4];
			if (numberCheck(argv[2])) topK = atoi(argv[2]);
			else topK = 0;
			//Invalid for negative or zero result
			if (topK <=0) paramError(argv[0], "This is not an appropriate number");
		}
		else {
			paramError(argv[0], "Invalid arguments");
		}
		//paramError(argv[0], "You need to provide input file");
	}
	else paramError(argv[0], "This is not an appropriate syntax");

	cout << "Arguments taken : " << inputFile << " " << topK << endl;
}

void print(char ** arr, const int& lineNum){
	for (int i=0; i < lineNum ; i++){
		int len = (int)strlen(arr[i]);
		for (int j=0; j<len;j++)
			cout << " --- " << arr[i][j] << endl;
	}
}

void printSplit(char ** arr, const int& lineNum){
	char * pch;
	for (int i=0; i < lineNum ; i++){
		cout << "Splitting string "<< arr[i] << " into tokens:" << endl;
		pch = strtok(arr[i]," \t\n");
		while (pch != NULL){
			printf ("%s\n",pch);
			pch = strtok(NULL, " \t\n");
		}
	}
}

void free2D(char ** documents, const int& lineNum){
	for (int i=0; i < lineNum ; i++) {
		delete[] documents[i];
	}
	delete[] documents;
}

int numberLen(int n, int base = 10){
	int count = 0;
	do {
		count++; 
		n /= base;
	} while (n);
	return count;
}

/******************************TRIE****************************************************/

LetterList* insertTrie(char** documents, const int& lineNum, int* nwords){
	LetterList *llist = new LetterList;
	//For each sentence we add the words
	char * word;
	//number of words
	for (int i=0; i<lineNum ; i++){  //i<lineNum//2
		cout << "Splitting LINE "<< documents[i] << " into WORDS:" << endl;
		word = strtok(documents[i]," \t\n");
		//Removed number from sentence
		word = strtok(NULL, " \t\n");
		while (word != NULL){
			nwords[i]++;
			printf ("%s\n",word);
			cout << "------------------------------------"<<numberLen(atoi(word))<<endl;
			llist->add(word,i);
			word = strtok(NULL, " \t\n");
		}
		//1 more cell for sum of all cells
		nwords[lineNum]+=nwords[i];
	}	
	return llist;
}

void search(){
	char * q = strtok(NULL, " \t");
	int n=0; //number of queries
	WordList wlist; //it is ok
	while(q != NULL && n<10){
		cout << "My lovely q -> "<< q <<endl;
		wlist.add(q);
		q = strtok(NULL, " \t");
		n++;
	}
	if (n==0) cerr << "Provide at least 1 argument for search!" <<endl;
	else wlist.print(); //wlist.//search(llist,lineNum,nwords); //list of queries? anti to n
}

void df(LetterList* llist){
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
			PostingList* plist = llist->search(param);
			if (plist!=NULL) cout << param << " " << plist->getTotalTimes() <<endl;
			else cout << "The word was not found." <<endl;
		}
		else llist->findAll();
	}
	delete[] param;
}

void tf(LetterList* llist, int lineNum){
	char * q = strtok(NULL, " \t");
	//number of parameters (id,word)
	int n=0; 
	char** params = new char*[2];
	while(q != NULL && n<=2){
		cout << "hi"<<endl;
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
			else cout << params[0] << " " << params[1] << " " << tf(llist,argLine,params[1]) << endl;
			free2D(params,2);
	}
}

int tf(LetterList* llist, const int& id, const char* word){
	PostingList* plist = llist->search(word);
	if (plist!=NULL) return plist->tf(id);
	return 0;
}

/*double f = 1234.12345678;
cout << floor(100* f)/100 <<endl;
*/