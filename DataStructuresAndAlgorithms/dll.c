#include <stdio.h>
#include <stdlib.h>

#include "dll.h"

/*
	dll.c - a collection of routines for generic Doubly  Linked List class.

	By: Carter Yancey
	Date: 01-21-17
*/

dll *newDLL(void (*d)(FILE *, void *)){
	dll *items = malloc(sizeof(dll));
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

void insertDLL(dll *items, int index, void *value){
	dllnode *NewNode = malloc(sizeof(dllnode));
	NewNode->value = value;
	NewNode->next = items->head;
	if (index == items->size){
		NewNode->prev = items->tail;
		if (items->size == 0){
			items->head = NewNode;
			items->tail = NewNode;
			NewNode->next = NewNode;
			NewNode->prev = NewNode;
		}
		else{
			items->tail->next = NewNode;
			items->tail = NewNode;
			NewNode->next = items->head;
		}
		items->size += 1;
	}
	else{
		if (index == 0){
			NewNode->next = items->head;
			NewNode->prev = items->tail;
			items->head = NewNode;
			items->head->next->prev = NewNode;
			items->tail->next = NewNode;
		}
		else{
			while (index>1){
				NewNode->next = NewNode->next->next;
				index -= 1;
			}
			dllnode *spotNode = malloc(sizeof(dllnode));
			spotNode = NewNode->next;
			NewNode->next = NewNode->next->next;
			NewNode->prev = spotNode;
			spotNode->next = NewNode;
			NewNode->next->prev = NewNode;
		}
		items->size += 1;
	}
			
	return;
}

void *removeDLL(dll *items, int index){
	void *ReturnedValue;
	if (index == 0){
		items->size -= 1;
		ReturnedValue = items->head->value;
		items->head = items->head->next;
		items->head->prev = items->tail;
		items->tail->next = items->head;
		return ReturnedValue;
	}
	else if (index == items->size - 1){
		ReturnedValue = items->tail->value;
		items->head->prev = items->tail->prev;
		items->tail->prev->next = items->head;
		items->tail = items->tail->prev;
		items->size -= 1;
		return ReturnedValue;
	}
	else{
		dllnode *NewNode = malloc(sizeof(dllnode));
		NewNode->value = 0;
		if (index < (items->size-1)/2){
			NewNode->next = items->head;
			while (index>1){
				NewNode->next = NewNode->next->next;
				index -= 1;
			}
			ReturnedValue = NewNode->next->next->value;
			NewNode->next->next = NewNode->next->next->next;
			NewNode->next->next->prev = NewNode->next;
		}
		else{
			NewNode->prev = items->tail;
			while (index<(items->size-2)){
				NewNode->prev = NewNode->prev->prev;
				index += 1;
			}
			ReturnedValue = NewNode->prev->prev->value;
			NewNode->prev->prev = NewNode->prev->prev->prev;
			NewNode->prev->prev->next = NewNode->prev;
		}
			
		items->size -= 1;

		return ReturnedValue;
	}
	
}

void unionDLL(dll *recipient, dll *donor){
	if (donor->head == NULL) return;
	else if (recipient->head == NULL){
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		recipient->size = donor->size;
		donor->head = 0;
		donor->size = 0;
	}
	else{
		donor->head->prev = recipient->tail;
		recipient->tail->next = donor->head;
		recipient->tail = donor->tail;
		recipient->head->prev = donor->tail;
		recipient->size += donor->size;
		donor->head = 0;
		donor->size = 0;
	}
//	while(sizeSLL(donor) != 0)
//		insertSLL(recipient, sizeSLL(recipient), removeSLL(donor,0));
	return;
}

void *getDLL(dll *items, int index){
	if (index == 0){
		return items->head->value;
	}
	if (index == items->size - 1){
		return items->tail->value;
	}
	else{
		dllnode *NewNode = malloc(sizeof(dllnode));
		NewNode->value = 0;
		NewNode->next = items->head;
		while (index>1){
			NewNode->next = NewNode->next->next;
			index -= 1;
		}
		return NewNode->next->next->value;
	}
}

int sizeDLL(dll *items){
	return items->size;
}

void displayDLL(FILE *file, dll *items){
	int size = items->size;
	dllnode *Node = malloc(sizeof(dllnode));
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

void displayDLLreverse(FILE *file, dll *items){
	int size = items->size;
	dllnode *Node = malloc(sizeof(dllnode));
	Node = items->tail;
	fprintf(file, "[");
	while(size >0){
		items->display(file, Node->value);
		Node = Node->prev;
		size -= 1;
		if (size != 0) fprintf(file, ",");
	}
	fprintf(file, "]");
	return;
}
