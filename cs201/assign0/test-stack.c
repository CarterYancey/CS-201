#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "integer.h"
#include "dll.h"

static void showStack(stack *s)
{
		printf("The stack is ");
		displayStack(stdout,s);
		printf(".\n");
}

int main()
{
		stack *items = newStack(displayInteger);
		showStack(items);
		push(items,newInteger(3));
		push(items,newInteger(2));
		showStack(items);
		printf("The value ");
		displayInteger(stdout,pop(items));
		printf(" was popped.\n");
		showStack(items);

		//MY CODE STARTS HERE
		
		stack *items2 = newStack(displayInteger);
		showStack(items2);
		push(items2,newInteger(0));
		showStack(items2);
		push(items2,newInteger(1));
		showStack(items2);
		push(items2,newInteger(2));
		showStack(items2);
		push(items2,newInteger(3));
		showStack(items2);
		int x = getInteger((integer *) peekStack(items2));
		printf("The peeked value is: %d\n", x);
		x = getInteger((integer *) peekStack(items2));
		printf("The peeked value is: %d\n", x);
		printf("The value ");
		displayInteger(stdout,pop(items2));
		printf(" was popped.\n");
		showStack(items2);
		x = getInteger((integer *) peekStack(items2));
		printf("The peeked value is: %d\n", x);


		return 0;
}
