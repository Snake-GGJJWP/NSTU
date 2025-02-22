#include <stdio.h>
#include <string.h>
#include "printreverse.h"

static void __rec(int num);

void printReverseNum(int num) {
	int isNeg = 0;
	if (num < 0) {
		num = -num;
		isNeg = 1;
	}

	__rec(num);
	
	if (isNeg == 1) {
		printf("-");
	}
}

static void __rec(int num) {
	if (num <= 9) {
		printf("%d", num);
		return;
	}

	printf("%d", num % 10);
	__rec(num / 10);
}