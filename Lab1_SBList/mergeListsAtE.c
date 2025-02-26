#include <stdlib.h>
#include "mergeListsAtE.h"

// Insert elements from listSrc to listDest after first encounter of elemnt e in listDest
// Returns length of the listDest on success, -1 on failure 
int mergeListsAtE(IList* listDest, const IList* listSrc, int e) {
	IList* startNode = listDest;
	while (startNode != NULL && startNode->val != e) startNode = startNode->next;
	
	if (startNode == NULL) return -1;

	for (IList* node = listSrc; node != NULL; node = node->next) {
		ilistInsert(startNode, node->val, 1); // insert the new value right after the current node
		startNode = startNode->next;
	}

	return ilistLength(listDest);
}