#pragma once
#include "WashingMachine.h"

// Single-binded int List structure

typedef struct WMList {
	WashingMachine val;
	struct WMList* next;
} WMList;

typedef int (*Compare) (WashingMachine*, WashingMachine*);

// Construct a single integer list node.
WMList* newWMListNode(WashingMachine val);
// Construct an integer list, containing values from the array.
WMList* newWMList(const WashingMachine* arr, int len);
// Insert integer 'val' at index 'ind' in 'list'. Return 1 on success, 0 on failure
char wmlistInsert(WMList** list, WashingMachine val, int ind);
// Get value at index 'ind' in 'list'. Return value if there's any, empty structure on failure
WashingMachine wmlistGetValue(const WMList* list, int ind);
// Get list node at index 'ind' in 'list'. Return node if there's any, NULL on failure
WMList* wmlistGetNode(const WMList* list, int ind);
// Get 'list' length. Return length on success, -1 on failure.
int wmlistLength(const WMList* list);
// Remove node at index 'ind' from 'list'. Return 1 on success, 0 on failure 
char wmlistRemoveIndex(WMList** list, int ind);
// Remove node with value 'val' from 'list'. Return 1 on success, 0 on failure 
char wmlistRemoveElement(WMList** list, WashingMachine val);
// Free memory allocated for list. Return 1 on success, 0 on failure 
char wmlistDelete(WMList* list);
// Get string representation of 'list';
char* wmlistToString(const WMList* list);
// Sort list with key. If 'key' is NULL, WM's default compare function is used.
// Return 1 on success, 0 on failure.
char wmlistSort(WMList** wmlist, Compare key);
// Insert 'val' into sorted list. The list is assumed to be sorted by the 'key'.
// If 'key' is null the list is assumed to be sorted by the WM's default compare function.
// Return 1 on success, 0 on failure.
char wmlistSortedInsert(WMList** wmlist, WashingMachine val, Compare key);