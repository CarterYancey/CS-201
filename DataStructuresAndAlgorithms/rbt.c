#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "bst.h"
#include "rbt.h"

typedef struct RBTval{
	void *value;
	int freq;
	int color; //1=red; 0=black
	void (*d)(FILE*, void*);
	int (*c)(void*, void*);
}RBTval;

void rbtDisplay(FILE *fp, void* v){
	RBTval *vv = (RBTval*)v;
	vv->d(fp,vv->value);
	if (vv->freq >1) fprintf(fp, "-%d", vv->freq);
	if (vv->color == 0) fprintf(fp, "-B");
	else fprintf(fp, "-R");
}

int rbtCompare(void* x, void* y){
	RBTval *xx = (RBTval*)x;
	RBTval *yy = (RBTval*)y;
	return yy->c(xx->value, yy->value);
}

int getRBTFreq(void *v){
	RBTval *vv = (RBTval*)v;
	return vv->freq;
}
int getRBTColor(void *v){
	RBTval *vv = (RBTval*)v;
	return vv->color;
}

void setRBTFreq(void *v, int s){
	RBTval *vv = (RBTval*)v;
	vv->freq =s;
	return;
}

RBTval *newRBTval(void *v, void(*d)(FILE*, void*), int(*c)(void*, void*)){
	RBTval *Value = malloc(sizeof(RBTval));
	Value->value = v;
	Value->freq = 1;
	Value->color = 1;
	Value->d = d;
	Value->c = c;
	return Value;
}

void rotateLeft(bst *bstTree, bstNode *x){
	bstNode *y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == x){
		bstTree->root = y;
		y->parent = y;
	}
	else{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void rotateRight(bst *bstTree, bstNode *x){
	bstNode *y = x->parent;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == y){
		bstTree->root = x;
		x->parent = x;
	}
	else{
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;

}

void rbtFixUp(rbt *rbtTree, bstNode *Node){
	while(1){
		if (Node == rbtTree->tree->root) break;
		RBTval *ParentValue = Node->parent->value;
		if (ParentValue->color == 0) break;
		bstNode *Uncle = Node->parent->parent->right;
		if (Node->parent == Node->parent->parent->right)
			Uncle = Node->parent->parent->left;
		RBTval *UncleValue;
		if (Uncle != NULL){
			UncleValue = Uncle->value;}
		RBTval *GrandparentValue = Node->parent->parent->value;
		if (Uncle != NULL && UncleValue->color == 1){
			ParentValue->color = 0;
			UncleValue->color = 0;
			GrandparentValue->color = 1;
			Node->parent->value = ParentValue;
			Uncle->value = UncleValue;
			Node->parent->parent->value = GrandparentValue;
			Node = Node->parent->parent;
		}
		else{
			int NtoPrelation = 1;
			int PtoGPrelation = 1;
			if (Node == Node->parent->left)
				NtoPrelation = 0;
			if (Node->parent == Node->parent->parent->left)
				PtoGPrelation = 0;
			if (NtoPrelation != PtoGPrelation){
				//rotate node to parent
				if (NtoPrelation == 1){
					rotateLeft(rbtTree->tree, Node->parent);
					Node->left->parent = Node;
					Node = Node->left;
				}
				else{
					rotateRight(rbtTree->tree, Node);
					Node->right->parent = Node;
					Node = Node->right;
				}
				//??? parent = old x

			}
			ParentValue = Node->parent->value;
			ParentValue->color = 0;
			Node->parent->value = ParentValue;
			GrandparentValue = Node->parent->parent->value;
			GrandparentValue->color = 1;
			Node->parent->parent->value = GrandparentValue;
			//rotate parent to grandparent
			if (PtoGPrelation == 1)
				rotateLeft(rbtTree->tree, Node->parent->parent);
			else
				rotateRight(rbtTree->tree, Node->parent);
			break;
		}
	}
	//color root black
	RBTval *RootValue = rbtTree->tree->root->value;
	RootValue->color = 0;
	rbtTree->tree->root->value = RootValue;
	return;
}

rbt *newRBT(void (*d)(FILE *,void *),int (*c)(void *,void *)){
	rbt *rbtTree = malloc(sizeof(rbt));
	if (rbtTree == 0){
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	rbtTree->tree = newBST(rbtDisplay, rbtCompare);
	rbtTree->size = 0;
	rbtTree->words = 0;
	rbtTree->display = d;
	rbtTree->compare = c;
	return rbtTree;
}

void insertRBT(rbt *rbtTree,void *v){
	RBTval *Value = newRBTval(v, rbtTree->display, rbtTree->compare);
	bstNode *node= findBSTNode(rbtTree->tree, Value);
	if (node != NULL){
		Value->freq += getRBTFreq(node->value);
		Value->color = getRBTColor(node->value);
		node->value = Value;
	}
	else{
		insertBST(rbtTree->tree, Value);
		rbtFixUp(rbtTree, findBSTNode(rbtTree->tree, Value));
		rbtTree->size += 1;
	}
	rbtTree->words += 1;
	return;
}

int findRBT(rbt *rbtTree,void *v){
	RBTval *Value = newRBTval(v, rbtTree->display, rbtTree->compare);
	bstNode *node = findBSTNode(rbtTree->tree, Value);
	if (node != NULL)
	return getRBTFreq(node->value);
	else return 0;
}

void deleteRBT(rbt *rbtTree, void *v){ //dont do
	RBTval *Value = newRBTval(v, rbtTree->display, rbtTree->compare);
	bstNode *node = findBSTNode(rbtTree->tree, Value);
	if (node == NULL) fprintf(stderr, "Value \"%s\" not found\n", (char*)v);
	return;
}

int sizeRBT(rbt *rbtTree){
	return rbtTree->size;
}

int wordsRBT(rbt *rbtTree){
	return rbtTree->words;
}
	
void statisticsRBT(rbt *rbtTree,FILE *outfile){
	fprintf(outfile, "Words/Phrases: %d\n", (rbtTree->words));
	statisticsBST(rbtTree->tree, outfile);
}

void displayRBT(FILE *outfile,rbt *rbtTree){
	displayBST(outfile, rbtTree->tree);
}
void checkRBT(rbt *);               //optional
