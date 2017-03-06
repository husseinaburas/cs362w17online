
//Konstantin Yakovenko
//2k17/02/19
//Random Test for Smithy Card implementation playSmithy( &G, handPos);

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

	printf("\nOnly Hand should have changed:\n");
	printf("\n\tCoins: pre(%d), post(%d) -- ", preG->coins, postG->coins); 
	failFlag += assertTrue(preG->coins == postG->coins); 
	printf("\n\tHand: pre(%d), post(%d) -- ",  preG->handCount[thisPlayer],  postG->handCount[thisPlayer]);
	failFlag += assertTrue( preG->handCount[thisPlayer] == postG->handCount[thisPlayer] - 3 + 1); //got 3 new cards. Lost Smithy
	printf("\n\tDeck: pre(%d), post(%d) -- ",  preG->deckCount[thisPlayer],  postG->deckCount[thisPlayer]);
	failFlag += assertTrue(preG->deckCount[thisPlayer] == postG->deckCount[thisPlayer] + 3 - 1);//3 drawn, 1 shuffled

	// Because if the deck is smaller than 3, reshuffling of the discard pile is necessary,
	// so, we can't be sure of what card will end up in the hand after reshuffling.
	if(preG->deckCount[thisPlayer] >= 3){
		printf("\nFirst comparison deckPre(%d) and handPost(%d)  -- ", postG->hand[thisPlayer][postG->handCount[thisPlayer] - 3],
																		 preG->deck[thisPlayer][preG->deckCount[thisPlayer] - 1]);
		failFlag += assertTrue(postG->hand[thisPlayer][postG->handCount[thisPlayer] - 3] == preG->deck[thisPlayer][preG->deckCount[thisPlayer] - 1]);
		printf("\nSecond comparison pre(%d) and post(%d)  -- ", postG->hand[thisPlayer][postG->handCount[thisPlayer] - 2],
																preG->deck[thisPlayer][preG->deckCount[thisPlayer] - 2]);
		failFlag += assertTrue(postG->hand[thisPlayer][postG->handCount[thisPlayer] - 2] == preG->deck[thisPlayer][preG->deckCount[thisPlayer] - 2]);
		printf("\nThird comparison pre(%d) and post(%d)  -- ", postG->hand[thisPlayer][postG->handCount[thisPlayer] - 1] ,
																 preG->deck[thisPlayer][preG->deckCount[thisPlayer] - 3]);
		failFlag += assertTrue(postG->hand[thisPlayer][postG->handCount[thisPlayer] - 1] == preG->deck[thisPlayer][preG->deckCount[thisPlayer] - 3]);
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
	   	int k = floor(rand() % MAX_HAND) + 1;
	   	printf("k: %d", k);
	   	for(k; k >= 0 ; k--){
	   		int supplyPos = floor(rand() % 10);
	   		int toFlag = floor(rand() % 4);
	   		gainCard(supplyPos, &G, toFlag, thisPlayer);
	   	}

	   	// Make sure that one of our cards is the Smithy
	   	int handPos = 0;
	   	if(G.handCount[thisPlayer] != 0){
	   		handPos = floor(rand() % G.handCount[thisPlayer]);
	   		G.hand[thisPlayer][handPos] = smithy;
		}else{
			G.handCount[thisPlayer]++;
			G.hand[thisPlayer][handPos] = smithy;
		}

	   	// Randomize discard pile
	   	//for(k = 0; k < G.discardCount[thisPlayer]; k++){
	   	//	G.discard[thisPlayer][k] = floor(Random() * 27); //enum of cards.
	   	//}
	   	// backup the game for the PRE state
		memcpy(&preG, &G, sizeof(struct gameState));

		printf("\n\tCase: numPlayers(%d), thisPlayer(%d), phase(%d) -- ", numPlayers, thisPlayer, G.phase); 
		printf("\n\tCase: handCount(%d), handPosSmithy(%d), smithy?13?(%d) -- ", G.handCount[thisPlayer], handPos, G.hand[thisPlayer][handPos]); 
	   	playSmithy( &G, handPos);
	    failFlag += checkCardEffect(thisPlayer, &preG, &G);
	}

	if(failFlag){
		printf("\nRANDOM TESTS FOR SMITHY CARD FAILED.\n");
	}else{
		printf("\nRANDOM TESTS FOR SMITHY CARD PASSED.\n");
	}

	return 0;
}