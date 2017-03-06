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

// count treasure cards in hand
int handTreasureCount(struct gameState G, int p) {
	int j, treasureCount = 0;
	for (j = 0; j < G.handCount[p]; j++) {	
		if (G.hand[p][j] == copper || G.hand[p][j] == silver || G.hand[p][j] == gold) 
			treasureCount++;
	}
	return treasureCount;
}

// count treasure cards in deck
int deckTreasureCount(struct gameState G, int p) {
	int j, treasureCount = 0;
	for (j = 0; j < G.deckCount[p]; j++) {
		if (G.deck[p][j] == copper || G.deck[p][j] == silver || G.deck[p][j] == gold) 
			treasureCount++;
	}
	return treasureCount;
}

// count treasure cards in discard pile
int discardTreasureCount(struct gameState G, int p) {
	int j, treasureCount = 0;
	for (j = 0; j < G.discardCount[p]; j++) {	
		if (G.discard[p][j] == copper || G.discard[p][j] == silver || G.discard[p][j] == gold) 
			treasureCount++;
	}
	return treasureCount;
}

// calculate value of coins in hand
int coinCount(struct gameState G, int p) {
	int j, totalCoins = 0;
	for (j = 0; j < G.handCount[p]; j++) {	
		if(G.hand[p][j] == copper)
			totalCoins+=1;
		else if(G.hand[p][j] == silver)
			totalCoins+=2;
		else if (G.hand[p][j] == gold)
				totalCoins+=3;
	}
	return totalCoins;
}

