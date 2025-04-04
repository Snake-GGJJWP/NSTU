#pragma once

#include "WashingMachine.h"

typedef struct WMBST {
	WashingMachine value;
	struct WMBST* left;
	struct WMBST* right;
} WMBST;

// Insert val into BST. Return 1 on succes, 0 on failure.
char WMBSTinsert(WashingMachine val, WMBST** tree);

// Delete value from BST. Return 1 on success, 0 on failure.
char WMBSTremove(WashingMachine val, WMBST** tree);

// Print BST elements in increasing order
void WMBSTprintInc(WMBST* tree);

// Print BST elements in decreasing order
void WMBSTprintDec(WMBST* tree);

// Get number of elements in BST
int WMBSTsize(WMBST* tree);

// Delete the whole tree
void WMBSTdelete(WMBST* tree);