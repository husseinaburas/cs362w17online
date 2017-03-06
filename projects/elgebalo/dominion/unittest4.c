#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void asserttrue(int num){
    if(num) printf("TEST PASSED. \n");
    else printf("TEST FAILED.\n");
    return;
}


int main(int argc, char ** argv){
	printf("\n--- TESTING getCost() ---\n");
	
	//initialize game
	struct gameState game;
	int random = 0;
	random = rand() % 10;
	int k[10] = {adventurer, smithy, council_room, feast, mine, gardens, remodel, village, great_hall, baron};
	initializeGame(2, k, random, &game);
	
	//begin testing	indidividual cards by asserting that they are equal to their in game cost 
	printf("testing getCost() on curse card\n");
	asserttrue(getCost(curse) == 0);
	printf("testing getCost() on estate card\n");
	asserttrue(getCost(estate) == 2);
	printf("testing getCost() on duchy card\n");
	asserttrue(getCost(duchy) == 5);
	printf("testing getCost() on province card\n");
	asserttrue(getCost(province) == 8);
	printf("testing getCost() on copper card\n");
	asserttrue(getCost(copper) == 0);
	printf("testing getCost() on silver card\n");
	asserttrue(getCost(silver) == 3);
	printf("testing getCost() on gold card\n");
	asserttrue(getCost(gold) == 6);
	printf("testing getCost() on smithy card\n");
	asserttrue(getCost(smithy) == 4);
	printf("testing getCost() on adventurer card\n");
	asserttrue(getCost(adventurer) == 6);
	printf("testing getCost() on council_room card\n");
	asserttrue(getCost(council_room) == 5);
	printf("testing getCost() on feast card\n");
	asserttrue(getCost(feast) == 4);
	printf("testing getCost() on gardens card\n");
	asserttrue(getCost(gardens) == 4);
	printf("testing getCost() on mine card\n");
	asserttrue(getCost(mine) == 5);
	printf("testing getCost() on remodel card\n");
	asserttrue(getCost(remodel) == 4);
	printf("testing getCost() on village card\n");
	asserttrue(getCost(village) == 3);
	printf("testing getCost() on baron card\n");
	asserttrue(getCost(baron) == 4);
	printf("testing getCost() on great_hall card\n");
	asserttrue(getCost(great_hall) == 3);
	printf("testing getCost() on minion card\n");
	asserttrue(getCost(minion) == 5);
	printf("testing getCost() on steward card\n");
	asserttrue(getCost(steward) == 3);
	printf("testing getCost() on tribute card\n");
	asserttrue(getCost(tribute) == 5);
	printf("testing getCost(tribute) on ambassador card\n");
	asserttrue(getCost(ambassador) == 3);
	printf("testing getCost() on cutpurse card\n");
	asserttrue(getCost(cutpurse) == 4);
	printf("testing getCost() on outpost card\n");
	asserttrue(getCost(outpost) == 5);
	printf("testing getCost() on salvager card\n");
	asserttrue(getCost(salvager) == 4);
	printf("testing getCost() on sea_hag card\n");
	asserttrue(getCost(sea_hag) == 4);
	printf("testing getCost() on embargo card\n");
	asserttrue(getCost(embargo) == 2);
	printf("testing getCost() on treasure_map card\n");
	asserttrue(getCost(treasure_map) == 4);
	
	printf("\n--- END TESTING ---\n");
	
	return 0;
}