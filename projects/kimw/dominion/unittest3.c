#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
	printf("------  getCost unit test ------\n");

	//initialize
	int i;
	int notCard = -1;

	//test each case for getCost
	printf("Get cost for curse\n");
	i = getCost(curse);
	asserttrue(i == 0);

	printf("Get cost for estate\n");
	i = getCost(estate);
	asserttrue(i == 2);

	printf("Get cost for duchy\n");
	i = getCost(duchy);
	asserttrue(i == 5);

	printf("Get cost for province\n");
	i = getCost(province);
	asserttrue(i == 8);

	printf("Get cost for copper\n");
	i = getCost(copper);
	asserttrue(i == 0);

	printf("Get cost for silver\n");
	i = getCost(silver);
	asserttrue(i == 3);

	printf("Get cost for gold\n");
	i = getCost(gold);
	asserttrue(i == 6);

	printf("Get cost for adventurer\n");
	i = getCost(adventurer);
	asserttrue(i == 6);

	printf("Get cost for council_room\n");
	i = getCost(council_room);
	asserttrue(i == 5);

	printf("Get cost for feast\n");
	i = getCost(feast);
	asserttrue(i == 4);

	printf("Get cost for gardens\n");
	i = getCost(gardens);
	asserttrue(i == 4);

	printf("Get cost for mine\n");
	i = getCost(mine);
	asserttrue(i == 5);

	printf("Get cost for remodel\n");
	i = getCost(remodel);
	asserttrue(i == 4);

	printf("Get cost for smithy\n");
	i = getCost(smithy);
	asserttrue(i == 4);

	printf("Get cost for village\n");
	i = getCost(village);
	asserttrue(i == 3);

	printf("Get cost for baron\n");
	i = getCost(baron);
	asserttrue(i == 4);

	printf("Get cost for great_hall\n");
	i = getCost(great_hall);
	asserttrue(i == 3);

	printf("Get cost for minion\n");
	i = getCost(minion);
	asserttrue(i == 5);

	printf("Get cost for steward\n");
	i = getCost(steward);
	asserttrue(i == 3);

	printf("Get cost for tribute\n");
	i = getCost(tribute);
	asserttrue(i == 5);

	printf("Get cost for ambassador\n");
	i = getCost(ambassador);
	asserttrue(i == 3);

	printf("Get cost for cutpurse\n");
	i = getCost(cutpurse);
	asserttrue(i == 4);

	printf("Get cost for embargo\n");
	i = getCost(embargo);
	asserttrue(i == 2);

	printf("Get cost for outpost\n");
	i = getCost(outpost);
	asserttrue(i == 5);

	printf("Get cost for salvager\n");
	i = getCost(salvager);
	asserttrue(i == 4);

	printf("Get cost for sea_hag\n");
	i = getCost(sea_hag);
	asserttrue(i == 4);

	printf("Get cost for treasure_map\n");
	i = getCost(treasure_map);
	asserttrue(i == 4);

	printf("Get cost for card that does not exist\n");
	i = getCost(notCard);
	asserttrue(i == -1);
		
	printf("--------------- end --------------\n");
	return 0;
}