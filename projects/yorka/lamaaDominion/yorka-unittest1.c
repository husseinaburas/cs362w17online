/* *****************************************************************************
 * Antonina (Toni) York
 * OSU CS 362 Winter 2017
 * Assignment 3 Unit Test 1
 *
 * Tests discardCard() in dominion.c
 * ************************************************************************** */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define PRINT_TESTS 1

void printif1(char* string, int value) {
	if(PRINT_TESTS == 1)
		printf(string, value);
}

void printif2(char* string, int value1, int value2) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2);
}

int isindiscard(int card, int player, struct gameState *game) {
	int i = 0;
	int answer = 0;
	for(i = 0; i < game->discardCount[player]; i++) {
		if(game->discard[player][i] == card) {
			answer = 1;
			break;
		}
	}
	return answer;
}

int isinhand(int card, int player, struct gameState *game) {
	int i = 0;
	int answer = 0;
	for(i = 0; i < game->handCount[player]; i++) {
		if(game->hand[player][i] == card) {
			answer = 1;
			break;
		}
	}
	return answer;
}

int main() {
	
	int i = 0;
	int player = 0;
	int card = copper;
	int result = 0;
	int expected = 0;
	int maxHandCount = 5;
	int seed = 1000;
	int numPlayers = 4;
	int allPassed = 1;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};
			   
	struct gameState game;
	
	printf("Testing discardCard()...\n\n");
	
	// check players 0, 1, 2, and 3
	for(player = 0; player < numPlayers; player++) {
		// clear game state and initialize game
		memset(&game, 23, sizeof(struct gameState));
		result = initializeGame(numPlayers, k, seed, &game);
	
		// check case where card to discard is in first position
		game.handCount[player] = maxHandCount;
		for(i = 1; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.hand[player][0] = card;
		discardCard(0, player, &game, 0);
		// discarded card must be in player's discard pile
		expected = 1;
		result = isindiscard(card, player, &game);
		if(result != expected) {
			printif1("Player %d, discard first position, card in discard pile... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard first position, card in discard pile... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// discarded card must no longer be in player's hand
		expected = 0;
		result = isinhand(card, player, &game);
		if(result != expected) {
			printif1("Player %d, discard first position, card not in hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard first position, card not in hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// player's hand must be reduced by one
		expected = maxHandCount - 1;
		result = game.handCount[player];
		if(result != expected) {
			printif1("Player %d, discard first position, hand count reduced... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard first position, hand count reduced... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
	
		// check case where card to discard is in middle position
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.hand[player][maxHandCount / 2] = card;
		discardCard(maxHandCount / 2, player, &game, 0);
		// discarded card must be in player's discard pile
		expected = 1;
		result = isindiscard(card, player, &game);
		if(result != expected) {
			printif1("Player %d, discard middle position, card in discard pile... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard middle position, card in discard pile... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// discarded card must no longer be in player's hand
		expected = 0;
		result = isinhand(card, player, &game);
		if(result != expected) {
			printif1("Player %d, discard middle position, card not in hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard middle position, card not in hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// player's hand must be reduced by one
		expected = maxHandCount - 1;
		result = game.handCount[player];
		if(result != expected) {
			printif1("Player %d, discard middle position, hand count reduced... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard middle position, hand count reduced... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
	
		// check case where card to discard is in last position
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.hand[player][maxHandCount - 1] = card;
		discardCard(maxHandCount - 1, player, &game, 0);
		// discarded card must be in player's discard pile
		expected = 1;
		result = isindiscard(card, player, &game);
		if(result != expected) {
			printif1("Player %d, discard last position, card in discard pile... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard last position, card in discard pile... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// discarded card must no longer be in player's hand
		expected = 0;
		result = isinhand(card, player, &game);
		if(result != expected) {
			printif1("Player %d, discard last position, card not in hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard last position, card not in hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// player's hand must be reduced by one
		expected = maxHandCount - 1;
		result = game.handCount[player];
		if(result != expected) {
			printif1("Player %d, discard last position, hand count reduced... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard last position, hand count reduced... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where card to discard is only card in hand
		game.handCount[player] = 1;
		game.hand[player][0] = card;
		discardCard(0, player, &game, 0);
		// discarded card must be in player's discard pile
		expected = 1;
		result = isindiscard(card, player, &game);
		if(result != expected) {
			printif1("Player %d, discard only card, card in discard pile... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard only card, card in discard pile... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// discarded card must no longer be in player's hand
		expected = 0;
		result = isinhand(card, player, &game);
		if(result != expected) {
			printif1("Player %d, discard only card, card not in hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard only card, card not in hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// player's hand must be reduced by one
		expected = 0;
		result = game.handCount[player];
		if(result != expected) {
			printif1("Player %d, discard only card, hand count reduced... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, discard only card, hand count reduced... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where trash flag is set, card is only card in hand
		game.handCount[player] = 1;
		game.hand[player][0] = card;
		discardCard(0, player, &game, 1);
		// discarded card must not be in player's discard pile
		expected = 0;
		result = isindiscard(card, player, &game);
		if(result != expected) {
			printif1("Player %d, trash only card, card not in discard pile... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, trash only card, card not in discard pile... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// discarded card must no longer be in player's hand
		expected = 0;
		result = isinhand(card, player, &game);
		if(result != expected) {
			printif1("Player %d, trash only card, card not in hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, trash only card, card not in hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// player's hand must be reduced by one
		expected = 0;
		result = game.handCount[player];
		if(result != expected) {
			printif1("Player %d, trash only card, hand count reduced... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, trash only card, hand count reduced... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
	}
	
	if(PRINT_TESTS == 1)
		printf("\n");
	if(allPassed == 1)
		printf("All tests passed!\n");
	else printf("One or more tests failed!\n");
	
	return 0;
}