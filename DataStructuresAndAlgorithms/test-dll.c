#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "integer.h"

static void showItems(dll *items)
{
		printf("The items are ");
		displayDLL(stdout,items);
		printf(".\n");
}

static void showItemsR(dll *items)
{
		printf("The items reversed are ");
		displayDLLreverse(stdout,items);
		printf(".\n");
}

int main()
{
		dll *items = newDLL(displayInteger);
		showItems(items);
		showItemsR(items);
		insertDLL(items,0,newInteger(3));                   //insert at front
		insertDLL(items,sizeDLL(items),newInteger(2));      //insert at back
		insertDLL(items,1,newInteger(1));                   //insert at middle
		showItems(items);
		showItemsR(items);
		printf("The value ");
		displayInteger(stdout,removeDLL(items,0));          //remove from front
		printf(" was removed.\n");
		showItems(items);
		showItemsR(items);
		int x = getInteger((integer *) getDLL(items,0));    //get the first item
		printf("The first item is %d.\n",x);

		//My code starts here		
		printf("\n------Now for a new dll!!------\n\n");

		dll *newItems = newDLL(displayInteger);
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems,0,newInteger(77)); printf("Added 77 to position 0\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems,0, newInteger(119)); printf("Added 119 to position 0\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems, 0, newInteger(8)); printf("Added 8 to position 0\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems, 1, newInteger(0)); printf("added 0 to position 1\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems, 2, newInteger(1)); printf("Added 1 to position 2\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems, sizeDLL(newItems), newInteger(400)); printf("Added 400 to the last position\n");
		showItems(newItems);
		showItemsR(newItems);
		removeDLL(newItems, 3); printf("Removed item from position 3\n");
		showItems(newItems);
		showItemsR(newItems);
		removeDLL(newItems, 0); printf("Removed item from position 0\n");
		showItems(newItems);
		showItemsR(newItems);
		removeDLL(newItems, sizeDLL(newItems)-1); printf("Removed item from last position\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems, sizeDLL(newItems), newInteger(500)); printf("Added 500 to last position\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems, 1, newInteger(501)); printf("Added 501 to position 1\n");
		showItems(newItems);
		showItemsR(newItems);
		x = getInteger((integer *) getDLL(newItems,0));    //get the first item
		printf("The first item is %d.\n",x);
		x = getInteger((integer *) getDLL(newItems,2));    //get the first item
		printf("The third item is %d.\n",x);
		x = getInteger((integer *) getDLL(newItems, newItems->size-1));    //get the first item
		printf("The last item is %d.\n",x);
		showItems(newItems);
		showItemsR(newItems);

		printf("\nNow to merge "); displayDLL(stdout, items); printf(" with "); displayDLL(stdout, newItems); printf("\n");
		unionDLL(items, newItems);
		showItems(items);
		showItems(newItems);
		showItemsR(items);
		showItemsR(newItems);
		printf("\nNow to merge "); displayDLL(stdout, items); printf(" with "); displayDLL(stdout, newItems); printf("\n");
		unionDLL(items, newItems);
		showItems(items);
		showItems(newItems);
		showItemsR(items);
		showItemsR(newItems);
		printf("\nNow to merge "); displayDLL(stdout, newItems); printf(" with "); displayDLL(stdout, items); printf("\n");
		unionDLL(newItems, items);
		showItems(items);
		showItems(newItems);
		showItemsR(items);
		showItemsR(newItems);

		printf("\nNow to empty the list...\n");
		while(sizeDLL(items) > 0){
				removeDLL(items, 0);
		}
		showItems(items);
		printf("...and add again\n");
		insertDLL(newItems,0,newInteger(77)); printf("Added 77 to position 0\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems,1, newInteger(119)); printf("Added 119 to position 1\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems, 2, newInteger(8)); printf("Added 8 to position 2\n");
		showItems(newItems);
		showItemsR(newItems);
		insertDLL(newItems,1, newInteger(118)); printf("Added 118 to position 1\n");
		showItems(newItems);
		showItemsR(newItems);
		printf("\n\n");
		printf("TEST #15\n");
		dll *a = newDLL(displayInteger);






		insertDLL(a,0,newInteger(86));
		insertDLL(a,1,newInteger(93));
		insertDLL(a,0,newInteger(92));
		insertDLL(a,3,newInteger(62));
		insertDLL(a,3,newInteger(59));
		insertDLL(a,0,newInteger(40));
		insertDLL(a,3,newInteger(36));
		insertDLL(a,5,newInteger(67));
		insertDLL(a,8,newInteger(30));
		insertDLL(a,5,newInteger(67));
		insertDLL(a,10,newInteger(2));
		removeDLL(a,7);
		removeDLL(a,3);
		insertDLL(a,2,newInteger(11));
		removeDLL(a,3);
		removeDLL(a,2);
		insertDLL(a,5,newInteger(37));
		insertDLL(a,0,newInteger(15));
		insertDLL(a,2,newInteger(26));
		insertDLL(a,9,newInteger(56));
		insertDLL(a,6,newInteger(70));
		insertDLL(a,13,newInteger(5));
		insertDLL(a,11,newInteger(27));
		insertDLL(a,1,newInteger(46));
		insertDLL(a,11,newInteger(57));
		removeDLL(a,14);
		removeDLL(a,14);
		removeDLL(a,14);
		insertDLL(a,5,newInteger(43));
		insertDLL(a,12,newInteger(8));
		displayDLL(stdout,a);

		printf("\n[15,46,40,26,92,43,93,67,70,67,37,62,8,57,56,27]\n");
						return 0;
}
