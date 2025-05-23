#pragma once
#include <stdlib.h>
#include "WMQueue.h"


// Create new queue
WMQueue* wmqueueNew(WashingMachine* wmarr, int n) {
	WMQueue* q = NULL;
	for (int i = 0; i < n; i++)
		wmqueueAppendRight(&q, wmarr[i]);
	return q;
}

// Remove the rightmost element from list 'q' and return it
WashingMachine wmqueuePopRight(WMQueue** q) {
	WashingMachine wm;

	// NULL pointer or empty list
	if (q == NULL || (*q) == NULL) {
		wmInit(&wm, "", 0, 0); // default object
		return wm;
	}

	// Single element in the list
	if ((*q)->next == (*q)) {
		wm = (*q)->val;
		free(*q); // delete the element
		*q = NULL;
		return wm;
	}

	// 2 and more elements
	wm = (*q)->prev->val; // save the value to return
	(*q)->prev->prev->next = (*q); // connect prelast and first elements
	WMQueue* link = (*q)->prev->prev; // save the link to the prelast element
	free((*q)->prev); // delete element
	(*q)->prev = link; // connect first and prelast elements

	return wm;
}
// Remove the leftmost element from list 'q' and return it
WashingMachine wmqueuePopLeft(WMQueue** q) {
	WashingMachine wm;

	// NULL pointer or empty list
	if (q == NULL || (*q) == NULL) {
		wmInit(&wm, "", 0, 0); // default object
		return wm;
	}

	// Single element in the list
	if ((*q)->next == (*q)) {
		wm = (*q)->val;
		free(*q); // delete the element
		*q = NULL;
		return wm;
	}

	// 2 and more elements
	wm = (*q)->val; // save the value to return
	WMQueue* toDelete = (*q); // remember the element to delete
	(*q) = toDelete->next; // second element is now the head
	(*q)->prev = toDelete->prev; // connect second and last elements
	(*q)->prev->next = (*q); // connect last and second elements
	free(toDelete); // delete element

	return wm;
}
// Add the element 'val' to the rightmost position in 'q'
void wmqueueAppendRight(WMQueue** q, WashingMachine val) {
	// NULL pointer
	if (q == NULL) return;

	WMQueue* newNode = (WMQueue*)malloc(sizeof(WMQueue));
	newNode->val = val;
	
	
	// Empty list
	if (*q == NULL) {
		newNode->next = newNode;
		newNode->prev = newNode;
		*q = newNode;
		return;
	}

	// One or more elements
	newNode->next = *q;
	newNode->prev = (*q)->prev;
	(*q)->prev->next = newNode;
	(*q)->prev = newNode;
}

// Add the element 'val' to the leftmost position in 'q'
void wmqueueAppendLeft(WMQueue** q, WashingMachine val) {
	// IT'S ABSOLUTELY THE SAME, EXCEPT WE CHANGE THE HEAD. KEKW
	wmqueueAppendRight(q, val);
	(*q) = (*q)->prev;
}


// Delete queue
void wmqueueDelete(WMQueue** q) {
	if (*q == NULL) return; // don't need to delete an empty queue

	(*q)->prev->next = NULL; // Remove cycle
	while ((*q) != NULL) {
		WMQueue* toDelete = *q;
		*q = (*q)->next;
		free(toDelete);
	}
}