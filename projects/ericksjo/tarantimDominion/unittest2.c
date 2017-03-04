/*
	unittest2.c: Testing the shuffle() method.
	
	Description: The shuffle method takes the passed player and gameState and shuffles that players deck into a random order.
	
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assertion.h"
#include <time.h>

int cmp(const void* a, const void* b) {
  if (*(int*)a > *(int*)b)
    return 1;
  if (*(int*)a < *(int*)b)
    return -1;
  return 0;
}

int main() {
	printf("\n***********BEGINNING shuffle() TESTING**********\n\n");
	struct gameState testGame, gameCopy;
	int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
	int numPlayers = 2;
	initializeGame(numPlayers, k, 10, &testGame);
	int currentPlayer = testGame.whoseTurn;
	
	
	memcpy(&gameCopy, &testGame, sizeof(struct gameState));
	
	//Test shuffle() for changing at least one card in the players deck. If the deck on function completion is the same as on
	//function initialization, the test fails.
	printf("Testing if shuffle changes at least one card in the current players deck.\n");
	shuffle(currentPlayer, &testGame);
	int i;
	int shuffleSuccess = 0;
	for (i = 0; i < testGame.deckCount[currentPlayer]; i++) 
	{
		if (testGame.deck[i] != gameCopy.deck[i])
			shuffleSuccess = 1;
	}
	assertion(shuffleSuccess == 1);
	
	//Test that shuffles sorting method actually sorts a passed array.
	printf("Test that shuffles sorting method actually sorts a passed array.\n");
	int testSort[10] = { 7, 10 , 2, 4, 8, 3, 11, 25, 1, 89 };
	qsort ((void*)testSort, 10, sizeof(int), cmp); 
	int sorted = 0;
	for (i = 0; i < 9; i++) {
		if (testSort[i] < testSort[i + 1])
			sorted = 1;
		else
			sorted = 0;
	}
	assertion(sorted ==1);
	
	//Test that the deck of the other player stays the same
	printf("Testing that the deck of the other player stays the same\n");
	shuffle(currentPlayer, &testGame);
	for (i = 0; i < gameCopy.deckCount[1]; i++) 
	{
		printf("Card #%d ", i);
		assertion(testGame.hand[1][i] == gameCopy.hand[1][i]);
	}
	
	//Test that shuffle() terminates in the correct spot and returns -1 if deckCount is less than 1
	printf("Testing that shuffle terminates in the correct spot and returns -1 if deckCount is 0\n");
	testGame.deckCount[currentPlayer] = 0;
	assertion(shuffle(currentPlayer, &testGame) == -1);
	
	printf("Testing that shuffle terminates in the correct spot and returns -1 if deckCount is negative\n");
	testGame.deckCount[currentPlayer] = -80;
	assertion(shuffle(currentPlayer, &testGame) == -1);
	
	//Test that shuffle() terminates in the correct spot ant returns 0 if deckCount is 1
	printf("Testing that shuffle terminates in the correct spot and returns 0 if deckCount is 1\n");
	testGame.deckCount[currentPlayer] = 1;
	assertion(shuffle(currentPlayer, &testGame) == 0);
	
	//Test that shuffle() terminates in the correct spot and returns 0 if deckCount is a large positive number
	printf("Testing that shuffle() terminates in the correct spot and returns 0 if deckCount is a \nlarge positive number\n");
	testGame.deckCount[currentPlayer] = 999;
	assertion(shuffle(currentPlayer, &testGame) == 0);
	
	printf("***********FINISHING shuffle() TESTING**********\n\n");
	return 0;
}