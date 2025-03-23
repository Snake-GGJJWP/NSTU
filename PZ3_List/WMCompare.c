#include "WMCompare.h"
#include "stdlib.h"
#include "string.h"

// Compare two washing machines. Return 0 if two objects are equal, -1 if wm1 is greater, 1 if wm2 is greater.
// If error occured returns something else
int wmcmp(const WashingMachine* wm1, const WashingMachine* wm2) {
	if (wm1 == NULL || wm2 == NULL) return -2;
	return compare(wm1, wm2);
}

// Return 0 if wm1 and wm2 are equal (by each field), other number otherwise. 
int wmIsEqual(const WashingMachine* wm1, const WashingMachine* wm2) {
	if (strcmp(wm1->model, wm2->model) == 0 &&
		wm1->waterConsume_l == wm2->waterConsume_l &&
		wm1->priceUsd == wm2->priceUsd)
		return 0;
	return -1;
}

// ### PRIVATE FUNCTIONS ###
// Default compare function
int compare(const WashingMachine* wm1, const WashingMachine* wm2) {
	if (wm1->priceUsd > wm2->priceUsd) {
		return -1;
	}
	if (wm1->priceUsd < wm2->priceUsd) {
		return 1;
	}
	return 0;
}