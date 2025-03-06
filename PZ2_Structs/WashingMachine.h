#pragma once

#define MODEL_MAX_LEN 40

typedef struct WashingMachine {
	char* model; // string size must be less than MODEL_MAX_LEN
	double waterConsume_l; // can't be negative, can't go over 100
	double priceUsd; // can't be non-positive
} WashingMachine;

// Returns the number corresponding to the cumulative sum of 2^(n) where n is the number of the invalid field
// i.e it returns 0 if no fields are invalid, 2^1 + 2^2 = 6 if waterConsume_l and priceUsd fields are invalid.
// Fields go from 0 to 2 corresponding model, waterConsume_l and priceUsd respectively.
char wmIsValid(WashingMachine* wm);

// WashingMachine initialization by fields.
// Returns the number corresponding to the cumulative sum of 2^(n) where n is the number of the invalid field
// i.e it returns 0 if no fields are invalid, 2^1 + 2^2 = 6 if waterConsume_l and priceUsd fields are invalid.
// Fields go from 0 to 2 corresponding model, waterConsume_l and priceUsd respectively. 
char wmInit(WashingMachine* wm, char* model, double waterConsume_l, double priceUsd);

// Copy fields from 'wmSrc' to 'wmDest' if they're correct.
// Returns the number corresponding to the cumulative sum of 2^(n) where n is the number of the invalid field
// i.e it returns 0 if no fields are invalid, 2^1 + 2^2 = 6 if waterConsume_l and priceUsd fields are invalid.
// Fields go from 0 to 2 corresponding model, waterConsume_l and priceUsd respectively.
char wmCopyInit(WashingMachine* wmDest, WashingMachine* wmSrc);

// Create a new Washing Machine structure. Fill in with default values.
// Return the pointer to the new structure on success, NULL on failure. 
WashingMachine* newWashingMachine();

// Free the memory taken by 'wm'
void wmDelete(WashingMachine* wm);

// Get string representation of the structure.
char* wmToString(const WashingMachine* wm);

// Setters. Return 0 on failure, 1 on success.
char wmSetModel(WashingMachine* wm, char* model);
char wmSetWaterConsumption(WashingMachine* wm, double waterConsume_l);
char wmSetPrice(WashingMachine* wm, double priceUsd);

