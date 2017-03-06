/*
	unittest4.c: Testing the isGameOver() method.
	
	Description: The isGameOver method tests if the game is over. The game is over if the stack of Province cards is 
	empty or if 3 supply piles are at 0.
	
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assertion.h"
#include <time.h>

int main() {
	printf("\n***********BEGINNING isGameOver() TESTING**********\n\n");
	struct gameState testGame, gameCopy;
	int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
	int numPlayers = 2;
	initializeGame(numPlayers, k, 10, &testGame);
	int currentPlayer = testGame.whoseTurn;
	
	//Testing if game is over with just one supply pile containing cards
	printf("Testing if game is over if just the treasure_map supply pile contains cards\nExpected result: Game Over (return 1).\n");
	int i;
	for (i = 0; i < treasure_map+1; i++)
	{
		testGame.supplyCount[i] = 0;
	}
	//Setting treasure map supply count to 10
	testGame.supplyCount[treasure_map] = 10;
	
	assertion(isGameOver(&testGame) == 1);
	
	//Testing if game is over with all the supply piles containing cards
	printf("Testing if game is over with all the supply piles containing cards\nExpected result: Game Not Over (return 0).\n");
	for (i = 0; i < treasure_map+1; i++)
	{
		testGame.supplyCount[i] = 5;
	}
	assertion(isGameOver(&testGame) == 0);
	
	//Testing if game is over with all the supply piles but one containing cards
	printf("Testing if game is over with all the supply piles but one containing cards\nExpected result: Game Not Over (return 0).\n");
	for (i = 0; i < treasure_map+1; i++)
	{
		testGame.supplyCount[i] = 5;
	}
	testGame.supplyCount[curse] = 0;
	assertion(isGameOver(&testGame) == 0);
	
	//Testing if game is over with all the supply piles but two containing cards
	printf("Testing if game is over with all the supply piles but two containing cards\nExpected result: Game Not Over (return 0).\n");
	for (i = 0; i < treasure_map+1; i++)
	{
		testGame.supplyCount[i] = 5;
	}
	testGame.supplyCount[gold] = 0;
	testGame.supplyCount[estate] = 0;
	assertion(isGameOver(&testGame) == 0);
	
	
	//Testing if game is over with all the supply piles but three containing cards
	printf("Testing if game is over with all the supply piles but three containing cards\nExpected result: Game Over (return 1).\n");
	for (i = 0; i < treasure_map+1; i++)
	{
		testGame.supplyCount[i] = 5;
	}
	testGame.supplyCount[curse] = 0;
	testGame.supplyCount[duchy] = 0;
	testGame.supplyCount[silver] = 0;
	assertion(isGameOver(&testGame) == 1);
	
	//Testing if game is over with all the supply piles containing cards except for the province pile
	printf("Testing if game is over with all the supply piles containing cards except for the province pile\nExpected result: Game Over (return 1).\n");
	for (i = 0; i < treasure_map+1; i++)
	{
		testGame.supplyCount[i] = 5;
	}
	testGame.supplyCount[province] = 0;
	assertion(isGameOver(&testGame) == 1);
	
	//Testing if game is over with 3 supply piles being empty, two of those supply piles being at the min and max of the isGameOver supply pile checks,
	//0 and 24
	printf("Testing if game is over with 3 supply piles being empty, two of those supply piles being at the \nmin and max of the isGameOver supply pile checks, 0 and 24\nExpected result: Game Over (return 1).\n");
	for (i = 0; i < treasure_map+1; i++)
	{
		testGame.supplyCount[i] = 5;
	}
	testGame.supplyCount[0] = 0;
	testGame.supplyCount[24] = 0;
	testGame.supplyCount[1] = 0;
	assertion(isGameOver(&testGame) == 1);
	
	printf("***********FINISHING isGameOver() TESTING**********\n\n");
	return 0;
}