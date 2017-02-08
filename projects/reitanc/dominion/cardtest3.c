/*
 * cardtest3.c
 *
 * Based off a model for testing a card that was provided in class portal.
 * Adapted for the use of the cards that were being tested in Assignment 3
 * Oregon State University - CS 362 Winter 2017
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

int main() {
	int ReturnValue = 0;
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int FoundCard = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1500;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	discarded = 1;


	// TEST 1 Setup
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 3;

	// BEGIN Test Segment
	ReturnValue = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (ReturnValue == -1)
	{
		printf("\n --- FAILED: Testing %s card. ReturnValue == -1   ---\n", TESTCARD);
	}else{
		FoundCard = 0;
		for (i = 0; i < G.handCount[thisPlayer]; i++)
		{
			if (G.hand[thisPlayer][i] == choice2)
			{
				FoundCard = 1;
			}
		}
		if (FoundCard == 0)
		{
			printf("\n --- FAILED: Testing %s card. FoundCard == 0 for player's hand.   ---\n", TESTCARD);
		}else{
			FoundCard = 0;
			for (i = 0; i < testG.discardCount[thisPlayer]; i++){
					if(testG.discard[thisPlayer][i] == mine){
						// Found the Mine Card in the Discard pile.
						FoundCard = 1;
					}
				}

			if ((testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - discarded) &&
					FoundCard == 1)
			{
				printf("\n --- SUCCESS: Testing %s card. FoundCard in player hand & mine card in discard.  ---\n", TESTCARD);
			}else{
				printf("\n --- FAIL: Testing %s card. FoundCard in player hand AND NOT a mine card in discard.  ---\n", TESTCARD);
			}
		}
	} 
	// END Test Segment

	// TEST 2 Setup
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 4;

	// BEGIN Test Segment
	ReturnValue = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (ReturnValue == -1)
	{
		printf("\n --- FAILED: Testing %s card. ReturnValue == -1   ---\n", TESTCARD);
	}else{
		FoundCard = 0;
		for (i = 0; i < G.handCount[thisPlayer]; i++)
		{
			if (G.hand[thisPlayer][i] == choice2)
			{
				FoundCard = 1;
			}
		}
		if (FoundCard == 0)
		{
			printf("\n --- FAILED: Testing %s card. FoundCard == 0 for player's hand.   ---\n", TESTCARD);
		}else{
			FoundCard = 0;
			for (i = 0; i < testG.discardCount[thisPlayer]; i++){
					if(testG.discard[thisPlayer][i] == mine){
						// Found the Mine Card in the Discard pile.
						FoundCard = 1;
					}
				}

			if ((testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - discarded) &&
					FoundCard == 1)
			{
				printf("\n --- SUCCESS: Testing %s card. FoundCard in player hand & mine card in discard.  ---\n", TESTCARD);
			}else{
				printf("\n --- FAIL: Testing %s card. FoundCard in player hand AND NOT a mine card in discard.  ---\n", TESTCARD);
			}
		}
	} 
	// END Test Segment


	// TEST 3 Setup
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 5;

	// BEGIN Test Segment
	ReturnValue = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (ReturnValue == -1)
	{
		printf("\n --- FAILED: Testing %s card. ReturnValue == -1   ---\n", TESTCARD);
	}else{
		FoundCard = 0;
		for (i = 0; i < G.handCount[thisPlayer]; i++)
		{
			if (G.hand[thisPlayer][i] == choice2)
			{
				FoundCard = 1;
			}
		}
		if (FoundCard == 0)
		{
			printf("\n --- FAILED: Testing %s card. FoundCard == 0 for player's hand.   ---\n", TESTCARD);
		}else{
			FoundCard = 0;
			for (i = 0; i < testG.discardCount[thisPlayer]; i++){
					if(testG.discard[thisPlayer][i] == mine){
						// Found the Mine Card in the Discard pile.
						FoundCard = 1;
					}
				}

			if ((testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - discarded) &&
					FoundCard == 1)
			{
				printf("\n --- SUCCESS: Testing %s card. FoundCard in player hand & mine card in discard.  ---\n", TESTCARD);
			}else{
				printf("\n --- FAIL: Testing %s card. FoundCard in player hand AND NOT a mine card in discard.  ---\n", TESTCARD);
			}
		}
	} 
	// END Test Segment

	// TEST 4 Setup
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	choice2 = 13;

	// BEGIN Test Segment
	ReturnValue = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (ReturnValue == -1)
	{
		printf("\n --- FAILED: Testing %s card. ReturnValue == -1   ---\n", TESTCARD);
	}else{
		FoundCard = 0;
		for (i = 0; i < G.handCount[thisPlayer]; i++)
		{
			if (G.hand[thisPlayer][i] == choice2)
			{
				FoundCard = 1;
			}
		}
		if (FoundCard == 0)
		{
			printf("\n --- FAILED: Testing %s card. FoundCard == 0 for player's hand.   ---\n", TESTCARD);
		}else{
			FoundCard = 0;
			for (i = 0; i < testG.discardCount[thisPlayer]; i++){
					if(testG.discard[thisPlayer][i] == mine){
						// Found the Mine Card in the Discard pile.
						FoundCard = 1;
					}
				}

			if ((testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - discarded) &&
					FoundCard == 1)
			{
				printf("\n --- SUCCESS: Testing %s card. FoundCard in player hand & mine card in discard.  ---\n", TESTCARD);
			}else{
				printf("\n --- FAIL: Testing %s card. FoundCard in player hand AND NOT a mine card in discard.  ---\n", TESTCARD);
			}
		}
	} 
	// END Test Segment

	// TEST 5 Setup
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 7;
	choice2 = 17;

	// BEGIN Test Segment
	ReturnValue = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (ReturnValue == -1)
	{
		printf("\n --- FAILED: Testing %s card. ReturnValue == -1   ---\n", TESTCARD);
	}else{
		FoundCard = 0;
		for (i = 0; i < G.handCount[thisPlayer]; i++)
		{
			if (G.hand[thisPlayer][i] == choice2)
			{
				FoundCard = 1;
			}
		}
		if (FoundCard == 0)
		{
			printf("\n --- FAILED: Testing %s card. FoundCard == 0 for player's hand.   ---\n", TESTCARD);
		}else{
			FoundCard = 0;
			for (i = 0; i < testG.discardCount[thisPlayer]; i++){
					if(testG.discard[thisPlayer][i] == mine){
						// Found the Mine Card in the Discard pile.
						FoundCard = 1;
					}
				}

			if ((testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - discarded) &&
					FoundCard == 1)
			{
				printf("\n --- SUCCESS: Testing %s card. FoundCard in player hand & mine card in discard.  ---\n", TESTCARD);
			}else{
				printf("\n --- FAIL: Testing %s card. FoundCard in player hand AND NOT a mine card in discard.  ---\n", TESTCARD);
			}
		}
	} 
	// END Test Segment

	// TEST 6 Setup
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 4;
	choice2 = -1;

	// BEGIN Test Segment
	ReturnValue = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (ReturnValue == -1)
	{
		printf("\n --- FAILED: Testing %s card. ReturnValue == -1   ---\n", TESTCARD);
	}else{
		FoundCard = 0;
		for (i = 0; i < G.handCount[thisPlayer]; i++)
		{
			if (G.hand[thisPlayer][i] == choice2)
			{
				FoundCard = 1;
			}
		}
		if (FoundCard == 0)
		{
			printf("\n --- FAILED: Testing %s card. FoundCard == 0 for player's hand.   ---\n", TESTCARD);
		}else{
			FoundCard = 0;
			for (i = 0; i < testG.discardCount[thisPlayer]; i++){
					if(testG.discard[thisPlayer][i] == mine){
						// Found the Mine Card in the Discard pile.
						FoundCard = 1;
					}
				}

			if ((testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - discarded) &&
					FoundCard == 1)
			{
				printf("\n --- SUCCESS: Testing %s card. FoundCard in player hand & mine card in discard.  ---\n", TESTCARD);
			}else{
				printf("\n --- FAIL: Testing %s card. FoundCard in player hand AND NOT a mine card in discard.  ---\n", TESTCARD);
			}
		}
	} 
	// END Test Segment

	// TEST 7 Setup
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 5;
	choice2 = 50;

	// BEGIN Test Segment
	ReturnValue = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (ReturnValue == -1)
	{
		printf("\n --- FAILED: Testing %s card. ReturnValue == -1   ---\n", TESTCARD);
	}else{
		FoundCard = 0;
		for (i = 0; i < G.handCount[thisPlayer]; i++)
		{
			if (G.hand[thisPlayer][i] == choice2)
			{
				FoundCard = 1;
			}
		}
		if (FoundCard == 0)
		{
			printf("\n --- FAILED: Testing %s card. FoundCard == 0 for player's hand.   ---\n", TESTCARD);
		}else{
			FoundCard = 0;
			for (i = 0; i < testG.discardCount[thisPlayer]; i++){
					if(testG.discard[thisPlayer][i] == mine){
						// Found the Mine Card in the Discard pile.
						FoundCard = 1;
					}
				}

			if ((testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - discarded) &&
					FoundCard == 1)
			{
				printf("\n --- SUCCESS: Testing %s card. FoundCard in player hand & mine card in discard.  ---\n", TESTCARD);
			}else{
				printf("\n --- FAIL: Testing %s card. FoundCard in player hand AND NOT a mine card in discard.  ---\n", TESTCARD);
			}
		}
	} 
	// END Test Segment

	printf("\n >>>>> COMPLETED: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


