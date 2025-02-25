#include <stdio.h>
#include <stdlib.h>

#include "List.h"

// Construct a single integer list node.
IList* newIListNode(int val) {
	IList* node = (IList*)malloc(sizeof(IList));
	node->val = val;
	node->next = NULL;
	return node;
}
// Construct an integer list, containing values from the array.
IList* newIList(const int* arr, int len) {
	if (len <= 0) return NULL;

	IList* headNode = newIListNode(arr[0]);
	IList* prevNode = headNode;
	for (int i = 1; i < len; i++) {
		IList* node = newIListNode(arr[i]);
		prevNode->next = node;
		prevNode = node;
	}
	prevNode->next = NULL;
	return headNode;
}
// Insert integer 'val' at index 'ind' in 'list'. Return 0 on failure, 1 on success
char ilistInsert(IList* list, int val, int ind) {
	IList* newNode;
}
// Get value at index 'ind' in 'list'. Return value if there's any, INT_MIN on failure
int ilistGetValue(const IList* list, int ind) {}
// Get list node at index 'ind' in 'list'. Return node if there's any, NULL on failure
IList* ilistGetNode(const IList* list, int ind) {}
// Get 'list' length. Return length on success, -1 on failure.
int ilistLength(const IList* list) {}

// WIP
char* toString(const IList* list) {
	char* string = malloc(1000); // change later
	int ind = 0;

	for (IList* node = list; node != NULL; node = node->next);
}

void printList(const IList* list) {
	for (IList* node = list; node != NULL; node = node->next) {
		printf("%d ", node->val);
	}
}