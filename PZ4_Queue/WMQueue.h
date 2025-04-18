#pragma once
#include "WashingMachine.h"

typedef struct WMQueue {
	WashingMachine val;
	struct WMQueue* next;
	struct WMQueue* prev;
} WMQueue;

// Create new queue
WMQueue* wmqueueNew(WashingMachine* wmarr, int n);
// Remove the rightmost element from list 'q' and return it
WashingMachine wmqueuePopRight(WMQueue** q);
// Remove the leftmost element from list 'q' and return it
WashingMachine wmqueuePopLeft(WMQueue** q);
// Add the element 'val' to the rightmost position in 'q'
void wmqueueAppendRight(WMQueue** q, WashingMachine val);
// Add the element 'val' to the rightmost position in 'q'
void wmqueueAppendLeft(WMQueue** q, WashingMachine val);
// Delete queue
void wmqueueDelete(WMQueue** q);