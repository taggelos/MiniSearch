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
	cerr << "#\t\t\t" << "/df" << endl << "#\t\t\t" << "/tf" << endl << "#\t\t\t" << "/exit" << endl;			
	cerr << "####################################################"<<endl;
}

int numberCheck(char *str){
	int len = (int)strlen(str);
	//In case there is a letter with the number and atoi clears it
	for (int j=0; j<len; j++)
		if (!isdigit(str[j])) return 0;
	return atoi(str);
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
		for (int i=0; i<lines;i++){
			//Reinitialize
			mystring = NULL;
			n = 0;
			getline(&mystring, &n, file);
			documents[i] = new char[strlen(mystring)+1];
			//Store the line without the number
			strcpy(documents[i],mystring);
			//For first character of first line we check without using atoi
			if (i==0) {
				if (mystring[0] != '0') {
					cerr << "Invalid first line of file" <<endl;
					exit(3);
				}
			}
			else if (atoi(mystring)!=i) {
				cerr <<"Invalid number close in line "<< i+1 << " of file" <<endl;  //i - 1 ???
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
			topK = numberCheck(argv[4]);
			//Invalid for negative or zero result
			if (topK <=0) paramError(argv[0], "This is not an appropriate number");
		}
		else if (!strcmp(argv[3],"-i") && !strcmp(argv[1],"-k")){
			inputFile = argv[4];
			topK = numberCheck(argv[2]);
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

void freeDocs(char ** documents, const int& lineNum){
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
void insertTrie(char** documents, int lineNum){
	PostingList plist (4);
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
	cout << "plist count nodes: "<<plist.countNodes()<<endl;;

	LetterList llist;
	//for (int i=0; i < lineNum ; i++){
	//	llist.add(documents[i]);
	//}
	//For each sentence we add the words
	char * word;
	for (int i=0; i<lineNum ; i++){  //i<lineNum//2
		cout << "Splitting LINE "<< documents[i] << " into WORDS:" << endl;
		word = strtok (documents[i]," \t\n");
		//Removed number from sentence // TODO CARE?
		word = strtok (NULL, " \t\n");
		while (word != NULL){
			printf ("%s\n",word);
			cout << "------------------------------------"<<numberLen(atoi(word))<<endl;			
			llist.add(word,i);
			word = strtok (NULL, " \t\n");
			//break; //COMMENT IT
		}
	}
	//llist.add(documents[0]);
	cout<<"~~~~ALL~~~~"<<endl;
	//llist.print();
	cout<<"~~~~DOWN~~~~"<<endl;
	//llist.printDown();
	cout<<"~~~~RIGHT~~~~"<<endl;
	//llist.printRight();
	cout<<"~~~~LEAFS~~~~"<<endl;
	//llist.printLeafs();
	cout<<"~~~~SEARCHING "<< " red "<<"~~~~"<<endl;
	llist.search((char*)"red");
}

void search(){
	cout << "My lovely search" <<endl;
}
void df(){
	cout << "My lovely DF" <<endl;
}
void tf(){
	cout << "My lovely TF" <<endl;
}