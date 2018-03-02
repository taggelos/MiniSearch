#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstring>
#include <ctype.h>
//#include <cstdio>
#include "postingList.h"
#include "letterList.h"

using namespace std;

void paramError(char * programName ,const char * reason){
	//Display the problem
	cerr << reason << ", please try again." << endl;
	//Show the usage and exit.
	cerr << "Usage : " << programName << " [-i <DOCUMENT>][-k <NUMBER OF RESULTS GREATER THAN ZERO>]" << endl; 
	exit(1);
}

int numberCheck(char *str){	
	//In case there is a letter with the number and atoi clears it
	for (int j=0; j<strlen(str); j++)
		if (!isdigit(str[j])) return 0;
	return atoi(str);
}


char** readFile(char* myFile, int &lineNum){
	FILE * file;
	char * mystring = NULL;
	size_t n;
	//int lineNum = 0;
	bool firstLine = true;
	//char ** documents = NULL;
	int lines = 0;

	file = fopen (myFile, "r");
	if (file == NULL){
		cerr << "Error opening file" << endl;
		exit(2);
	}
	else {
		while (getline(&mystring, &n, file) !=-1){lines++;}
		char ** documents = new char*[lines];
		rewind(file);
		while (getline(&mystring, &n, file) !=-1){
			documents[lineNum] = new char[strlen(mystring)];
			//Store the line without the number
			memcpy(documents[lineNum],mystring+'\0'+1,strlen(mystring)+1);
			puts (mystring);
			//For first character of first line we check without using atoi
			if (firstLine) {
				cout << mystring[0]<< "---"<<endl;
				if (mystring[0] != '0') {
					cerr << "Invalid first line of file" <<endl;
					exit(3);
				}
				firstLine = false;
				lineNum++;
			}
			else if (atoi(mystring)!=lineNum++) {
				cerr << "Invalid number in line "<< lineNum-1 << " of file" <<endl;
				exit(4);
			}			
		}
		free(mystring);
		fclose (file);
		return documents;
	}
}

void print(char ** arr, int lineNum){
	for (int i=0; i < lineNum ; i++)
		for (int j=0; j < strlen(arr[i]);j++)
			cout << " --- " << arr[i][j] << endl;
}

void printSplit(char ** arr, int lineNum){
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

void insertTrie(char** documents, int lineNum){
	PostingList plist;
	//print(documents, lineNum);
	//printSplit(documents, lineNum);
	plist.add(4,4);
	plist.add(3,3);
	plist.add(22,13);
	plist.add(32,121);
	plist.add(47,88);
	plist.print();

	LetterList llist;
	//for (int i=0; i < lineNum ; i++){
	//	llist.add(documents[i]);
	//}
	char * word;
	for (int i=0; i < lineNum ; i++){
		cout << "Splitting LINE "<< documents[i] << " into WORDS:" << endl;
		word = strtok (documents[i]," \t\n");
		while (word != NULL){
			printf ("%s\n",word);			
			llist.add(word);
			word = strtok (NULL, " \t\n");
		}
	}
	//llist.add(documents[0]);
	llist.printNext();
}

int main(int argc, char* argv[]){
	char* inputFile = NULL;	
	//Use by default 10 as number of results (piazza) 
	int numRes = 10;
	if (argc == 3){
		if (strcmp(argv[1],"-i")) {
			paramError(argv[0], "You need to provide input file");
		}
		inputFile = argv[2];
	}
	else if (argc== 5) {
		if (!strcmp(argv[1],"-i") && !strcmp(argv[3],"-k")){
			inputFile = argv[2];
			numRes = numberCheck(argv[4]);	
			if (numRes <=0) paramError(argv[0], "This is not an appropriate number");
		}
		else if (!strcmp(argv[3],"-i") && !strcmp(argv[1],"-k")){
			inputFile = argv[4];
			numRes = numberCheck(argv[2]);	
			if (numRes <=0) paramError(argv[0], "This is not an appropriate number");
		}
		else {
			paramError(argv[0], "Invalid arguments");
		}
		//paramError(argv[0], "You need to provide input file");
	}
	else paramError(argv[0], "This is not an appropriate syntax");

	cout << "Arguments taken : " << inputFile << " " << numRes << endl;
	int lineNum = 0;
	char ** documents = readFile(inputFile, lineNum);
	insertTrie(documents,lineNum);

	//to be continued..
	cin.get();
	exit(0);
}