#include <stdlib.h>
#include "mergeListsAtE.h"

// Insert elements from listSrc to listDest after first encounter of elemnt e in listDest
// Returns length of the listDest on success, -1 on failure 
int mergeListsAtE(IList* listDest, const IList* listSrc, int e) {
	IList* startNode = listDest;
	while (startNode != NULL && startNode->val != e) startNode = startNode->next;
	
	if (startNode == NULL) return -1;

	// Can be optimized? 
	int i = 0;
	for (IList* node = listSrc; node != NULL; node = node->next) {
		// Insert the new value right after the current node.
		// It's important that we insert values node by node,
		// so we basically copy them, and listSrc stays independent.  
		ilistInsert(&startNode, node->val, i + 1);
		i++;
	}

	return ilistLength(listDest);
}