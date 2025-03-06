#include <stdio.h>
#include "WashingMachine.h"

void checkInit(char report, char* name, char* model, double waterConsume, double priceUsd);

int main() {
	WashingMachine wm1, wm2; // exist in stack
	WashingMachine* wmDin1, *wmDin2; // exist in heap
	char report;

	char* model1 = "Midea", * model2 = "Hisense";
	double water1 = 9.0, water2 = 9.8;
	double price1 = 339.99, price2 = 479.99;

	report = wmInit(&wm1, model1, water1, price1);
	checkInit(report, "wm1", model1, water1, price1);
	if (report) return 0;

	report = wmInit(&wm2, model2, water2, price2);
	checkInit(report, "wm2", model2, water2, price2);
	if (report) return 0;

	printf("STACK:\n");
	printf("Washing machine 1: %s\n", wmToString(&wm1));
	printf("Washing machine 2: %s\n\n", wmToString(&wm2));

	report = wmCopyInit(&wm2, &wm1); // copying shouldn't create a 'link' between structures
	checkInit(report, "wm2", wm1.model, wm1.waterConsume_l, wm1.priceUsd);
	if (report) return 0;

	{
		int price = 400;
		if (!wmSetPrice(&wm1, price)) { // so if we change the field in the first wm, it shouldn't carry over to the second one
			printf("[ERROR]: Couldn't set wm1->priceUsd with value %d\n", price);
			return 0;
		}
	}

	printf("COPIED wm1 TO wm2 AND CHANGED wm1->price:\n");
	printf("Washing machine 1: %s\n", wmToString(&wm1));
	printf("Washing machine 2: %s\n\n", wmToString(&wm2));

	wmDin1 = newWashingMachine();
	if (wmDin1 == NULL) {
		printf("[ERROR]: Failure when creating wmDin1. Possibly failure at memory allocation.\n");
		return 0;
	}

	wmDin2 = newWashingMachine();
	if (wmDin2 == NULL) {
		printf("[ERROR]: Failure when creating wmDin2. Possibly failure at memory allocation.\n");
		return 0;
	}

	report = wmInit(wmDin1, model1, water1, price1); // basic constructor
	checkInit(report, "wmDin1", model1, water1, price1);
	if (report) return 0;

	// Testing setters
	{
		char* model = "LG";
		double water = 8.9;
		double price = 299.99;
		if (!wmSetModel(wmDin2, model)) {
			printf("[ERROR]: Couldn't set wmDin2->model with value %s\n", model);
			return 0;
		}
		if (!wmSetWaterConsumption(wmDin2, water)) {
			printf("[ERROR]: Couldn't set wmDin2->waterConsume with value %.2f\n", water);
			return 0;
		}
		if (!wmSetPrice(wmDin2, price)) {
			printf("[ERROR]: Couldn't set wmDin2->priceUsd with value %.2f\n", price);
			return 0;
		}
	}

	printf("HEAP:\n");
	printf("Washing machine 1: %s\n", wmToString(wmDin1));
	printf("Washing machine 2: %s\n\n", wmToString(wmDin2));

	report = wmCopyInit(wmDin2, wmDin1); // Copying shouldn't create a 'link' between structures
	checkInit(report, "wmDin2", wmDin1->model, wmDin1->waterConsume_l, wmDin1->priceUsd);
	if (report) return 0;

	{
		int price = 500;
		if (!wmSetPrice(wmDin1, price)) { // so if we change the field in the first wm, it shouldn't carry over to the second one
			printf("[ERROR]: Couldn't set wmDin2->priceUsd with value %d\n", price);
			return 0;
		}
	}

	printf("COPIED wmDin1 TO wmDin2 AND CHANGED wmDin1->price:\n");
	printf("Washing machine 1: %s\n", wmToString(wmDin1));
	printf("Washing machine 2: %s\n", wmToString(wmDin2));

	wmDelete(wmDin1);
	wmDelete(wmDin2);
	

	return 0;
}

void checkInit(char report, char* name, char* model, double waterConsume, double priceUsd) {
	if (report & 1) printf("[ERROR]: Couldn't initialize %s->model field. Possibly invalid initializing value: %s.\n", name, model);
	if (report & 2) printf("[ERROR]: Couldn't initialize %s->waterConsume field. Possibly invalid initializing value: %.2f.\n", name, waterConsume);
	if (report & 4) printf("[ERROR]: Couldn't initialize %s->priceUsd field. Possibly invalid initializing value: %.2f.\n", name, priceUsd);
}