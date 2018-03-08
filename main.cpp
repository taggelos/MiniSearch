#include "functions.h"

int main(int argc, char* argv[]){
	char* inputFile = NULL;	
	//Use by default 10 as number of results (piazza) 
	int topK = 10;	
	inputCheck(argc,argv,inputFile,topK);
	int lineNum = 0;
	char ** documents = readFile(inputFile, lineNum);
	cout << "Please wait while your input file is being processed." <<endl;
	//Insert in Trie and take number of words for each sentence
	int * nwords = new int [lineNum+1]();
	LetterList *llist = insertTrie(documents,lineNum,nwords);
	cout << "Your file: '"<< inputFile <<"' was processed!"<< endl << "Type your commands.." <<endl;
	//Read Command
	char * cmd;
	char * q;
	while(1){
		char * mystring = NULL;
		size_t s = 0;
		getline(&mystring, &s, stdin);
		//Handle enter
		if (!strcmp(mystring,"\n"))	cmd = mystring;
		else cmd = strtok(mystring, " \n");
		/* /exit */
		if (!strcmp(cmd,"/exit")) break;
		/* /search */
		else if (!strcmp(cmd,"/search")) {
			q = strtok (NULL, " \t\n");
			int n=0; //number of queries
			while(q != NULL && n<10){
				cout << "My lovely q -> "<< q <<endl;
				q = strtok (NULL, " \t\n");
				n++;
			}
			if (n==0) cerr << "Provide at least 1 argument for search!" <<endl;
			else search(llist,n,lineNum,nwords); //list of queries? anti to n
			// Try again
			continue;
		}
		/* /df */
		else if (!strcmp(cmd,"/df")) {
			//df();
			q = strtok (NULL, " \t\n");
			int n=0; //number of queries
			while(q != NULL && n<10){
				cout << "My lovely q -> "<< q <<endl;
				q = strtok (NULL, " \t\n");
				n++;
			}
			if (n==0) cerr << "Provide at least 1 argument for search!" <<endl;
			else search(llist,n,lineNum,nwords); //list of queries? anti to n
			// Try again
			continue;
		}
		/* /tf */
		else if (!strcmp(cmd,"/tf")) {
			q = strtok (NULL, " \t\n");
			int n=0; //number of parameters (id,word)
			char** params = new char*[2];
			while(q != NULL && n<=2){
				params[n] = new char[strlen(q)+1];
				strcpy(params[n],q);
				//if (!numberCheck(q)) n=2;
				q = strtok (NULL, " \t\n");
				n++;
			}
			switch (n){
				case 0: 
					cerr << "2 arguments needed, 0 provided!" << endl;
					break;
				case 1:	
					cerr << "Need 1 more argument!" << endl;
					break;
				case 3:	
					cerr << "Provide no more than 2 arguments for search!" << endl;
					break;
				default: 
					if(!numberCheck(params[0]))	{
						cerr << "1st argument must be an integer!" << endl;
						break;
					}
					int argLine  = atoi(params[0]);
					if(argLine >= lineNum || argLine < 0 ) cerr << "Not a valid line number!" << endl;
					else cout << params[0] << " " << params[1] << " " << tf(llist,argLine,params[1]) << endl;
			}
			free2D(params,2);
			// Try again
			continue;
		}
		//Wrong Command
		else commandError();
		cout <<endl<<"Type next command or '/exit' to terminate"<<endl;
		free(mystring);
	}
	//Free Document
	free2D(documents,lineNum);
	exit(0);
}