#include <stdio.h>
#include "Smartphone.h"
#include "SmartphoneList.h"
#include "SmartphoneSer.h"

int main() {

	// ### PART 1A ###
	Smartphone smApple, smHuawei;
	smInit(&smApple, "Apple", 10, 2024, 6.2, 2000);
	smInit(&smHuawei, "Huawei", RED, 2020, 5.8, 200);

	printf("Apple: %s\n", smToString(&smApple));
	printf("Huawei: %s\n", smToString(&smHuawei));

	char cmp = smcmp(&smApple, &smHuawei);
	if (cmp == 0) printf("%s and %s have the same price\n", smApple.model, smHuawei.model);
	else if (cmp == -1) printf("%s is more expensive\n", smApple.model);
	else if (cmp == 1) printf("%s is more expensive\n", smHuawei.model);

	if (smIsEqual(&smApple, &smHuawei) == 0) {
		printf("%s and %s are the same phone\n", smApple.model, smHuawei.model);
	}

	smDelete(&smApple);

	// ### PART 1B ###
	Smartphone smarr[3] =
	{
		{.model = "Apple1", .color = RED, .year = 2020, .size = 5.4, .priceUsd = 500},
		{.model = "Apple2", .color = GREEN, .year = 2021, .size = 5.6, .priceUsd = 600},
		{.model = "Apple3", .color = BLUE, .year = 2022, .size = 5.8, .priceUsd = 700},
	};

	SMList* smlist = newSMList(smarr, 3);
	smlistInsert(&smlist, (Smartphone) { .model = "Apple4", .color = GOLD, .year = 2023, .size = 7, .priceUsd = 1500 }, 0);
	smlistInsert(&smlist, (Smartphone) { .model = "Apple5", .color = SILVER, .year = 2024, .size = 7.2, .priceUsd = 1000 }, 0);

	printf("LIST1_INSERT: \n%s\n", smlistToString(smlist));

	smlistRemoveIndex(&smlist, 0);

	printf("LIST1_REMOVE: \n%s\n", smlistToString(smlist));

	// smlistDelete(smlist);

	// ## PART 1C ###
	smlistdump("smlist.bin", smlist);
	SMList* smload = smlistload("smlist.bin");
	printf("\nLoaded list: \n%s\n", smlistToString(smload));
	

	return 0;
}