/*
  unit test for getCost() 
  */ 



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
	int cardcost;
    int seed = 1000;
    int numPlayers = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G;

    initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Unit: getCost ----------------\n");

	// ----------- TEST 1: Testing cost of curse --------------
	printf("TEST 1: TEST 1: Testing cost of curse\n");
	cardcost = getCost(curse);
	printf("cost = %d, expected = 0\n", cardcost);
	assert(cardcost == 0);
	// ----------- TEST 1: Testing cost of estate --------------
	printf("TEST 1: TEST 1: Testing cost of estate\n");
	cardcost = getCost(estate);
	printf("cost = %d, expected = 2\n", cardcost);
	assert(cardcost == 2);
	// ----------- TEST 1: Testing cost of duchy --------------
	printf("TEST 1: TEST 1: Testing cost of duchy\n");
	cardcost = getCost(duchy);
	printf("cost = %d, expected = \n", cardcost);
	assert(cardcost == 5);
	// ----------- TEST 1: Testing cost of province --------------
	printf("TEST 1: TEST 1: Testing cost of province\n");
	cardcost = getCost(province);
	printf("cost = %d, expected = 8\n", cardcost);
	assert(cardcost == 8);
	// ----------- TEST 1: Testing cost of copper --------------
	printf("TEST 1: TEST 1: Testing cost of copper\n");
	cardcost = getCost(copper);
	printf("cost = %d, expected = 0\n", cardcost);
	assert(cardcost == 0);
	// ----------- TEST 1: Testing cost of silver --------------
	printf("TEST 1: TEST 1: Testing cost of silver\n");
	cardcost = getCost(silver);
	printf("cost = %d, expected = 3\n", cardcost);
	assert(cardcost == 3);
	// ----------- TEST 1: Testing cost of gold --------------
	printf("TEST 1: TEST 1: Testing cost of gold\n");
	cardcost = getCost(gold);
	printf("cost = %d, expected = 6\n", cardcost);
	assert(cardcost == 6);
	// ----------- TEST 1: Testing cost of adventurer --------------
	printf("TEST 1: TEST 1: Testing cost of adventurer\n");
	cardcost = getCost(adventurer);
	printf("cost = %d, expected = 6\n", cardcost);
	assert(cardcost == 6);
	// ----------- TEST 1: Testing cost of council_room --------------
	printf("TEST 1: TEST 1: Testing cost of council_room\n");
	cardcost = getCost(council_room);
	printf("cost = %d, expected = 5\n", cardcost);
	assert(cardcost == 5);
	// ----------- TEST 1: Testing cost of  feast--------------
	printf("TEST 1: TEST 1: Testing cost of feast\n");
	cardcost = getCost(feast);
	printf("cost = %d, expected = 4\n", cardcost);
	assert(cardcost == 4);
	// ----------- TEST 1: Testing cost of gardens --------------
	printf("TEST 1: TEST 1: Testing cost of gardens\n");
	cardcost = getCost(gardens);
	printf("cost = %d, expected = 4\n", cardcost);
	assert(cardcost == 4);
	// ----------- TEST 1: Testing cost of mine --------------
	printf("TEST 1: TEST 1: Testing cost of mine\n");
	cardcost = getCost(mine);
	printf("cost = %d, expected = 5\n", cardcost);
	assert(cardcost == 5);
	// ----------- TEST 1: Testing cost of remodel --------------
	printf("TEST 1: TEST 1: Testing cost of remodel\n");
	cardcost = getCost(remodel);
	printf("cost = %d, expected = 4\n", cardcost);
	assert(cardcost == 4);
	// ----------- TEST 1: Testing cost of smithy --------------
	printf("TEST 1: TEST 1: Testing cost of smithy\n");
	cardcost = getCost(smithy);
	printf("cost = %d, expected = 4\n", cardcost);
	assert(cardcost == 4);
	// ----------- TEST 1: Testing cost of village --------------
	printf("TEST 1: TEST 1: Testing cost of village\n");
	cardcost = getCost(village);
	printf("cost = %d, expected = 3\n", cardcost);
	assert(cardcost == 3);
	// ----------- TEST 1: Testing cost of  baron--------------
	printf("TEST 1: TEST 1: Testing cost of baron\n");
	cardcost = getCost(baron);
	printf("cost = %d, expected = 4\n", cardcost);
	assert(cardcost == 4);
	// ----------- TEST 1: Testing cost of great_hall --------------
	printf("TEST 1: TEST 1: Testing cost of great_hall\n");
	cardcost = getCost(great_hall);
	printf("cost = %d, expected = 3\n", cardcost);
	assert(cardcost == 3);
	// ----------- TEST 1: Testing cost of minion --------------
	printf("TEST 1: TEST 1: Testing cost of minion\n");
	cardcost = getCost(minion);
	printf("cost = %d, expected = 5\n", cardcost);
	assert(cardcost == 5);
	// ----------- TEST 1: Testing cost of  steward--------------
	printf("TEST 1: TEST 1: Testing cost of steward\n");
	cardcost = getCost(steward);
	printf("cost = %d, expected = 3\n", cardcost);
	assert(cardcost == 3);
	// ----------- TEST 1: Testing cost of tribute --------------
	printf("TEST 1: TEST 1: Testing cost of tribute\n");
	cardcost = getCost(tribute);
	printf("cost = %d, expected = 5\n", cardcost);
	assert(cardcost == 5);
	// ----------- TEST 1: Testing cost of  ambassador--------------
	printf("TEST 1: TEST 1: Testing cost of ambassador\n");
	cardcost = getCost(ambassador);
	printf("cost = %d, expected = 3\n", cardcost);
	assert(cardcost == 3);
	// ----------- TEST 1: Testing cost of  cutpurse--------------
	printf("TEST 1: TEST 1: Testing cost of cutpurse\n");
	cardcost = getCost(cutpurse);
	printf("cost = %d, expected = 4\n", cardcost);
	assert(cardcost == 4);
	// ----------- TEST 1: Testing cost of embargo --------------
	printf("TEST 1: TEST 1: Testing cost of embargo\n");
	cardcost = getCost(embargo);
	printf("cost = %d, expected = 2\n", cardcost);
	assert(cardcost == 2);
	// ----------- TEST 1: Testing cost of outpost --------------
	printf("TEST 1: TEST 1: Testing cost of outpost\n");
	cardcost = getCost(outpost);
	printf("cost = %d, expected = 5\n", cardcost);
	assert(cardcost == 5);
	// ----------- TEST 1: Testing cost of salvager --------------
	printf("TEST 1: TEST 1: Testing cost of salvager\n");
	cardcost = getCost(salvager);
	printf("cost = %d, expected = 4\n", cardcost);
	assert(cardcost == 4);
	// ----------- TEST 1: Testing cost of  sea_hag--------------
	printf("TEST 1: TEST 1: Testing cost of sea_hag\n");
	cardcost = getCost(sea_hag);
	printf("cost = %d, expected = 4\n", cardcost);
	assert(cardcost == 4);
	// ----------- TEST 1: Testing cost of  treasure_map--------------
	printf("TEST 1: TEST 1: Testing cost of treasure_map\n");
	cardcost = getCost(treasure_map);
	printf("cost = %d, expected = 4\n", cardcost);
	assert(cardcost == 4);
	
	printf("\n >>>>> SUCCESS: Testing complete for unittest4 <<<<<\n\n");
	return 0;
}