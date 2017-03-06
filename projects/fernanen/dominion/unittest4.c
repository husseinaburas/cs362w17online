/* -----------------------------------------------------------------------
 *	getCost() Tescase
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
int main() {
    int p;
    int seed = 1000;
    int r=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    printf ("TESTING getCost():\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(p, k, seed, &G);
	printf("getting curse price: returns 0");
	if(getCost(curse) == 0) 
		printf("PASSED \n;");
	else
		printf("FAILED\n");
	
	printf("getting duchy price: returns 5 ");
	if(getCost(duchy) == 5) 
		printf("PASSED \n");
	else
		printf("FAILED\n");
	
	printf("getting province price: returns 8 ");
	if(getCost(province) == 8) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting copper price: returns 0");
	if(getCost(copper) == 0) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
		printf("getting silver price: returns 3");
	if(getCost(silver) == 3) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
		printf("getting gold price: returns 6 ");
	if(getCost(gold) == 6) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting adventurer price: returns 6");
	if(getCost(adventurer) == 6) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting council_room price: returns 5");
	if(getCost(council_room) == 5) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting feast price: returns 4 ");
	if(getCost(feast) == 4) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
		printf("getting gardens price: returns 4 ");
	if(getCost(gardens) == 4) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting mine price: returns 5");
	if(getCost(mine) == 5) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting remodel price: returns 4");
	if(getCost(remodel) == 4) 
		printf("PASSED\n;");
	else
		printf("FAILED\n");
	
	printf("getting smithy price: returns 4 ");
	if(getCost(smithy) == 4) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting village price: returns 3 ");
	if(getCost(village) == 3) 
		printf("PASSED \n");
	else
		printf("FAILED\n");
	
	printf("getting baron price: returns 4 ");
	if(getCost(baron) == 4) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting great_hall price: returns 3");
	if(getCost(great_hall) == 3) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
		printf("getting minion price: returns 5 ");
	if(getCost(minion) == 5) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
		printf("getting steward price: returns 3");
	if(getCost(steward) == 3) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting tribute price: returns 5");
	if(getCost(tribute) == 5) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting ambassador price: returns 3");
	if(getCost(ambassador) == 3) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting cutpurse price: returns 4 ");
	if(getCost(cutpurse) == 4)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
		printf("getting embargo price: returns 2 ");
	if(getCost(embargo) == 2) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting outpost price: returns 5");
	if(getCost(outpost) == 5) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
		printf("getting salvager price: returns 4 ");
	if(getCost(salvager) == 4) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
		printf("getting sea_hag price: returns 4 ");
	if(getCost(sea_hag) == 4) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("getting treasure_map price: returns 4");
	if(getCost(treasure_map) == 4) 
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("All tests complete!\n");
    return 0;
}
