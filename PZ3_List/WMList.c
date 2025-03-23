#define WM_LEN (MODEL_MAX_LEN + 5 + 6 + 42 + 2) // model_string_len + waterConsume_len + price_len + signatures + comma

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "WMList.h"
#include "WMCompare.h"

// ### PRIVATE FUNCTIONS ###
void static wmqsort(WashingMachine* wmarr, int l, int r, Compare key);

// Construct a single integer list nextNode.
WMList* newWMListNode(WashingMachine val) {
	WMList* node = (WMList*)malloc(sizeof(WMList));
	node->val = val;
	node->next = NULL;
	return node;
}

// Construct an integer list, containing values from the array.
WMList* newWMList(const WashingMachine* arr, int len) {
	if (len <= 0) return NULL;

	WMList* headNode = newWMListNode(arr[0]);
	WMList* prevNode = headNode;
	for (int i = 1; i < len; i++) {
		WMList* node = newWMListNode(arr[i]);
		prevNode->next = node;
		prevNode = node;
	}
	prevNode->next = NULL;
	return headNode;
}

// Insert integer 'val' at index 'ind' in 'list'. Return 1 on success, 0 on failure
char wmlistInsert(WMList** list, WashingMachine val, int ind) {
	WMList* newNode = newWMListNode(val);
	WMList* nextNode = wmlistGetNode(*list, ind); // nextNode at index 'ind'
	WMList* prevNode = wmlistGetNode(*list, ind - 1); // prevNode at index 'ind - 1'

	// if index is not valid (no neighbouring nodes and the list is not empty)
	if (*list != NULL && nextNode == NULL && prevNode == NULL) return 0;

	if (nextNode != NULL) newNode->next = nextNode;
	if (prevNode != NULL) prevNode->next = newNode;
	else *list = newNode; // if the value inserted in the head, we should change the head

	return 1;
}

// Get value at index 'ind' in 'list'. Return value if there's any, empty structure on failure
WashingMachine wmlistGetValue(const WMList* list, int ind) {
	WMList* node = wmlistGetNode(list, ind);
	WashingMachine wm;
	wmInit(&wm, "", 0, 0);

	if (node == NULL) {
		return wm;
	}

	return node->val;
}

// Get list nextNode at index 'ind' in 'list'. Return nextNode if there's any, NULL on failure
WMList* wmlistGetNode(const WMList* list, int ind) {
	if (ind < 0) return NULL;

	WMList* node = list;
	for (int i = 0; i < ind; node = node->next) {
		if (node == NULL) return NULL;
		i++;
	}

	return node;
}

// Get 'list' length.
int wmlistLength(const WMList* list) {
	int count = 0;
	for (WMList* node = list; node != NULL; node = node->next)
		count++;
	return count;
}

// Remove node at index 'ind' from 'list'. Return 1 on success, 0 on failure 
char wmlistRemove(WMList** list, int ind) {
	WMList* currentNode = wmlistGetNode(*list, ind); // currentNode at index 'ind' 
	WMList* nextNode = wmlistGetNode(*list, ind + 1); // nextNode at index 'ind + 1'
	WMList* prevNode = wmlistGetNode(*list, ind - 1); // prevNode at index 'ind - 1'

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

// Free memory allocated for list. Return 1 on success, 0 on failure 
char wmlistDelete(WMList* list) {
	while (list != NULL) {
		WMList* next = list->next;
		free(list);
		list = next;
	}
}

char* wmlistToString(const WMList* list) {
	int len = wmlistLength(list);
	int maxBuffer = WM_LEN * len + 2; // WM_LEN - is a maximum length of integer, plus comma. And additional 2 bytes for '[' and ']'
	char* string = malloc(maxBuffer);
	int ind = 0;

	snprintf(string, maxBuffer, "[");
	ind++;

	for (WMList* node = list; node != NULL; node = node->next) {
		char* currentNum = malloc(WM_LEN); // 12 - is a maximum length of integer, plus comma.
		if (node->next != NULL) snprintf(currentNum, WM_LEN, "%s, ", wmToString(&node->val));
		else snprintf(currentNum, WM_LEN, "%s", wmToString(&node->val));

		snprintf(string + ind, maxBuffer, "%s", currentNum);
		ind += strlen(currentNum);
	}

	snprintf(string + ind, maxBuffer, "]");
	return string;
}

// Sort list with key. If 'key' is NULL, WM's default compare function is used.
// Return 1 on success, 0 on failure.
// Quick sort is used.
char wmlistSort(WMList** wmlist, Compare key) {
	// IDEA: Convert list to array and do quicksort on array

	if (wmlist == NULL || *wmlist == NULL) return 0; // Protection from idiots

	if (key == NULL) key = wmcmp; // Default compare function
	
	int n = wmlistLength(*wmlist);
	WashingMachine* wmarr = (WashingMachine*)calloc(n, sizeof(WashingMachine)); // init array of WM of size N

	if (wmarr == NULL) return 0;

	// Traverse through list and fill in the array
	int i = 0;
	WMList* head = *wmlist;
	while (head != NULL) {
		wmarr[i] = head->val;
		head = head->next;
		i++;
	}

	wmqsort(wmarr, 0, n - 1, key);

	// Convert it back to list
	wmlistDelete(*wmlist);
	*wmlist = newWMList(wmarr, n);

	return 1;
}

// Insert 'val' into sorted list. The list is assumed to be sorted by the 'key'.
// If 'key' is null the list is assumed to be sorted by the WM's default compare function.
// Return 1 on success, 0 on failure.
char wmlistSortedInsert(WMList** wmlist, WashingMachine val, Compare key) {
	if (wmlist == NULL || *wmlist == NULL) return 0; // Protection from idiots

	if (key == NULL) key = wmcmp; // Default compare function

	// Find index where to insert val
	WMList* head = *wmlist;
	int index = 0;
	while (head != NULL) {
		if (key(&head->val, &val) < 0) break;
		index++;
		head = head->next;
	}
	
	wmlistInsert(wmlist, val, index);
	return 1;
}

// ### PRIVATE FUNCTIONS ###
void static wmqsort(WashingMachine* wmarr, int l, int r, Compare key) {
	// Lomuto's partition
	if (l >= r) return;

	int pivot = r;

	int i = l - 1;
	for (int j = l; j < r; j++) {
		
		// If element at index j is less than pivot, then swap it with element at index i+1
		if (key(&wmarr[j], &wmarr[pivot]) > 0) {
			i++;
			WashingMachine tmp = wmarr[j];
			wmarr[j] = wmarr[i];
			wmarr[i] = tmp;
		}
	}

	// Swap pivot and (i+1)'th element
	i++;
	WashingMachine tmp = wmarr[pivot];
	wmarr[pivot] = wmarr[i];
	wmarr[i] = tmp;

	wmqsort(wmarr, l, i - 1, key);
	wmqsort(wmarr, i + 1, r, key);
}