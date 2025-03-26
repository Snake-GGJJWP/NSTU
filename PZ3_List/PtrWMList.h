#pragma once
#include "WashingMachine.h"

// Single-binded int List structure

typedef struct PtrWMList {
	WashingMachine* val; // Value
	struct PtrWMList* next; // Next node
} PtrWMList;

typedef int (*Compare) (WashingMachine*, WashingMachine*);

// Construct a single integer list node.
PtrWMList* newptrWMListNode(WashingMachine* val);
// Construct an integer list, containing values from the array.
PtrWMList* newptrWMList(const WashingMachine** arr, int len);
// Insert integer 'val' at index 'ind' in 'list'. Return 1 on success, 0 on failure
char ptrwmlistInsert(PtrWMList** list, WashingMachine* val, int ind);
// Get value at index 'ind' in 'list'. Return value if there's any, empty structure on failure
WashingMachine* ptrwmlistGetValue(const PtrWMList* list, int ind);
// Get list node at index 'ind' in 'list'. Return node if there's any, NULL on failure
PtrWMList* ptrwmlistGetNode(const PtrWMList* list, int ind);
// Get 'list' length. Return length on success, -1 on failure.
int ptrwmlistLength(const PtrWMList* list);
// Remove node at index 'ind' from 'list'. Return 1 on success, 0 on failure 
char ptrwmlistRemoveIndex(PtrWMList** list, int ind);
// Remove node with value 'val' from 'list'. Return 1 on success, 0 on failure 
char ptrwmlistRemoveElement(PtrWMList** list, WashingMachine* val);
// Free memory allocated for list. Return 1 on success, 0 on failure 
char ptrwmlistDelete(PtrWMList* list);
// Get string representation of 'list';
char* ptrwmlistToString(const PtrWMList* list);
// Sort list with key. If 'key' is NULL, WM's default compare function is used.
// Return 1 on success, 0 on failure.
char ptrwmlistSort(PtrWMList** wmlist, Compare key);
// Insert 'val' into sorted list. The list is assumed to be sorted by the 'key'.
// If 'key' is null the list is assumed to be sorted by the WM's default compare function.
// Return 1 on success, 0 on failure.
char ptrwmlistSortedInsert(PtrWMList** wmlist, WashingMachine* val, Compare key);