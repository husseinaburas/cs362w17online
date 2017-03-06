/**
* Card Test 1 - Smithy
* Parameters: hand position of card to play, 3 optional choice fields, current game state
* 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Smithy"

int checkSmithy(int p, struct gameState *post){
    int r;
    r = smithyCard(p,post,p);
	if(r == 0){
		printf("SMITHY SUCCEEDED");		
	}
	else{
		printf("SMITHY FAILED");
	}

    return 0;
  
}

int main(int argc, char* argv[]){
	
	int i, n, r, p, deckCount, discardCount, handCount;
	int seed = 1000;
	//(int) argv[1]; // passed seed number

	int k[10] = { adventurer, remodel, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };
	
	struct gameState G, testG;
	
	// initializeGame(numPlayers, k, seed, &G);
	SelectStream(2);
	PutSeed(seed);
	// initialize a game state and player cards
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 2);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		checkSmithy(p, &G); 
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	exit(0);
  	
	// // ----------- TEST a: This Player puts Smithy to discard --------------
	// printf("Test a: This Player uses Smithy and it moves from hand to Discard\n");

	// G.hand[thisPlayer][0] = smithy;
	// G.hand[thisPlayer][1] = copper;
	// G.hand[thisPlayer][2] = duchy;
	// G.hand[thisPlayer][3] = estate;
	// G.hand[thisPlayer][4] = village;

	// // copy the game state to a test case - Control
	// memcpy(&testG, &G, sizeof(struct gameState));
	

	// newCards = 3;
	// xtraCoins = 0;
	// printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	// printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	// printf("Discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	// printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	// printf("Action Count = %d, expected = %d\n", testG.numActions, G.numActions - 1);
	// assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	// assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
	// assert(testG.discardCount[thisPlayer] == (G.discardCount[thisPlayer]));
	// assert(testG.numActions == (G.numActions - 1));
	// assert(testG.coins == G.coins + xtraCoins);

	// // ----------- TEST b: Other State's Conditions --------------
	// printf("Test b: Other State's Conditions\n");

	// printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	// printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
	// printf("copper count = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper]);
	// printf("silver count = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver]);
	// printf("gold count = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);
	// printf("estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
	// printf("duchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	// printf("adventurer count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
	// printf("remodel count = %d, expected = %d\n", testG.supplyCount[remodel], G.supplyCount[remodel]);
	// printf("village count = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village]);
	// printf("minion count = %d, expected = %d\n", testG.supplyCount[minion], G.supplyCount[minion]);
	// printf("mine count = %d, expected = %d\n", testG.supplyCount[mine], G.supplyCount[mine]);
	// printf("cutpurse count = %d, expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
	// printf("sea_hag count = %d, expected = %d\n", testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);
	// printf("tribute count = %d, expected = %d\n", testG.supplyCount[tribute], G.supplyCount[tribute]);
	// printf("smithy count = %d, expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);
	// printf("council_room count = %d, expected = %d\n", testG.supplyCount[council_room], G.supplyCount[council_room]);

	// assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
	// assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);
	// assert(testG.supplyCount[copper] == G.supplyCount[copper]);
	// assert(testG.supplyCount[silver] == G.supplyCount[silver]);
	// assert(testG.supplyCount[gold] == G.supplyCount[gold]);
	// assert(testG.supplyCount[estate] == G.supplyCount[estate]);
	// assert(testG.supplyCount[duchy] == G.supplyCount[duchy]);
	// assert(testG.supplyCount[adventurer] == G.supplyCount[adventurer]);
	// assert(testG.supplyCount[remodel] == G.supplyCount[remodel]);
	// assert(testG.supplyCount[village] == G.supplyCount[village]);
	// assert(testG.supplyCount[minion] == G.supplyCount[minion]);
	// assert(testG.supplyCount[mine] == G.supplyCount[mine]);
	// assert(testG.supplyCount[cutpurse] == G.supplyCount[cutpurse]);
	// assert(testG.supplyCount[sea_hag] == G.supplyCount[sea_hag]);
	// assert(testG.supplyCount[tribute] == G.supplyCount[tribute]);
	// assert(testG.supplyCount[smithy] == (G.supplyCount[smithy]));
	// assert(testG.supplyCount[council_room] == G.supplyCount[council_room]); */

	return 0;
}