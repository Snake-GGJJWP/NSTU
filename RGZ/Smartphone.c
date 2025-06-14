#include "Smartphone.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_MODEL "Samsung Galaxy A5"
#define DEFAULT_COLOR RED
#define DEFAULT_YEAR 2016
#define DEFAULT_SIZE 6.2
#define DEFAULT_PRICE 100

#define STRING_MAX_LEN 100

static const char* ColorStrings[] = {
	"Blue", "Red", "Green", "White", "Black", "Yellow", "Pink", "Bronze", "Silver", "Gold"
};

char smIsValid(Smartphone* sm) {
	char report = 0;

	time_t t = time(NULL);
	struct tm* time_info = localtime(&t);
	int year = time_info->tm_year + 1900;

	if (strlen(sm->model) > MODEL_MAX_LEN) report += 1;
	if (sm->color < 0 || sm->color > 9) report += 2;
	if (sm->year <= 0 || sm->year > year) report += 4;
	if (sm->size <= 0) report += 8;
	if (sm->priceUsd < 0) report += 16;

	return report;
}

// Smaprtphones initialization by fields.
char smInit(Smartphone* sm, char* model, COLOR color, short year, double size, double priceUsd) {
	if (sm == NULL) {
		return 1;
	}
	
	char report = smIsValid(&(Smartphone) { .model = model, .color = color, .year = year, .size = size, .priceUsd = priceUsd });

	// Model field
	sm->model = (char*)malloc(MODEL_MAX_LEN);
	if (sm->model == NULL) return 1;
	if (report & 1) {
		strcpy_s(sm->model, MODEL_MAX_LEN, DEFAULT_MODEL);
	}
	else {
		strcpy_s(sm->model, MODEL_MAX_LEN, model);
	}

	// Color field
	sm->color = (report & 2) ? DEFAULT_COLOR : color;
	sm->year = (report & 4) ? DEFAULT_YEAR : year;
	sm->size = (report & 8) ? DEFAULT_SIZE : size;
	sm->priceUsd = (report & 16) ? DEFAULT_PRICE : priceUsd;

	return 0;
}

// Free the memory taken by 'sm'
void smDelete(Smartphone* sm) {
	free(sm->model);
}

// Get string representation of the structure.
char* smToString(const Smartphone* sm) {
	char* s = (char*)malloc(STRING_MAX_LEN);
	snprintf(s, STRING_MAX_LEN, "{ \nModel: %s, \nColor: %s, \nRelease year: %d, \nDisplay size: %.1f'', \nPrice: $%.2f  }", 
		sm->model, ColorStrings[sm->color], sm->year, sm->size, sm->priceUsd);
	return s;
}

// Compare two washing machines. Return 0 if two objects are equal, -1 if sm1 is greater, 1 if sm2 is greater.
// If error occured returns something else
int smcmp(const Smartphone* sm1, const Smartphone* sm2) {
	if (sm1 == NULL || sm2 == NULL) return -2;
	return compare(sm1, sm2);
}

// Return 0 if sm1 and sm2 are equal (by each field), other number otherwise. 
int smIsEqual(const Smartphone* sm1, const Smartphone* sm2) {
	if (strcmp(sm1->model, sm2->model) == 0 &&
		sm1->color == sm2->color &&
		sm1->size == sm2->size &&
		sm1->year == sm2->year &&
		sm1->priceUsd == sm2->priceUsd)
		return 0;
	return -1;
}

static int compare(const Smartphone* sm1, const Smartphone* sm2) {
	if (sm1->priceUsd > sm2->priceUsd) {
		return -1;
	}
	if (sm1->priceUsd < sm2->priceUsd) {
		return 1;
	}
	return 0;
}