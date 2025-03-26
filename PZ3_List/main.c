#include <stdio.h>
#include "WMList.h"

#define N 8

int main() {
	WashingMachine wmarr[N] =
	{
		{.model = "Tesla1", .waterConsume_l = 20, .priceUsd = 500},
		{.model = "Tesla2", .waterConsume_l = 30, .priceUsd = 600},
		{.model = "Tesla3", .waterConsume_l = 40, .priceUsd = 900},
		{.model = "Tesla4", .waterConsume_l = 50, .priceUsd = 700},
		{.model = "Tesla5", .waterConsume_l = 60, .priceUsd = 500},
		{.model = "Tesla6", .waterConsume_l = 70, .priceUsd = 800},
		{.model = "Tesla7", .waterConsume_l = 80, .priceUsd = 1000},
		{.model = "Tesla8", .waterConsume_l = 90, .priceUsd = 100},
	};

	WMList* wmlist = newWMList(wmarr, N);
	wmlistInsert(&wmlist, (WashingMachine) { .model = "Tesla9", .waterConsume_l = 10, .priceUsd = 1200 }, 0);
	wmlistInsert(&wmlist, (WashingMachine) { .model = "Tesla10", .waterConsume_l = 15, .priceUsd = 99 }, 0);
	wmlistInsert(&wmlist, (WashingMachine) { .model = "Tesla11", .waterConsume_l = 10.4, .priceUsd = 589.99 }, 0);

	printf("LIST1_INSERT: \n%s\n", wmlistToString(wmlist));

	wmlistRemoveIndex(&wmlist, 0);

	printf("LIST1_REMOVE: \n%s\n", wmlistToString(wmlist));

	wmlistDelete(wmlist);

	wmlist = newWMList(wmarr, N);
	wmlistSort(&wmlist, NULL);
	printf("LIST2_SORTED: \n%s\n", wmlistToString(wmlist));

	wmlistSortedInsert(&wmlist, (WashingMachine){.model = "Tesla9", .waterConsume_l = 20, .priceUsd = 700}, NULL);
	wmlistSortedInsert(&wmlist, (WashingMachine) { .model = "Tesla10", .waterConsume_l = 30, .priceUsd = 600 }, NULL);
	wmlistSortedInsert(&wmlist, (WashingMachine) { .model = "Tesla11", .waterConsume_l = 12, .priceUsd = 1240.5 }, NULL);
	wmlistSortedInsert(&wmlist, (WashingMachine) { .model = "Tesla12", .waterConsume_l = 55.4, .priceUsd = 999.99 }, NULL);
	printf("LIST2_INSERT: \n%s\n", wmlistToString(wmlist));

	wmlistRemoveElement(&wmlist, (WashingMachine) { .model = "Tesla12", .waterConsume_l = 55.4, .priceUsd = 999.99 });


	printf("LIST2_REMOVE: \n%s\n", wmlistToString(wmlist));

	wmlistDelete(wmlist);
}