int main(int argc, char **argv) {
	// validate user input
	if (argc != 2) {
		fprintf(stderr, "usage: randomtestadventurer [(int)seed]");
		exit(1);
	}
	int actual, expected;
	int handCount, deckCount, discardCount, playedCount;
	int numPlayers, player, i, j; 
	int preDeckTreasureCount, preHandTreasureCount, preDiscardTreasureCount, preCoinCount;
	int postDeckTreasureCount, postHandTreasureCount, postDiscardTreasureCount, postCoinCount;
	int testCycles = 1000;
	int randomSeed = atoi(argv[1]);
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall};
				 
	struct gameState G;

	printf("\n-------------- Random Testing: Adventurer ----------------\n");
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
		
		// set played card count and whose turn
		playedCount = G.playedCardCount;
		G.whoseTurn = player;
		
		//assign cards in hand, deck, discard
		G.hand[player][0] = adventurer;
		for (j = 1; j < handCount; j++) {
			G.hand[player][j] = (rand() % 27);
		}
		for (j = 0; j < deckCount; j++) {
			G.deck[player][j] = (rand() % 27);
		}
		for (j = 0; j < discardCount; j++) {
			G.discard[player][j] = (rand() % 27);
		}
		
		// save pre-adventurer hand, deck, discard, coins
		preHandTreasureCount = handTreasureCount(G, player);
		preDeckTreasureCount = deckTreasureCount(G, player);
		preDiscardTreasureCount = discardTreasureCount(G, player);
		preCoinCount = coinCount(G, player);
		
		printf ("\nCALL #%d test Adventurer card\n", i+1);

		if (NOISY_TEST) {
			printf("\n\tNumber of players: %d \n", numPlayers);
			printf("\n\tPlayer %d, before playing Adventurer: \n", player);
			printf("\tCards in hand: %d\n", G.handCount[player]);
			printf("\t\tTreasure cards in hand: %d\n", preHandTreasureCount);
			printf("\tCards in deck: %d\n", G.deckCount[player]);
			printf("\t\tTreasure cards in deck: %d\n", preDeckTreasureCount);
			printf("\tCards in discard: %d\n", G.discardCount[player]);
			printf("\t\tTreasure cards in discard: %d\n", preDiscardTreasureCount);
			printf("\tCoins in hand: %d\n", preCoinCount);
		}
		
		cardEffect(adventurer, -1, -1, -1, &G, 0, 0);

		// recalculate coins in hand
		updateCoins(player, &G, 0);
		
		// save post-adventurer hand, deck, discard, coins
		postHandTreasureCount = handTreasureCount(G, player);
		postDeckTreasureCount = deckTreasureCount(G, player);
		postDiscardTreasureCount = discardTreasureCount(G, player);
		postCoinCount = coinCount(G, player);

		if (NOISY_TEST)	{
			printf("\n\tPlayer %d, after playing Adventurer: \n", player);
			printf("\tCards in hand: %d\n", G.handCount[player]);
			printf("\t\tTreasure cards in hand: %d\n", postHandTreasureCount);
			printf("\tCards in deck: %d\n", G.deckCount[player]);
			printf("\t\tTreasure cards in deck: %d\n", postDeckTreasureCount);
			printf("\tCards in discard: %d\n", G.discardCount[player]);		
			printf("\t\tTreasure cards in discard: %d\n", postDiscardTreasureCount);
			printf("\tCoins in hand: %d\n\n", postCoinCount);
		}
		
		// ----   TEST 1 - check cards in hand  
		printf("TEST 1 - number of cards in hand \n");
		
		// 2+ treasures to draw -> hand +2 -1 = +1
		if (preDeckTreasureCount + preDiscardTreasureCount > 1)
			expected = handCount + 1;
		// 1 treasure to draw -> hand +1 -1 = 0
		else if (preDeckTreasureCount + preDiscardTreasureCount == 1)
			expected = handCount;
		// 0 treasure to draw -> hand +0 -1 = -1
		else 
			expected = handCount - 1;
		
		actual = G.handCount[player];
		assertTest(actual, expected, 1);
		
		// ----   TEST 2 - check treasure in hand  
		printf("TEST 2 - treasure cards in hand \n");
		
		// 2+ treasures to draw -> +2
		if (preDeckTreasureCount + preDiscardTreasureCount > 1)
			expected = preHandTreasureCount + 2;
		// 1 treasure to draw -> +1
		else if (preDeckTreasureCount + preDiscardTreasureCount == 1)
			expected = preHandTreasureCount + 1;
		// 0 treasure to draw -> 0
		else 
			expected = preHandTreasureCount;
		
		actual = postHandTreasureCount;
		assertTest(actual, expected, 2);
		
		// ----   TEST 3 - check cards in deck  
		printf("TEST 3 - number of cards in deck \n");
			
		// 2+ treasures to draw -> deck -discard -1
		if (preDeckTreasureCount > 1)
			expected = deckCount - (G.discardCount[player] - discardCount) - 1;
		// 1 treasure to draw -> deck -discard
		else if (preDeckTreasureCount == 1) {
			if (preDiscardTreasureCount > 0)
				expected = discardCount - (G.discardCount[player] - deckCount) - 1;
			else
				expected = 0;
		}
		// 0 treasure to draw -> 0
		else {
			if (preDiscardTreasureCount > 1)
				expected = discardCount - (G.discardCount[player] - deckCount) - 1;
			else if (preDiscardTreasureCount > 0)
				expected = discardCount - (G.discardCount[player] - deckCount);
			else
				expected = 0;
		}
		actual = G.deckCount[player];
		assertTest(actual, expected, 3);

		// ----   TEST 4 - check treasure in deck  
		printf("TEST 4 - treasure cards in deck \n");
		
		// 2+ treasures in deck -> -2
		if (preDeckTreasureCount > 1)
			expected = preDeckTreasureCount - 2;
		// 1 treasure in deck -> -1
		else if (preDeckTreasureCount == 1) {
			if (preDiscardTreasureCount > 0)
				expected = preDeckTreasureCount + preDiscardTreasureCount - 2;
			else
				expected = preDeckTreasureCount - 1;
		}
		// 0 treasure to draw -> 0
		else {
			if (preDiscardTreasureCount > 1)
				expected = preDeckTreasureCount + preDiscardTreasureCount - 2;
			else
				expected = preDeckTreasureCount;
		}
		actual = postDeckTreasureCount;
		assertTest(actual, expected, 4);			
		
		// ----  TEST 5 - check playedCardCount  
		printf("TEST 5 - played card count +1\n");
		// start with 0 played cards + 1 = 1
		expected = playedCount + 1;
		actual = G.playedCardCount;
		assertTest(actual, expected, 5);

		// ----  TEST 6 - check playedCardCount  
		printf("TEST 6 - coin count in hand\n");
		// check increase in coin count
		expected = postCoinCount - preCoinCount;
		actual = G.coins - preCoinCount;
		assertTest(actual, expected, 6);	

		// ----   TEST 7 - check playedCards  
		printf("TEST 7 - check adventurer in played cards\n");
		// adventurer card should be in playedCards array
		expected = 1;
		actual = 0;
		int i;
		for (i = 0; i < G.playedCardCount; i++) {
			if (G.playedCards[i] == adventurer) 
				actual = 1;
		}
		assertTest(actual, expected, 7);		
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
					
					// set played card count and whose turn
					playedCount = G.playedCardCount;
					G.whoseTurn = player;
					
					//assign cards in hand, deck, discard
					G.hand[player][0] = adventurer;
					for (j = 1; j < handCount; j++) {
						G.hand[player][j] = (rand() % 27);
					}
					for (j = 0; j < deckCount; j++) {
						G.deck[player][j] = (rand() % 27);
					}
					for (j = 0; j < discardCount; j++) {
						G.discard[player][j] = (rand() % 27);
					}
					
					// save pre-adventurer hand, deck, discard, coins
					preHandTreasureCount = handTreasureCount(G, player);
					preDeckTreasureCount = deckTreasureCount(G, player);
					preDiscardTreasureCount = discardTreasureCount(G, player);
					preCoinCount = coinCount(G, player);
					
					printf ("\nCALL #%d test Adventurer card\n", i+1);

					if (NOISY_TEST) {
						printf("\n\tNumber of players: 2 \n");
						printf("\n\tPlayer %d, before playing Adventurer: \n", player);
						printf("\tCards in hand: %d\n", G.handCount[player]);
						printf("\t\tTreasure cards in hand: %d\n", preHandTreasureCount);
						printf("\tCards in deck: %d\n", G.deckCount[player]);
						printf("\t\tTreasure cards in deck: %d\n", preDeckTreasureCount);
						printf("\tCards in discard: %d\n", G.discardCount[player]);
						printf("\t\tTreasure cards in discard: %d\n", preDiscardTreasureCount);
						printf("\tCoins in hand: %d\n", preCoinCount);
					}
					
					cardEffect(adventurer, -1, -1, -1, &G, 0, 0);

					// recalculate coins in hand
					updateCoins(player, &G, 0);
					
					// save post-adventurer hand, deck, discard, coins
					postHandTreasureCount = handTreasureCount(G, player);
					postDeckTreasureCount = deckTreasureCount(G, player);
					postDiscardTreasureCount = discardTreasureCount(G, player);
					postCoinCount = coinCount(G, player);

					if (NOISY_TEST)	{
						printf("\n\tPlayer %d, after playing Adventurer: \n", player);
						printf("\tCards in hand: %d\n", G.handCount[player]);
						printf("\t\tTreasure cards in hand: %d\n", postHandTreasureCount);
						printf("\tCards in deck: %d\n", G.deckCount[player]);
						printf("\t\tTreasure cards in deck: %d\n", postDeckTreasureCount);
						printf("\tCards in discard: %d\n", G.discardCount[player]);		
						printf("\t\tTreasure cards in discard: %d\n", postDiscardTreasureCount);
						printf("\tCoins in hand: %d\n\n", postCoinCount);
					}
					
					// ----   TEST 1 - check cards in hand  
					printf("TEST 1 - number of cards in hand \n");
					
					// 2+ treasures to draw -> hand +2 -1 = +1
					if (preDeckTreasureCount + preDiscardTreasureCount > 1)
						expected = handCount + 1;
					// 1 treasure to draw -> hand +1 -1 = 0
					else if (preDeckTreasureCount + preDiscardTreasureCount == 1)
						expected = handCount;
					// 0 treasure to draw -> hand +0 -1 = -1
					else 
						expected = handCount - 1;
					
					actual = G.handCount[player];
					assertTest(actual, expected, 1);
					
					// ----   TEST 2 - check treasure in hand  
					printf("TEST 2 - treasure cards in hand \n");
					
					// 2+ treasures to draw -> +2
					if (preDeckTreasureCount + preDiscardTreasureCount > 1)
						expected = preHandTreasureCount + 2;
					// 1 treasure to draw -> +1
					else if (preDeckTreasureCount + preDiscardTreasureCount == 1)
						expected = preHandTreasureCount + 1;
					// 0 treasure to draw -> 0
					else 
						expected = preHandTreasureCount;
					
					actual = postHandTreasureCount;
					assertTest(actual, expected, 2);
					
					// ----   TEST 3 - check cards in deck  
					printf("TEST 3 - number of cards in deck \n");
					
					// 2+ treasures to draw -> deck -discard -1
					if (preDeckTreasureCount > 1)
						expected = deckCount - (G.discardCount[player] - discardCount) - 1;
					// 1 treasure to draw -> deck -discard
					else if (preDeckTreasureCount == 1) {
						if (preDiscardTreasureCount > 0)
							expected = discardCount - (G.discardCount[player] - deckCount) - 1;
						else
							expected = 0;
					}
					// 0 treasure to draw -> 0
					else {
						if (preDiscardTreasureCount > 1)
							expected = discardCount - (G.discardCount[player] - deckCount) - 1;
						else if (preDiscardTreasureCount > 0)
							expected = discardCount - (G.discardCount[player] - deckCount);
						else
							expected = 0;
					}
					actual = G.deckCount[player];
					assertTest(actual, expected, 3);

					// ----   TEST 4 - check treasure in deck  
					printf("TEST 4 - treasure cards in deck \n");
					
					// 2+ treasures in deck -> -2
					if (preDeckTreasureCount > 1)
						expected = preDeckTreasureCount - 2;
					// 1 treasure in deck -> -1
					else if (preDeckTreasureCount == 1) {
						if (preDiscardTreasureCount > 0)
							expected = preDeckTreasureCount + preDiscardTreasureCount - 2;
						else
							expected = preDeckTreasureCount - 1;
					}
					// 0 treasure to draw -> 0
					else {
						if (preDiscardTreasureCount > 1)
							expected = preDeckTreasureCount + preDiscardTreasureCount - 2;
						else
							expected = preDeckTreasureCount;
					}
					
					actual = postDeckTreasureCount;
					assertTest(actual, expected, 4);			
					
					// ----  TEST 5 - check playedCardCount  
					printf("TEST 5 - played card count +1\n");
					// start with 0 played cards + 1 = 1
					expected = playedCount + 1;
					actual = G.playedCardCount;
					assertTest(actual, expected, 5);

					// ----  TEST 6 - check playedCardCount  
					printf("TEST 6 - coin count in hand\n");
					// check increase in coin count
					expected = postCoinCount - preCoinCount;
					actual = G.coins - preCoinCount;
					assertTest(actual, expected, 6);	
					
					// ----   TEST 7 - check playedCards  
					printf("TEST 7 - check adventurer in played cards\n");
					// adventurer card should be in playedCards array
					expected = 1;
					actual = 0;
					int i;
					for (i = 0; i < G.playedCardCount; i++) {
						if (G.playedCards[i] == adventurer) 
							actual = 1;
					}
					assertTest(actual, expected, 7);	
					
					i++;
				}		
			}
		}
	}

	printf("\n-------------- Testing Complete: Adventurer ----------------\n\n");

	return 0;
}