#include "trieUtil.h"
#include "heap.h"

int main(int argc, char* argv[]){
	char* inputFile = NULL;	
	//Use by default 10 as number of results (piazza)
	int topK = 10;	
	inputCheck(argc,argv,inputFile,topK);
	int lineNum = 0;
	char ** documents = readFile(inputFile, lineNum);
	cout << "Please wait while your input file is being processed." <<endl;
	//Insert in Trie and take number of words for each sentence
	int *nwords = new int [lineNum+1]();
	Trie *trie = insertTrie(documents,lineNum,nwords);
	cout << "Your file: '"<< inputFile <<"' was processed!"<< endl << "Type your commands.." <<endl;
	//Read Command
	char *cmd;
	char *mystring = NULL;
	size_t s = 0;
	while(getline(&mystring, &s, stdin)!=-1){
		//Delete \n
		mystring[strlen(mystring)-1]= '\0';
		//Handle enter
		if (!strcmp(mystring,"")) cmd = mystring;
		else cmd = strtok(mystring, " ");
		/* /exit */
		if (!strcmp(cmd,"/exit")){
			break;
		}
		/* /search */
		else if (!strcmp(cmd,"/search")) search(trie, lineNum, topK, documents, nwords);
		/* /df */
		else if (!strcmp(cmd,"/df")) df(trie);
		/* /tf */
		else if (!strcmp(cmd,"/tf")) tf(trie,lineNum);
		//Wrong Command
		else commandError();
		cout <<endl<<"Type next command or '/exit' to terminate"<<endl;		
	}
	if(mystring!=NULL) free(mystring);
	//Delete nwords
	delete[] nwords;
	//Delete trie
	delete trie;
	//Free Document
	free2D(documents,lineNum);
	exit(0);
}