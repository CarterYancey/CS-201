#include <stdio.h>
#include <stdlib.h>

#include "integer.h"
#include "sll.h"
#include "queue.h"


queue *newQueue(void (*d)(FILE *,void *)){
	queue *Queue = malloc(sizeof(queue));
	Queue->list = newSLL(d);
	return Queue;
}

void enqueue(queue *items,void *value){
	insertSLL(items->list, sizeSLL(items->list), value);
	return;
}

void *dequeue(queue *items){
	return removeSLL(items->list, 0);
}

void *peekQueue(queue *items){
	return getSLL(items->list, 0);
}

int sizeQueue(queue *items){
	return sizeSLL(items->list);
}

void displayQueue(FILE *file, queue *items){
	displaySLL(file, items->list);
	return;
}
