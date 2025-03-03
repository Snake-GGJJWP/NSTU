#include <stdio.h>
#include "List.h"
#include "listFindmax.h"
#include "listMenu.h"
#include "mergeListsAtE.h"

int main() {
	listMenu();

	//int check, ind = 3, testArr[3] = { 1, 2, 3 };
	//IList* list = newIList(testArr, 3);
	//printList(list);

	//// TEST getLength
	//printf("\nLENGTH OF LIST %s:\n", ilistToString(list));
	//int len = ilistLength(list);
	//printf("Len: %d\n", len);

	//// TEST getNode
	//printf("\nGET NODE AT INDEX %d:\n", ind);
	//IList* node = ilistGetNode(list, ind);
	//printf("Node: %s\n", ilistToString(node));

	//// TEST getValue
	//printf("\nGET VALUE AT INDEX %d:\n", ind);
	//int val = ilistGetValue(list, ind);
	//printf("Value: %d\n", val);

	//// TEST insert
	//printf("\nINSERT 6 AT INDEX %d:\n", ind);
	//check = ilistInsert(&list, 6, ind);
	//printf("NEW LIST: %s\n", ilistToString(list));

	//// TEST list
	//printf("\nREMOVE NODE AT INDEX %d:\n", ind);
	//check = ilistRemove(&list, ind);
	//printf("NEW LIST: %s\n", ilistToString(list));

	//// TEST findMax
	//printf("\nGET MAX NODE:\n");
	//IList* maxNode = getMax(list);
	//printList(maxNode);

	//// TEST merge
	//int el = 2, newArr[2] = { 7, 8 };
	//IList* newList = newIList(newArr, 2);
	//printf("\nMERGE %s and %s at element %d:\n", ilistToString(list), ilistToString(newList), el);
	//len = mergeListsAtE(list, newList, el);
	//printf("LEN: %d\n", len);
	//printf("NEW LIST: %s\n", ilistToString(list));


	return 0;
}