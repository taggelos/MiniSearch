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

void freeDocs(char ** documents, const int& lineNum);


/******************************TRIE****************************************************/

int* insertTrie(char** documents, int lineNum);
void search();
void df();
void tf();

double idf(const int& n, const int& nqi );
double score(const double& idf, const int& tf, const int& avgdl, const int& D, const int& k1, const int& b);


#endif