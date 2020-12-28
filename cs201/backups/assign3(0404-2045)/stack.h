#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__
#include "dll.h"

typedef struct stack{
	dll *list;
} stack;

stack *newStack(void (*d)(FILE *,void *));   //constructor
void push(stack *items,void *value);         //stores a generic value
void *pop(stack *items);                     //returns a generic value
void *peekStack(stack *items);               //returns a generic value
int sizeStack(stack *items);
void displayStack(FILE *,stack *items);

#endif
