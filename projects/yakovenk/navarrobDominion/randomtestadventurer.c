
//Konstantin Yakovenko
//2k17/02/19
//Random Test for Adventurer Card implementation playAdventurer(&G);


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

	// Check the phase we are in. If anything other than 0, action phase, nothing should have changed.
	printf("Phase: (%d) \n", preG->phase);
	if(preG->phase == 0){
		printf("Card should change anything only during action phase: ");
		failFlag += assertTrue(memcmp(preG, postG, sizeof(struct gameState)));
	}

	// Make sure that the number of coins hasn't changed.
	printf("Only Coins and Hand should have changed:\n");
	printf("\n\tCoins: pre(%d), post(%d) -- ", preG->coins, postG->coins); 
	failFlag += assertTrue(preG->coins == postG->coins); 

	// Make sure that the number of cards in hand has changed.
	printf("\n\tHand: pre(%d), post(%d) -- ", preG->handCount[thisPlayer],  postG->handCount[thisPlayer]);
	failFlag += assertTrue(preG->handCount[thisPlayer] ==  postG->handCount[thisPlayer] - 2); //got 2 new cards.

	// Make sure that the new cards are both treasures.
	printf("\nMake sure that we got a treasure  -- ");
	if(preG->handCount[thisPlayer] <=  postG->handCount[thisPlayer] - 2){
		printf("\nFirst treasure is treasure  -- ");
		failFlag += assertTrue(postG->hand[thisPlayer][postG->handCount[thisPlayer] - 1] == gold ||
								postG->hand[thisPlayer][postG->handCount[thisPlayer] - 1] == silver ||
								postG->hand[thisPlayer][postG->handCount[thisPlayer] - 1] == copper); 
		
		//technically possible to get only one treasure, so if we got 2, we check the second one also
		if(preG->handCount[thisPlayer] ==  postG->handCount[thisPlayer] - 2){
		printf("\nSecond treasure is treasure  -- ");
			failFlag += assertTrue(postG->hand[thisPlayer][postG->handCount[thisPlayer] - 2] == gold ||
								postG->hand[thisPlayer][postG->handCount[thisPlayer] - 2] == silver ||
								postG->hand[thisPlayer][postG->handCount[thisPlayer] - 2] == copper); 
		}
	}

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

	struct gameState G, preG, bkpG;

	int n;	

	//things we can test: do we draw 3 cards? Do they disappear from the deck? Does the deck get reshuffled?
	printf("\n----------------- Test Card: Adventurer ----------------\n");

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
	   		int supplyPos = floor(rand() % 10); // There are 10 supply card positions.
	   		int toFlag = floor(rand() % 4); // There are 3 different places a card could go.
	   		gainCard(supplyPos, &G, toFlag, thisPlayer);
	   	}

	   	// Randomize discard pile
	   	//for(k = 0; k < G.discardCount[thisPlayer]; k++){
	   	//	G.discard[thisPlayer][k] = floor(Random() * 27); //enum of cards.
	   	//}
	   	// backup the game for the PRE state
		memcpy(&preG, &G, sizeof(struct gameState));


	   	playAdventurer(&G);
	    failFlag += checkCardEffect(thisPlayer, &preG, &G);
	}

	if(failFlag){
		printf("\nRANDOM TESTS FOR ADVENTURER CARD FAILED.\n");
	}else{
		printf("\nRANDOM TESTS FOR ADVENTURER CARD PASSED.\n");
	}

	return 0;
}