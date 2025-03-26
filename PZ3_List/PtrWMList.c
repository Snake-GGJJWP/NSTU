#define WM_LEN (MODEL_MAX_LEN + 5 + 6 + 42 + 2) // model_string_len + waterConsume_len + price_len + signatures + comma

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "PtrWMList.h"
#include "WMCompare.h"

// ### PRIVATE FUNCTIONS ###
void static wmqsort(WashingMachine* wmarr, int l, int r, Compare key);

// Construct a single integer list nextNode.
PtrWMList* newptrWMListNode(WashingMachine* val) {
	PtrWMList* node = (PtrWMList*)malloc(sizeof(PtrWMList));
	node->val = val;
	node->next = NULL;
	return node;
}

// Construct an integer list, containing values from the array.
PtrWMList* newptrWMList(const WashingMachine** arr, int len) {
	if (len <= 0) return NULL;

	PtrWMList* headNode = newptrWMListNode(arr[0]);
	PtrWMList* prevNode = headNode;
	for (int i = 1; i < len; i++) {
		PtrWMList* node = newptrWMListNode(arr[i]);
		prevNode->next = node;
		prevNode = node;
	}
	prevNode->next = NULL;
	return headNode;
}

// Insert integer 'val' at index 'ind' in 'list'. Return 1 on success, 0 on failure
char ptrwmlistInsert(PtrWMList** list, WashingMachine* val, int ind) {
	PtrWMList* newNode = newptrWMListNode(val);
	PtrWMList* nextNode = ptrwmlistGetNode(*list, ind); // nextNode at index 'ind'
	PtrWMList* prevNode = ptrwmlistGetNode(*list, ind - 1); // prevNode at index 'ind - 1'

	// if index is not valid (no neighbouring nodes and the list is not empty)
	if (*list != NULL && nextNode == NULL && prevNode == NULL) return 0;

	if (nextNode != NULL) newNode->next = nextNode;
	if (prevNode != NULL) prevNode->next = newNode;
	else *list = newNode; // if the value inserted in the head, we should change the head

	return 1;
}

// Get value at index 'ind' in 'list'. Return value if there's any, NULL on failure
WashingMachine* ptrwmlistGetValue(const PtrWMList* list, int ind) {
	PtrWMList* node = wmlistGetNode(list, ind);

	if (node == NULL) {
		return NULL;
	}

	return node->val;
}

// Get list nextNode at index 'ind' in 'list'. Return nextNode if there's any, NULL on failure
PtrWMList* ptrwmlistGetNode(const PtrWMList* list, int ind) {
	if (ind < 0) return NULL;

	PtrWMList* node = list;
	for (int i = 0; i < ind; node = node->next) {
		if (node == NULL) return NULL;
		i++;
	}

	return node;
}

// Get 'list' length.
int ptrwmlistLength(const PtrWMList* list) {
	int count = 0;
	for (PtrWMList* node = list; node != NULL; node = node->next)
		count++;
	return count;
}

