#pragma once
#include "Smartphone.h"

typedef struct SMList {
	Smartphone val; // Value
	struct SMList* next; // Next node
} SMList;

// Construct a single integer list node.
SMList* newSMListNode(Smartphone val);
// Construct an integer list, containing values from the array.
SMList* newSMList(const Smartphone* arr, int len);
// Insert integer 'val' at index 'ind' in 'list'. Return 1 on success, 0 on failure
char smlistInsert(SMList** list, Smartphone val, int ind);
// Get value at index 'ind' in 'list'. Return value if there's any, empty structure on failure
Smartphone smlistGetValue(const SMList* list, int ind);
// Get 'list' length. Return length on success, -1 on failure.
int smlistLength(const SMList* list);
// Remove node at index 'ind' from 'list'. Return 1 on success, 0 on failure 
char smlistRemoveIndex(SMList** list, int ind);
// Free memory allocated for list. Return 1 on success, 0 on failure 
char smlistDelete(SMList* list);
// Get string representation of 'list';
char* smlistToString(const SMList* list);