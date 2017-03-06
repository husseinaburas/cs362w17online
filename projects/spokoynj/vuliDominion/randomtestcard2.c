#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

#define NOISY_TEST 0

int assertTest(int actual, int expected, int testNo) {
	if (actual == expected) {
		printf("\tTEST %d SUCCESSFULLY COMPLETED\n",testNo);
		return 1;
	} 
	else {
		printf("\tTEST %d FAILED\n",testNo);
		printf("\tEXPECTED %d ---- ACTUAL %d\n",expected,actual);
		return 0;
	}
}

int main(int argc, char **argv) {
	// validate user input
	if (argc != 2) {
		fprintf(stderr, "usage: randomtestcard2 [(int)seed]");
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

	printf("\n---------------- Random Testing: Smithy ----------------\n");
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
				
		// set played card count, numBuys, numActions, whose turn
		numActions = G.numActions;
		numBuys = G.numBuys;
		playedCount = G.playedCardCount;
		G.whoseTurn = player;
		
		//assign cards in hand, deck, discard
		G.hand[player][0] = smithy;
		for (j = 1; j < handCount; j++) {
			G.hand[player][j] = (rand() % 27);
		}
		for (j = 0; j < deckCount; j++) {
			G.deck[player][j] = (rand() % 27);
		}
		for (j = 0; j < discardCount; j++) {
			G.discard[player][j] = (rand() % 27);
		}
		
		printf ("\nCALL #%d test Smithy card\n", i+1);

		if (NOISY_TEST) {
			printf("\n\tNumber of players: %d \n", numPlayers);
			printf("\n\tPlayer %d, before playing Smithy: \n", player);
			printf("\tCards in hand: %d\n", G.handCount[player]);
			printf("\tCards in deck: %d\n", G.deckCount[player]);
			printf("\tCards in discard: %d\n", G.discardCount[player]);
			printf("\tActions: %d\n\n", numActions);
		}
		
		cardEffect(smithy, -1, -1, -1, &G, 0, 0);

		if (NOISY_TEST)	{
			printf("\tPlayer %d, after playing Smithy: \n", player);
			printf("\tCards in hand: %d\n", G.handCount[player]);
			printf("\tCards in deck: %d\n", G.deckCount[player]);
			printf("\tCards in discard: %d\n", G.discardCount[player]);		
			printf("\tActions: %d\n\n", G.numActions);
		}
		
		// ----   TEST 1 - check cards in hand
		printf("TEST 1 - number of cards in hand \n");
		// hand + 3 - 1
		// there are enough cards to draw
		if (deckCount + discardCount > 2)
			expected = handCount + 2;
		// only 2 cards to draw
		else if (deckCount + discardCount == 2)
			expected = handCount + 1;
		// only 1 card to draw
		else if (deckCount + discardCount == 1)
			expected = handCount;
		// no cards to draw
		else 
			expected = handCount - 1;
		actual = G.handCount[player];
		assertTest(actual, expected, 1);

		// ----   TEST 2 - check numActions 
		printf("TEST 2 - action count \n");
		// actions + 0
		expected = numActions;
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
		if (deckCount > 2)
			expected = discardCount + 1;
		else
			expected = 1;
		actual = G.discardCount[player];
		assertTest(actual, expected, 4);

		// ----   TEST 5 - check deckCount  
		printf("TEST 5 - deck count \n");
		// deck - 3 
		// there are enough cards to draw
		if (deckCount > 2)
			expected = deckCount - 3;
		// only 2 cards to draw
		else if (deckCount == 2) {
			if (discardCount > 0)
				expected = discardCount - 1;
			else
				expected = 0;
		}
		// only 1 card to draw
		else if (deckCount == 1) {
			if (discardCount > 1)
				expected = discardCount - 2;
			else
				expected = 0;
		}
		// no cards to draw
		else {
			if (discardCount > 2)
				expected = discardCount - 3;
			else
				expected = 0;
		}
		actual = G.deckCount[player];
		assertTest(actual, expected, 5);
		
		// ----   TEST 6 - check getCost  
		printf("TEST 6 - smithy cost (4)\n");
		// cost = 4 coins
		expected = 4;
		actual = getCost(smithy);
		assertTest(actual, expected, 6);

		// ----   TEST 7 - check numBuys  
		printf("TEST 7 - number of buys \n");
		// buys unchanged
		expected = numBuys;
		actual = G.numBuys;
		assertTest(actual, expected, 7);	
		
		// ----   TEST 8 - check playedCards  
		printf("TEST 8 - check smithy in played cards\n");
		// smithy card should be in playedCards array
		expected = 1;
		actual = 0;
		int i;
		for (i = 0; i < G.playedCardCount; i++) {
			if (G.playedCards[i] == smithy) 
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
					
					// set played card count, numBuys, numActions, whose turn
					numActions = G.numActions;
					numBuys = G.numBuys;
					playedCount = G.playedCardCount;
					G.whoseTurn = player;
					
					//assign cards in hand, deck, discard
					G.hand[player][0] = smithy;
					for (j = 1; j < handCount; j++) {
						G.hand[player][j] = (rand() % 27);
					}
					for (j = 0; j < deckCount; j++) {
						G.deck[player][j] = (rand() % 27);
					}
					for (j = 0; j < discardCount; j++) {
						G.discard[player][j] = (rand() % 27);
					}
					
					printf ("\nCALL #%d test Smithy card\n", i+1);

					if (NOISY_TEST) {
						printf("\n\tNumber of players: 2 \n");
						printf("\n\tPlayer %d, before playing Smithy: \n", player);
						printf("\tCards in hand: %d\n", G.handCount[player]);
						printf("\tCards in deck: %d\n", G.deckCount[player]);
						printf("\tCards in discard: %d\n", G.discardCount[player]);
						printf("\tActions: %d\n\n", numActions);
					}
					
					cardEffect(smithy, -1, -1, -1, &G, 0, 0);

					if (NOISY_TEST)	{
						printf("\tPlayer %d, after playing Smithy: \n", player);
						printf("\tCards in hand: %d\n", G.handCount[player]);
						printf("\tCards in deck: %d\n", G.deckCount[player]);
						printf("\tCards in discard: %d\n", G.discardCount[player]);		
						printf("\tActions: %d\n\n", G.numActions);
					}
					
					// ----   TEST 1 - check cards in hand
					printf("TEST 1 - number of cards in hand \n");
					// hand + 3 - 1
					// there are enough cards to draw
					if (deckCount + discardCount > 2)
						expected = handCount + 2;
					// only 2 cards to draw
					else if (deckCount + discardCount == 2)
						expected = handCount + 1;
					// only 1 card to draw
					else if (deckCount + discardCount == 1)
						expected = handCount;
					// no cards to draw
					else 
						expected = handCount - 1;
					actual = G.handCount[player];
					assertTest(actual, expected, 1);

					// ----   TEST 2 - check numActions 
					printf("TEST 2 - action count \n");
					// actions + 0
					expected = numActions;
					actual = G.numActions;
					assertTest(actual, expected, 2);

					// ----  TEST 3 - check playedCardCount  
					printf("TEST 3 - played card count\n");
					// played cards + 1 
					expected = playedCount + 1;
					actual = G.playedCardCount;
					assertTest(actual, expected, 3);

					// ----   TEST 4 - check discardCount  
					printf("TEST 4 - discard count \n");
					// there are enough cards in deck
					if (deckCount > 2)
						expected = discardCount + 1;
					else
						expected = 1;
					actual = G.discardCount[player];
					assertTest(actual, expected, 4);

					// ----   TEST 5 - check deckCount  
					printf("TEST 5 - deck count \n");
					// deck - 3 
					// there are enough cards to draw
					if (deckCount > 2)
						expected = deckCount - 3;
					// only 2 cards to draw
					else if (deckCount == 2) {
						if (discardCount > 0)
							expected = discardCount - 1;
						else
							expected = 0;
					}
					// only 1 card to draw
					else if (deckCount == 1) {
						if (discardCount > 1)
							expected = discardCount - 2;
						else
							expected = 0;
					}
					// no cards to draw
					else {
						if (discardCount > 2)
							expected = discardCount - 3;
						else
							expected = 0;
					}
					actual = G.deckCount[player];
					assertTest(actual, expected, 5);
					
					// ----   TEST 6 - check getCost  
					printf("TEST 6 - smithy cost (4)\n");
					// cost = 4 coins
					expected = 4;
					actual = getCost(smithy);
					assertTest(actual, expected, 6);

					// ----   TEST 7 - check numBuys  
					printf("TEST 7 - number of buys \n");
					// buys unchanged
					expected = numBuys;
					actual = G.numBuys;
					assertTest(actual, expected, 7);

					// ----   TEST 8 - check playedCards  
					printf("TEST 8 - check smithy in played cards\n");
					// smithy card should be in playedCards array
					expected = 1;
					actual = 0;
					int i;
					for (i = 0; i < G.playedCardCount; i++) {
						if (G.playedCards[i] == smithy) 
							actual = 1;
					}
					assertTest(actual, expected, 8);					
											
					i++;
				}		
			}
		}
	}					

	printf("\n-------------- Testing Complete: Smithy ----------------\n\n");
	
	return 0;
}