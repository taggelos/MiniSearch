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
	exit(0);
}*/

int main(int argc, char* argv[]){
	//test();
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
		//delete \n
		mystring[strlen(mystring)-1]= '\0';
		//Handle enter
		if (!strcmp(mystring,"")) cmd = mystring;
		else cmd = strtok(mystring, " ");
		/* /exit */
		if (!strcmp(cmd,"/exit")) {
			delete mystring;
			break;
		}
		/* /search */
		else if (!strcmp(cmd,"/search")) {
			q = strtok (NULL, " \t");
			int n=0; //number of queries
			WordList wlist; //it is ok
			while(q != NULL && n<10){
				cout << "My lovely q -> "<< q <<endl;
				wlist.add(q);
				q = strtok (NULL, " \t");
				n++;
			}
			if (n==0) cerr << "Provide at least 1 argument for search!" <<endl;
			else wlist.print(); //wlist.//search(llist,lineNum,nwords); //list of queries? anti to n
		}
		/* /df */
		else if (!strcmp(cmd,"/df")) {
			q = strtok (NULL, " \t");
			int n=0;
			char* param=NULL;
			//take 0 or 1 arguments
			while(q != NULL && n<=1){
				param = new char[strlen(q)+1];
				strcpy(param,q);
				q = strtok (NULL, " \t");
				n++;
			}
			if (n>1) {
				cerr << "Provide at most 1 argument to search!" <<endl;
				delete param;
			}
			else {
				if (param!=NULL){
					PostingList* plist = llist->search(param);
					if (plist!=NULL){
						cout << param << " " << plist->getTotalTimes() <<endl;
					}
					else {
						cout << "The word was not found." <<endl;
					}
					delete param;
				}
				else llist->findAll();
			}
		}
		/* /tf */
		else if (!strcmp(cmd,"/tf")) {
			q = strtok (NULL, " \t");
			int n=0; //number of parameters (id,word)
			char** params = new char*[2];
			while(q != NULL && n<=2){
				params[n] = new char[strlen(q)+1];
				strcpy(params[n],q);
				//if (!numberCheck(q)) n=2;
				q = strtok (NULL, " \t");
				n++;
			}
			switch (n){
				case 0: 
					cerr << "2 arguments needed, 0 provided!" << endl;
					break;
				case 1:	
					cerr << "Need 1 more argument!" << endl;
					delete[] params;
					break;
				case 3:	
					cerr << "Provide no more than 2 arguments for search!" << endl;
					free2D(params,2);
					break;
				default: 
					if(!numberCheck(params[0]))	{
						cerr << "1st argument must be an integer!" << endl;
						break;
					}
					int argLine  = atoi(params[0]);
					if(argLine >= lineNum || argLine < 0 ) cerr << "Not a valid line number!" << endl;
					else cout << params[0] << " " << params[1] << " " << tf(llist,argLine,params[1]) << endl;
					free2D(params,2);
			}
		}
		//Wrong Command
		else commandError();
		cout <<endl<<"Type next command or '/exit' to terminate"<<endl;
	}
	//Free Document
	free2D(documents,lineNum);
	exit(0);
}