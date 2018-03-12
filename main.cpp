#include "functions.h"
#include "heap.h"

/*void test(){
	WordList wlist ("axne");
	wlist.add("wldsa"); 
	wlist.add("asad"); 
	wlist.add("wlqwerwqdsa"); 
	wlist.print(); 
	exit(0);
}*/

/*void test(){
	Heap h(11);
	h.add(3,1);
	h.add(4,7);
	h.add(5,3);
	cout<< "axne "<<endl;
	HeapNode* hn = h.popMax();
	cout<< "23e32 "<<endl;
	cout << hn->score<<endl;
	delete hn;
}*/

int main(int argc, char* argv[]){
	//test();
	//exit(0);
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
	char * mystring = NULL;
	while(1){
		size_t s = 0;
		getline(&mystring, &s, stdin);
		//delete \n
		mystring[strlen(mystring)-1]= '\0';
		//Handle enter
		if (!strcmp(mystring,"")) cmd = mystring;
		else cmd = strtok(mystring, " ");
		/* /exit */
		if (!strcmp(cmd,"/exit")) {
			free(mystring);
			break;
		}
		/* /search */
		else if (!strcmp(cmd,"/search")) search();
		/* /df */
		else if (!strcmp(cmd,"/df")) df(llist);
		/* /tf */
		else if (!strcmp(cmd,"/tf")) tf(llist,lineNum);
		//Wrong Command
		else commandError();
		cout <<endl<<"Type next command or '/exit' to terminate"<<endl;
		free(mystring);
	}
	//Delete nwords
	delete[] nwords;
	//Delete trie
	delete llist;
	//Free Document
	free2D(documents,lineNum);
	exit(0);
}