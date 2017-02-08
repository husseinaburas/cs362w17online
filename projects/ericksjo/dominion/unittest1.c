/*
	unittest1.c: Testing the updateCoins() method.
	
	Description: The update coins method takes into account any copper, silver, and gold cards in the players hand, along
	with any bonuses passed in the method parameters, sums those up and updates the gameStates coin value.
	
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
	printf("\n***********BEGINNING updateCoins() TESTING**********\n\n");
	struct gameState testGame, gameCopy;
	int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
	int numPlayers = 2;
	initializeGame(numPlayers, k, 10, &testGame);
	int currentPlayer = testGame.whoseTurn;
	
	//Initializing the current players hand to be full of smithys
	printf("Filling the current players hand with smithys\n");
	int i;
	for (i = 0; i < testGame.handCount[currentPlayer]; i++)
	{
		testGame.hand[currentPlayer][i] = smithy;
	}
	
	//Copying testGame state to gameCopy state
	memcpy(&gameCopy, &testGame, sizeof(struct gameState));
	
	//Testing that updateCoins() sets coins to 0 when no treasure cards are found in hand
	printf("Testing that updateCoins() sets coins to 0 if no treasure cards are found in hand and bonus is 0\n");
	updateCoins(currentPlayer, &testGame, 0);
	assertion(testGame.coins == 0);
	
	//Testing that updateCoins() correctly sets coins with no treasure cards and a non-zero bonus
	printf("Testing that updateCoins() correctly sets coins with no treasure cards and a non-zero bonus\n");
	updateCoins(currentPlayer, &testGame, 6);
	assertion(testGame.coins == 6);
	
	//Testing that updateCoins() correctly resets coins at the beginning of the function if coins is something other than 0 when it is called
	printf("Testing that updateCoins() correctly resets coins at the beginning of the function if coins is\nsomething other than 0 when it is called\n");
	testGame.coins = 19;
	updateCoins(currentPlayer, &testGame, 0);
	assertion(testGame.coins == 0);
	
	//Testing that updateCoins() correctly calculates and sets coins with the players hand full of coppers
	printf("Testing that updateCoins() correctly calculates and sets coins with the players hand full \nof coppers\n");
	for (i = 0; i < testGame.handCount[currentPlayer]; i++)
	{
		testGame.hand[currentPlayer][i] = copper;
	}
	updateCoins(currentPlayer, &testGame, 0);
	assertion(testGame.coins == testGame.handCount[currentPlayer] * 1);
	
	//Testing that updateCoins() correctly calculates and sets coins with the players hand full of silvers
	printf("Testing that updateCoins() correctly calculates and sets coins with the players hand full \nof silvers\n");
	for (i = 0; i < testGame.handCount[currentPlayer]; i++)
	{
		testGame.hand[currentPlayer][i] = silver;
	}
	updateCoins(currentPlayer, &testGame, 0);
	assertion(testGame.coins == testGame.handCount[currentPlayer] * 2);
	
	//Testing that updateCoins() correctly calculates and sets coins with the players hand full of golds
	printf("Testing that updateCoins() correctly calculates and sets coins with the players hand full \nof golds\n");
	for (i = 0; i < testGame.handCount[currentPlayer]; i++)
	{
		testGame.hand[currentPlayer][i] = gold;
	}
	updateCoins(currentPlayer, &testGame, 0);
	assertion(testGame.coins == testGame.handCount[currentPlayer] * 3);
	
	//Testing that updateCoins() correctly calculates and sets coins with the players hand full a random mix of treasure cards
	printf("Testing that updateCoins() correctly calculates and sets coins with the players hand full \nof a random mix of treasure cards\n");
	int numCoppers = 0;
	int numSilvers = 0;
	int numGolds = 0;
	for (i = 0; i < testGame.handCount[currentPlayer]; i++)
	{
		int randNum = rand() % 3 + 1;
		if (randNum == 1) {
			testGame.hand[currentPlayer][i] = copper;
			numCoppers++;
		}
		else if (randNum == 2) {
			testGame.hand[currentPlayer][i] = silver;
			numSilvers++;
		}
		else {
			testGame.hand[currentPlayer][i] = gold;
			numGolds++;
		}
	}
	updateCoins(currentPlayer, &testGame, 0);
	assertion(testGame.coins == numCoppers + numSilvers*2 + numGolds*3);
	
	//Testing that the current players deck count has remained the same after all these updateCoins() calls
	printf("Testing that the current players deck count has remained the same after all these updateCoins() \ncalls\n");
	assertion(testGame.deckCount[currentPlayer] == gameCopy.deckCount[currentPlayer]);
	
	//Testing that the current players hand count has remained the same after all these updateCoins() calls
	printf("Testing that the current players hand count has remained the same after all these updateCoins() \ncalls\n");
	assertion(testGame.handCount[currentPlayer] == gameCopy.handCount[currentPlayer]);
	
	printf("***********FINISHING updateCoins() TESTING**********\n\n");
	return 0;
}
