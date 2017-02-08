/*
Author: hutterj
Date: 2017.02.07
File: cardtest1.c
Purpose: Perform unit tests of adventurer card in dominion.c

Rules of adventurer:
	can't go through deck if deck empty
	go through deck, get 2 treasures
	non-player deck/hand/discard is unchanged
	supply pile unchanged
		
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


/*
Name: asserttrue
Purpose:  use something like assert to check conditions
but still be able to collect coverage
*/
void asserttrue(int condition, char* condName){
	if (condition){
		printf("Test: %-33s success.\n", condName);
	}
	else {
		printf("Test: %-33s FAIL.\n", condName);
	}
	return;
}

int main(void){
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int funcStatus;
	int handPos;
	int i;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Card: adventurer ----------------\n");
	thisPlayer = whoseTurn(&G);
	asserttrue((gainCard(adventurer, &G, 2, thisPlayer)==0), "added adventurer to hand");
	for (i = 0; i < MAX_HAND; i++){
		if (G.hand[thisPlayer][i] == adventurer){
			handPos = i;
			printf("adventurer in hand position %d\n", handPos);
			break;
		}
	}
	memcpy(&testG, &G, sizeof(struct gameState));
	funcStatus = playCard(handPos, -1, -1, -1, &G); 
	asserttrue((funcStatus == 0), "play card");
	asserttrue((G.coins >= testG.coins+2), "coins at least +2 from before");
	printf("Current coin count: %d\nPrevious  coin count: %d\n", G.coins, testG.coins);
	asserttrue((G.handCount[thisPlayer]-2 == testG.handCount[thisPlayer]), "hand count at least +2 from before");
	printf("Current handcount: %d\nPrevious handcount: %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer]);
	asserttrue((G.discardCount[thisPlayer] > testG.discardCount[thisPlayer]), "discard 1 or more cards");
	printf("Current discard count: %d\nPrevious discard count: %d\n", G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);
	
	
	
	printf("\n\n\n");
		
	return 0;
	

}


