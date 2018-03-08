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
	cerr << "####################################################"<<endl;
	cerr << "#Invalid command!" <<endl;
	cerr << "#Available commands :\t/search q1 q2 q3 q4 ... q10" << endl;
	cerr << "#\t\t\t" << "/df <integer> <word>" << endl << "#\t\t\t" << "/tf" << endl << "#\t\t\t" << "/exit" << endl;			
	cerr << "####################################################"<<endl;
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
			mystring = NULL;
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
		pch = strtok (arr[i]," \t\n");
		while (pch != NULL){
			printf ("%s\n",pch);
			pch = strtok (NULL, " \t\n");
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
		word = strtok (documents[i]," \t\n");
		//Removed number from sentence
		word = strtok (NULL, " \t\n");
		while (word != NULL){
			nwords[i]++;
			printf ("%s\n",word);
			cout << "------------------------------------"<<numberLen(atoi(word))<<endl;
			llist->add(word,i);
			word = strtok (NULL, " \t\n");
		}
		nwords[lineNum]+=nwords[i]; //1 more cell for sum of all cells
	}	
	return llist;
}

void search(LetterList* llist, const int& n, const int& N, int* nwords){
	int D=0; //number of words in a document -> |D|
	double sum=0;
	int nqi=0; // number of sentences containing a word
	int tf=0; // term frequency, number of a word in a sentence
	int avgdl = nwords[N] / N; // average number of words
	double curIdf; //IDF

	//for (i in queries)
	//for (j in documents)
	cout<<"~~~~SEARCHING "<< " red "<<"~~~~"<<endl;
	PostingList* plist = llist->search((char*)"red");
	if (plist!=NULL){
		nqi = plist->countNodes();
		//alltf = plist->getTotalTimes();
		//tf = plist->getCount(j);
		//D = nwords[j];
		curIdf= idf(N,nqi);
		sum=score(curIdf,tf,avgdl,D);
	}
	//insert in heap

	cout << n << sum << "<- forget them"<<endl; //n will be changed
}

void df(){
	cout << "My lovely DF" <<endl;
}

int tf(LetterList* llist, const int& id, const char* word){
	PostingList* plist = llist->search(word);
	if (plist!=NULL) return plist->tf(id);
	return 0;
}

double idf(const int& N, const int& nqi ){
	return log((N - nqi + 0.5)/(nqi + 0.5));
}

double score(const double& idf, const int& tf, const int& avgdl, const int& D, const double& k1, const double& b){
	return idf * (tf * (k1 + 1)) / (tf + k1 * (1 - b + b * D/avgdl));
}

/*double f = 1234.12345678;
cout << floor(100* f)/100 <<endl;
*/

/*PostingList plist (4);
	//print(documents, lineNum);
	//printSplit(documents, lineNum);
	plist.add(44);
	plist.add(3);
	plist.add(223);
	plist.add(3);
	plist.add(3221);
	plist.add(3221);
	plist.add(3221);
	plist.add(3221);
	plist.add(3221);
	plist.add(3221);
	plist.add(478);
	plist.add(478);
	plist.add(478);
	plist.add(3);
	plist.print();
	cout << "plist count nodes: "<<plist.countNodes()<<endl;;*/