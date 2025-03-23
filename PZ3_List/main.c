#include <stdio.h>
#include "WMList.h"

#define N 8

int main() {
	WashingMachine wmarr[N] =
	{
		{.model = "Tesla1", .waterConsume_l = 20, .priceUsd = 500},
		{.model = "Tesla2", .waterConsume_l = 20, .priceUsd = 600},
		{.model = "Tesla3", .waterConsume_l = 20, .priceUsd = 900},
		{.model = "Tesla4", .waterConsume_l = 20, .priceUsd = 700},
		{.model = "Tesla5", .waterConsume_l = 20, .priceUsd = 500},
		{.model = "Tesla6", .waterConsume_l = 20, .priceUsd = 800},
		{.model = "Tesla7", .waterConsume_l = 20, .priceUsd = 1000},
		{.model = "Tesla8", .waterConsume_l = 20, .priceUsd = 1000},
	};

	WMList* wmlist = newWMList(wmarr, N);
	// printf("%s", wmlistToString(wmlist));
	wmlistSort(&wmlist, NULL);
	printf("SORTED: %s\n", wmlistToString(wmlist));
	wmlistSortedInsert(&wmlist, (WashingMachine){.model = "Tesla9", .waterConsume_l = 20, .priceUsd = 700}, NULL);
	printf("INSERT: %s", wmlistToString(wmlist));
}