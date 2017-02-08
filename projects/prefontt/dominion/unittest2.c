/* Testing the getCost function */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {

	int newCards, extraCoins, shuffledCards = 0;
	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	int discarded = 1;
	int garbage = 100;
	int i;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy, council_room};

	int numPlayers = 2;
	int thisPlayer = 0;
	int seed = 10;
	int cost = 0;

	initializeGame(numPlayers, k, seed, &G);
	
	printf("++++++++++++ TESTING getCost Function ++++++++++++++++\n\n\n");

	cost = getCost(curse);
	printf("Testing cost of Curse = %d, expected = 0\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 0);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(estate);
	printf("Testing cost of estate = %d, expected = 2\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 2);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(duchy);
	printf("Testing cost of duchy = %d, expected = 5\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 5);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(province);
	printf("Testing cost of province = %d, expected = 8\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 8);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(copper);
	printf("Testing cost of copper = %d, expected = 0\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 0);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(silver);
	printf("Testing cost of silver = %d, expected = 3\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 3);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(gold);
	printf("Testing cost of gold = %d, expected = 6\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 6);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(adventurer);
	printf("Testing cost of adventurer = %d, expected = 6\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 6);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(council_room);
	printf("Testing cost of council_room = %d, expected = 5\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 5);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(gardens);
	printf("Testing cost of gardens = %d, expected = 4\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 4);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(feast);
	printf("Testing cost of feast = %d, expected = 4\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 4);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(mine);
	printf("Testing cost of mine = %d, expected = 5\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 5);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(remodel);
	printf("Testing cost of remodel = %d, expected = 4\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 4);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(smithy);
	printf("Testing cost of smithy = %d, expected = 4\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 4);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(village);
	printf("Testing cost of village = %d, expected = 3\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 3);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(baron);
	printf("Testing cost of baron = %d, expected = 4\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 4);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(great_hall);
	printf("Testing cost of great_hall = %d, expected = 3\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 3);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(minion);
	printf("Testing cost of minion = %d, expected = 5\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 5);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(steward);
	printf("Testing cost of steward = %d, expected = 3\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 3);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(tribute);
	printf("Testing cost of tribute = %d, expected = 5\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 5);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(ambassador);
	printf("Testing cost of ambassador = %d, expected = 3\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 3);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(cutpurse);
	printf("Testing cost of cutpurse = %d, expected = 4\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 4);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(embargo);
	printf("Testing cost of embargo = %d, expected = 2\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 2);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(outpost);
	printf("Testing cost of outpost = %d, expected = 5\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 5);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(salvager);
	printf("Testing cost of salvager = %d, expected = 4\n", cost);
	printf("Cost is %d\n", cost);
	assertTrue(cost, 4);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(sea_hag);
	printf("Testing cost of sea_hag = %d, expected = 4\n", cost);
	assertTrue(cost, 4);
	
	printf("------------------------------------------------------------------\n");
	
	cost = getCost(treasure_map);
	printf("Testing cost of treasure_map = %d, expected = 4\n", cost);
	assertTrue(cost, 4);
	
	printf("------------------------------------------------------------------\n");
	
	printf("Testing with garbage value, expected = -1\n");
	cost = getCost(garbage);
	assertTrue(cost, -1);
	
	printf("\n");

	return 0;
}
