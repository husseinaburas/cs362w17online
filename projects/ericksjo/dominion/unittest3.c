/*
	unittest3.c: Testing the getCost() method.
	
	Description: The getCost method takes an integer as a parameter and returns the cost of the card associated with that integer. If the passed
	integer doesn't match a card, -1 is returned.
	
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assertion.h"
#include <time.h>

int main() {
	printf("\n***********BEGINNING getCost() TESTING**********\n\n");
	struct gameState testGame, gameCopy;
	int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
	int numPlayers = 2;
	initializeGame(numPlayers, k, 10, &testGame);
	int currentPlayer = testGame.whoseTurn;
	
	//Testing each card passed into the getCost method, making sure they all return the correct values.
	printf("Testing each card passed into the getCost method, making sure they all return the correct values\n");
	
	printf("Curse Cost: 0. Testing.\n");
	assertion(getCost(curse) == 0);
	
	printf("Estate Cost: 2. Testing.\n");
	assertion(getCost(estate) == 2);
	
	printf("Duchy Cost: 5. Testing.\n");
	assertion(getCost(duchy) == 5);
	
	printf("Province Cost: 8. Testing.\n");
	assertion(getCost(province) == 8);
	
	printf("Copper Cost: 0. Testing.\n");
	assertion(getCost(copper) == 0);
	
	printf("Silver Cost: 3. Testing.\n");
	assertion(getCost(silver) == 3);
	
	printf("Gold Cost: 6. Testing.\n");
	assertion(getCost(gold) == 6);
	
	printf("Adventurer Cost: 6. Testing.\n");
	assertion(getCost(adventurer) == 6);
	
	printf("Council Room Cost: 5. Testing.\n");
	assertion(getCost(council_room) == 5);
	
	printf("Feast Cost: 4. Testing.\n");
	assertion(getCost(feast) == 4);
	
	printf("Gardens Cost: 4. Testing.\n");
	assertion(getCost(gardens) == 4);
	
	printf("Mine Cost: 5. Testing.\n");
	assertion(getCost(mine) == 5);
	
	printf("Remodel Cost: 4. Testing.\n");
	assertion(getCost(remodel) == 4);
	
	printf("Smithy Cost: 4. Testing.\n");
	assertion(getCost(smithy) == 4);
	
	printf("Village Cost: 3. Testing.\n");
	assertion(getCost(village) == 3);
	
	printf("Baron Cost: 4. Testing.\n");
	assertion(getCost(baron) == 4);
	
	printf("Great Hall Cost: 3. Testing.\n");
	assertion(getCost(great_hall) == 3);
	
	printf("Minion Cost: 5. Testing.\n");
	assertion(getCost(minion) == 5);
	
	printf("Steward Cost: 3. Testing.\n");
	assertion(getCost(steward) == 3);
	
	printf("Tribute Cost: 5. Testing.\n");
	assertion(getCost(tribute) == 5);
	
	printf("Ambassador Cost: 3. Testing.\n");
	assertion(getCost(ambassador) == 3);
	
	printf("Cutpurse Cost: 4. Testing.\n");
	assertion(getCost(cutpurse) == 4);
	
	printf("Embargo Cost: 2. Testing.\n");
	assertion(getCost(embargo) == 2);
	
	printf("Outpost Cost: 5. Testing.\n");
	assertion(getCost(outpost) == 5);
	
	printf("Salvager Cost: 4. Testing.\n");
	assertion(getCost(salvager) == 4);
	
	printf("Sea Hag Cost: 4. Testing.\n");
	assertion(getCost(sea_hag) == 4);
	
	printf("Treasure Map Cost: 4. Testing.\n");
	assertion(getCost(treasure_map) == 4);
	
	//Two conditions will return -1, a negative integer or an abnormally high integer, beyond the bounds of the set enums
	printf("Testing conditions to return -1\n");
	printf("Testing getCost with 200. Expectation: -1 returned. \n");
	assertion(getCost(200) == -1);
	
	printf("Testing getCost with -25. Expectation: -1 returned. \n");
	assertion(getCost(-25) == -1);
	
	printf("***********FINISHING getCost() TESTING**********\n\n");
	return 0;
}