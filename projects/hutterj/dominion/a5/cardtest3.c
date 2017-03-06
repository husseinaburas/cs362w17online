/*
Author: hutterj
Date: 2017.02.07
File: cardtest1.c
Purpose: Perform unit tests of great hall card in dominion.c

Rules of great hall:
	add a card to hand
	add an action (ie same number of actions available as before playing that action)
	add a victory point
	deck is decremented
	non-player hand/deck/discard same
	hand incremented unless deck is empty
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
			great_hall, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Card: great hall ----------------\n");
	thisPlayer = whoseTurn(&G);
	asserttrue((gainCard(great_hall, &G, 2, thisPlayer)==0), "added great hall to hand");
	for (i = 0; i < MAX_HAND; i++){
		if (G.hand[thisPlayer][i] == great_hall){
			handPos = i;
			printf("great hall in hand position %d\n", handPos);
			break;
		}
	}
	memcpy(&testG, &G, sizeof(struct gameState));
	funcStatus = playCard(handPos, -1, -1, -1, &G); 
	asserttrue((funcStatus == 0), "play card");
	asserttrue((G.numActions == testG.numActions), "action added (1 remains)");
	asserttrue((G.handCount[thisPlayer]-1 == testG.handCount[thisPlayer]), "hand count +1 from before");
	printf("Current handcount: %d\nPrevious handcount: %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer]);
	asserttrue((G.discardCount[thisPlayer] > testG.discardCount[thisPlayer]), "discard 1 or more cards");
	printf("Current discard count: %d\nPrevious discard count: %d\n", G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);
	
	for (i = 0; i < MAX_HAND; i++){
		if (G.hand[thisPlayer][i] == great_hall){
			handPos = i;
			printf("great_hall in hand position %d\n", handPos);
			
			//since we already found smithy and assumed running through this with only the just-played smithy in hand because of fresh game
			asserttrue((0), "great hall discarded after use");
			break;
		}
	}
	
	
	printf("\n\n\n");
		
	return 0;
	

}


