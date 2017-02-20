#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

#define NOISY_TEST 0

int assertTest(int actual, int expected, int testNo) {
	if (actual == expected) {
		printf("\tTEST %d SUCCESSFULLY COMPLETED\n", testNo);
		return 1;
	} 
	else {
		printf("\tTEST %d FAILED\n",testNo);
		printf("\tEXPECTED %d ---- ACTUAL %d\n", expected, actual);
		return 0;
	}
}

int main(int argc, char **argv) {
	// validate user input
	if (argc != 2) {
		fprintf(stderr, "usage: randomtestcard1 [(int)seed]");
		exit(1);
	}
	int actual, expected;
	int handCount, deckCount, discardCount, playedCount, numActions, numBuys;
	int numPlayers, player, i, j; 
	int testCycles = 1000;
	int randomSeed = atoi(argv[1]);
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall};
				 
	struct gameState G;

	printf("\n---------------- Random Testing: Village ----------------\n");
	printf ("\nRANDOM TESTS\n");

	for (i = 0; i < testCycles; i++) {
		// clear the game state
		memset(&G, 23, sizeof(struct gameState)); 

		// assign random number of players between 2 and 4
		numPlayers = (rand() % 3) + 2;
		
		// initialize a new game
		initializeGame(numPlayers, k, randomSeed, &G); 
		
		// select player to evaluate
		player = (rand() % numPlayers);
		
		// assign random hand, deck, discard count
		handCount = floor(Random() * MAX_HAND);
		deckCount = floor(Random() * MAX_DECK);
		discardCount = floor(Random() * MAX_DECK);
		G.handCount[player] = (rand() % handCount);                 
		G.deckCount[player] = (rand() % deckCount);
		G.discardCount[player] = (rand() % discardCount);
		if (G.handCount[player] == 0)
			G.handCount[player] = 1;
		handCount = G.handCount[player];
		deckCount = G.deckCount[player];
		discardCount = G.discardCount[player];

		// set played card count, numBuys, numActions and whose turn
		numActions = G.numActions;
		numBuys = G.numBuys;
		playedCount = G.playedCardCount;
		G.whoseTurn = player;
		
		//assign cards in hand, deck, discard
		G.hand[player][0] = village;
		for (j = 1; j < handCount; j++) {
			G.hand[player][j] = (rand() % 27);
		}
		for (j = 0; j < deckCount; j++) {
			G.deck[player][j] = (rand() % 27);
		}
		for (j = 0; j < discardCount; j++) {
			G.discard[player][j] = (rand() % 27);
		}
		
		printf ("\nCALL #%d test Village card\n", i+1);

		if (NOISY_TEST) {
			printf("\n\tNumber of players: %d \n", numPlayers);
			printf("\n\tPlayer %d, before playing Village: \n", player);
			printf("\tCards in hand: %d\n", G.handCount[player]);
			printf("\tCards in deck: %d\n", G.deckCount[player]);
			printf("\tCards in discard: %d\n", G.discardCount[player]);
			printf("\tNumber of actions: %d\n", numActions);
			printf("\tNumber of buys: %d\n", numBuys);
		}
		
		cardEffect(village, -1, -1, -1, &G, 0, 0);

		if (NOISY_TEST)	{
			printf("\n\tPlayer %d, after playing Village: \n", player);
			printf("\tCards in hand: %d\n", G.handCount[player]);
			printf("\tCards in deck: %d\n", G.deckCount[player]);
			printf("\tCards in discard: %d\n", G.discardCount[player]);		
			printf("\tNumber of actions: %d\n", G.numActions);
			printf("\tNumber of buys: %d\n\n", G.numBuys);
		}
		
		// ----   TEST 1 - check cards in hand  
		printf("TEST 1 - number of cards in hand \n");
		// hand + 1 - 1
		// there are enough cards to draw
		if (deckCount + discardCount > 0)
			expected = handCount;
		// no cards to draw
		else 
			expected = handCount - 1;
		actual = G.handCount[player];
		assertTest(actual, expected, 1);
		
		// ----   TEST 2 - check numActions 
		printf("TEST 2 - action count \n");
		// actions + 2  
		expected = numActions + 2;
		actual = G.numActions;
		assertTest(actual, expected, 2);

		// ----  TEST 3 - check playedCardCount  
		printf("TEST 3 - played card count \n");
		// played cards + 1 
		expected = playedCount + 1;
		actual = G.playedCardCount;
		assertTest(actual, expected, 3);

		// ----   TEST 4 - check discardCount  
		printf("TEST 4 - discard count \n");
		// there are enough cards in deck
		if (deckCount == 0)
			expected = 1;
		else
			expected = discardCount + 1;
		actual = G.discardCount[player];
		assertTest(actual, expected, 4);
		
		// ----   TEST 5 - check deckCount  
		printf("TEST 5 - deck count \n");
		// deck - 1
		// there are enough cards in deck
		if (deckCount > 0)
			expected = deckCount - 1;
		// there are enough cards in discard
		else if (discardCount > 0)
			expected = discardCount - 1;
		// no cards to draw
		else 
			expected = deckCount;
		actual = G.deckCount[player];
		assertTest(actual, expected, 5);
		
		// ----   TEST 6 - check getCost  
		printf("TEST 6 - village cost (3)\n");
		// cost = 3 coins
		expected = 3;
		actual = getCost(village);
		assertTest(actual, expected, 6);

		// ----   TEST 7 - check numBuys  
		printf("TEST 7 - number of buys \n");
		// buys unchanged
		expected = numBuys;
		actual = G.numBuys;
		assertTest(actual, expected, 7);	
		
		// ----   TEST 8 - check playedCards  
		printf("TEST 8 - check village in played cards\n");
		// village card should be in playedCards array
		expected = 1;
		actual = 0;
		int i;
		for (i = 0; i < G.playedCardCount; i++) {
			if (G.playedCards[i] == village) 
				actual = 1;
		}
		assertTest(actual, expected, 8);
	}
	
	printf ("\nSIMPLE FIXED TESTS\n");
	for (player = 0; player < 2; player++) {
		for (deckCount = 0; deckCount < 5; deckCount++) {
			for (discardCount = 0; discardCount < 5; discardCount++) {
				for (handCount = 1; handCount < 5; handCount++) {
					memset(&G, 23, sizeof(struct gameState)); 
					initializeGame(2, k, randomSeed, &G);
					
					G.deckCount[player] = deckCount;
					G.discardCount[player] = discardCount;
					G.handCount[player] = handCount;
					
					// set played card count, numBuys, numActions and whose turn
					numActions = G.numActions;
					numBuys = G.numBuys;
					playedCount = G.playedCardCount;
					G.whoseTurn = player;
					
					//assign cards in hand, deck, discard
					G.hand[player][0] = village;
					for (j = 1; j < handCount; j++) {
						G.hand[player][j] = (rand() % 27);
					}
					for (j = 0; j < deckCount; j++) {
						G.deck[player][j] = (rand() % 27);
					}
					for (j = 0; j < discardCount; j++) {
						G.discard[player][j] = (rand() % 27);
					}
					
					printf ("\nCALL #%d test Village card\n", i+1);

					if (NOISY_TEST) {
						printf("\n\tNumber of players: 2 \n");
						printf("\n\tPlayer %d, before playing Village: \n", player);
						printf("\tCards in hand: %d\n", G.handCount[player]);
						printf("\tCards in deck: %d\n", G.deckCount[player]);
						printf("\tCards in discard: %d\n", G.discardCount[player]);
						printf("\tNumber of actions: %d\n", numActions);
					}
					
					cardEffect(village, -1, -1, -1, &G, 0, 0);

					if (NOISY_TEST)	{
						printf("\n\tPlayer %d, after playing Village: \n", player);
						printf("\tCards in hand: %d\n", G.handCount[player]);
						printf("\tCards in deck: %d\n", G.deckCount[player]);
						printf("\tCards in discard: %d\n", G.discardCount[player]);		
						printf("\tNumber of actions: %d\n\n", G.numActions);
					}
					
					// ----   TEST 1 - check cards in hand  
					printf("TEST 1 - number of cards in hand \n");
					// hand + 1 - 1
					// there are enough cards to draw
					if (deckCount + discardCount > 0)
						expected = handCount;
					// no cards to draw
					else 
						expected = handCount - 1;
					actual = G.handCount[player];
					assertTest(actual, expected, 1);
					
					// ----   TEST 2 - check numActions 
					printf("TEST 2 - action count \n");
					// actions + 2  
					expected = numActions + 2;
					actual = G.numActions;
					assertTest(actual, expected, 2);

					// ----  TEST 3 - check playedCardCount  
					printf("TEST 3 - played card count \n");
					// played cards + 1 
					expected = playedCount + 1;
					actual = G.playedCardCount;
					assertTest(actual, expected, 3);

					// ----   TEST 4 - check discardCount  
					printf("TEST 4 - discard count \n");
					// there are enough cards in deck
					if (deckCount == 0)
						expected = 1;
					else
						expected = discardCount + 1;
					actual = G.discardCount[player];
					assertTest(actual, expected, 4);
					
					// ----   TEST 5 - check deckCount  
					printf("TEST 5 - deck count \n");
					// deck - 1
					// there are enough cards in deck
					if (deckCount > 0)
						expected = deckCount - 1;
					// there are enough cards in discard
					else if (discardCount > 0)
						expected = discardCount - 1;
					// no cards to draw
					else 
						expected = deckCount;
					actual = G.deckCount[player];
					assertTest(actual, expected, 5);
					
					// ----   TEST 6 - check getCost  
					printf("TEST 6 - village cost (3)\n");
					// cost = 3 coins
					expected = 3;
					actual = getCost(village);
					assertTest(actual, expected, 6);

					// ----   TEST 7 - check numBuys  
					printf("TEST 7 - number of buys \n");
					// buys unchanged
					expected = numBuys;
					actual = G.numBuys;
					assertTest(actual, expected, 7);
					
					// ----   TEST 8 - check playedCards  
					printf("TEST 8 - check village in played cards\n");
					// village card should be in playedCards array
					expected = 1;
					actual = 0;
					int i;
					for (i = 0; i < G.playedCardCount; i++) {
						if (G.playedCards[i] == village) 
							actual = 1;
					}
					assertTest(actual, expected, 8);
					
					i++;
				}		
			}
		}
	}

	printf("\n-------------- Testing Complete: Village ----------------\n\n");
	return 0;
}