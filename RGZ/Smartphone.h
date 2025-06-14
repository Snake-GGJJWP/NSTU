#pragma once

#define MODEL_MAX_LEN 40

typedef enum COLOR {
	BLUE, RED, GREEN, WHITE, BLACK, YELLOW, PINK, BRONZE, SILVER, GOLD
} COLOR;

typedef struct Smartphone {
	char* model; // string size must be less than MODEL_MAX_LEN
	COLOR color;
	short year; // Can't be negative and bigger than current year
	double size; // display size in inches. Can't be negative
	double priceUsd; // can't be non-positive
} Smartphone;

char smIsValid(Smartphone* sm);

// Smaprtphones initialization by fields.
char smInit(Smartphone* sm, char* model, COLOR color, short year, double size, double priceUsd);

// Free the memory taken by 'wm'
void smDelete(Smartphone* sm);

// Get string representation of the structure.
char* smToString(const Smartphone* sm);

// Compare two washing machines. Return 0 if two objects are equal, -1 if wm1 is greater, 1 if wm2 is greater.
// If error occured returns something else
int smcmp(const Smartphone* sm1, const Smartphone* sm2);

// Return 0 if wm1 and wm2 are equal (by each field), other number otherwise. 
int smIsEqual(const Smartphone* sm1, const Smartphone* sm2);