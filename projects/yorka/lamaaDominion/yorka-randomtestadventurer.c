/* *****************************************************************************
 * Antonina (Toni) York
 * OSU CS 362 Winter 2017
 * Assignment 4 Random Tester for Adventurer
 * yorka-randomtestadventurer.c
 *
 * REFACTORED for Assignment 5:
 *		Randomly tests refacAdventurer() in lamaa's dominion.c
 *
 *                usage: yorka-randomtestadventurer [optional seed value]
 * generate test report: make yorka-randomtestadventurer.out
 * ************************************************************************** */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define PRINT_TESTS 0		// 1 to turn on printing test outputs to console
#define NUM_TESTS 100		// number of random tests to generate and run
#define SEED_VALUE 1000		// default seed value for random number generation

void printif1(char* string, int value) {
	if(PRINT_TESTS == 1)
		printf(string, value);
}

void printif2(char* string, int value1, int value2) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2);
}

void printif3(char* string, int value1, int value2, int value3) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2, value3);
}

void printif4(char* string, int value1, int value2, int value3, int value4) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2, value3, value4);
}

// returns a pseudorandom integer in [min, max)
int randint(int min, int max) {
	return rand() % (max - min) + min;
}

int countinhand(int card, int player, struct gameState *game) {
	int i = 0;
	int count = 0;
	for(i = 0; i < game->handCount[player]; i++)
		if(game->hand[player][i] == card)
			count++;
	return count;
}

int countindeck(int card, int player, struct gameState *game) {
	int i = 0;
	int count = 0;
	for(i = 0; i < game->deckCount[player]; i++)
		if(game->deck[player][i] == card)
			count++;
	return count;
}

