#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "bst.h"

bst *newBST(void (*d)(FILE *, void*), int (*c)(void *, void *)){
	bst *bstTree = malloc(sizeof(bst));
	if (bstTree == 0){
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	bstTree->root = NULL;
	bstTree->display = d;
	bstTree->compare = c;

	return bstTree;
}

bstNode *insertBST(bst *bstTree, void *v){
	bstNode* NewNode = malloc(sizeof(bstNode));
	NewNode->value = v;
	NewNode->left = NULL;
	NewNode->right = NULL;
	NewNode->parent = bstTree->root;
	int stop = 0;

	if (bstTree->root == NULL){
		bstTree->root = NewNode;
		NewNode->parent = NewNode;
	}
	else{
		while (stop == 0){
			if (bstTree->compare(NewNode->value, NewNode->parent->value) == -1){
				if (NewNode->parent->left == NULL){
					NewNode->parent->left = NewNode;
					stop = 1;
				}
				else
					NewNode->parent = NewNode->parent->left;
			}
			else{
				if (NewNode->parent->right == NULL){
					NewNode->parent->right = NewNode;
					stop = 1;
				}
				else
					NewNode->parent = NewNode->parent->right;
			}
		}
	}
	return NewNode;
}
bstNode *findBSTNode(bst* bstTree, void *v){
	bstNode *node = bstTree->root;
	if (node == NULL) return NULL;
	while (bstTree->compare(v, node->value) != 0){
		if (bstTree->compare(v, node->value) == -1)
			node = node->left;
		else if (bstTree->compare(v, node->value) == 1)
			node = node->right;
		if (node == NULL)
			return NULL;
	}
	return node;

}

int findBST(bst* bstTree, void *v){
	bstNode *node = findBSTNode(bstTree, v);
	if (node == NULL) return 0;
	else return 1;
}


bstNode *swapToLeafBSTNode(bstNode *node){
	void* v = node->value;
	bstNode* p = node;
	if (p->left != NULL){
		node->value = p->left->value;
		p = p->left;
		while (p->right != NULL){
			node->value = p->right->value;
			p = p->right;
		}
	}
	else if (p->right != NULL){
		node->value = p->right->value;
		p = p->right;
		while (p->left != NULL){
			node->value = p->left->value;
			p = p->left;
		}
	}
	p->value = v;
	if (p->left != NULL || p->right != NULL)
		return swapToLeafBSTNode(p);
	else
		return p;
}

void pruneBSTNode(bst *bstTree, bstNode *node){
	if (node == bstTree->root) bstTree->root = NULL;
	if (node == node->parent->left) node->parent->left = NULL;
	if (node == node->parent->right) node->parent->right = NULL;
	if (node == node->parent) node = NULL;
//	node->parent = NULL;
}

int sizeBST(bst *bstTree){//Useless function that breaks code when implemented
	bstNode* BST = bstTree->root; //This is here so compiler doesn't complain. 
	if (BST == NULL) return 0;
return 1;
}

void statisticsBST(bst *bstTree, FILE *fp){
	queue *treeQ = newQueue(bstTree->display);
	int count = 0;
	int firstline = 1;
	enqueue(treeQ, bstTree->root);
	if (bstTree->root != NULL){
		count +=1;
		enqueue(treeQ, NULL);}
	bstNode *node;
	int line = 0;
	while (sizeQueue(treeQ)){
		node = dequeue(treeQ);
		if (node == NULL){
			line ++;
			if (sizeQueue(treeQ) > 0){
				enqueue(treeQ, NULL);
			}
		}
		else{
			if (node->left == NULL || node->right == NULL){
				if (line != 0 && firstline == 1)
					firstline = line+1;
			}
			if (node->left != NULL){
				enqueue(treeQ, node->left);
				count +=1;
			}
			if (node->right != NULL){
				enqueue(treeQ, node->right);
				count +=1;
			}
		}
	}
	fprintf(fp, "Nodes: %d\nMinimum depth: %d\nMaximum depth: %d\n",
			count, firstline, line);
	return;
}

void displayBST(FILE *file, bst *bstTree){
	queue *treeQ = newQueue(bstTree->display);
	enqueue(treeQ, bstTree->root);
	if (bstTree->root != NULL)
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
			if (node->left == NULL && node->right == NULL){
				fprintf(file," =");
			//	fprintf(file,"\"");
			}
			else
				fprintf(file," ");
			bstTree->display(file, node->value);
			fprintf(file,"(");
			bstTree->display(file, node->parent->value);
			fprintf(file,")");
			if (node == node->parent->left)
				fprintf(file,"-l");
			else if (node == node->parent->right)
				fprintf(file,"-r");
			else
				fprintf(file,"-");
			if (node->left != NULL)
				enqueue(treeQ, node->left);
			if (node->right != NULL)
				enqueue(treeQ, node->right);
		}
	}

	return;
}
