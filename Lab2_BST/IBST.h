#pragma once

typedef struct IBST {
	int value;
	struct IBST* left; 
	struct IBST* right;
} IBST;

// Insert val into BST. Return 1 on succes, 0 on failure.
char IBSTinsert(int val, IBST** tree);

// Delete value from BST. Return 1 on success, 0 on failure.
char IBSTremove(int val, IBST** tree);

// Print BST elements in increasing order
void IBSTprintInc(IBST* tree);

// Print BST elements in decreasing order
void IBSTprintDec(IBST* tree);

// Get number of elements in BST
int IBSTsize(IBST* tree);

// Delete the whole tree
void IBSTdelete(IBST* tree);