int main(int argc, char **argv) {
	
	// get random seed
	int seed = 0;
	if(argc > 1)
		seed = atoi(argv[1]);
	else seed = SEED_VALUE;
	
	// set up random number generator
	srand(seed);
	
	int i = 0;
	int j = 0;
	int card = 0;
	int total = 0;
	int player = 0;
	int maxHandSize = 5;
	int startHandSize = 1;
	int startDeckSize = 15;
	int startActionCount = 1;
	int maxStartTreasures = 5;
	int treasureState = 0;
	int result = 0;
	int expected = 0;
	int numPlayers = 4;
	int allPassed = 1;
	
	// variables needed to refactor to match lamaa's way of calling the card fn
	int currentPlayer = 0;
	int temphand[MAX_HAND];
	int drawntreasure = 0;
	int cardDrawn = 0;
	int z = 0;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};
			   
	struct gameState game;
	
	printf("Testing refacAdventurer()...\n\n");
	
	// loop through tests
	for(j = 0; j < NUM_TESTS; j++) {
		// randomly decide which player to look at
		player = randint(0, numPlayers);
		// randomly decide which treasure card to look at
		// options: coppers, silvers, and golds, which are enum 4, 5, and 6
		card = randint(4, 7);
		// randomly decide how many of these to generate
		// do not try 0 and 1 cases b/c of known bug (see Assignment 4 report)
		total = randint(2, maxStartTreasures);
		// randomly decide where these cards are located for this test
		// case 1 - all in deck
		// case 2 - all in discards
		// case 3 - one in deck and the rest in discards
		treasureState = randint(1, 4);
		// ouptut header
		printif4("\n=== Testing player %d with %d of card %d in state %d ===\n\n", player, total, card, treasureState);
		// clear game state and initialize game
		memset(&game, 23, sizeof(struct gameState));
		result = initializeGame(numPlayers, k, seed, &game);
		// run test depending on which treasureState was generated
		switch(treasureState) {
			// case where cards are all in deck
			case 1: game.whoseTurn = player;
					game.phase = 0;
					game.numActions = startActionCount;
					game.handCount[player] = startHandSize;
					game.hand[player][0] = adventurer;
					for(i = 1; i < maxHandSize; i++)
						game.hand[player][i] = estate;
					game.deckCount[player] = startDeckSize;
					for(i = 0; i < total; i++)
						game.deck[player][i] = card;
					for(i = total; i < startDeckSize; i++)
						game.deck[player][i] = estate;
					// initialize variables for lamaa's way of calling the card fn
					currentPlayer = whoseTurn(state);
					drawntreasure = 0;
					cardDrawn = 0;
					z = 0; // this is the counter for the temp hand
					refacAdventurer(drawntreasure, &game, currentPlayer, cardDrawn, temphand, z);
					// cards added to player's hand
					expected = 2;
					result = countinhand(card, player, &game);
					if(result != expected) {
						printif3("Player %d, %d of card %d, all in deck, added to hand... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, all in deck, added to hand... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					// player's hand size adjusted correctly
					expected = startHandSize - 1 + 2; // Adventurer removed, 2 treasure gained
					result = game.handCount[player];
					if(result != expected) {
						printif3("Player %d, %d of card %d, all in deck, hand size adjusted... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, all in deck, hand size adjusted... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					// cards removed from player's deck
					expected = 0;
					result = countindeck(card, player, &game);
					if(result != expected) {
						printif3("Player %d, %d of card %d, all in deck, removed from deck... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, all in deck, removed from deck... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					// player's deck size decreased correctly
					expected = startDeckSize - 2;
					result = game.deckCount[player];
					if(result != expected) {
						printif3("Player %d, %d of card %d, all in deck, deck size adjusted... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, all in deck, deck size adjusted... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					break;
					
			// case where cards are all in discards
			case 2: game.whoseTurn = player;
					game.phase = 0;
					game.numActions = startActionCount;
					game.handCount[player] = startHandSize;
					game.hand[player][0] = adventurer;
					for(i = 1; i < maxHandSize; i++)
						game.hand[player][i] = estate;
					game.deckCount[player] = startDeckSize - total;
					for(i = 0; i < startDeckSize - total; i++)
						game.deck[player][i] = estate;
					game.discardCount[player] = total;
					for(i = 0; i < total; i++)
						game.discard[player][i] = card;
					// initialize variables for lamaa's way of calling the card fn
					currentPlayer = whoseTurn(state);
					drawntreasure = 0;
					cardDrawn = 0;
					z = 0; // this is the counter for the temp hand
					refacAdventurer(drawntreasure, &game, currentPlayer, cardDrawn, temphand, z);
					// cards added to player's hand
					expected = 2;
					result = countinhand(card, player, &game);
					if(result != expected) {
						printif3("Player %d, %d of card %d, all in discard, added to hand... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, all in discard, added to hand... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					// player's hand size increased correctly
					expected = startHandSize - 1 + 2; // Adventurer removed, 2 treasure gained
					result = game.handCount[player];
					if(result != expected) {
						printif3("Player %d, %d of card %d, all in discard, hand size adjusted... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, all in discard, hand size adjusted... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					// cards removed from player's deck
					expected = 0;
					result = countindeck(card, player, &game);
					if(result != expected) {
						printif3("Player %d, %d of card %d, all in discard, removed from deck... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, all in discard, removed from deck... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					// player's deck size decreased correctly
					expected = startDeckSize - total - 2;
					result = game.deckCount[player];
					if(result != expected) {
						printif3("Player %d, %d of card %d, all in discard, deck size adjusted... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, all in discard, deck size adjusted... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					break;
					
			// case where 1 is in deck and rest are in discards
			case 3: game.whoseTurn = player;
					game.phase = 0;
					game.numActions = startActionCount;
					game.handCount[player] = startHandSize;
					game.hand[player][0] = adventurer;
					for(i = 1; i < maxHandSize; i++)
						game.hand[player][i] = estate;
					game.deckCount[player] = startDeckSize - (total - 1);
					game.deck[player][0] = card;
					for(i = 1; i < startDeckSize - (total - 1); i++)
						game.deck[player][i] = estate;
					game.discardCount[player] = (total - 1);
					for(i = 0; i < (total - 1); i++)
						game.discard[player][i] = card;
					// initialize variables for lamaa's way of calling the card fn
					currentPlayer = whoseTurn(state);
					drawntreasure = 0;
					cardDrawn = 0;
					z = 0; // this is the counter for the temp hand
					refacAdventurer(drawntreasure, &game, currentPlayer, cardDrawn, temphand, z);
					// cards added to player's hand
					expected = 2;
					result = countinhand(card, player, &game);
					if(result != expected) {
						printif3("Player %d, %d of card %d, one in deck, added to hand... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, one in deck, added to hand... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					// player's hand size increased correctly
					expected = startHandSize - 1 + 2; // Adventurer removed, 2 treasure gained
					result = game.handCount[player];
					if(result != expected) {
						printif3("Player %d, %d of card %d, one in deck, hand size adjusted... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, one in deck, hand size adjusted... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					// cards removed from player's deck
					expected = 0;
					result = countindeck(card, player, &game);
					if(result != expected) {
						printif3("Player %d, %d of card %d, one in deck, removed from deck... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, one in deck, removed from deck... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					// player's deck size decreased correctly
					expected = startDeckSize - (total - 1) - 2;
					result = game.deckCount[player];
					if(result != expected) {
						printif3("Player %d, %d of card %d, one in deck, deck size adjusted... failed!\n", player, total, card);
						allPassed = 0;
					}
					else printif3("Player %d, %d of card %d, one in deck, deck size adjusted... passed!\n", player, total, card);
					printif2("   Expected: %d   Actual: %d\n", expected, result);
					break;
					
			// default case - should never see this
			default: printf("Something went terribly awry with treasureState!\n");
		}
	}
	
	if(PRINT_TESTS == 1)
		printf("\n");
	if(allPassed == 1)
		printf("All tests passed!\n");
	else printf("One or more tests failed!\n");
	
	return 0;
}