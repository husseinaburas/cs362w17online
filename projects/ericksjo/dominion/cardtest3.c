/*
	cardtest3.c: Testing the Village card.
	
	Description: Will test the implemetation of the playVillage function. Correct implementation should cause
	one card to be drawn and two actions to be gained.
	
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assertion.h"

int main() {
	printf("\n***********BEGINNING VILLAGE CARD TESTING**********\n\n");
	struct gameState testGame, gameCopy;
	int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
	int numPlayers = 2;
	initializeGame(numPlayers, k, 10, &testGame);
	int currentPlayer = testGame.whoseTurn;
	
	
	//Have the first player gain a Village card into their hand
	printf("Giving the current player a Village card in the last position of their hand\n");
	//gainCard(village, &testGame, 2, currentPlayer);
	testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] = village;
	printf("Testing that the current player has a Village card in the last position of their hand\n");
	assertion(testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == village);

	//Copying testGame state to gameCopy state
	memcpy(&gameCopy, &testGame, sizeof(struct gameState));
	
	//Play the Village card in the first players hand
	printf("Playing the Village card in the last position of the hand\n");
	playVillage(&testGame, testGame.handCount[currentPlayer] - 1);
	
	//Checking that the played card (in the played cards array), is the Village card
	printf("Testing that the played card was the Village card.\n");
	assertion(testGame.playedCards[0] == village);
	
	//Checking that the players hand stayed static (1 card drawn, village card discarded)
	printf("Testing that the player drew 1 cards (Gaining 0 cards overall, after discard)\n(This could give a false positive)\n");
	assertion(testGame.handCount[currentPlayer] == gameCopy.handCount[currentPlayer]);
	
	//Checking that 1 card was drawn from the deck
	printf("Testing that 1 card was drawn from the deck\n");
	assertion(testGame.deckCount[currentPlayer] == gameCopy.deckCount[currentPlayer] - 1);
	
	//Test that players number of actions increased by 2
	printf("Testing that the current number of actions increased by 2\n");
	assertion(testGame.numActions == gameCopy.numActions + 2);
	
	//Checking that 1, and only 1, cards have been played
	printf("Testing that only 1 card was played\n");
	assertion(testGame.playedCardCount == 1);
	
	//Check that the other players hand has the same number of cards that it started with
	printf("Testing the the other players hand has the same number of cards that it started with\n");
	assertion(testGame.handCount[1] == gameCopy.handCount[1]);
	
	//Check that the other players deck count remained the same
	printf("Testing that the other players deck count remained the same\n");
	assertion(testGame.deckCount[1] == gameCopy.deckCount[1]);
	
	
	//Checking that the other players deck has the same cards in it as at game initialization
	printf("Testing that the other players deck has the same cards in it as at game initialization\n");
	int i;
	for (i = 0; i < gameCopy.deckCount[1]; i++) 
	{
		printf("Card #%d ", i);
		assertion(testGame.hand[1][i] == gameCopy.hand[1][i]);
	}
	
	//Check that the other players discard pile has the same number of cards that it started with
	printf("Testing the the other players discard pile has the same number of cards that it started with\n");
	assertion(testGame.discardCount[1] == gameCopy.discardCount[1]);
	
	printf("***********FINISHING VILLAGE CARD TESTING**********\n\n");
	return 0;
}


