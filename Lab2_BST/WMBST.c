#include <stdio.h>
#include <stdlib.h>

#include "WMBST.h"
#include "WMCompare.h"


typedef enum Direction
{
	LEFT = 0,
	RIGHT = 1
} Direction;

static void getNodeAndParent(WMBST** parent, WMBST** node, Direction* direction, WashingMachine val);
static void getLeafAndParentR(WMBST** parent, WMBST** leaf, Direction* direction, WashingMachine val);
static void getLeafAndParentL(WMBST** parent, WMBST** leaf, Direction* direction, WashingMachine val);

// Insert val into WMBST. Return 1 on success, 0 on failure.
char WMBSTinsert(WashingMachine val, WMBST** tree) {
	if (tree == NULL) return 0;
	// If NULL-tree is met
	if (*tree == NULL) {
		*tree = (WMBST*)malloc(sizeof(WMBST)); // create new tree
		if (*tree == NULL) return 0;

		(*tree)->left = NULL;
		(*tree)->right = NULL;
		(*tree)->value = val;
		return 1;
	}

	if (wmIsEqual(&(*tree)->value, &val) == 0) return 0; // guarantee uniqness

	if (wmcmp(&(*tree)->value, &val) == -1)
		return WMBSTinsert(val, &(*tree)->left);
	else
		return WMBSTinsert(val, &(*tree)->right);
}

// Print WMBST elements in increasing order
void WMBSTprintInc(WMBST* tree) {
	if (tree == NULL) return;
	WMBSTprintInc(tree->left);
	printf("%s\n", wmToString(&tree->value));
	WMBSTprintInc(tree->right);
}

// Print BST elements in decreasing order
void WMBSTprintDec(WMBST* tree) {
	if (tree == NULL) return;
	WMBSTprintDec(tree->right);
	printf("%s\n", wmToString(&tree->value));
	WMBSTprintDec(tree->left);
}

// Get number of elements in BST
int WMBSTsize(WMBST* tree) {
	if (tree == NULL) return 0;
	return WMBSTsize(tree->left) + WMBSTsize(tree->right) + 1;
}

// Delete value from WMBST iteratively. Return 1 on success, 0 on failure.
char WMBSTremove(WashingMachine val, WMBST** tree) {
	// Recursion is beautiful, but iterative is more solid.
	// IDEA:
	// 1. Find god damn subtree containing the value (Call it Sanya)
	// 2. Find god damn left-most or right-most element in the right or left subtrees (call it Jeff)
	// 3. Swap the values between Sanya and Jeff
	// 4. Delete Jeff

	// Fool protection
	if (tree == NULL || *tree == NULL) return 0;

	// Case, where the tree is a single node
	if ((*tree)->left == NULL && (*tree)->right == NULL) {
		if (wmIsEqual(&(*tree)->value, &val) == 0) {
			free(tree);
			return 1;
		}
		return 0;
	}

	WMBST* parent = NULL; // node parent
	WMBST* node = *tree;
	Direction direction = RIGHT; // 0 - child is left from parent, 1 - child is right from parent

	// Find subtree containing the value
	getNodeAndParent(&parent, &node, &direction, val);

	if (node == NULL) return 0; // no such node

	WMBST* leaf = node;

	// Find the RIGHTMOST leaf from the LEFT side.
	if (leaf->left != NULL) {
		getLeafAndParentR(&parent, &leaf, &direction, val);
	}
	// Find the LEFTMOST leaf from the RIGHT side.
	else if (leaf->right != NULL) {
		getLeafAndParentL(&parent, &leaf, &direction, val);
	}

	// Swap values
	node->value = leaf->value;

	// Delete leaf
	free(leaf);

	// Delete link if there's any
	if (parent == NULL) return 1; // no link
	if (direction == LEFT) parent->left = NULL; // left link
	else parent->right = NULL; // right link

	return 1;
}

void WMBSTdelete(WMBST* tree) {
	if (tree == NULL) return;
	WMBSTdelete(tree->left);
	WMBSTdelete(tree->right);
	free(tree);
}

// Find node with the value 'val' and its parent
static void getNodeAndParent(WMBST** parent, WMBST** node, Direction* direction, WashingMachine val) {
	while ((*node) != NULL && wmIsEqual(&(*node)->value, &val) != 0) {
		*parent = *node;
		if (wmcmp(&(*node)->value, &val) == -1) {
			*node = (*node)->left;
			*direction = LEFT;
		}
		else {
			*node = (*node)->right;
			*direction = RIGHT;
		}
	}
}

// Find the RIGHTMOST leaf from the LEFT side and its parent
static void getLeafAndParentR(WMBST** parent, WMBST** leaf, Direction* direction, WashingMachine val) {
	*parent = *leaf;
	*leaf = (*leaf)->left;
	*direction = LEFT;

	while ((*leaf)->right != NULL) {
		*parent = *leaf;
		*leaf = (*leaf)->right;
		*direction = RIGHT;
	}
}

// Find the LEFTMOST leaf from the RIGHT side and its parent
static void getLeafAndParentL(WMBST** parent, WMBST** leaf, Direction* direction, WashingMachine val) {
	*parent = *leaf;
	*leaf = (*leaf)->right;
	*direction = RIGHT;

	while ((*leaf)->left != NULL) {
		*parent = *leaf;
		*leaf = (*leaf)->left;
		*direction = LEFT;
	}
}