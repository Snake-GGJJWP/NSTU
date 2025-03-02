#define INT_LEN 12

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
// Insert integer 'val' at index 'ind' in 'list'. Return 1 on success, 0 on failure
char ilistInsert(IList** list, int val, int ind) {
	IList* newNode = newIListNode(val);
	IList* nextNode = ilistGetNode(*list, ind); // nextNode at index 'ind'
	IList* prevNode = ilistGetNode(*list, ind - 1); // prevNode at index 'ind - 1'

	// if index is not valid (no neighbouring nodes and the list is not empty)
	if (*list != NULL && nextNode == NULL && prevNode == NULL) return 0;

	if (nextNode != NULL) newNode->next = nextNode;
	if (prevNode != NULL) prevNode->next = newNode;
	else *list = newNode; // if the value inserted in the head, we should change the head

	return 1;
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

// Remove node at index 'ind' from 'list'. Return 1 on success, 0 on failure 
char ilistRemove(IList** list, int ind) {
	IList* currentNode = ilistGetNode(*list, ind); // currentNode at index 'ind' 
	IList* nextNode = ilistGetNode(*list, ind + 1); // nextNode at index 'ind + 1'
	IList* prevNode = ilistGetNode(*list, ind - 1); // prevNode at index 'ind - 1'

	if (currentNode == NULL) return 0; // if the node we remove is not present, return NULL

	free(currentNode);

	// if head is removed update the pointer
	if (prevNode == NULL) {
		*list = nextNode;
		return 1;
	}
	
	prevNode->next = nextNode; // doesn't matter if nextNode is actual node or NULL
	return 1;
}

char* ilistToString(const IList* list) {
	int len = ilistLength(list);
	int maxBuffer = INT_LEN * len + 2; // INT_LEN - is a maximum length of integer, plus comma. And additional 2 bytes for '[' and ']'
	char* string = malloc(maxBuffer);
	int ind = 0;

	snprintf(string, maxBuffer, "[");
	ind++;

	for (IList* node = list; node != NULL; node = node->next) {
		char* currentNum = malloc(INT_LEN); // 12 - is a maximum length of integer, plus comma.
		if (node->next != NULL) snprintf(currentNum, INT_LEN, "%d, ", node->val);
		else snprintf(currentNum, INT_LEN, "%d", node->val);

		snprintf(string + ind, maxBuffer, "%s", currentNum);
		ind += strlen(currentNum);
	}

	snprintf(string + ind, maxBuffer, "]");
	return string;
}

void printList(const IList* list) {
	printf("[");
	for (IList* node = list; node != NULL; node = node->next) {
		if (node->next != NULL) printf("%d, ", node->val);
		else printf("%d", node->val);
	}
	printf("]\n");
}