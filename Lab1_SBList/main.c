#include <stdio.h>
#include "List.h"
#include "listFindmax.h"
#include "mergeListsAtE.h"

int main() {
	int testArr[6] = { 1, 2, 3, 4, 5, 6 };
	IList* list = newIList(testArr, 3);
	printList(list);

	// TEST getLength
	printf("LIST LENGTH:\n");
	int len = ilistLength(list);
	printf("\nlen: %d\n", len);

	// TEST getNode
	printf("GET NODE AT INDEX 2:\n");
	IList* node = ilistGetNode(list, 2);
	printList(node);

	// TEST getValue
	printf("GET VALUE AT INDEX 2:\n");
	int val = ilistGetValue(list, 0);
	printf("\nvalue: %d\n", val);

	// TEST insert
	printf("INSERT 6 AT INDEX 1:\n");
	list = ilistInsert(list, 6, 1);
	printList(list);

	// TEST list
	printf("REMOVE NODE AT INDEX 1:\n");
	list = ilistRemove(list, 1);
	printList(list);

	// TEST findMax
	printf("GET MAX NODE:\n");
	IList* maxNode = getMax(list);
	printList(maxNode);

	// TEST merge
	printf("MERGE:\n");
	int newArr[4] = { 6, 7, 8, 9 };
	IList* newList = newIList(newArr, 4);
	int check = mergeListsAtE(list, newList, 2);
	printf("%d\n", check);
	printList(list);

	// TEST toString
	printf("TOSTRING:\n");
	printf("%s", ilistToString(list));


	return 0;
}