// Remove node at index 'ind' from 'list'. Return 1 on success, 0 on failure 
char ptrwmlistRemoveIndex(PtrWMList** list, int ind) {
	PtrWMList* currentNode = ptrwmlistGetNode(*list, ind); // currentNode at index 'ind' 
	PtrWMList* nextNode = ptrwmlistGetNode(*list, ind + 1); // nextNode at index 'ind + 1'
	PtrWMList* prevNode = ptrwmlistGetNode(*list, ind - 1); // prevNode at index 'ind - 1'

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

// Remove node with value 'val' from 'list'. Return 1 on success, 0 on failure 
char ptrwmlistRemoveElement(PtrWMList** list, WashingMachine* val) {
	int ind = 0;
	PtrWMList* head = *list;
	for (; head != NULL; head = head->next) {
		if (wmIsEqual(head->val, val) == 0) break;
		ind++;
	}

	// No such element
	if (head == NULL) return 0;

	return ptrwmlistRemoveIndex(list, ind);
}

// Free memory allocated for list. Return 1 on success, 0 on failure 
char ptrwmlistDelete(PtrWMList* list) {
	while (list != NULL) {
		PtrWMList* next = list->next;
		free(list);
		list = next;
	}
}

char* ptrwmlistToString(const PtrWMList* list) {
	int len = ptrwmlistLength(list);
	int maxBuffer = WM_LEN * len + 2; // WM_LEN - is a maximum length of integer, plus comma. And additional 2 bytes for '[' and ']'
	char* string = malloc(maxBuffer);
	int ind = 0;

	snprintf(string, maxBuffer, "[");
	ind++;

	for (PtrWMList* node = list; node != NULL; node = node->next) {
		char* currentNum = malloc(WM_LEN); // 12 - is a maximum length of integer, plus comma.
		if (node->next != NULL) 
			snprintf(currentNum, WM_LEN, "%s\n ", wmToString(node->val));
		else snprintf(currentNum, WM_LEN, "%s", wmToString(node->val));

		snprintf(string + ind, maxBuffer, "%s", currentNum);
		ind += strlen(currentNum);
	}

	snprintf(string + ind, maxBuffer, "]");
	return string;
}

// Sort list with key. If 'key' is NULL, WM's default compare function is used.
// Return 1 on success, 0 on failure.
// Quick sort is used.
char ptrwmlistSort(PtrWMList** wmlist, Compare key) {
	// IDEA: Convert list to array and do quicksort on array

	if (wmlist == NULL || *wmlist == NULL) return 0; // Protection from idiots

	if (key == NULL) key = wmcmp; // Default compare function

	int n = ptrwmlistLength(*wmlist);
	WashingMachine** wmarr = (WashingMachine**)calloc(n, sizeof(WashingMachine*)); // init array of WM of size N

	if (wmarr == NULL) return 0;

	// Traverse through list and fill in the array
	int i = 0;
	PtrWMList* head = *wmlist;
	while (head != NULL) {
		wmarr[i] = head->val;
		head = head->next;
		i++;
	}

	wmqsort(wmarr, 0, n - 1, key);

	// Convert it back to list
	ptrwmlistDelete(*wmlist);
	*wmlist = newptrWMList(wmarr, n);

	return 1;
}

// Insert 'val' into sorted list. The list is assumed to be sorted by the 'key'.
// If 'key' is null the list is assumed to be sorted by the WM's default compare function.
// Return 1 on success, 0 on failure.
char ptrwmlistSortedInsert(PtrWMList** wmlist, WashingMachine* val, Compare key) {
	if (wmlist == NULL || *wmlist == NULL) return 0; // Protection from idiots

	if (key == NULL) key = wmcmp; // Default compare function

	// Find index where to insert val
	PtrWMList* head = *wmlist;
	int index = 0;
	while (head != NULL) {
		if (key(&head->val, &val) < 0) break;
		index++;
		head = head->next;
	}

	ptrwmlistInsert(wmlist, val, index);
	return 1;
}

// ### PRIVATE FUNCTIONS ###
void static wmqsort(WashingMachine** wmarr, int l, int r, Compare key) {
	// Lomuto's partition
	if (l >= r) return;

	int pivot = r;

	int i = l - 1;
	for (int j = l; j < r; j++) {

		// If element at index j is less than pivot, then swap it with element at index i+1
		if (key(wmarr[j], wmarr[pivot]) > 0) {
			i++;
			WashingMachine* tmp = wmarr[j];
			wmarr[j] = wmarr[i];
			wmarr[i] = tmp;
		}
	}

	// Swap pivot and (i+1)'th element
	i++;
	WashingMachine* tmp = wmarr[pivot];
	wmarr[pivot] = wmarr[i];
	wmarr[i] = tmp;

	wmqsort(wmarr, l, i - 1, key);
	wmqsort(wmarr, i + 1, r, key);
}