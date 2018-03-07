#include "functions.h"

int main(int argc, char* argv[]){
	char* inputFile = NULL;	
	//Use by default 10 as number of results (piazza) 
	int topK = 10;
	
	inputCheck(argc,argv,inputFile,topK);
	int lineNum = 0;
	char ** documents = readFile(inputFile, lineNum);
	cout << "Please wait while your input file is being processed." <<endl;
	//Insert
	insertTrie(documents,lineNum);
	cout << "Your file: '"<< inputFile <<"' was processed!"<< endl << "Type your commands.." <<endl;
	//Read Command
	char * cmd = NULL;
	char * q = NULL;
	while(1){
		char * mystring = NULL;
		size_t n = 0;
		getline(&mystring, &n, stdin);
		//Handle enter
		if (!strcmp(mystring,"\n"))	cmd = mystring;
		else cmd = strtok(mystring, " \n");
		if (!strcmp(cmd,"/exit")) break;
		else if (!strcmp(cmd,"/search")) {
			q = strtok (NULL, " \t\n");
			int c =0;
			while(q != NULL && c<10){
				cout << "My lovely q -> "<< q <<endl;
				q = strtok (NULL, " \t\n");
				c++;
			}
			if (c==0) cerr << "Provide at least 1 argument for search!" <<endl;
			continue; // Try again
		}
		else if (!strcmp(cmd,"/df")) df();
		else if (!strcmp(cmd,"/tf")) tf();
		else commandError();
		cout <<endl<<"Type next command or '/exit' to terminate"<<endl;
	}
	//Free Document
	freeDocs(documents,lineNum);
	exit(0);
}