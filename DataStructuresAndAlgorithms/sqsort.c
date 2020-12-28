#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
#include "dll.h"
#include "stack.h"
#include "queue.h"
#include "integer.h"
#include "real.h"
#include "scanner.h"
#include "comparator.h"

typedef int (*Comparator)(void* x ,void* y);
typedef void (*Printer)(FILE* f, void* v);

void displayString(FILE *fp,void *v){
	fprintf(fp, "\"%s\"", (char*)v);
	}

int main(int argc,char **argv)
{
	FILE *file = stdin;
	if (argc == 3) file = fopen(argv[2],"r");
	Comparator comp;
	Printer print;
	queue *input;

	if (strcmp(argv[1], "-v") == 0){
		printf("Carter D. Yancey\n");
		return 0;
	}
	else if (strcmp(argv[1], "-d") == 0){
		comp = intComparator;
		print = displayInteger;
		input = newQueue(print);
		int x = readInt(file);
		while (!feof(file)){
			enqueue(input, newInteger(x));
			x = readInt(file);
		}
		//enqueue(input, newInteger(x));
		displayQueue(stdout,input);
		printf("\n");
	}
	else if (strcmp(argv[1], "-r") == 0){
		comp = realComparator;
		print = displayReal;
		input = newQueue(print);
		double x = readReal(file);
		while (!feof(file)){
			enqueue(input, newReal(x));
			x = readReal(file);
		}
		displayQueue(stdout, input);
		printf("\n");
	}
	else if (strcmp(argv[1], "-s") == 0){
		comp = stringComparator;
		print = displayString;
		input = newQueue(print);
		char* x = readString(file);
		while (!feof(file)){
			enqueue(input, x);
			x = readString(file);
		}
		displayQueue(stdout, input);
		printf("\n");
	}
	else{
		printf("unknown flag '%c', valid flags are -d, -r, -s, and -v\n", argv[1][1]);
		return 0;
	}
//	printf("%d", comp(dequeue(input), dequeue(input)));
	stack *Stack = newStack(print);
	queue *output = newQueue(print);
	void *item;
	int isSorted = 0;
	int count =0;
	while (isSorted == 0){
		isSorted = 1;
		while (sizeQueue(input) >1){
			while (sizeStack(Stack) != 0 && (comp(peekStack(Stack), peekQueue(input)) == 1 || comp(peekStack(Stack), peekQueue(input)) == 0) 
			&& sizeQueue(output) != 0 && 
			(comp(getSLL(output->list, sizeQueue(output)-1), peekStack(Stack)) == 1 || comp(getSLL(output->list, sizeQueue(output)-1), peekStack(Stack)) == 0))
				enqueue(output, pop(Stack));
			item = dequeue(input);
			if (comp(item, peekQueue(input)) ==1){
				enqueue(output, item);}
			else if (comp(item, peekQueue(input)) ==0){
				enqueue(output, item);}
			else{
				push(Stack, item);
				isSorted = 0;
			}
		
		}
			while (sizeStack(Stack) != 0 && (comp(peekStack(Stack), peekQueue(input)) == 1 || comp(peekStack(Stack), peekQueue(input)) == 0) 
			&& sizeQueue(output) != 0 && 
			(comp(getSLL(output->list, sizeQueue(output)-1), peekStack(Stack)) == 1 || comp(getSLL(output->list, sizeQueue(output)-1), peekStack(Stack)) == 0))
				enqueue(output, pop(Stack));
		if (sizeQueue(input) == 1){
			item = dequeue(input);
			enqueue(output, item);
		}
	
//		if (sizeStack(Stack) == 0) isSorted = 1;
		while (sizeStack(Stack) > 0)
			enqueue(output, pop(Stack));
		if (isSorted == 0 || count == 0){
			displayQueue(stdout, output);
			printf("\n");
		
	
		input->list->head = output->list->head;
		input->list->tail = output->list->tail;
		input->list->size = output->list->size;
		output->list->head = NULL;
		output->list->tail = NULL;
		output->list->size = 0;
		}
		count +=1;
//		for (int x=0; x < sizeQueue(input)-1; x++){
//			if (comp(getSLL(input->list, x),getSLL(input->list, x+1)) ==0)
//				isSorted = 0;
//		}
	
	}
	return 0;

}
