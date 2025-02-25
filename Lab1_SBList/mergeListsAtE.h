#pragma once

#include "List.h"

// Insert elements from listSrc to listDest after first encounter of elemnt e in listDest
// Returns length of the listDest on success, -1 on failure 
int mergeListsAtE(IList* listDest, const IList* listSrc, int e);