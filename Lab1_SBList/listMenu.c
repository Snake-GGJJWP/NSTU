#define MAX_LEN 1000

#include <stdio.h>
#include "listMenu.h"
#include "List.h"
#include "listFindmax.h"
#include "mergeListsAtE.h"

typedef void (*Option) (IList**); // alias to the `option` function type

void option1(IList**);
void option2(IList**);
void option3(IList**);
void option4(IList**);
void option5(IList**);
void option6(IList**);
void option7(IList**);
void option8(IList**);
void option9(IList**);
void printOptions();

void listMenu() {
	Option options[9] = {option1, option2, option3, option4, option5, option6, option7, option8, option9};

	int op = 1;
	IList* list = NULL;
	while (op != 0) 
	{
		if (op == 0) break; // exit

		printOptions();
		if (!scanf_s("%d", &op) || op > 9 || op < 0) {
			printf("Incorrect option! Enter a number from 1 to 9!\n");
			continue;
		}
		
		printf("\n");
		
		options[op-1](&list); // call the function by its number
	}
}

void option1(IList** list) {
	*list = NULL; // clean current list first
	printf("Enter integer elements. Enter non integer, to stop:\n");
	while (1) {
		int el;
		if (!scanf_s("%d", &el)) {
			char c;
			while ((c = getchar()) != '\n' && c != EOF); // clean stdin buffer
			break;
		}
		ilistInsert(list, el, 1);

		// Since we have a double pointer, to move it to the next node we need to
		// dereference it, take the next node's pointer, get a pointer to that pointer
		// and assign it to the original double pointer. It works best if you don't think how it works.  
		list = &((*list)->next);
	}
}

void option2(IList** list) {
	printf("List length's: %d\n", ilistLength(*list));
}

void option3(IList** list) {
	int ind;

	printf("Enter index: ");
	if (!scanf_s("%d", &ind)) {
		printf("ValueError: index must be integer\n");
		return;
	}

	printf("Node at index %d is:\n%s\n", ind, ilistToString(ilistGetNode(*list, ind)));
}

void option4(IList** list) {
	int ind;

	printf("Enter index: ");
	if (!scanf_s("%d", &ind)) {
		printf("ValueError: index must be integer\n");
		return;
	}

	printf("Value at index %d is %d\n", ind, ilistGetValue(*list, ind));
}

void option5(IList** list) {
	int ind, val;
	char check;

	printf("Enter value: ");
	if (!scanf_s("%d", &val)) {
		printf("ValueError: value must be integer\n");
		return;
	}

	printf("Enter index: ");
	if (!scanf_s("%d", &ind)) {
		printf("ValueError: index must be integer\n");
		return;
	}

	check = ilistInsert(list, val, ind);
	if (!check) {
		printf("IndexError: index %d is out of range\n", ind);
		return;
	}

	printf("Inserted %d at index %d\n", val, ind);
}

void option6(IList** list) {
	int ind;
	char check;

	printf("Enter index: ");
	if (!scanf_s("%d", &ind)) {
		printf("ValueError: index must be integer\n");
		return;
	}

	check = ilistRemove(list, ind);
	if (!check) {
		printf("IndexError: index %d is out of range\n", ind);
		return;
	}

	printf("Removed element at index %d\n", ind);
}

void option7(IList** list) {
	printf("Current list: %s\n", ilistToString(*list));
}

void option8(IList** list) {
	printf("Maximum node in current list: %s\n", ilistToString(getMax(*list)));
}

void option9(IList** list) {
	int el = 0, newLen;
	IList* newList = NULL;

	printf("Enter list you want to merge into current list:\n");
	option1(&newList);
	
	printf("Enter element, where you want to start merging: ");
	if (!scanf_s("%d", &el)) {
		printf("ValueError: element must be integer\n");
		return;
	}

	newLen = mergeListsAtE(*list, newList, el);
	if (newLen == -1) {
		printf("No element %d in current list\n", el);
		return;
	}

	printf("Current list's length after merging: %d\n", newLen);
}

void printOptions() {
	printf("### MAIN LIST FUNCTIONS ###\n");
	printf("1. Create new list\n");
	printf("2. Get current list's length\n");
	printf("3. Get node at index\n");
	printf("4. Get value at index\n");
	printf("5. Insert value at index\n");
	printf("6. Remove element at index\n");
	printf("7. Print current list\n");
	printf("\n### SPECIFIC FUNCTIONS ###\n");
	printf("8. Get maximum node\n");
	printf("9. Merge two lists at element E\n");
	printf("0. Exit\n");
	printf("Enter option between (1-9): ");
}
