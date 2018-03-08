// Header --> Functions Declarations
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstring>
#include <ctype.h>
//#include <cstdio>
#include <math.h> //log //floor
#include "postingList.h"
#include "letterList.h"

using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void paramError(char * programName ,const char * reason);

void commandError();

bool numberCheck(char *str);

char** readFile(char* myFile, int &lines);

void inputCheck(int argc, char* argv[], char*& inputFile, int& topK);

void print(char ** arr, const int& lineNum);

void printSplit(char ** arr, const int& lineNum);

void free2D(char ** documents, const int& lineNum);


/******************************TRIE****************************************************/

LetterList* insertTrie(char** documents, const int& lineNum, int* nwords);
void search(LetterList* llist, const int& n, const int& lineNum, int* nwords);
void df();
int tf(LetterList* llist, const int& id, const char* word);

double idf(const int& n, const int& nqi );
double score(const double& idf, const int& tf, const int& avgdl, const int& D, const double& k1 = 1.2, const double& b = 0.75);


#endif