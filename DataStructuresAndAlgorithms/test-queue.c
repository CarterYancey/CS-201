#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "integer.h"
#include "sll.h"

static void showQueue(queue *s)
{
		printf("The queue is ");
		displayQueue(stdout,s);
		printf(".\n");
}

int main()
{
		queue *items = newQueue(displayInteger);
		showQueue(items);
		enqueue(items,newInteger(3));
		enqueue(items,newInteger(2));
		showQueue(items);
		printf("The value ");
		displayInteger(stdout,dequeue(items));
		printf(" was dequeued.\n");
		showQueue(items);

			
		//MY CODE STARTS HERE
		
		queue *items2 = newQueue(displayInteger);
		showQueue(items2);
		enqueue(items2,newInteger(0));
		showQueue(items2);
		enqueue(items2,newInteger(1));
		showQueue(items2);
		enqueue(items2,newInteger(2));
		showQueue(items2);
		enqueue(items2,newInteger(3));
		showQueue(items2);
		int x = getInteger((integer *) peekQueue(items2));
		printf("The peeked value is: %d\n", x);
		x = getInteger((integer *) peekQueue(items2));
		printf("The peeked value is: %d\n", x);
		printf("The value ");
		displayInteger(stdout,dequeue(items2));
		printf(" was dequeueped.\n");
		showQueue(items2);
		x = getInteger((integer *) peekQueue(items2));
		printf("The peeked value is: %d\n", x);
		return 0;
}
