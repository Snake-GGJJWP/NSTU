#include <stdio.h>
#include "List.h"

int main() {
	int testArr[6] = { 1, 2, 3, 4, 5, 6 };
	IList* list = newIList(testArr, 3);
	printList(list);

	// TEST getLength
	int len = ilistLength(list);
	printf("\nlen: %d\n", len);

	// TEST getNode
	IList* node = ilistGetNode(list, 2);
	printList(node);

	// TEST getValue
	int val = ilistGetValue(list, 0);
	printf("\nvalue: %d\n", val);

	// TEST insert
	// IList* head = ilistInsert(list, 6, -1);
	// printList(head);

	// TEST remove
	IList* head = ilistRemove(list, -1);
	printList(head);

	return 0;
}