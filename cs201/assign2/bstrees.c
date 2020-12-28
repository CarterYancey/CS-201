#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dll.h"
#include "stack.h"
#include "queue.h"
#include "integer.h"
#include "real.h"
#include "scanner.h"
#include "comparator.h"
#include "bst.h"
#include "rbt.h"
#include "vbst.h"

typedef int (*Comparator)(void* x ,void* y);
typedef void (*Printer)(FILE* f, void* v);
//void runTests();
char* cleanTokens(char* word); 

void displayString(FILE *fp,void *v){
	fprintf(fp, "\"%s\"", (char*)v);
}

int main(int argc,char **argv)
{
	FILE *outfile = stdout;
	FILE *corpus = fopen(argv[2], "r");
	FILE *commands = fopen(argv[3], "r");
	if (argc == 5) outfile = fopen(argv[4],"w");

	vbst *fVBST = newVBST(displayString, stringComparator);
	rbt *fRBT = newRBT(displayString, stringComparator);
	if (strcmp(argv[1], "-v") == 0){
		//Reading Corpus
		char* word;
		if (corpus != 0){
			if (stringPending(corpus))
				word = readString(corpus);
			else
				word = readToken(corpus);
			while (!feof(corpus)){
				word = cleanTokens(word);
				if (strlen(word) >0){
					insertVBST(fVBST, word);
					}//fprintf(outfile, "%s ", word);}
				if (stringPending(corpus)) 
					word = readString(corpus);
				else
					word = readToken(corpus);
			}
		}
		//Reading Commands
		char* command;
		if (commands != 0){
		if (stringPending(commands)) command = readString(commands);
		else
			command = readToken(commands);
		while (!feof(commands)){
			if (strcmp(command,"s") == 0)
				displayVBST(outfile, fVBST);
			else if (strcmp(command,"r") == 0)
				statisticsVBST(fVBST, outfile);
			else if (strcmp(command,"i") == 0){
				if (stringPending(commands)) command = readString(commands);
				else
					command = readToken(commands);
				command = cleanTokens(command);
				if (strlen(command) >0)
					insertVBST(fVBST, command);
			}
			else if (strcmp(command,"d") == 0){
				if (stringPending(commands)) command = readString(commands);
				else
					command = readToken(commands);
				command = cleanTokens(command);
				deleteVBST(fVBST, command);
			}
			else if (strcmp(command,"f") == 0){
				if (stringPending(commands)) command = readString(commands);
				else
					command = readToken(commands);
				command = cleanTokens(command);
				fprintf(outfile, "Frequency of \"%s\": %d\n", command, findVBST(fVBST, command));
			}
			if (stringPending(commands)) command = readString(commands);
			else
				command = readToken(commands);
		}
		}
	}
	else if (strcmp(argv[1], "-r") == 0){
		//Reading Corpus
		char* word;
		if (corpus != 0){
		if (stringPending(corpus)) word = readString(corpus);
		else
			{word = readToken(corpus);}
		while (!feof(corpus)){
			word = cleanTokens(word);
			if (strlen(word) >0){
				insertRBT(fRBT, word);
			}
			if (stringPending(corpus)) word = readString(corpus);
			else
				{word = readToken(corpus);}
		}
		}
		//Reading Commands
		char* command;
		if (commands != 0){
			if (stringPending(commands)) command = readString(commands);
			else
				command = readToken(commands);
		while (!feof(commands)){
			if (strcmp(command,"s") == 0)
				displayRBT(outfile, fRBT);
			else if (strcmp(command,"r") == 0)
				statisticsRBT(fRBT, outfile);
			else if (strcmp(command,"i") == 0){
//				command = readToken(commands);
			if (stringPending(commands)) command = readString(commands);
			else
				command = readToken(commands);
				command = cleanTokens(command);
				if (strlen(command) >0)
					insertRBT(fRBT, command);
			}
			else if (strcmp(command,"f") == 0){
//				command = readToken(commands);
			if (stringPending(commands)) command = readString(commands);
			else
				command = readToken(commands);
				command = cleanTokens(command);
				fprintf(outfile, "Frequency of \"%s\": %d\n", command, findRBT(fRBT, command));
			}
//			command = readToken(commands);
			if (stringPending(commands)) command = readString(commands);
			else
				command = readToken(commands);
		}
		}
				
	}
//	runTests(argv, outfile, corpus);
	return 0;
}
/*
void runTests(char** argv, FILE *outfile, FILE *corpus){
	fprintf(outfile, "\n\n----------------- NOW TESTING----------------------- \n\n");
	vbst *VBT = newVBST(displayInteger, intComparator);
	insertVBST(VBT, newInteger(13));
	insertVBST(VBT, newInteger(13));
	displayVBST(outfile, VBT);
	//displayBST(outfile, VBT->tree);
	return;
}
	bst *BST2 = newBST(displayString, stringComparator);
/	bst *BT = newBST(displayInteger, intComparator);
/	insertBST(BT, newInteger(13));
/	insertBST(BT, newInteger(13));
/	displayBST(outfile, BT);
	insertBST(BST2, "c");
	insertBST(BST2, "e");
	insertBST(BST2, "b");
	insertBST(BST2, "a");
	insertBST(BST2, "d");
	insertBST(BST2, "f");
	insertBST(BST2, "g");
	insertBST(BST2, "h");
	insertBST(BST2, "i");
	displayBST(outfile, BST2);
	fprintf(outfile, "\n");
	statisticsBST(BST2, outfile);
	fprintf(outfile, "Was found = %d\n", findBST(BST2, "c"));
	fprintf(outfile, "Was found = %d\n", findBST(BST2, "y"));
	bst *BST3 = newBST(displayString, stringComparator);
	displayBST(outfile, BST3);
	printf("\n swapping c\n");
	bstNode* n = swapToLeafBSTNode(findBSTNode(BST2, "c"));
	displayBST(outfile, BST2);
	printf("\n pruing c\n");
	pruneBSTNode(n);
	displayBST(outfile, BST2);
	printf("\n swapping a\n");
	bstNode* g = swapToLeafBSTNode(findBSTNode(BST2, "a"));
	displayBST(outfile, BST2);
	printf("\n pruning a\n");
	pruneBSTNode(g);
	displayBST(outfile, BST2);

	fprintf(outfile, "\n\n NOW TESTING VBST \n\n");
	vbst *VBST = newVBST(displayVBSTstring, vbstComparator);
	insertVBST(VBST, "c");
	insertVBST(VBST, "c");
	insertVBST(VBST, "e");
	insertVBST(VBST, "b");
	insertVBST(VBST, "a");
	insertVBST(VBST, "a");
	insertVBST(VBST, "a");
	insertVBST(VBST, "d");
	insertVBST(VBST, "f");
	insertVBST(VBST, "g");
	insertVBST(VBST, "h");
	insertVBST(VBST, "h");
	insertVBST(VBST, "h");
	insertVBST(VBST, "h");
	insertVBST(VBST, "i");
	displayVBST(outfile, VBST);
	corpus = fopen(argv[2], "r");
	vbst *vBST = newVBST(displayVBSTstring, vbstComparator);
	if (strcmp(argv[1], "-v") == 0){
		char* word = readToken(corpus);
		while (!feof(corpus)){
			if (word[0] == '"'){
				if (word[strlen(word)-1] != '"'){
				char* word2 = readToken(corpus);
				while (word2[strlen(word2)-1] != '"'){
					strcat(word, " ");
					strcat(word, word2);
					word2 = readToken(corpus);
				}
				strcat(word, " ");
				strcat(word, word2);
				}
			}
				char* word3 = malloc(sizeof(word));
				unsigned int w3 = 0;
				for (unsigned int x =0; x<strlen(word); x++){
					if (isalpha(word[x])){
						word3[w3] = tolower(word[x]);
						w3 += 1;
					}
					else if (word[x] == ' '){
						word3[w3] = ' ';
						w3 += 1;
					}
				}
				strcpy(word, word3);
			insertVBST(vBST, word);
			printf("%s\n", word);
			word = readToken(corpus);
		}
	displayVBST(outfile, vBST);
	statisticsVBST(vBST, outfile);
	fprintf(outfile, "Deleting the word 'the'\n");
	deleteVBST(vBST, "the");
	displayVBST(outfile, vBST);
	statisticsVBST(vBST, outfile);
	fprintf(outfile, "Deleting the word 'lazy'\n");
	deleteVBST(vBST, "lazy");
	displayVBST(outfile, vBST);
	statisticsVBST(vBST, outfile);
	fprintf(outfile, "Deltiting the again\n");
	deleteVBST(vBST, "the");
	displayVBST(outfile, vBST);
	statisticsVBST(vBST, outfile);
	fprintf(outfile, "Deltiting 'dog'\n");
	deleteVBST(vBST, "dog");
	displayVBST(outfile, vBST);
	statisticsVBST(vBST, outfile);
	}
	fprintf(outfile, "\n DONE WITH VBST\n");

	fprintf(outfile, "\n\n NOW TESTING RBT \n\n");
	rbt *RBT = newRBT(displayRBTstring, rbtComparator);
	insertRBT(RBT, "c");
	insertRBT(RBT, "e");
	insertRBT(RBT, "b");
	insertRBT(RBT, "a");
	insertRBT(RBT, "d");
	insertRBT(RBT, "f");
	insertRBT(RBT, "g");
	insertRBT(RBT, "h");
	insertRBT(RBT, "i");
	displayRBT(outfile, RBT);
	statisticsRBT(RBT, outfile);


	return;
}
*/
char* cleanTokens(char* word){
			int w3 = 0;
			int length = strlen(word);
//			char* word3 = (char*)malloc(1000000);//(length+1)*sizeof(word));
			char* word3 = malloc(sizeof(word)*(length+1));
			for (int x=0; x<length; x++){
				if (isalpha(word[x])){
					word3[w3] = tolower(word[x]);
					w3 += 1;
				}
				else if (isspace(word[x])){//word[x] == ' ' || word[x] == '\n'){
					if (w3 == 0 || word3[w3-1] != ' '){
						word3[w3] = ' ';
						w3 += 1;
					}
				}
			}
			strcpy(word, word3);
			return word;

}
