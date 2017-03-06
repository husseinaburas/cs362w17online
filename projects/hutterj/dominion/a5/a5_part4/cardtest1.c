/*
Author: hutterj
Date: 2017.02.07
File: cardtest1.c
Purpose: Perform unit tests of smithy card in dominion.c

Rules of smithy:
	hand size is +3 from before (if deck had at least 3 cards)
	discard pile is same
	other player's piles are same
	coins same
	smithy card now in discard pile
		
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

	printf("----------------- Testing Card: smithy ----------------\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	thisPlayer = whoseTurn(&G);
	asserttrue((gainCard(smithy, &G, 2, thisPlayer)==0), "added smithy to hand");
	for (i = 0; i < MAX_HAND; i++){
		if (G.hand[thisPlayer][i] == smithy){
			handPos = i;
			printf("smithy in hand position %d\n", handPos);
			break;
		}
	}
	memcpy(&testG, &G, sizeof(struct gameState));
	funcStatus = playCard(handPos, -1, -1, -1, &G); 
	asserttrue((funcStatus == 0), "play card");
	asserttrue((G.handCount[thisPlayer]-2 == testG.handCount[thisPlayer]), "hand size +2 from before");
	printf("Current handcount: %d\nPrevious handcount: %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer]);
	asserttrue((G.discardCount[thisPlayer]-1 == testG.discardCount[thisPlayer]), "discard +1 card");
	printf("Current discard count: %d\nPrevious discard count: %d\n", G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);
	for (i = 0; i < MAX_HAND; i++){
		if (G.hand[thisPlayer][i] == smithy){
			handPos = i;
			printf("smithy in hand position %d\n", handPos);
			
			//since we already found smithy and assumed running through this with only the just-played smithy in hand because of fresh game
			asserttrue((0), "smithy discarded after use");
			break;
		}
	}
	
	
	
	
	
	printf("\n\n\n");
		
	return 0;
	

}


