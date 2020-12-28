#include <stdio.h>
#include <stdlib.h>

#include "dll.h"
#include "queue.h"
#include "bst.h"
#include "vbst.h"

typedef struct VBSTval{
	void *value;
	int freq;
	void (*d);
	void (*c);
} VBSTval;

int getFreq(void *v){
	VBSTval *vv = (VBSTval*)v;
	return vv->freq;
}

VBSTval *newVBSTval(void *v, void(*d)(FILE *, void*), int(*c)(void *, void*)){
	VBSTval *Value = malloc(sizeof(VBSTval));
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
	vbstTree->tree = newBST(d, c);
	vbstTree->size = 0;
	vbstTree->words = 0;
	
	return vbstTree;
}

void insertVBST(vbst *vbstTree,void *v){
	VBSTval *Value = newVBSTval(v, vbstTree->tree->display, vbstTree->tree->compare);
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
}

int findVBST(vbst *vbstTree,void *v){
	VBSTval *Value = newVBSTval(v, vbstTree->tree->display, vbstTree->tree->compare);
	return findBST(vbstTree->tree, Value->value);
}

void deleteVBST(vbst *vbstTree,void *v){
	VBSTval *Value = newVBSTval(v, vbstTree->tree->display, vbstTree->tree->compare);
	if (findVBST(vbstTree, v) ==1){
		if (Value->freq > 1)
			Value->freq -= 1;
		else{
			bstNode *node = findBSTNode(vbstTree->tree, Value->value);
			swapToLeafBSTNode(node);
			pruneBSTNode(node);
			vbstTree->size -= 1;
		}
		vbstTree->words -= 1;
	}
	else{
		fprintf(stderr, "not found");
	}
}

int sizeVBST(vbst *vbstTree){
	return vbstTree->size;
}

int wordsVBST(vbst *vbstTree){
	return vbstTree->words;
}

void statisticsVBST(vbst *,FILE *);

void displayVBST(FILE *file,vbst *vbstTree){
	queue *treeQ = newQueue(vbstTree->tree->display);
	enqueue(treeQ, vbstTree->tree->root);
	if (vbstTree->tree->root != NULL)
		enqueue(treeQ, NULL);
	bstNode *node;
	int line = 0;
	fprintf(file,"%d:", line);
	while (sizeQueue(treeQ)){
		node = dequeue(treeQ);
		if (node == NULL){
			fprintf(file,"\n");
			line ++;
			if (sizeQueue(treeQ) > 0){
				enqueue(treeQ, NULL);
				fprintf(file,"%d:", line);
			}
		}
		else{
			if (node->left == NULL && node->right == NULL)
				fprintf(file," =");
			fprintf(file," \"");
			vbstTree->tree->display(file, node->value);
			fprintf(file,"\"-%d(\"", getFreq(node->value));
			vbstTree->tree->display(file, node->parent->value);
			fprintf(file,"\"-%d)", getFreq(node->parent->value));
			if (node == node->parent->left)
				fprintf(file,"-l ");
			else if (node == node->parent->right)
				fprintf(file,"-r ");
			else
				fprintf(file,"- ");
			if (node->left != NULL)
				enqueue(treeQ, node->left);
			if (node->right != NULL)
				enqueue(treeQ, node->right);
		}
	}

	return;
}
void checkVBST(vbst *);               //optional
