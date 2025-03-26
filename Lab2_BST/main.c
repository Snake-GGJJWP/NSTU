#include <stdio.h>
#include <stdlib.h>

#include "BST.h"

int main() {
	BST* bst = (BST*)malloc(sizeof(BST));

	BSTinsert(1, &bst);
	BSTinsert(2, &bst);
	BSTinsert(4, &bst);
	BSTinsert(3, &bst);

	BSTprintInc(bst);

	return 0;
}