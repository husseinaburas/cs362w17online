/* *****************************************************************************
 * Antonina (Toni) York
 * OSU CS 362 Winter 2017
 * Assignment 3 Card Unit Test 1
 *
 * Tests playAdventurer() in dominion.c
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

void printif3(char* string, int value1, int value2, int value3) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2, value3);
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

int main() {
	
	int i = 0;
	int card = 0;
	int total = 0;
	int player = 0;
	int maxHandSize = 5;
	int startHandSize = 1;
	int startDeckSize = 15;
	int startActionCount = 1;
	int result = 0;
	int expected = 0;
	int seed = 1000;
	int numPlayers = 4;
	int allPassed = 1;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};
			   
	struct gameState game;
	
	printf("Testing playAdventurer()...\n\n");
	
	// check players 0, 1, 2, and 3
	for(player = 0; player < numPlayers; player++) {
		// for coppers, silvers, and golds, which are enum 4, 5, and 6
		for(card = 4; card < 7; card++) {
			// check cases where there are 2 to 4
			// but not 0 or 1 to avoid infinite loop bug
			for(total = 2; total < 5; total++) {
				// clear game state and initialize game
				memset(&game, 23, sizeof(struct gameState));
				result = initializeGame(numPlayers, k, seed, &game);
				
				// check case where cards are all in deck
				game.whoseTurn = player;
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
				playAdventurer(&game);
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
				
				// check case where cards are all in discards
				game.whoseTurn = player;
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
				playAdventurer(&game);
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
				
				// check case where 1 is in deck and rest are in discards
				game.whoseTurn = player;
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
				playAdventurer(&game);
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
			}
		}
	}
	
	if(PRINT_TESTS == 1)
		printf("\n");
	if(allPassed == 1)
		printf("All tests passed!\n");
	else printf("One or more tests failed!\n");
	
	return 0;
}