#include <stdio.h>
#include <stdlib.h>

#include "sll.h"

/*
	sll.c - a collection of routines for generic Singly Linked List class.

	By: Carter Yancey
	Date: 01-17-17
*/

sll *newSLL(void (*d)(FILE *, void *)){
	sll *items = malloc(sizeof(sll));
        if (items == 0)
            {
            fprintf(stderr,"out of memory");
            exit(-1);
            }
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        return items;
        }

void insertSLL(sll *items, int index, void *value){
	sllnode *NewNode = malloc(sizeof(sllnode));
	NewNode->value = value;
	NewNode->next = items->head;
	if (index == items->size){
		NewNode->next = NULL;
		if (items->size == 0){
			items->head = NewNode;
			items->tail = NewNode;
		}
		else{
			items->tail->next = NewNode;
			items->tail = NewNode;
		}
		items->size += 1;
	}
	else{
		if (index == 0){
			NewNode->next = items->head;
			items->head = NewNode;
		}
		else{
			while (index>1){
				NewNode->next = NewNode->next->next;
				index -= 1;
			}
			sllnode *spotNode = malloc(sizeof(sllnode));
			spotNode = NewNode->next;
			NewNode->next = NewNode->next->next;
			spotNode->next = NewNode;
		}
		items->size += 1;
	}
			
	return;
}

void *removeSLL(sll *items, int index){
	void *ReturnedValue;
	if (index == 0){
		items->size -= 1;
		ReturnedValue = items->head->value;
		items->head = items->head->next;
		return ReturnedValue;
	}
	else if (index == items->size - 1){
		sllnode *NewNode = malloc(sizeof(sllnode));
		NewNode->value = 0;
		NewNode->next = items->head;
		items->size -= 1;
		ReturnedValue = items->tail->value;
		while (index > 1){
			NewNode->next = NewNode->next->next;
			index -= 1;
		}
		NewNode->next->next = 0;
		items->tail = NewNode->next;
		return ReturnedValue;
	}
	else{
		sllnode *NewNode = malloc(sizeof(sllnode));
		NewNode->value = 0;
		NewNode->next = items->head;
		while (index>1){
			NewNode->next = NewNode->next->next;
			index -= 1;
		}
		ReturnedValue = NewNode->next->next->value;
		NewNode->next->next = NewNode->next->next->next;
		items->size -= 1;

		return ReturnedValue;
	}
	
}

void unionSLL(sll *recipient, sll *donor){
	if (donor->head == NULL) return;
	else if (recipient->head == NULL){ 
		recipient->head = donor->head; 
		recipient->tail=donor->tail; 
		recipient->size=donor->size; 
		donor->head=0; 
		donor->size=0;
	}
	else{
		recipient->tail->next = donor->head;
		recipient->tail = donor->tail;
		recipient->size += donor->size;
		donor->head = 0;
		donor->size = 0;
	}
//	while(sizeSLL(donor) != 0)
//		insertSLL(recipient, sizeSLL(recipient), removeSLL(donor,0));
	return;
}

void *getSLL(sll *items, int index){
	if (index == 0){
		return items->head->value;
	}
	if (index == items->size - 1){
		return items->tail->value;
	}
	else{
		sllnode *NewNode = malloc(sizeof(sllnode));
		NewNode->value = 0;
		NewNode->next = items->head;
		while (index>1){
			NewNode->next = NewNode->next->next;
			index -= 1;
		}
		return NewNode->next->next->value;
	}
}

int sizeSLL(sll *items){
	return items->size;
}

void displaySLL(FILE *file, sll *items){
	int size = items->size;
	sllnode *Node = malloc(sizeof(sllnode));
	Node = items->head;
	fprintf(file, "[");
	while(size >0){
		items->display(file, Node->value);
		Node = Node->next;
		size -= 1;
		if (size != 0) fprintf(file, ",");
	}
	fprintf(file, "]");
	return;
}
