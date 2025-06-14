#include "SmartphoneList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SM_LEN 100

// Get list nextNode at index 'ind' in 'list'. Return nextNode if there's any, NULL on failure
static SMList* smlistGetNode(const SMList* list, int ind) {
	if (ind < 0) return NULL;

	SMList* node = list;
	for (int i = 0; i < ind; node = node->next) {
		if (node == NULL) return NULL;
		i++;
	}

	return node;
}

// Construct a single integer list nextNode.
SMList* newSMListNode(Smartphone val) {
	SMList* node = (SMList*)malloc(sizeof(SMList));
	node->val = val;
	node->next = NULL;
	return node;
}

// Construct an integer list, containing values from the array.
SMList* newSMList(const Smartphone* arr, int len) {
	if (len <= 0) return NULL;

	SMList* headNode = newSMListNode(arr[0]);
	SMList* prevNode = headNode;
	for (int i = 1; i < len; i++) {
		SMList* node = newSMListNode(arr[i]);
		prevNode->next = node;
		prevNode = node;
	}
	prevNode->next = NULL;
	return headNode;
}

// Insert integer 'val' at index 'ind' in 'list'. Return 1 on success, 0 on failure
char smlistInsert(SMList** list, Smartphone val, int ind) {
	SMList* newNode = newSMListNode(val);
	SMList* nextNode = smlistGetNode(*list, ind); // nextNode at index 'ind'
	SMList* prevNode = smlistGetNode(*list, ind - 1); // prevNode at index 'ind - 1'

	// if index is not valid (no neighbouring nodes and the list is not empty)
	if (*list != NULL && nextNode == NULL && prevNode == NULL) return 0;

	if (nextNode != NULL) newNode->next = nextNode;
	if (prevNode != NULL) prevNode->next = newNode;
	else *list = newNode; // if the value inserted in the head, we should change the head

	return 1;
}

// Get value at index 'ind' in 'list'. Return value if there's any, empty structure on failure
Smartphone smlistGetValue(const SMList* list, int ind) {
	SMList* node = smlistGetNode(list, ind);
	Smartphone sm;
	smInit(&sm, "UNDEFINED", 0, 0, 0, 0);

	if (node == NULL) {
		return sm;
	}

	return node->val;
}

// Get 'list' length.
int smlistLength(const SMList* list) {
	int count = 0;
	for (SMList* node = list; node != NULL; node = node->next)
		count++;
	return count;
}

// Remove node at index 'ind' from 'list'. Return 1 on success, 0 on failure 
char smlistRemoveIndex(SMList** list, int ind) {
	SMList* currentNode = smlistGetNode(*list, ind); // currentNode at index 'ind' 
	SMList* nextNode = smlistGetNode(*list, ind + 1); // nextNode at index 'ind + 1'
	SMList* prevNode = smlistGetNode(*list, ind - 1); // prevNode at index 'ind - 1'

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

char smlistDelete(SMList* list) {
	while (list != NULL) {
		SMList* next = list->next;
		free(list->val.model);
		free(list);
		list = next;
	}
}

char* smlistToString(const SMList* list) {
	int len = smlistLength(list);
	int maxBuffer = SM_LEN * len + 2; // WM_LEN - is a maximum length of integer, plus comma. And additional 2 bytes for '[' and ']'
	char* string = malloc(maxBuffer);
	int ind = 0;

	snprintf(string, maxBuffer, "[");
	ind++;

	for (SMList* node = list; node != NULL; node = node->next) {
		char* currentNum = malloc(SM_LEN);
		if (node->next != NULL) snprintf(currentNum, SM_LEN, "%s\n ", smToString(&node->val));
		else snprintf(currentNum, SM_LEN, "%s", smToString(&node->val));

		snprintf(string + ind, maxBuffer, "%s", currentNum);
		ind += strlen(currentNum);
	}

	snprintf(string + ind, maxBuffer, "]");
	return string;
}