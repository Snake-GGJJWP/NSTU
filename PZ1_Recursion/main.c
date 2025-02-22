#define _CRT_SECURE_NO_WARNINGS
#define BUF 10

#include <stdio.h>
#include <stdlib.h>
#include "printReverse.h"
#include "isNumber.h"

int main() {
	char numStr[BUF];
	int num;

	printf("Enter number you want to reverse: ");
	if (fgets(numStr, BUF, stdin) == NULL) {
		printf("\nFailure on reading!");
		return 0;
	}

	numStr[strlen(numStr) - 1] = '\0';

	if (!isNumber(numStr)) {
		printf("%s is not an int!", numStr);
		return 0;
	}
	
	num = atoi(numStr);
	printReverseNum(num);
	return 0;
}