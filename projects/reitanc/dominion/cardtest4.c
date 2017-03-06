/*
 * cardtest4.c
 *
 * Based off a model for testing a card that was provided in class portal.
 * Adapted for the use of the cards that were being tested in Assignment 3
 * Oregon State University - CS 362 Winter 2017
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

int main() {
	int ReturnValue = 0;
    int newCards = 1;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int numActions = 1;
    int FoundCard = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 2000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);

	memcpy(&testG, &G, sizeof(struct gameState));

	ReturnValue = cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded + newCards);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	printf("numActions count = %d, expected = %d\n", testG.numActions, G.numActions + numActions);

	if (testG.numActions == (G.numActions + numActions))
		printf("SUCCESS - Player Action Count is Correct after playing Great Hall.\n");
	else
		printf("FAIL - Player Action Count is NOT Correct after playing Great Hall.\n");

	if (testG.handCount[thisPlayer] == (G.handCount[thisPlayer] - discarded + newCards))
		printf("SUCCESS - Player Hand Count is Correct after playing Great Hall.\n");
	else
		printf("FAIL - Player Hand Count is NOT Correct after playing Great Hall.\n");

	if (testG.deckCount[thisPlayer] == (G.deckCount[thisPlayer] - newCards + shuffledCards))
		printf("SUCCESS - Player Deck Count is Correct after playing Great Hall.\n");
	else
		printf("FAIL - Player Deck Count is NOT Correct after playing Great Hall.\n");

	if (testG.discardCount[thisPlayer] == (G.discardCount[thisPlayer] + discarded))
		printf("SUCCESS - Player Discard Count is Correct after playing Great Hall.\n");
	else
		printf("FAIL - Player Discard Count is NOT Correct after playing Great Hall.\n");


	for (i = 0; i < testG.handCount[thisPlayer]; i++){
		if(testG.hand[thisPlayer][i] == great_hall){
			FoundCard = 1;
		}
	}	
	if (FoundCard == 1)
		printf("Great Hall card was found in the player hand.\n");
	else
		printf("Great Hall card was NOT found in the player hand.\n");

	// Reset for the next search
	FoundCard = 0;
	for (i = 0; i < testG.deckCount[thisPlayer]; i++){
		if(testG.deck[thisPlayer][i] == great_hall){
			FoundCard = 1;
		}
	}	
	if (FoundCard == 1)
		printf("Great Hall card was found in the player deck.\n");
	else
		printf("Great Hall card was NOT found in the player deck.\n");

	// Reset for the next search
	FoundCard = 0;
	for (i = 0; i < testG.discardCount[thisPlayer]; i++){
		if(testG.discard[thisPlayer][i] == great_hall){
			FoundCard = 1;
		}
	}
	if (FoundCard == 1)
		printf("Great Hall card was found in the player discard.\n");
	else
		printf("Great Hall card was NOT found in the player discard.\n");

	printf("\n >>>>> COMPLETE: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


