#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "WashingMachine.h"

#define STRING_MAX_LEN MODEL_MAX_LEN + 5 + 6 + 42

#define DEFAULT_MODEL "Tesla"
#define DEFAULT_WATERCONSUME 10.0
#define DEFAULT_PRICE 1000

// Returns the number corresponding to the cumulative sum of 2^(n) where n is the number of the invalid field
// i.e it returns 0 if no fields are invalid, 2^1 + 2^2 = 6 if waterConsume and priceUsd fields are invalid.
// Fields go from 0 to 2 corresponding model, waterConsume and priceUsd respectively.
char wmIsValid(WashingMachine* wm) {
	char report = 0;

	if (strlen(wm->model) > MODEL_MAX_LEN) report += 1;
	if (wm->waterConsume <= 0 || wm->waterConsume > 100) report += 2;
	if (wm->priceUsd < 0) report += 4;

	return report;
}

// WashingMachine initialization by fields.
// Returns the number corresponding to the cumulative sum of 2^(n) where n is the number of the invalid field
// i.e it returns 0 if no fields are invalid, 2^1 + 2^2 = 6 if waterConsume and priceUsd fields are invalid.
// Fields go from 0 to 2 corresponding model, waterConsume and priceUsd respectively. 
char wmInit(WashingMachine* wm, char* model, double waterConsume, double priceUsd) {
	char report = wmIsValid(&(WashingMachine){ .model = model, .waterConsume = waterConsume, .priceUsd = priceUsd });

	if (report) return report;

	strcpy_s(wm->model, MODEL_MAX_LEN, model); // it's important to copy string not to lose it later
	wm->waterConsume = waterConsume;
	wm->priceUsd = priceUsd;
}

// WashingMachine initialization by structure.
// Returns the number corresponding to the cumulative sum of 2^(n) where n is the number of the invalid field
// i.e it returns 0 if no fields are invalid, 2^1 + 2^2 = 6 if waterConsume and priceUsd fields are invalid.
// Fields go from 0 to 2 corresponding model, waterConsume and priceUsd respectively.
char wmCopy(WashingMachine* wmDest, WashingMachine* wmSrc) {
	char report = wmIsValid(wmSrc);

	if (report) return report;

	strcpy_s(wmDest->model, MODEL_MAX_LEN, wmSrc->model); // it's important to copy string not to lose it later
	wmDest->waterConsume = wmSrc->waterConsume;
	wmDest->priceUsd = wmSrc->priceUsd;
}

// Create a new Washing Machine structure. Fill in with default values.
// Return the pointer to the new structure on success, NULL on failure. 
WashingMachine* newWashingMachine() {
	WashingMachine* wm = (WashingMachine*)malloc(sizeof(WashingMachine));
	
	wm->model = (char*)malloc(MODEL_MAX_LEN);
	strcpy_s(wm->model, MODEL_MAX_LEN, DEFAULT_MODEL);
	wm->waterConsume = DEFAULT_WATERCONSUME;
	wm->priceUsd = DEFAULT_PRICE;
}

// Free the memory taken by 'wm'
void wmDelete(WashingMachine* wm) {
	free(wm);
}

// Get string representation of the structure.
char* wmToString(const WashingMachine* wm) {
	char* s = malloc(STRING_MAX_LEN);
	snprintf(s, STRING_MAX_LEN, "{ model: %s, waterConsume: %.2f L, priceUsd: $%.2f }", wm->model, wm->waterConsume, wm->priceUsd);
	return s;
}

// Setters. Return 0 on failure, 1 on success.
char wmSetModel(WashingMachine* wm, char* model) {  
	char* temp = wm->model;
	wm->model = model;

	if (wmIsValid(wm) != 0) {
		wm->model = temp;
		return 0;
	}

	free(temp); // avoid memory leaks
	strcpy_s(wm->model, MODEL_MAX_LEN, model); // copying instead of assigning

	return 1;
}

char wmSetWaterConsumption(WashingMachine* wm, double waterConsume) {
	double temp = wm->waterConsume;
	wm->waterConsume = waterConsume;

	if (wmIsValid(wm) != 0) {
		wm->waterConsume = temp;
		return 0;
	}

	return 1;
}

char wmSetPrice(WashingMachine* wm, double priceUsd) {
	double temp = wm->priceUsd;
	wm->priceUsd = priceUsd;

	if (wmIsValid(wm) != 0) {
		wm->priceUsd = temp;
		return 0;
	}

	return 1;
}