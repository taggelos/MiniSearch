// Header --> Functions Declarations
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstring>
#include <ctype.h>
//#include <cstdio>
#include "postingList.h"
#include "letterList.h"

using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void paramError(char * programName ,const char * reason);

void commandError();

int numberCheck(char *str);

char** readFile(char* myFile, int &lines);

void inputCheck(int argc, char* argv[], char*& inputFile, int& topK);

void print(char ** arr, const int& lineNum);

void printSplit(char ** arr, const int& lineNum);

void freeDocs(char ** documents, const int& lineNum);


/******************************TRIE****************************************************/

void insertTrie(char** documents, int lineNum);
void search();
void df();
void tf();

#endif