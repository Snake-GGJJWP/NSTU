#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "WashingMachine.h"

#define STRING_MAX_LEN (MODEL_MAX_LEN + 5 + 6 + 42)

#define DEFAULT_MODEL "Tesla"
#define DEFAULT_WATERCONSUME 10.0
#define DEFAULT_PRICE 1000

// Returns the number corresponding to the cumulative sum of 2^(n) where n is the number of the invalid field
// i.e it returns 0 if no fields are invalid, 2^1 + 2^2 = 6 if waterConsume_l and priceUsd fields are invalid.
// Fields go from 0 to 2 corresponding model, waterConsume_l and priceUsd respectively.
char wmIsValid(WashingMachine* wm) {
	char report = 0;

	if (strlen(wm->model) > MODEL_MAX_LEN) report += 1;
	if (wm->waterConsume_l <= 0 || wm->waterConsume_l > 100) report += 2;
	if (wm->priceUsd < 0) report += 4;

	return report;
}

// WashingMachine initialization by fields. Should be used once! Memory leaks otherwise.
// Returns the number corresponding to the cumulative sum of 2^(n) where n is the number of the invalid field
// i.e it returns 0 if no fields are invalid, 2^1 + 2^2 = 6 if waterConsume_l and priceUsd fields are invalid.
// Fields go from 0 to 2 corresponding model, waterConsume_l and priceUsd respectively. 
char wmInit(WashingMachine* wm, char* model, double waterConsume_l, double priceUsd) {
	char report = wmIsValid(&(WashingMachine){ .model = model, .waterConsume_l = waterConsume_l, .priceUsd = priceUsd });

	if (report) return report;
	
	// [ASK]: How pointers gets initialized?
	wm->model = (char*)malloc(MODEL_MAX_LEN); // do I need to allocate memory before copying?
	if (wm->model == NULL) return 1; // failure at allocation
	strcpy_s(wm->model, MODEL_MAX_LEN, model); // it's important to copy string not to lose it later

	wm->waterConsume_l = waterConsume_l;
	wm->priceUsd = priceUsd;

	return 0;
}

// WashingMachine initialization by structure. Should be used once! Memory leaks otherwise.
// Returns the number corresponding to the cumulative sum of 2^(n) where n is the number of the invalid field
// i.e it returns 0 if no fields are invalid, 2^1 + 2^2 = 6 if waterConsume_l and priceUsd fields are invalid.
// Fields go from 0 to 2 corresponding model, waterConsume_l and priceUsd respectively.
char wmCopyInit(WashingMachine* wmDest, WashingMachine* wmSrc) {
	char report = wmIsValid(wmSrc);

	if (report) return report;

	wmDest->model = (char*)malloc(MODEL_MAX_LEN); // do I need to allocate memory before copying?
	if (wmDest->model == NULL) return 1; // failure at allocation
	strcpy_s(wmDest->model, MODEL_MAX_LEN, wmSrc->model); // it's important to copy string not to lose it later

	wmDest->waterConsume_l = wmSrc->waterConsume_l;
	wmDest->priceUsd = wmSrc->priceUsd;

	return 0;
}

// Create a new Washing Machine structure. Fill in with default values.
// Return the pointer to the new structure on success, NULL on failure. 
WashingMachine* newWashingMachine() {
	WashingMachine* wm = (WashingMachine*)malloc(sizeof(WashingMachine));

	if (wm == NULL) return NULL; // failure at allocation 
	
	char report = wmInit(wm, DEFAULT_MODEL, DEFAULT_WATERCONSUME, DEFAULT_PRICE);

	if (report) return NULL;

	return wm;
}

// Free the memory taken by 'wm'
void wmDelete(WashingMachine* wm) {
	free(wm->model);
	free(wm);
}

// Get string representation of the structure.
char* wmToString(const WashingMachine* wm) {
	char* s = (char*)malloc(STRING_MAX_LEN);
	snprintf(s, STRING_MAX_LEN, "{ model: %s, waterConsume_l: %.2f L, priceUsd: $%.2f }", wm->model, wm->waterConsume_l, wm->priceUsd);
	return s;
}

// Setters 
// Return 0 on failure, 1 on success.
char wmSetModel(WashingMachine* wm, char* model) {  
	char* temp = wm->model;
	wm->model = model;

	if (wmIsValid(wm) != 0) {
		wm->model = temp;
		return 0;
	}

	wm->model = temp; // change the pointer back
	strcpy_s(wm->model, MODEL_MAX_LEN, model); // copying instead of assigning

	return 1;
}

// Return 0 on failure, 1 on success.
char wmSetWaterConsumption(WashingMachine* wm, double waterConsume_l) {
	double temp = wm->waterConsume_l;
	wm->waterConsume_l = waterConsume_l;

	if (wmIsValid(wm) != 0) {
		wm->waterConsume_l = temp;
		return 0;
	}

	return 1;
}

// Return 0 on failure, 1 on success.
char wmSetPrice(WashingMachine* wm, double priceUsd) {
	double temp = wm->priceUsd;
	wm->priceUsd = priceUsd;

	if (wmIsValid(wm) != 0) {
		wm->priceUsd = temp;
		return 0;
	}

	return 1;
}