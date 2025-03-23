#pragma once
#include "WashingMachine.h"

// Compare two washing machines. Return 0 if two objects are equal, -1 if wm1 is greater, 1 if wm2 is greater.
// If error occured returns something else
int wmcmp(const WashingMachine* wm1, const WashingMachine* wm2);

// Return 0 if wm1 and wm2 are equal (by each field), other number otherwise. 
int wmIsEqual(const WashingMachine* wm1, const WashingMachine* wm2);