#pragma once
#include "WashingMachine.h"

typedef struct PtrWMQueue {
	WashingMachine* val;
	struct PtrWMQueue* next;
	struct PtrWMQueue* prev;
} PtrWMQueue;

// Create new queue
PtrWMQueue* ptrwmqueueNew(WashingMachine** wmarr, int n);
// Remove the rightmost element from list 'q' and return it
WashingMachine* ptrwmqueuePopRight(PtrWMQueue** q);
// Remove the leftmost element from list 'q' and return it
WashingMachine* ptrwmqueuePopLeft(PtrWMQueue** q);
// Add the element 'val' to the rightmost position in 'q'
void ptrwmqueueAppendRight(PtrWMQueue** q, WashingMachine* val);
// Add the element 'val' to the rightmost position in 'q'
void ptrwmqueueAppendLeft(PtrWMQueue** q, WashingMachine* val);
// Delete queue
void ptrwmqueueDelete(PtrWMQueue** q);