/* *****************************************************************************
 * Antonina (Toni) York
 * OSU CS 362 Winter 2017
 * Assignment 3 Unit Test 3
 *
 * Tests fullDeckCount() in dominion.c
 * ************************************************************************** */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define PRINT_TESTS 0

void printif1(char* string, int value) {
	if(PRINT_TESTS == 1)
		printf(string, value);
}

void printif2(char* string, int value1, int value2) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2);
}

int main() {
	
	int i = 0;
	int player = 0;
	int card = gardens;
	int result = 0;
	int expected = 0;
	int maxDeckCount = 15;
	int maxHandCount = 5;
	int maxDiscardCount = 15;
	int seed = 1000;
	int numPlayers = 4;
	int allPassed = 1;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};
			   
	struct gameState game;
	
	printf("Testing fullDeckCount()...\n\n");
	
	// check players 0, 1, 2, and 3
	for(player = 0; player < numPlayers; player++) {
		// clear game state and initialize game
		memset(&game, 23, sizeof(struct gameState));
		result = initializeGame(numPlayers, k, seed, &game);
		
		// check case where card is not in any pile
		game.deckCount[player] = maxDeckCount;
		for(i = 0; i < maxDeckCount; i++)
			game.deck[player][i] = estate;
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.discardCount[player] = maxDiscardCount;
		for(i = 0; i < maxDiscardCount; i++)
			game.discard[player][i] = estate;
		expected = 0;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card not in any pile... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card not in any pile... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where card is only in deck
		game.deckCount[player] = maxDeckCount;
		for(i = 0; i < maxDeckCount; i++)
			game.deck[player][i] = estate;
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.discardCount[player] = maxDiscardCount;
		for(i = 0; i < maxDiscardCount; i++)
			game.discard[player][i] = estate;
		expected = 1;
		// first position
		game.deck[player][0] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in deck, first position... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in deck, first position... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// middle position
		game.deck[player][0] = estate;
		game.deck[player][maxDeckCount / 2] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in deck, middle position... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in deck, middle position... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// last position
		game.deck[player][0] = estate;
		game.deck[player][maxDeckCount / 2] = estate;
		game.deck[player][maxDeckCount - 1] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in deck, last position... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in deck, last position... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where card is only in hand
		game.deckCount[player] = maxDeckCount;
		for(i = 0; i < maxDeckCount; i++)
			game.deck[player][i] = estate;
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.discardCount[player] = maxDiscardCount;
		for(i = 0; i < maxDiscardCount; i++)
			game.discard[player][i] = estate;
		expected = 1;
		// first position
		game.hand[player][0] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in hand, first position... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in hand, first position... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// middle position
		game.hand[player][0] = estate;
		game.hand[player][maxHandCount / 2] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in hand, middle position... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in hand, middle position... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// last position
		game.hand[player][0] = estate;
		game.hand[player][maxHandCount / 2] = estate;
		game.hand[player][maxHandCount - 1] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in hand, last position... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in hand, last position... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where card is only in discards
		game.deckCount[player] = maxDeckCount;
		for(i = 0; i < maxDeckCount; i++)
			game.deck[player][i] = estate;
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.discardCount[player] = maxDiscardCount;
		for(i = 0; i < maxDiscardCount; i++)
			game.discard[player][i] = estate;
		expected = 1;
		// first position
		game.discard[player][0] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in discard, first position... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in discard, first position... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// middle position
		game.discard[player][0] = estate;
		game.discard[player][maxDiscardCount / 2] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in discard, middle position... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in discard, middle position... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// last position
		game.discard[player][0] = estate;
		game.discard[player][maxDiscardCount / 2] = estate;
		game.discard[player][maxDiscardCount - 1] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in discard, last position... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in discard, last position... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where card is in both deck and hand
		game.deckCount[player] = maxDeckCount;
		for(i = 0; i < maxDeckCount; i++)
			game.deck[player][i] = estate;
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.discardCount[player] = maxDiscardCount;
		for(i = 0; i < maxDiscardCount; i++)
			game.discard[player][i] = estate;
		expected = 2;
		game.deck[player][0] = card;
		game.hand[player][0] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in deck and hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in deck and hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where card is in both deck and discards
		game.deckCount[player] = maxDeckCount;
		for(i = 0; i < maxDeckCount; i++)
			game.deck[player][i] = estate;
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.discardCount[player] = maxDiscardCount;
		for(i = 0; i < maxDiscardCount; i++)
			game.discard[player][i] = estate;
		expected = 2;
		game.deck[player][0] = card;
		game.discard[player][0] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in deck and discards... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in deck and discards... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where card is in both hand and discards
		game.deckCount[player] = maxDeckCount;
		for(i = 0; i < maxDeckCount; i++)
			game.deck[player][i] = estate;
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.discardCount[player] = maxDiscardCount;
		for(i = 0; i < maxDiscardCount; i++)
			game.discard[player][i] = estate;
		expected = 2;
		game.hand[player][0] = card;
		game.discard[player][0] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in hand and discards... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in hand and discards... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where card is in all three piles
		game.deckCount[player] = maxDeckCount;
		for(i = 0; i < maxDeckCount; i++)
			game.deck[player][i] = estate;
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.discardCount[player] = maxDiscardCount;
		for(i = 0; i < maxDiscardCount; i++)
			game.discard[player][i] = estate;
		expected = 3;
		game.deck[player][0] = card;
		game.hand[player][0] = card;
		game.discard[player][0] = card;
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in all three piles... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in all three piles... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		
		// check case where three of card are in each pile
		game.deckCount[player] = maxDeckCount;
		for(i = 0; i < maxDeckCount; i++)
			game.deck[player][i] = estate;
		game.handCount[player] = maxHandCount;
		for(i = 0; i < maxHandCount; i++)
			game.hand[player][i] = estate;
		game.discardCount[player] = maxDiscardCount;
		for(i = 0; i < maxDiscardCount; i++)
			game.discard[player][i] = estate;
		expected = 9;
		for(i = 0; i < 3; i++) {
			game.deck[player][i] = card;
			game.hand[player][i] = card;
			game.discard[player][i] = card;
		}
		result = fullDeckCount(player, card, &game);
		if(result != expected) {
			printif1("Player %d, card in all three piles... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, card in all three piles... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
	}
	
	if(PRINT_TESTS == 1)
		printf("\n");
	if(allPassed == 1)
		printf("All tests passed!\n");
	else printf("One or more tests failed!\n");
	
	return 0;
}