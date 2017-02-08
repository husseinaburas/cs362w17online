/*
	cardtest1.c: Testing the Smithy card.
	
	Description: Will test the implemetation of the playSmithy function. The Smithy card, when played, is expected to
	cause the player to draw 3 cards. The code for this is very simple, a loop is initiated and iterated 
	through 3 times. Each iteration calls the function drawCard, which is passed the gameState and the 
	currentPlayer so that the correct player draws 3 cards. The played card is then discarded from the 
	hand and 0 is returned to exit the switch statement.
	
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assertion.h"

int main() {
	printf("\n***********BEGINNING SMITHY CARD TESTING**********\n\n");
	struct gameState testGame, gameCopy;
	int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
	int numPlayers = 2;
	initializeGame(numPlayers, k, 10, &testGame);
	int currentPlayer = testGame.whoseTurn;
	
	
	//Have the first player gain a smithy card into their hand
	printf("Giving the current player a smithy card in the last position of their hand\n");
	gainCard(smithy, &testGame, 2, currentPlayer);
	printf("Testing that the current player has a smithy card in the last position of their hand\n");
	assertion(testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == smithy);

	//Copying testGame state to gameCopy state
	memcpy(&gameCopy, &testGame, sizeof(struct gameState));
	
	//Play the smithy card in the first players hand
	printf("Playing the Smithy card in the last position of the hand\n");
	playSmithy(&testGame, testGame.handCount[currentPlayer] - 1);
	
	//Checking that the played card (in the played cards array), is the smithy card
	printf("Testing that the played card was the Smithy card.\n");
	assertion(testGame.playedCards[0] == smithy);
	
	//Checking that the players hand increased by 2 cards
	printf("Testing that the player drew 3 cards (Gaining 2 cards overall, after discard)\n");
	assertion(testGame.handCount[currentPlayer] == gameCopy.handCount[currentPlayer] + 2);
	
	//Checking that 3 cards were drawn from the deck
	printf("Testing that 3 cards were taken from the deck\n");
	assertion(testGame.deckCount[currentPlayer] == gameCopy.deckCount[currentPlayer] - 3);
	
	//Checking that 1, and only 1, cards have been played
	printf("Testing that only 1 card was played\n");
	assertion(testGame.playedCardCount == 1);
	
	//Check that the other players hand has the same number of cards that it started with
	printf("Testing the the other players hand has the same number of cards that it started with\n");
	assertion(testGame.handCount[1] == gameCopy.handCount[1]);
	
	//Check that the other players deck count remained the same
	printf("Checking that the other players deck count remained the same\n");
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
	
	printf("***********FINISHING SMITHY CARD TESTING**********\n\n");
	return 0;
}


