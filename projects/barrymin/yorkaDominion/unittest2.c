/* *****************************************************************************
 * Antonina (Toni) York
 * OSU CS 362 Winter 2017
 * Assignment 3 Unit Test 2
 *
 * Tests updateCoins() in dominion.c
 * ************************************************************************** */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define COPPER_VALUE 1
#define SILVER_VALUE 2
#define GOLD_VALUE 3

#define PRINT_TESTS 0

void printif(char* string, int value1, int value2) {
	if(PRINT_TESTS == 1)
		printf(string, value1, value2);
}

int main() {
	
	int i = 0;
	int player = 0;
	int bonus = 0;
	int result = 0;
	int expected = 0;
	int maxHandCount = 5;
	int seed = 1000;
	int numPlayers = 4;
	int allPassed = 1;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};
			   
	struct gameState game;
	
	// bizarre shenanigans to get rid of annoying warnings
	bonus = result;
	
	printf ("Testing updateCoins()...\n\n");
	
	// check players 0, 1, 2, and 3
	for(player = 0; player < numPlayers; player++) {
		// check cases where bonus is 0, 1, and 2
		for(bonus = 0; bonus < 3; bonus++) {
			// clear game state, initialize game and player's hand count
			memset(&game, 23, sizeof(struct gameState));
			result = initializeGame(numPlayers, k, seed, &game);
			game.handCount[player] = maxHandCount;

			// check case where player has no coins in hand
			expected = bonus;
			for(i = 0; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, no coins... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, no coins... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has one copper in first position of hand
			expected = COPPER_VALUE + bonus;
			for(i = 0; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			game.hand[player][0] = copper;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, one copper in first position... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, one copper in first position... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has one copper in middle position of hand
			expected = COPPER_VALUE + bonus;
			for(i = 0; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			game.hand[player][maxHandCount / 2] = copper;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, one copper in mid position... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, one copper in mid position... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has one copper in last position of hand
			expected = COPPER_VALUE + bonus;
			for(i = 0; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			game.hand[player][maxHandCount - 1] = copper;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, one copper in last position... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, one copper in last position... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has one silver in first position of hand
			expected = SILVER_VALUE + bonus;
			for(i = 0; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			game.hand[player][0] = silver;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, one silver in first position... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, one silver in first position... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has one gold in first position of hand
			expected = GOLD_VALUE + bonus;
			for(i = 0; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			game.hand[player][0] = gold;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, one gold in first position... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, one gold in first position... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has three coppers in hand
			expected = (3 * COPPER_VALUE) + bonus;
			for(i = 0; i < 3; i++)
				game.hand[player][i] = copper;
			for(i = 3; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, three coppers... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, three coppers... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has three silvers in hand
			expected = (3 * SILVER_VALUE) + bonus;
			for(i = 0; i < 3; i++)
				game.hand[player][i] = silver;
			for(i = 3; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, three silvers... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, three silvers... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has three golds in hand
			expected = (3 * GOLD_VALUE) + bonus;
			for(i = 0; i < 3; i++)
				game.hand[player][i] = gold;
			for(i = 3; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, three golds... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, three golds... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has one copper and one silver in hand
			expected = (COPPER_VALUE + SILVER_VALUE) + bonus;
			for(i = 2; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			game.hand[player][0] = copper;
			game.hand[player][1] = silver;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, one copper and one silver... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, one copper and one silver... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has one copper and one gold in hand
			expected = (COPPER_VALUE + GOLD_VALUE) + bonus;
			for(i = 2; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			game.hand[player][0] = copper;
			game.hand[player][1] = gold;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, one copper and one gold... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, one copper and one gold... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has one silver and one gold in hand
			expected = (SILVER_VALUE + GOLD_VALUE) + bonus;
			for(i = 2; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			game.hand[player][0] = silver;
			game.hand[player][1] = gold;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, one silver and one gold... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, one silver and one gold... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has one of each in hand
			expected = (COPPER_VALUE + SILVER_VALUE + GOLD_VALUE) + bonus;
			for(i = 3; i < maxHandCount; i++)
				game.hand[player][i] = estate;
			game.hand[player][0] = copper;
			game.hand[player][1] = silver;
			game.hand[player][2] = gold;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, one of each... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, one of each... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has all coppers in hand
			expected = (maxHandCount * COPPER_VALUE) + bonus;
			for(i = 0; i < maxHandCount; i++)
				game.hand[player][i] = copper;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, all coppers... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, all coppers... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has all silvers in hand
			expected = (maxHandCount * SILVER_VALUE) + bonus;
			for(i = 0; i < maxHandCount; i++)
				game.hand[player][i] = silver;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, all silvers... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, all silvers... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where player has all golds in hand
			expected = (maxHandCount * GOLD_VALUE) + bonus;
			for(i = 0; i < maxHandCount; i++)
				game.hand[player][i] = gold;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, all golds... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, all golds... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
			
			// check case where hand is completely empty
			expected = bonus;
			game.handCount[player] = 0;
			updateCoins(player, &game, bonus);
			if(game.coins != expected) {
				printif("Player %d with bonus %d, empty hand... failed!\n", player, bonus);
				allPassed = 0;
			}
			else printif("Player %d with bonus %d, empty hand... passed!\n", player, bonus);
			printif("   Expected: %d   Actual: %d\n", expected, game.coins);
		}
	}
	
    if(PRINT_TESTS == 1)
		printf("\n");
	if(allPassed == 1)
		printf("All tests passed!\n");
	else printf("One or more tests failed!\n");

    return 0;
}