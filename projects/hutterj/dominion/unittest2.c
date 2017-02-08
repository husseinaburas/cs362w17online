/*
Author: hutterj
Date: 2017.02.07
File: unittest2.c
Purpose: Perform unit tests of function drawCard in dominion.c

Rules of drawCard:
	take top card from deck and put it into hand
	if deck is empty, discard => deck and shuffle
	can't draw card if discard and deck are both empty
	after a shuffle, discard is empty
	after drawing:
		deckcount decremented from before drawCard (or discard pile if deck was shuffled in)
		handcount++
		
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
	int notPlayer = 0;
	int funcStatus;
	int i;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Function: drawCard ----------------\n");
	
	// ----------- TEST 1: player deck decr  --------------
	printf("TEST 1: player deck count decrements\n");
	thisPlayer = whoseTurn(&G);
	// freshly init'ed game: deck count = 5, hand count = 5, discard count = 0
	
	// loop until deck
	while (G.deckCount[thisPlayer] > 0){
		memcpy(&testG, &G, sizeof(struct gameState));
		funcStatus = drawCard(thisPlayer, &G);
		printf("Deck count before draw: %d\n",testG.deckCount[thisPlayer]);
		asserttrue((funcStatus==0), "draw card");
		asserttrue((G.deckCount[thisPlayer]+1 == testG.deckCount[thisPlayer]), "deck decremented");
		if (G.deckCount[thisPlayer] == 0){
			asserttrue((G.deckCount[thisPlayer]==0),"deck is now empty");
		}
	}
	
	
	// ----------- TEST 2: non-player deck decr  --------------
	printf("\n\nTEST 2: non-player deck count doesn't decrement\n");
	initializeGame(numPlayers, k, seed, &G);
	thisPlayer = whoseTurn(&G);
	notPlayer = thisPlayer+1; //2 players total
	// freshly init'ed game: deck count = 5, hand count = 5, discard count = 0
	
	// loop until deck empty
	while (G.deckCount[thisPlayer] > 0){
		memcpy(&testG, &G, sizeof(struct gameState));
		funcStatus = drawCard(thisPlayer, &G);
		printf("Player deck count before draw: %d\n",testG.deckCount[thisPlayer]);
		asserttrue((funcStatus==0), "draw card");
		asserttrue((G.deckCount[notPlayer] == testG.deckCount[notPlayer]), "non-player deck not decremented");
		if (G.deckCount[thisPlayer] == 0){
			asserttrue((G.deckCount[thisPlayer]==0)," player deck is now empty");
		}
	}
	
	
	// ----------- TEST 3: discard doesn't change  --------------
	printf("\n\nTEST 3: discard doesn't change\n");
	initializeGame(numPlayers, k, seed, &G);
	thisPlayer = whoseTurn(&G);
	// freshly init'ed game: deck count = 5, hand count = 5, discard count = 0
	
	// loop until deck empty
	while (G.deckCount[thisPlayer] > 0){
		memcpy(&testG, &G, sizeof(struct gameState));
		funcStatus = drawCard(thisPlayer, &G);
		printf("Player deck count before draw: %d\n",testG.deckCount[thisPlayer]);
		asserttrue((funcStatus==0), "draw card");
		asserttrue((memcmp(&(G.discard),&(testG.discard), sizeof(G.discard)) == 0), "all discard piles same after draw");
		asserttrue((memcmp(&(G.discardCount),&(testG.discardCount), sizeof(G.discardCount)) == 0), "all discard counts same");
		if (G.deckCount[thisPlayer] == 0){
			asserttrue((G.deckCount[thisPlayer]==0)," player deck is now empty");
		}
	}
	
	// ----------- TEST 4: hand increments  --------------
	printf("\n\nTEST 4: player hand increments\n");
	initializeGame(numPlayers, k, seed, &G);
	thisPlayer = whoseTurn(&G);
	// freshly init'ed game: deck count = 5, hand count = 5, discard count = 0
	
	// loop until deck empty
	while (G.deckCount[thisPlayer] > 0){
		memcpy(&testG, &G, sizeof(struct gameState));
		funcStatus = drawCard(thisPlayer, &G);
		printf("Player deck count before draw: %d\n",testG.deckCount[thisPlayer]);
		asserttrue((funcStatus==0), "draw card");
		asserttrue((G.handCount[thisPlayer]-1 == testG.handCount[thisPlayer]), "hand count incr after draw");
		if (G.deckCount[thisPlayer] == 0){
			asserttrue((G.deckCount[thisPlayer]==0)," player deck is now empty");
		}
	}
	
	// ----------- TEST 5: non-player hand no change  --------------
	printf("\n\nTEST 5: non-player hand no change\n");
	initializeGame(numPlayers, k, seed, &G);
	thisPlayer = whoseTurn(&G);
	// freshly init'ed game: deck count = 5, hand count = 5, discard count = 0
	
	// loop a couple times
	while (G.deckCount[thisPlayer] > 0){
		memcpy(&testG, &G, sizeof(struct gameState));
		funcStatus = drawCard(thisPlayer, &G);
		printf("Player deck count before draw: %d\n",testG.deckCount[thisPlayer]);
		asserttrue((funcStatus==0), "draw card");
		for (i = thisPlayer+1; i < MAX_PLAYERS; i++){
			printf("Player # %d deck:\n", i);
			//check count same
			asserttrue((G.deckCount[i] == testG.deckCount[i]),"non-player deck count unchanged");
			//check contents same
			asserttrue((memcmp(&(G.deck[i]),&(testG.deck[i]), sizeof(G.deck[i])) == 0), "non-player deck content unchanged");
			
		}
		if (G.deckCount[thisPlayer] == 0){
			asserttrue((G.deckCount[thisPlayer]==0)," player deck is now empty");
		}
	}
	
	// ----------- TEST 6: draw from empty deck, 0 discard  --------------
	printf("\n\nTEST 6: can't draw from empty deck if 0 discard to shuffle back in\n");
	initializeGame(numPlayers, k, seed, &G);
	thisPlayer = whoseTurn(&G);
	// freshly init'ed game: deck count = 5, hand count = 5, discard count = 0
	
	// loop a couple times
	while (G.deckCount[thisPlayer] > 0){
		drawCard(thisPlayer, &G);
	}
	funcStatus = drawCard(thisPlayer, &G);
	asserttrue((G.deckCount[thisPlayer]==0), "deck count is 0");
	asserttrue((G.discardCount[thisPlayer]==0), "discard count is 0");
	asserttrue((funcStatus == -1), "no draw from empty deck & discard");
	
	// ----------- TEST 7: draw from empty deck, nonzero discard  --------------
	printf("\n\nTEST 7: draw from empty deck\n");
	initializeGame(numPlayers, k, seed, &G);
	thisPlayer = whoseTurn(&G);
	// freshly init'ed game: deck count = 5, hand count = 5, discard count = 0
	
	// discard a few cards so that they're in the discard pile (trash flag off)
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue((discardCard(0, thisPlayer, &G, 0)==0), "discard hand index 0");
	asserttrue((G.handCount[thisPlayer]==2), "post-discard hand size is 2");
	asserttrue((G.discardCount[thisPlayer]==3), "post-discard count is 3");
	
	asserttrue((drawCard(thisPlayer, &G)==0), "draw card to empty deck");
	asserttrue((drawCard(thisPlayer, &G)==0), "draw card to empty deck");
	asserttrue((drawCard(thisPlayer, &G)==0), "draw card to empty deck");
	asserttrue((drawCard(thisPlayer, &G)==0), "draw card to empty deck");
	asserttrue((drawCard(thisPlayer, &G)==0), "draw card to empty deck");
	asserttrue((G.deckCount[thisPlayer]==0), "deck count now 0");
	
	asserttrue((drawCard(thisPlayer, &G)==0), "draw card, should reshuffle");
	
	
	printf("\n\n\n");
		
	return 0;
	

}


