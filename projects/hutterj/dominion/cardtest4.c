/*
Author: hutterj
Date: 2017.02.07
File: cardtest1.c
Purpose: Perform unit tests of village card in dominion.c

Rules of village:
	add a card to hand
	hand incremented
	deck decremented (unless empty and then it's shuffled from discard)
	add 2 actions (ie +1 from being paying 1 action to play village)
	non-player hand/deck/discard unchanged
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
	
	printf("----------------- Testing Card: village ----------------\n");
	thisPlayer = whoseTurn(&G);
	asserttrue((gainCard(village, &G, 2, thisPlayer)==0), "added village to hand");
	for (i = 0; i < MAX_HAND; i++){
		if (G.hand[thisPlayer][i] == village){
			handPos = i;
			printf("village in hand position %d\n", handPos);
			break;
		}
	}
	memcpy(&testG, &G, sizeof(struct gameState));
	funcStatus = playCard(handPos, -1, -1, -1, &G); 
	asserttrue((funcStatus == 0), "play card");
	asserttrue((G.numActions >= testG.numActions), "actions added");
	asserttrue((G.numActions == 2), "2 actions remain");
	asserttrue((G.handCount[thisPlayer]-1 == testG.handCount[thisPlayer]), "hand count +1 from before");
	printf("Current handcount: %d\nPrevious handcount: %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer]);
	asserttrue((G.discardCount[thisPlayer] > testG.discardCount[thisPlayer]), "discard 1 card");
	printf("Current discard count: %d\nPrevious discard count: %d\n", G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);
	
	for (i = 0; i < MAX_HAND; i++){
		if (G.hand[thisPlayer][i] == village){
			handPos = i;
			printf("village in hand position %d\n", handPos);
			
			//since we already found smithy and assumed running through this with only the just-played smithy in hand because of fresh game
			asserttrue((0), "village discarded after use");
			break;
		}
	}
	
	
	
	printf("\n\n\n");
		
	return 0;
	

}


