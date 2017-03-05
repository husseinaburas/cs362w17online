
//Konstantin Yakovenko
//2k17/02/19
//Random Test for Great Hall Card implementation cardGreatHall()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define GAME_PHASES 3
#define MAX_COINS 10
#define MAX_BUYS 4

int checkCardEffect(int thisPlayer, struct gameState* preG, struct gameState* postG){
	int failFlag = 0; 

	printf("\nHand, Actions, Discard should have changed:\n");
	printf("\n\tCoins: pre(%d), post(%d) -- ", preG->coins, postG->coins); 
	failFlag += assertTrue(preG->coins == postG->coins); 

	printf("\n\tHand: pre(%d), post(%d) -- ",  preG->handCount[thisPlayer],  postG->handCount[thisPlayer]);
	failFlag += assertTrue( preG->handCount[thisPlayer] == postG->handCount[thisPlayer] + 1 - 1); //got 1 new cards but lost great hall.

	printf("\n\tActions: pre(%d), post(%d) -- ",  preG->numActions,  postG->numActions);
	failFlag += assertTrue(preG->numActions == postG->numActions - 1);//gained 1 action

	printf("\n\tDiscarded Card into discard pile? pre(%d), post(%d) -- ", preG->discardCount[thisPlayer] , postG->discardCount[thisPlayer]);
	failFlag += assertTrue(preG->discardCount[thisPlayer] == postG->discardCount[thisPlayer] - 1); //discarded outpost.

	return failFlag;
	
}

int main(int argc, char** argv){
//setup the environment
//initialize the game state to where we could test the function under different game states
	int numTestsToRun = 10;
	int failFlag = 0; 

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
					sea_hag, tribute, smithy, council_room};
	int seed = atoi(argv[1]);

	srand(seed);

	struct gameState G, preG;

	int n;	

	//things we can test: do we draw 3 cards? Do they disappear from the deck? Does the deck get reshuffled?
	printf("\n----------------- Test Card: Smithy ----------------\n");

for (n = 0; n < numTestsToRun; n++) {
		//input: (int player, struct gameState *state, int bonus)
		int numPlayers, thisPlayer;
		numPlayers = floor(rand() % MAX_PLAYERS) + 1;
		thisPlayer = floor(rand() % numPlayers);


	
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

    	// Randomize gamestate
	    //G.deckCount[thisPlayer] = floor(Random() * 5); //MAX_DECK

	    G.whoseTurn = thisPlayer;
	    G.phase = floor(rand() % GAME_PHASES);
	    G.coins = floor(rand() % MAX_COINS);
	   	//G.handCount[thisPlayer] = floor(Random() * 10); //MAX_HAND
	   	//G.discardCount[thisPlayer] = floor(Random() * 5); //MAX_DECK
	   	G.numBuys = floor(rand() % MAX_BUYS);



	   	// Randomize hand
	   	int k = floor(rand() % MAX_HAND);
	   	for(k; k >= 0 ; k--){
	   		int supplyPos = floor(rand() % 10);
	   		int toFlag = floor(rand() % 4);
	   		gainCard(supplyPos, &G, toFlag, thisPlayer);
	   	}

	   	// Make sure that one of our cards is the Smithy
	   	int handPos = floor(rand() % G.handCount[thisPlayer]);
	   	G.hand[thisPlayer][handPos] = great_hall;
		

	   	// Randomize discard pile
	   	//for(k = 0; k < G.discardCount[thisPlayer]; k++){
	   	//	G.discard[thisPlayer][k] = floor(Random() * 27); //enum of cards.
	   	//}
	   	// backup the game for the PRE state
		memcpy(&preG, &G, sizeof(struct gameState));

		printf("\n\tCase: numPlayers(%d), thisPlayer(%d), phase(%d) ", numPlayers, thisPlayer, G.phase); 
		printf("\n\tCase: handCount(%d), handPosSmithy(%d), greatHall?16?(%d)\n ", G.handCount[thisPlayer], handPos, G.hand[thisPlayer][handPos]); 
	   	cardGreatHall(handPos, thisPlayer, &G);
	    failFlag += checkCardEffect(thisPlayer, &preG, &G);
	}

	if(failFlag){
		printf("\nRANDOM TESTS FOR GREAT HALL CARD FAILED.\n");
	}else{
		printf("\nRANDOM TESTS FOR GREAT HALL CARD PASSED.\n");
	}

	return 0;
}