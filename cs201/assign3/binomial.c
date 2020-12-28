#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "queue.h"
#include "darray.h"
#include "binomial.h"

typedef struct BinomialNode{
	void *value;
	DArray *children;
	struct BinomialNode *parent;
	void (*display)(FILE *fp, void *v);
} BinomialNode;

BinomialNode *newBinomialNode(void (*display)(FILE *,void *),void *value){
	BinomialNode *BNode = malloc(sizeof(BinomialNode));
	BNode->display = display;
	BNode->value = value;
	BNode->parent = NULL;
	BNode->children = newDArray(display);//malloc(sizeof(void*));
	return BNode;
}

void displayBinomialNode(FILE *fp,BinomialNode *n){
	n->display(fp, n->value);
	fprintf(fp,"-%d", sizeDArray(n->children));
}

typedef struct Binomial{
	DArray *rootlist;
	int (*compare)(void *v1, void *v2);
	void (*update)(void*v, BinomialNode *BNode);
	BinomialNode *extreme;
	int size;
	void (*display)(FILE *fp, void *v);
} Binomial;

Binomial *newBinomial(
	void (*d)(FILE *,void *),        //display
	int (*c)(void *,void *),         //comparator
	void (*u)(void *,BinomialNode *) //updater
	){
	Binomial *binomial = malloc(sizeof(Binomial));
	binomial->display = d;
	binomial->compare = c;
	binomial->update = u;
	binomial->rootlist = newDArray(d);
	binomial->extreme = NULL;
	binomial->size = 0;
	return binomial;
}

BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y){
	if (b->compare(x->value, y->value) < 0){
		int i = sizeDArray(y->children);
		setDArray(x->children, i, y);
		y->parent = x;
		return x;
	}
	else if (b->compare(x->value,y->value) >= 0){
		int i = sizeDArray(x->children);
		setDArray(y->children, i, x);
		x->parent = y;
		return y;
	}
	else return x;
}

void consolidate(Binomial *b, BinomialNode *n){
	int degree = sizeDArray(n->children);
	BinomialNode *d;// = getDArray(b->rootlist, degree);
	if (degree >= sizeDArray(b->rootlist)){d = NULL;} 
	else d = getDArray(b->rootlist, degree);
	while (d != NULL){//&& sizeDArray(b->rootlist)-1 != degree){
		n = combine(b,n, d);
		setDArray(b->rootlist,degree, NULL);
		degree += 1;
		if (degree >= sizeDArray(b->rootlist)){d = NULL;} 
		else d = getDArray(b->rootlist, degree);
	}
	setDArray(b->rootlist,degree, n);
}

void merge(Binomial *b, DArray *donor){
	for (int x = 0; x<sizeDArray(donor); x++){
		((BinomialNode*)(getDArray(donor, x)))->parent = getDArray(donor, x);
		consolidate(b,getDArray(donor, x));
	}
	free(donor);
}

BinomialNode *bubbleUp(Binomial *b, BinomialNode *n){
	if (n->parent == n) return n;//CHANGING NEX LINE TO < FROM >=
	else if (n != NULL && b->compare(n->value, n->parent->value) > 0) return n;
	else{
		if (b->update != NULL){// && n->value != NULL){
		b->update(n->value, n->parent);
		b->update(n->parent->value, n);}
	
		void* v = n->value;//	BinomialNode *temp = n;
		n->value = n->parent->value;
		n->parent->value = v;//temp->value;
		return bubbleUp(b, n->parent);
	}
}

BinomialNode *insertBinomial(Binomial *b,void *value){
	BinomialNode *n = newBinomialNode(b->display, value);
	n->parent = n;
	n->children = newDArray(b->display);
	consolidate(b, n);
	b->size += 1;
	if (b->extreme == NULL) b->extreme = n;
	else if (b->compare(b->extreme->value, n->value) > 0)
		b->extreme = n;
	//if (sizeDArray(b->rootlist) >1)
	return n;
}

int sizeBinomial(Binomial *b){
	return b->size;
}

void deleteBinomial(Binomial *b,BinomialNode *n){
	decreaseKeyBinomial(b, n, NULL);
	extractBinomial(b);
return;
}

void decreaseKeyBinomial(Binomial *b,BinomialNode *n,void *value){
	n->value = value;
	BinomialNode *new = bubbleUp(b, n);
	//update b's extreme value pointer
	if (b->compare(b->extreme->value, new->value) >= 0)
		b->extreme = new;
//	for (int x=0; x<sizeDArray(b->rootlist); x++){
//		BinomialNode *p = getDArray(b->rootlist, x);
//		if (p != NULL && b->compare(b->extreme->value, p->value) > 0)
//			b->extreme = p;
//	}
return;
}

void *extractBinomial(Binomial *b){
	BinomialNode *y = b->extreme;
	//removeDArray(b->rootlist);
	for (int x=0; x<sizeDArray(b->rootlist); x++){
		BinomialNode *p = getDArray(b->rootlist, x);
		if (y==p){//p != NULL && b->compare(y->value, p->value) == 0){
			setDArray(b->rootlist, x, NULL);
			break;
		}
	}
	merge(b,y->children);
	b->size -= 1;
	//store y value
	void *v = y->value;
	//free extreme node
	free(b->extreme);
	//find new extreme
	b->extreme = NULL;
	for (int x=0; x<sizeDArray(b->rootlist); x++){
		BinomialNode *n = getDArray(b->rootlist, x);
		if (n != NULL){
			if (b->extreme == NULL || b->compare(b->extreme->value, n->value) >= 0)
				b->extreme = n;
		}
	}
	return v;
}

void displayBinomial(FILE *fp,Binomial *b){
	for (int x=0; x<sizeDArray(b->rootlist); x++){
		queue *Q = newQueue(b->display);
		BinomialNode *n = getDArray(b->rootlist, x);
		int level = 0;
		if (n != NULL){
			fprintf(fp, "%d: ", level);
			displayBinomialNode(fp, n);
		
			if (sizeDArray(n->children) > 0)
				enqueue(Q, NULL);
			for (int c = 0; c< sizeDArray(n->children); c++){
				BinomialNode *child = getDArray(n->children, c);
				enqueue(Q, child);
			}
		
		while (sizeQueue(Q)){
			n = dequeue(Q);
			if (n == NULL){
	//			fprintf(fp,"\n");
				if (sizeQueue(Q) > 0){
					fprintf(fp,"\n%d:", ++level);
					enqueue(Q, NULL);
				}
	//			}
			}
			else{
				fprintf(fp, " ");
				displayBinomialNode(fp, n);
				fprintf(fp, "(");
				displayBinomialNode(fp, n->parent);
				fprintf(fp, ")");
			//	if (sizeDArray(n->children) > 0)
			//		enqueue(Q, NULL);
				for (int c =0; c< sizeDArray(n->children); c++){
					BinomialNode *child = getDArray(n->children, c);
					enqueue(Q, child);
				}
			}
		}
	
		fprintf(fp, "\n----\n");
		}
	}
return;
}
