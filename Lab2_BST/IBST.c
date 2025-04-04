#include <stdio.h>
#include <stdlib.h>

#include "IBST.h"

typedef enum Direction
{
	LEFT = 0,
	RIGHT = 1
} Direction;

static void getNodeAndParent(IBST** parent, IBST** node, Direction* direction, int val);
static void getLeafAndParentR(IBST** parent, IBST** leaf, Direction* direction, int val);
static void getLeafAndParentL(IBST** parent, IBST** leaf, Direction* direction, int val);

// Insert val into IBST. Return 1 on success, 0 on failure.
char IBSTinsert(int val, IBST** tree) {
	if (tree == NULL) return 0;
	// If NULL-tree is met
	if (*tree == NULL) {
		*tree = (IBST*)malloc(sizeof(IBST)); // create new tree
		if (*tree == NULL) return 0;

		(*tree)->left = NULL;
		(*tree)->right = NULL;
		(*tree)->value = val;
		return 1;
	}

	if ((*tree)->value == val) return 0; // guarantee uniqness

	if ((*tree)->value > val)
		return IBSTinsert(val, &(*tree)->left);
	else
		return IBSTinsert(val, &(*tree)->right);
}

// Print IBST elements in increasing order
void IBSTprintInc(IBST* tree) {
	if (tree == NULL) return;
	IBSTprintInc(tree->left);
	printf("%d ", tree->value);
	IBSTprintInc(tree->right);
}

// Print BST elements in decreasing order
void IBSTprintDec(IBST* tree) {
	if (tree == NULL) return;
	IBSTprintDec(tree->right);
	printf("%d ", tree->value);
	IBSTprintDec(tree->left);
}

// Get number of elements in BST
int IBSTsize(IBST* tree) {
	if (tree == NULL) return 0;
	return IBSTsize(tree->left) + IBSTsize(tree->right) + 1;
}

// Delete value from IBST iteratively. Return 1 on success, 0 on failure.
char IBSTremove(int val, IBST** tree) {
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
		if ((*tree)->value == val) {
			free(tree);
			return 1;
		}
		return 0;
	}
	
	IBST* parent = NULL; // node parent
	IBST* node = *tree;
	Direction direction = RIGHT; // 0 - child is left from parent, 1 - child is right from parent

	// Find subtree containing the value
	getNodeAndParent(&parent, &node, &direction, val);

	if (node == NULL) return 0; // no such node

	IBST* leaf = node;

	// Find the RIGHTMOST leaf from the LEFT side.
	if (leaf->left != NULL) {
		getLeafAndParentR(&parent, &leaf, &direction, val);
	}
	// Find the LEFTMOST leaf from the RIGHT side.
	else if (leaf->right != NULL){
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

void IBSTdelete(IBST* tree) {
	if (tree == NULL) return;
	IBSTdelete(tree->left);
	IBSTdelete(tree->right);
	free(tree);
}

// Find node with the value 'val' and its parent
static void getNodeAndParent(IBST** parent, IBST** node, Direction* direction, int val) {
	while ((*node) != NULL && (*node)->value != val) {
		*parent = *node;
		if ((*node)->value > val) {
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
static void getLeafAndParentR(IBST** parent, IBST** leaf, Direction* direction, int val) {
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
static void getLeafAndParentL(IBST** parent, IBST** leaf, Direction* direction, int val) {
	*parent = *leaf;
	*leaf = (*leaf)->right;
	*direction = RIGHT;

	while ((*leaf)->left != NULL) {
		*parent = *leaf;
		*leaf = (*leaf)->left;
		*direction = LEFT;
	}
}