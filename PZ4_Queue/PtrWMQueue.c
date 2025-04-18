#pragma once
#include <stdlib.h>
#include "PtrWMQueue.h"


// Create new queue
PtrWMQueue* ptrwmqueueNew(WashingMachine** wmarr, int n) {
	PtrWMQueue* q = NULL;
	for (int i = 0; i < n; i++)
		ptrwmqueueAppendRight(&q, wmarr[i]);
	return q;
}

// Remove the rightmost element from list 'q' and return it
WashingMachine* ptrwmqueuePopRight(PtrWMQueue** q) {
	WashingMachine* wm;

	// NULL pointer or empty list
	if (q == NULL || (*q) == NULL)
		return NULL;

	// Single element in the list
	if ((*q)->next == (*q)) {
		wm = (*q)->val;
		free(*q); // delete the element
		(*q) = NULL;
		return wm;
	}

	// 2 and more elements
	wm = (*q)->prev->val; // save the value to return
	(*q)->prev->prev->next = (*q); // connect prelast and first elements
	PtrWMQueue* link = (*q)->prev->prev; // save the link to the prelast element
	free((*q)->prev); // delete element
	(*q)->prev = link; // connect first and prelast elements

	return wm;
}
// Remove the leftmost element from list 'q' and return it
WashingMachine* ptrwmqueuePopLeft(PtrWMQueue** q) {
	WashingMachine* wm;

	// NULL pointer or empty list
	if (q == NULL || (*q) == NULL)
		return NULL;

	// Single element in the list
	if ((*q)->next == (*q)) {
		wm = (*q)->val;
		free(*q); // delete the element
		(*q) = NULL;
		return wm;
	}

	// 2 and more elements
	wm = (*q)->val; // save the value to return
	PtrWMQueue* toDelete = (*q); // remember the element to delete
	(*q) = toDelete->next; // second element is now the head
	(*q)->prev = toDelete->prev; // connect second and last elements
	(*q)->prev->next = (*q); // connect last and second elements
	free(toDelete); // delete element

	return wm;
}
// Add the element 'val' to the rightmost position in 'q'
void ptrwmqueueAppendRight(PtrWMQueue** q, WashingMachine* val) {
	// NULL pointer
	if (q == NULL) return;

	PtrWMQueue* newNode = (PtrWMQueue*)malloc(sizeof(PtrWMQueue));
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
void ptrwmqueueAppendLeft(PtrWMQueue** q, WashingMachine* val) {
	// IT'S ABSOLUTELY THE SAME, EXCEPT WE CHANGE THE HEAD. KEKW
	ptrwmqueueAppendRight(q, val);
	(*q) = (*q)->prev;
}


// Delete queue
void ptrwmqueueDelete(PtrWMQueue** q) {
	if (*q == NULL) return; // don't need to delete an empty queue

	(*q)->prev->next = NULL; // Remove cycle
	while ((*q) != NULL) {
		PtrWMQueue* toDelete = *q;
		*q = (*q)->next;
		free(toDelete->val);
		free(toDelete);
	}
}