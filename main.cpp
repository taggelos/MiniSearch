#include "main.h"

int main(int argc, char* argv[]){
	char* inputFile = NULL;	
	//Use by default 10 as number of results (piazza) 
	int numRes = 10;
	
	inputCheck(argc,argv,&inputFile,numRes);
	int lineNum = 0;
	char ** documents = readFile(inputFile, lineNum);
	insertTrie(documents,lineNum);

	//to be continued..
	cin.get();
	//freeDocs(documents,lineNum);
	exit(0);
}