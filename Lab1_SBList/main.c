#include <stdio.h>
#include "List.h"

int main() {
	int testArr[5] = { 1, 2, 3, 4, 5 };
	IList* list = newIList(testArr, 6);
	printList(list);
	return 0;
}