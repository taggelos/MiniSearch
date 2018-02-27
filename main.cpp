#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
//#include <cstdio>
//#include "trie.h"
#define LINESIZE 1024

using namespace std;

void readFile(char* myFile){
	FILE * pFile;
	char mystring [LINESIZE];
	int lineNum = 0;

	pFile = fopen (myFile, "r");
	if (pFile == NULL) perror ("Error opening file");
	else {
		while ( fgets (mystring , LINESIZE , pFile) != NULL ){
			puts (mystring);
			char *firstChar = mystring;
			if (atoi(&mystring[0])==lineNum++) cout << (mystring[0]) <<endl;		
		}
	    fclose (pFile);
	}
}

int main(int argc, char* argv[]){
	//Use by default 10 as number of results (piazza) 	
	char* inFile = NULL; 
	int numRes = 10; 
	bool fileTaken = false, numTaken = false;
	//We iterate over argv[] to get the parameters stored inside
	for (int i = 1; i < argc; i++){	
		if (i+1 != argc)
			if (strcmp(argv[i],"-i") == 0 && fileTaken == false){
				inFile = argv[i+1];
				fileTaken = true;
			}
			else if (strcmp(argv[i],"-k") == 0){	
				numRes = atoi(argv[i+1]);
			}
	}	
	//If we do not have the right number of parameters
	//show the usage and exit.	
	if (argc != 5 || inFile == NULL || numRes<=0){
		perror ("Not enough or invalid arguments, please try again.");
		cout << "Usage : " << argv[0] << " [-i <DOCUMENT>][-k <NUMBER OF RESULTS GREATER THAN ZERO>]" << endl; 
		exit(0);
	}
	cout << "Arguments taken : " << inFile << " " << numRes << endl;

	readFile(inFile);
	//to be continued..
	cin.get();
	exit(0);
}