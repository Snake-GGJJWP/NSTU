#include <stdio.h>
#include <stdlib.h>
#include "WMQueue.h"
#include "PtrWMQueue.h"

#define N 5

int main() {
	// ### Deque with structs ###

	WashingMachine wmarr[N] =
	{
		{.model = "Tesla1", .waterConsume_l = 20, .priceUsd = 500},
		{.model = "Tesla2", .waterConsume_l = 30, .priceUsd = 600},
		{.model = "Tesla3", .waterConsume_l = 40, .priceUsd = 900},
		{.model = "Tesla4", .waterConsume_l = 50, .priceUsd = 700},
		{.model = "Tesla5", .waterConsume_l = 60, .priceUsd = 500},
	};

	WMQueue* deque = wmqueueNew(wmarr, N);
	WashingMachine wm;

	// Print the elements out
	for (int i = 0; i < N; i++) {
		wm = wmqueuePopLeft(&deque);
		printf("%s\n", wmToString(&wm));
	}

	wmqueueDelete(&deque);

	// ### Deque with pointers ###
	// Create new array of wm pointers
	WashingMachine** ptrwmarr = (WashingMachine**)malloc(N * sizeof(WashingMachine*));
	for (int i = 0; i < N; i++) {
		WashingMachine* wmptr = newWashingMachine();
		wmCopyInit(wmptr, &wmarr[i]);
		ptrwmarr[i] = wmptr;
	}

	PtrWMQueue* ptrdeque = ptrwmqueueNew(ptrwmarr, N);

	// Print the elements out
	for (int i = 0; i < N; i++)
		printf("%s\n", wmToString(ptrwmqueuePopLeft(&ptrdeque)));

	ptrwmqueueDelete(&ptrdeque);

	return 0;
}