/* Card test for Village */ 

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assertion.h"

int main() {
	printf("\nVillage Card testing\n\n");
	struct gameState testGame, gameCopy;
	int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
	int numPlayers = 2;
	initializeGame(numPlayers, k, 10, &testGame);
	int currentPlayer = testGame.whoseTurn;

	//first player gain a village card in their hand
	printf("give current player a village card and put it in last position of hand\n");
	testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] = village;
	printf("Testing that current player has a village card in the last position of hand\n");
	assertion(testGame.hand[currentPlayer][testGame.handCount[currentPlayer] -1] == village);
	
	//copying testGame state to gameCopy state
	memcpy(&gameCopy, &testGame, sizeof(struct gameState));

	//play village card in the first players hand
	printf("Village card in last position of hand is played. \n");
	playVillage(&testGame, testGame.handCount[currentPlayer] - 1, currentPlayer);
	
	//check if played card in the player cards array is the village card
	printf("Testing to see if played card was a village card.\n");
	assertion(testGame.playedCards[0] == village);

	//check if players hand is static by having 1 card drawn and the village card discarded
	printf("Testing that player drew 1 card thus gaining 0 cards overall after discard\n(false positive)\n");
	assertion(testGame.handCount[currentPlayer] == gameCopy.handCount[currentPlayer]);

	//check to see if the 1 card was drawn from deck
	printf("Testing that 1 card was drawn from deck\n");
	assertion(testGame.deckCount[currentPlayer] == gameCopy.deckCount[currentPlayer] - 1);
	
	//test that players number of actions increased by 2
	printf("Testing that current number of actions increased by 2\n");
	assertion(testGame.numActions == gameCopy.numActions + 2);

	//check that 1 and only 1 card has been played
	printf("Testing to see if only 1 card was played\n");
	assertion(testGame.playedCardCount == 1);

	//check if other players have same number cards as in the beginning
	printf("Test to see if other players have same number of cards in hand as in the start\n");
	assertion(testGame.handCount[1] == gameCopy.handCount[1]);

	//check to see if deck count for other players is same
	printf("Testing that other players deck count is the same\n");
	assertion(testGame.deckCount[1] == gameCopy.deckCount[1]);
	
	// check to see if other players deck has same cards in as during game initialization
	printf("Testing to see if other players have same cards in deck as during game initialization\n");
	int i;
	for (i = 0; i < gameCopy.deckCount[1]; i++)
	{	
		printf("Card #%d ", i);
		assertion(testGame.hand[1][i] == gameCopy.hand[1][i]);
	}
	
	//check to see if other players discard pile has the same amount as in start
	printf("Testing to see if other players discard pile as the same amount as in start\n");
	assertion(testGame.discardCount[1] == gameCopy.discardCount[1]);
	
	printf("Finished Village Card testing \n\n");
	return 0;
} 

   

