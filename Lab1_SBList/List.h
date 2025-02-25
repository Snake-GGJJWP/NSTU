#pragma once

// Single-binded int List structure

typedef struct IList {
	int val;
	struct IList* next;
} IList;

// Construct a single integer list node.
IList* newIListNode(int val);
// Construct an integer list, containing values from the array.
IList* newIList(const int* arr, int len);
// Insert integer 'val' at index 'ind' in 'list'. Return 0 on failure, 1 on success
char ilistInsert(IList* list, int val, int ind);
// Get value at index 'ind' in 'list'. Return value if there's any, INT_MIN on failure
int ilistGetValue(const IList* list, int ind);
// Get list node at index 'ind' in 'list'. Return node if there's any, NULL on failure
IList* ilistGetNode(const IList* list, int ind);
// Get 'list' length. Return length on success, -1 on failure.
int ilistLength(const IList* list);
// Get string representation of 'list';
char* toString(const IList* list);
// Print list
void printList(const IList* list);