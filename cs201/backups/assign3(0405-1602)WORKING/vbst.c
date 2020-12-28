#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "bst.h"
#include "vbst.h"

typedef struct VBSTval{
	void *value;
	int freq;
	void (*d)(FILE *, void *);
	int (*c)(void *, void *);
} VBSTval;

void vbstDisplay(FILE *fp, void *v){
	VBSTval *vv = (VBSTval*)v;
	vv->d(fp, vv->value);
	if (vv->freq >1)
	fprintf(fp, "-%d", vv->freq);
	return;
}

int vbstCompare(void* x, void* y){
	VBSTval *xx = (VBSTval*)x;
	VBSTval *yy = (VBSTval*)y;
	return yy->c(xx->value, yy->value);
}

int getFreq(void *v){
	VBSTval *vv = (VBSTval*)v;
	return vv->freq;
}
void setFreq(void *v, int s){
	VBSTval *vv = (VBSTval*)v;
	vv->freq = s;
	return;
}

VBSTval *newVBSTval(void *v, void(*d)(FILE *, void*), int(*c)(void *, void*)){
	VBSTval *Value = malloc(sizeof(VBSTval));
	if (Value == 0){
		fprintf(stderr, "out of mem");
		exit(-1);
	}
	Value->value = v;
	Value->freq = 1;
	Value->d = d;
	Value->c = c;
	return Value;
	}

vbst *newVBST(void (*d)(FILE *,void *),int (*c)(void *,void *)){
	vbst *vbstTree = malloc(sizeof(vbst));
	if (vbstTree == 0){
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	vbstTree->tree = newBST(vbstDisplay, vbstCompare);
	vbstTree->display = d;
	vbstTree->compare = c;
	vbstTree->size = 0;
	vbstTree->words = 0;
	
	return vbstTree;
}

void insertVBST(vbst *vbstTree,void *v){
	VBSTval *Value = newVBSTval(v, vbstTree->display, vbstTree->compare);
	bstNode *node= findBSTNode(vbstTree->tree, Value);
	if (node != NULL){
		Value->freq += getFreq(node->value);
		node->value = Value;
	}
	else{
		insertBST(vbstTree->tree, Value);
		vbstTree->size += 1;
	}
	vbstTree->words += 1;
	return;
}

int findVBST(vbst *vbstTree,void *v){
	VBSTval *Value = newVBSTval(v, vbstTree->tree->display, vbstTree->tree->compare);
	bstNode *node = findBSTNode(vbstTree->tree, Value);
	if (node != NULL)
		return getFreq(node->value);
	else return 0;
}


void deleteVBST(vbst *vbstTree,void *v){
	VBSTval *Value = newVBSTval(v, vbstTree->tree->display, vbstTree->tree->compare);
	bstNode *node = findBSTNode(vbstTree->tree, Value);
	if (node != NULL){
		int freq = getFreq(node->value);
		if (freq > 1)
			setFreq(node->value, freq-1);
		else{
			bstNode *delete = swapToLeafBSTNode(node);
			if (delete == vbstTree->tree->root)
				vbstTree->tree->root = NULL;
			else
				pruneBSTNode(vbstTree->tree, delete);
			vbstTree->size -= 1;
		}
		vbstTree->words -= 1;
	}
	else{
		fprintf(stderr, "Value \"%s\" not found\n", (char*)v);
	}
	return;
}

int sizeVBST(vbst *vbstTree){
	return vbstTree->size;
}

int wordsVBST(vbst *vbstTree){
	return vbstTree->words;
}

void statisticsVBST(vbst *vbstTree,FILE *fp){
	fprintf(fp, "Words/Phrases: %d\n", wordsVBST(vbstTree));
	statisticsBST(vbstTree->tree, fp);
	return;
	
}

void displayVBST(FILE *file,vbst *vbstTree){
	displayBST(file, vbstTree->tree);
	return;
}
void checkVBST(vbst *);               //optional
