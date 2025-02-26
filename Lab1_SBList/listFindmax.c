#include "listFindmax.h"
#include <stdlib.h>

// Get address of maximum element in list of integers.
IList* getMax(const IList* list) {
	IList* maxNode = list;
	for (IList* node = list; node != NULL; node = node->next)
		if (maxNode->val < node->val) maxNode = node;
	return maxNode;
}