/* *****************************************************************************
 * Antonina (Toni) York
 * OSU CS 362 Winter 2017
 * Assignment 3 Card Unit Test 4
 *
 * REFACTORED for Assignment 5: Tests refacCouncilRoom() in lamaa's dominion.c
 * ************************************************************************** */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define PRINT_TESTS 0

void printif(char* string, int value1, int value2) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2);
}

void printif1(char* string, int value) {
	if(PRINT_TESTS == 1)
		printf(string, value);
}

void printif2(char* string, int value1, int value2) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2);
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

int main() {
	
	int i = 0;
	int card = province;
	int player = 0;
	int maxHandSize = 5;
	int startHandSize = 1;
	int startDeckSize = 15;
	int startActionCount = 1;
	int startBuyCount = 1;
	int result = 0;
	int expected = 0;
	int seed = 1000;
	int numPlayers = 4;
	int allPassed = 1;
	
	int oldHandCounts[numPlayers-1];
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};
			   
	struct gameState game;
	
	printf("Testing refacCouncilRoom()...\n\n");
	
	// check players 0, 1, 2, and 3
	for(player = 0; player < numPlayers; player++) {
		// clear game state and initialize game
		memset(&game, 23, sizeof(struct gameState));
		result = initializeGame(numPlayers, k, seed, &game);
		// set up
		game.whoseTurn = player;
		game.phase = 0;
		game.numActions = startActionCount;
		game.numBuys = startBuyCount;
		game.handCount[player] = startHandSize;
		game.hand[player][0] = council_room;
		for(i = 1; i < maxHandSize; i++)
			game.hand[player][i] = estate;
		game.deckCount[player] = startDeckSize;
		for(i = 0; i < startDeckSize; i++)
			game.deck[player][i] = card;
		refacCouncilRoom(player, &game);
		// copy game state
		for(i = 0; i < numPlayers; i++)
			oldHandCounts[i] = game.handCount[i];
		// council room removed from player's hand
		expected = 0;
		result = countinhand(council_room, player, &game);
		if(result != expected) {
			printif1("Player %d, Council Room removed from hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, Council Room removed from hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// council room found in played pile
		expected = 1;
		result = countinplayed(council_room, &game);
		if(result != expected) {
			printif1("Player %d, Council Room found in played pile... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, Council Room found in played pile... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// 4 cards removed from player's deck
		expected = startDeckSize - 4;
		result = game.deckCount[player];
		if(result != expected) {
			printif1("Player %d, 4 cards removed from deck... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, 4 cards removed from deck... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// 4 cards added to player's hand
		expected = 4;
		result = countinhand(card, player, &game);
		if(result != expected) {
			printif1("Player %d, 4 cards added to hand... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, 4 cards added to hand... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// buys increased by 1
		expected = startBuyCount + 1;
		result = game.numBuys;
		if(result != expected) {
			printif1("Player %d, buys increased by 1... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, buys increased by 1... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
		// other players' hands incremented
		expected = 0;
		result = 0;
		for(i = 0; i < numPlayers; i++)
			if(i != player)
				if(oldHandCounts[i] + 1 != game.handCount[i])
					result = 1;
		if(result != expected) {
			printif1("Player %d, other players' hands incremented... failed!\n", player);
			allPassed = 0;
		}
		else printif1("Player %d, other players' hands incremented... passed!\n", player);
		printif2("   Expected: %d   Actual: %d\n", expected, result);
	}
	
	if(PRINT_TESTS == 1)
		printf("\n");
	if(allPassed == 1)
		printf("All tests passed!\n");
	else printf("One or more tests failed!\n");
	
	return 0;
}