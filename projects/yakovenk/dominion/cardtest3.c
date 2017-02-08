
//Konstantin Yakovenko
//2k17/02/07
//Unit Test for Outpost Card implementation cardOutpost()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
//setup the environment
//initialize the game state to where we could test the function under different game states
	int failFlag = 0;

	//input: (int player, struct gameState *state, int bonus)
	int numPlayers = 2;
	int thisPlayer = 0;
    int k[10] = {outpost, embargo, village, minion, mine, cutpurse,
				sea_hag, tribute, smithy, council_room};
	int seed = 1000;

	//vars for keeping track of the relevant changes
	int preCardNumBuys, preCardCoinCount, preCardHandCount, preCardDiscardCount, preCardCurrentPlayer, preCardDeckCount;

	struct gameState G, bkpG;	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	int handPos;

	// backup the game to have a fresh copy
	memcpy(&bkpG, &G, sizeof(struct gameState));

	//run unit tests
	//things we can test: 
	//The extra turn is completely normal except that your starting hand for it is only 3 cards.
	//This means that you only drew 3 cards instead of 5 cards during the Clean-up phase of the turn when you played Outpost.
	//Leave Outpost in front of you until the end of the extra turn. 
	printf("\n----------------- Test Card: Outpost ----------------\n");

	// ----------- TEST 1  --------------
	printf("TEST 1: +3 cards - Smithy\n");

	G.hand[thisPlayer][0] = outpost;
	handPos = 0;

	//save state for later comparison
	preCardCoinCount =  G.coins;
	preCardHandCount =  G.handCount[thisPlayer];
	preCardCurrentPlayer =  whoseTurn(&G);
	preCardDiscardCount = G.discardCount[thisPlayer];

	cardOutpost(handPos, thisPlayer, &G);

	printf("Is the Outpost state set?:"); 
	failFlag += assertTrue(G.outpostPlayed != 0); //outpost played.
	printf("\n\tDiscarded Card from hand? pre(%d), post(%d) -- ", preCardHandCount,  G.handCount[thisPlayer]);
	failFlag += assertTrue(preCardHandCount ==  G.handCount[thisPlayer] + 1); //Lost Outpost
	printf("\n\tDiscarded Card into discard pile? pre(%d), post(%d) -- ", preCardDiscardCount , G.discardCount[thisPlayer]);
	failFlag += assertTrue(preCardDiscardCount == G.discardCount[thisPlayer] - 1); //discarded outpost.


	//end turn, and check if we draw 3 cards.
	printf("\nEnd turn to get to the next player:"); 
	endTurn(&G);

	printf("\nIs the Outpost state still set?:"); 
	failFlag += assertTrue(G.outpostPlayed != 0); //outpost played.

	printf("\n\tPlayer should be the same: pre(%d) post(%d) -- ", preCardCurrentPlayer, whoseTurn(&G));
	failFlag += assertTrue( whoseTurn(&G) == preCardCurrentPlayer); 

	printf("\n\tHand should be 3: %d -- ", G.handCount[thisPlayer]);
	failFlag += assertTrue( G.handCount[whoseTurn(&G)] == 3); //Since we are only allowed to get 3 this time



	printf("\n UNIT TESTS for cardOutpost(): ");
	assertTrue(failFlag == 0);
	printf("\n");
	

	return 0;
}