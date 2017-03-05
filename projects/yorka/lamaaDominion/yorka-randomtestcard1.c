/* *****************************************************************************
 * Antonina (Toni) York
 * OSU CS 362 Winter 2017
 * Assignment 4 Random Tester for Smithy
 * yorka-randomtestcard1.c
 *
 * REFACTORED for Assignment 5: Tests refacSmithy() in lamaa's dominion.c
 *
 *                usage: yorka-randomtestcard1 [optional seed value]
 * generate test report: make yorka-randomtestcard1.out
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

int countinplayed(int card, struct gameState *game) {
	int i = 0;
	int count = 0;
	for(i = 0; i < game->playedCardCount; i++)
		if(game->playedCards[i] == card)
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
	int card = province;
	int player = 0;
	int handPos = 0;
	int maxHandSize = 5;
	int startHandSize = 1;
	int startDeckSize = 15;
	int startActionCount = 1;
	int result = 0;
	int expected = 0;
	int numPlayers = 4;
	int allPassed = 1;
	
	int oldHandCounts[numPlayers-1];
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};
			   
	struct gameState game;
	
	printf("Testing refacSmithy()...\n\n");
	
	// loop through tests
	for(j = 0; j < NUM_TESTS; j++){
		// randomly decide which player to look at
		player = randint(0, numPlayers);
		// randomly decide which position in hand to place Smithy
		handPos = randint(0, maxHandSize);
		// ouptut header
		printif2("\n=== Testing player %d with hand position %d ===\n\n", player, handPos);
		// clear game state and initialize game
		memset(&game, 23, sizeof(struct gameState));
		result = initializeGame(numPlayers, k, seed, &game);
		// set up using randomized inputs
		game.whoseTurn = player;
		game.phase = 0;
		game.numActions = startActionCount;
		game.handCount[player] = startHandSize;
		game.hand[player][handPos] = smithy;
		for(i = 1; i < maxHandSize; i++)
			game.hand[player][i] = estate;
		game.deckCount[player] = startDeckSize;
		for(i = 0; i < startDeckSize; i++)
			game.deck[player][i] = card;
		refacSmithy(0, player, &game);
		// copy game state
		for(i = 0; i < numPlayers; i++)
			oldHandCounts[i] = game.handCount[i];
		// smithy removed from player's hand
		expected = 0;
		result = countinhand(smithy, player, &game);
		if(result != expected) {
			printif1("Player %d, Smithy removed from hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, Smithy removed from hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// simthy found in played pile
		expected = 1;
		result = countinplayed(smithy, &game);
		if(result != expected) {
			printif1("Player %d, Smithy found in played pile... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, Smithy found in played pile... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// 3 cards removed from player's deck
		expected = startDeckSize - 3;
		result = game.deckCount[player];
		if(result != expected) {
			printif1("Player %d, 3 cards removed from deck... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, 3 cards removed from deck... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// 3 cards added to player's hand
		expected = 3;
		result = countinhand(card, player, &game);
		if(result != expected) {
			printif1("Player %d, 3 cards added to hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, 3 cards added to hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// no changes to other players' hands
		expected = 0;
		result = 0;
		for(i = 0; i < numPlayers; i++)
			if(i != player)
				if(oldHandCounts[i] != game.handCount[i])
					result = 1;
		if(result != expected) {
			printif1("Player %d, other players unchanged... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, other players unchanged... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
	}
	
	if(PRINT_TESTS == 1)
		printf("\n");
	if(allPassed == 1)
		printf("All tests passed!\n");
	else printf("One or more tests failed!\n");
	
	return 0;
}