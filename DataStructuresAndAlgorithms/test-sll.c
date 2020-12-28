#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

static void showItems(sll *items)
{
		printf("The items are ");
		displaySLL(stdout,items);
		printf(".\n");
}

int main()
{
/*		sll *items = newSLL(displayInteger);
		showItems(items);
		insertSLL(items,0,newInteger(3));                   //insert at front
		insertSLL(items,sizeSLL(items),newInteger(2));      //insert at back
		insertSLL(items,1,newInteger(1));                   //insert at middle
		showItems(items);
		printf("The value ");
		displayInteger(stdout,removeSLL(items,0));          //remove from front
		printf(" was removed.\n");
		showItems(items);
		int x = getInteger((integer *) getSLL(items,0));    //get the first item
		printf("The first item is %d.\n",x);

//My code starts here		
		printf("\n------Now for a new sll!!------\n\n");

		sll *newItems = newSLL(displayInteger);
		showItems(newItems);
		insertSLL(newItems,0,newInteger(77)); printf("Added 77 to position 0\n");
		showItems(newItems);
		insertSLL(newItems,0, newInteger(119)); printf("Added 119 to position 0\n");
		showItems(newItems);
		insertSLL(newItems, 0, newInteger(8)); printf("Added 8 to position 0\n");
		showItems(newItems);
		insertSLL(newItems, 1, newInteger(0)); printf("added 0 to position 1\n");
		showItems(newItems);
		insertSLL(newItems, 2, newInteger(1)); printf("Added 1 to position 2\n");
		showItems(newItems);
		insertSLL(newItems, 3, newInteger(81)); printf("Added 81 to position 3\n");
		showItems(newItems);
		insertSLL(newItems, sizeSLL(newItems), newInteger(400)); printf("Added 400 to the last position\n");
		showItems(newItems);
		removeSLL(newItems, 3); printf("Removed item from position 3\n");
		showItems(newItems);
		removeSLL(newItems, 0); printf("Removed item from position 0\n");
		showItems(newItems);
		removeSLL(newItems, sizeSLL(newItems)-1); printf("Removed item from last position\n");
		showItems(newItems);
		insertSLL(newItems, sizeSLL(newItems), newInteger(500)); printf("Added 500 to last position\n");
		showItems(newItems);
		insertSLL(newItems, 1, newInteger(501)); printf("Added 501 to position 1\n");
		showItems(newItems);
		x = getInteger((integer *) getSLL(newItems,0));    //get the first item
		printf("The first item is %d.\n",x);
		x = getInteger((integer *) getSLL(newItems,2));    //get the first item
		printf("The third item is %d.\n",x);
		x = getInteger((integer *) getSLL(newItems, newItems->size-1));    //get the first item
		printf("The last item is %d.\n",x);
		showItems(newItems);

		printf("\nNow to merge "); displaySLL(stdout, items); printf(" with "); displaySLL(stdout, newItems); printf("\n");
		unionSLL(items, newItems);
		showItems(items);
		showItems(newItems);
		printf("\nNow to merge "); displaySLL(stdout, items); printf(" with "); displaySLL(stdout, newItems); printf("\n");
		unionSLL(items, newItems);
		showItems(items);
		showItems(newItems);
		printf("\nNow to merge "); displaySLL(stdout, newItems); printf(" with "); displaySLL(stdout, items); printf("\n");
		unionSLL(newItems, items);
		showItems(items);
		showItems(newItems);
		
		printf("\nNow to empty the list...\n");
		while(sizeSLL(items) > 0){
			removeSLL(items, 0);
		}
		showItems(items);
		printf("...and add again\n");
		insertSLL(newItems,0,newInteger(77)); printf("Added 77 to position 0\n");
		showItems(newItems);
		insertSLL(newItems,0, newInteger(119)); printf("Added 119 to position 0\n");
		showItems(newItems);
		insertSLL(newItems, 0, newInteger(8)); printf("Added 8 to position 0\n");
		showItems(newItems);
*/		printf("\n\n");
sll *a = newSLL(displayInteger);
sll *b = newSLL(displayInteger);
insertSLL(a, 0, newInteger(1));
insertSLL(a, 0, newInteger(2));
insertSLL(a, 0, newInteger(3));
insertSLL(a, 0, newInteger(4));
insertSLL(a, 0, newInteger(5));
insertSLL(b, 0, newInteger(6));
insertSLL(b, 0, newInteger(7));
insertSLL(b, 0, newInteger(8));
insertSLL(b, 0, newInteger(9));
displaySLL(stdout, a);
displaySLL(stdout, b);
unionSLL(a, b);
displaySLL(stdout, a);
displaySLL(stdout, b);
unionSLL(b, a);
displaySLL(stdout, a);
displaySLL(stdout, b);
unionSLL(a, b);
unionSLL(b, a);
unionSLL(a, b);
unionSLL(b, a);
unionSLL(a, b);
unionSLL(b, a);
unionSLL(a, b);
unionSLL(b, a);
unionSLL(a, b);
unionSLL(b, a);
displaySLL(stdout, a);
displaySLL(stdout, b);
		return 0;
}
