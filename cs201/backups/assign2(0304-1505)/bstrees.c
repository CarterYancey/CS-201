#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
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

typedef struct VBSTval{
	void *value;
	int freq;
	void (*d);
	void (*c);
}VBSTval;

int vbstComparator(void* x, void* y){
	VBSTval *xx = (VBSTval*)x;
	VBSTval *yy = (VBSTval*)y;
	void *xxx = xx->value;
	void *yyy = yy->value;
	return stringComparator(xxx, yyy);
}

void displayString(FILE *fp,void *v){
	fprintf(fp, "%s", (char*)v);
	}
void displayVBSTstring(FILE *fp,void *v){
	VBSTval *vv = (VBSTval*)v;
	displayString(fp, vv->value);
	//fprintf(fp, "%s", vv->value);
	}

int main(int argc,char **argv)
{
	FILE *outfile = stdout;
	FILE *corpus = fopen(argv[2], "r");
	FILE *commands = fopen(argv[3], "r");
	if (argc == 5) outfile = fopen(argv[4],"w");

	bst *BST = newBST(displayString, stringComparator);
	if (strcmp(argv[1], "-v") == 0){
		char* word = readToken(corpus);
		while (!feof(corpus)){
			if (word[0] == '"'){
				char* word2 = readToken(corpus);
				while (word2[strlen(word2)-1] != '"'){
					strcat(word, " ");
					strcat(word, word2);
					word2 = readToken(corpus);
				}
				strcat(word, " ");
				strcat(word, word2);
				char* word3 = malloc(sizeof(word));
				for (unsigned int x =1; x<strlen(word)-1; x++)
					word3[x-1] = tolower(word[x]);
				strcpy(word, word3);
			}
			insertBST(BST, word);
			printf("%s\n", word);
			word = readToken(corpus);
		}
	}

	bst *BST2 = newBST(displayString, stringComparator);
	insertBST(BST2, "c");
	insertBST(BST2, "e");
	insertBST(BST2, "b");
	insertBST(BST2, "a");
	insertBST(BST2, "d");
	insertBST(BST2, "f");
	insertBST(BST2, "g");
	insertBST(BST2, "h");
	insertBST(BST2, "i");
	displayBST(outfile, BST);
	fprintf(outfile, "\n");
	statisticsBST(BST, outfile);
	displayBST(outfile, BST2);
	fprintf(outfile, "\n");
	statisticsBST(BST2, outfile);
	fprintf(outfile, "Was found = %d\n", findBST(BST2, "c"));
	fprintf(outfile, "Was found = %d\n", findBST(BST2, "y"));
	bst *BST3 = newBST(displayString, stringComparator);
	displayBST(outfile, BST3);
	bstNode* n = swapToLeafBSTNode(findBSTNode(BST2, "b"));
	displayBST(outfile, BST2);
	pruneBSTNode(n);
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
				char* word2 = readToken(corpus);
				while (word2[strlen(word2)-1] != '"'){
					strcat(word, " ");
					strcat(word, word2);
					word2 = readToken(corpus);
				}
				strcat(word, " ");
				strcat(word, word2);
				char* word3 = malloc(sizeof(word));
				for (unsigned int x =1; x<strlen(word)-1; x++)
					word3[x-1] = tolower(word[x]);
				strcpy(word, word3);
			}
			insertVBST(vBST, word);
			printf("%s\n", word);
			word = readToken(corpus);
		}
	}
	displayVBST(outfile, vBST);
	fprintf(outfile, "\n DONE WITH VBST\n");
/*
 	bst *BST = newBST(displayInteger, intComparator);
	insertBST(BST, newInteger(3));
	insertBST(BST, newInteger(5));
	insertBST(BST, newInteger(2));
//	insertBST(BST, newInteger(1));
	insertBST(BST, newInteger(4));
	insertBST(BST, newInteger(6));
	insertBST(BST, newInteger(7));
	insertBST(BST, newInteger(8));
	insertBST(BST, newInteger(9));
	displayBST(outfile, BST);
	fprintf(outfile, "\n");
	statisticsBST(BST, outfile);

 	bst *BST2 = newBST(displayInteger, intComparator);
	insertBST(BST2, newInteger(0));
	displayBST(outfile, BST2);
	fprintf(outfile, "\n");
	statisticsBST(BST2, outfile);
*/
	return 0;
}
