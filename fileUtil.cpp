//Function Definitions
#include "fileUtil.h"

void paramError(char * programName ,const char * reason){
	//Display the problem
	cerr << reason << ", please try again." << endl;
	//Show the usage and exit.
	cerr << "Usage : " << programName << " [-i <DOCUMENT>][-k <NUMBER OF RESULTS GREATER THAN ZERO>]" << endl; 
	exit(1);
}

//Print Format when problem with command occurs
void commandError(){
	cerr << "##############################################################"<<endl;
	cerr << "#Invalid command!" <<endl;
	cerr << "#Available commands :\t/search <q1> <q2> <q3> <q4> ... <q10>" << endl;
	cerr << "#\t\t\t" << "/df or /df <word>" << endl << "#\t\t\t" << "/tf <integer> <word>" << endl << "#\t\t\t" << "/exit" << endl;
	cerr << "##############################################################"<<endl;
}

//Check string if it is number
bool numberCheck(char *str){
	int len = (int)strlen(str);
	//In case there is a letter with the number and atoi clears it
	for (int j=0; j<len; j++)
		if (!isdigit(str[j])) return false;
	return true;
}

//Read input File
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
		//Lines
		char * mystring = NULL;
		size_t n = 0;
		for (int i=0; i<lines;i++){
			ssize_t size = getline(&mystring, &n, file);
			mystring[size-1]='\0';
			char *token = strtok(mystring," \t");
			//For first character of first line we check without using atoi
			if (token==NULL || !numberCheck(token) || atoi(mystring)!=i ) {
				cerr <<"Invalid number close in line "<< i << " of file" <<endl;
				exit(4);
			}
			documents[i] = new char[size+1-strlen(token)];
			strcpy(documents[i],mystring+strlen(token)+1);	
		}
		if(mystring!=NULL) free(mystring);
		fclose (file);
		return documents;
	}
}

//Check the arguments given by the user
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
	}
	else paramError(argv[0], "This is not an appropriate syntax");

	cout << "Arguments taken : " << inputFile << " " << topK << endl;
}

//Free a 2D array knowing its size with lineNum
void free2D(char ** documents, const int& lineNum){
	for (int i=0; i < lineNum ; i++) {
		delete[] documents[i];
	}
	delete[] documents;
}