#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__
#include "sll.h"

typedef struct queue{
	sll *list;
} queue;

queue *newQueue(void (*d)(FILE *,void *));   //constructor
void enqueue(queue *items,void *value);         //stores a generic value
void *dequeue(queue *items);                     //returns a generic value
void *peekQueue(queue *items);               //returns a generic value
int sizeQueue(queue *items);
void displayQueue(FILE *,queue *items);

#endif
