#pragma once

typedef struct BST {
	int value;
	struct BST* left, *right;
} BST;

// Insert val into BST
void BSTinsert(int val, BST** q);

// Print BST elements in increasing order
void BSTprintInc(BST* p);

// Delete value from BST. Return 1 on success, 0 on failure.
int BSTdelete(int val, BST** node);