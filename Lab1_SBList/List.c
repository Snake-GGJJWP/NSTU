#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "List.h"

// Construct a single integer list nextNode.
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
IList* ilistInsert(IList* list, int val, int ind) {
	IList* newNode = newIListNode(val);
	IList* nextNode = ilistGetNode(list, ind); // nextNode at index 'ind'
	IList* prevNode = ilistGetNode(list, ind - 1); // prevNode at index 'ind - 1'

	if (nextNode == NULL && prevNode == NULL) return NULL;

	if (nextNode != NULL) newNode->next = nextNode;
	if (prevNode != NULL) prevNode->next = newNode;
	else return newNode; // if the value inserted in the head, we should change the head

	return list;
}
// Get value at index 'ind' in 'list'. Return value if there's any, INT_MIN on failure
int ilistGetValue(const IList* list, int ind) {
	IList* node = ilistGetNode(list, ind);

	if (node == NULL) return INT_MIN;

	return node->val;
}
// Get list nextNode at index 'ind' in 'list'. Return nextNode if there's any, NULL on failure
IList* ilistGetNode(const IList* list, int ind) {
	if (ind < 0) return NULL;

	IList* node = list;
	for (int i = 0; i < ind; node = node->next) {
		if (node == NULL) return NULL;
		i++;
	}

	return node;
}
// Get 'list' length.
int ilistLength(const IList* list) {
	int count = 0;
	for (IList* node = list; node != NULL; node = node->next)
		count++;
	return count;
}

// Remove node at index 'ind' from 'list'. Return 0 on failure, 1 on success
IList* ilistRemove(IList* list, int ind) {
	IList* nextNode = ilistGetNode(list, ind + 1); // nextNode at index 'ind + 1'
	IList* prevNode = ilistGetNode(list, ind - 1); // prevNode at index 'ind - 1'

	if (ilistGetNode(list, ind) == NULL) return NULL; // if the node we remove is not present, return NULL
	if (prevNode == NULL) return nextNode; // if head is removed return the new head
	
	prevNode->next = nextNode; // doesn't matter if nextNode is actual node or NULL
	return list;
}

// WIP
char* toString(const IList* list) {
	char* string = malloc(1000); // change later
	int ind = 0;

	for (IList* node = list; node != NULL; node = node->next);
}

void printList(const IList* list) {
	printf("[");
	for (IList* node = list; node != NULL; node = node->next) {
		if (node->next != NULL) printf("%d, ", node->val);
		else printf("%d", node->val);
	}
	printf("]\n");
}