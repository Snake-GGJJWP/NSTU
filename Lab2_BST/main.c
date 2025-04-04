#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "IBST.h"
#include "WMBST.h"

#define MAX_RAND 100
#define MIN_RAND 0

int main() {
	srand(time(NULL));

	IBST* bst = NULL;

	// Perfect BT
	/*IBSTinsert(8, &bst);
	IBSTinsert(4, &bst);
	IBSTinsert(12, &bst);
	IBSTinsert(2, &bst);
	IBSTinsert(6, &bst);
	IBSTinsert(10, &bst);
	IBSTinsert(14, &bst);
	IBSTinsert(1, &bst);
	IBSTinsert(3, &bst);
	IBSTinsert(5, &bst);
	IBSTinsert(7, &bst);
	IBSTinsert(9, &bst);
	IBSTinsert(11, &bst);
	IBSTinsert(13, &bst);
	IBSTinsert(15, &bst);*/

	int N = 15;
	int size = 0;
	while (size < N) {
		int val = MIN_RAND + rand()%(MAX_RAND - MIN_RAND);
		char isInserted = IBSTinsert(val, &bst);
		if (isInserted) size++;
	}

	printf("Tree. Increasing order: ");
	IBSTprintInc(bst);
	printf("\n");

	int rmVal;
	printf("Enter a number you want to remove: ");
	scanf_s("%d", &rmVal);
	IBSTremove(rmVal, &bst);

	printf("Tree. Increasing order: ");
	IBSTprintInc(bst);
	printf("\n");

	printf("Size: %d\n", IBSTsize(bst));

	IBSTdelete(bst);

	// ### PART 2 ###

	char* RANDOM_NAMES[8] = { "Tesla", "LG", "Lenovo", "Samsung", "Skynet", "Bazinga", "Aurora", "Mercedes" };
	
	WMBST* wmbst = NULL;
	size = 0;

	while (size < N) {
		WashingMachine wm;

		char* s = RANDOM_NAMES[rand() % 8];
		double price = ((MIN_RAND + rand() % (MAX_RAND - MIN_RAND)) * (MIN_RAND + rand() % (MAX_RAND - MIN_RAND))) / 10; // larger RNG
		double waterconsume_l = (rand() % 10000 / 100);
		wmInit(&wm, s, waterconsume_l, price);

		char isInserted = WMBSTinsert(wm, &wmbst);
		if (isInserted) size++;
	}

	printf("Tree: ");
	WMBSTprintInc(wmbst);
	printf("\n");

	char* model = (char*)malloc(10);
	double waterconsume_l, price;

	printf("Model: ");
	fgets(model, 10, stdin);
	int c;
	while ((c = getchar()) != '\n' && c != EOF);

	printf("Water consume: ");
	scanf_s("%lf", &waterconsume_l);
	
	printf("Price: ");
	scanf_s("%lf", &price);

	WashingMachine wmToDelete = { .model = model, .waterConsume_l = waterconsume_l, .priceUsd = price};
	WMBSTremove(wmToDelete, &wmbst);

	printf("Tree: ");
	WMBSTprintInc(wmbst);
	printf("\n");


	WMBSTdelete(wmbst);

	return 0;
}