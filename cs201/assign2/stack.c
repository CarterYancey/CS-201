#include <stdio.h>
#include <stdlib.h>

#include "integer.h"
#include "dll.h"
#include "stack.h"


stack *newStack(void (*d)(FILE *,void *)){
	stack *Stack = malloc(sizeof(stack));
	Stack->list = newDLL(d);
	return Stack;
}

void push(stack *items,void *value){
	insertDLL(items->list, 0, value);
	return;
}

void *pop(stack *items){
	return removeDLL(items->list, 0);
}

void *peekStack(stack *items){
	return getDLL(items->list, 0);
}

int sizeStack(stack *items){
	return sizeDLL(items->list);
}

void displayStack(FILE *file, stack *items){
	displayDLL(file, items->list);
	return;
}
