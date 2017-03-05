/*
	cardtest4.c: Testing the Council Room card.
	
	Description: Will test the implemetation of the playCouncil_Room function. When played, this card is expected to
	cause the player to draw 4 cards, gain +1 buy, and each other player should draw a card.
	
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assertion.h"

int main() {
	printf("\n***********BEGINNING COUNCIL ROOM CARD TESTING**********\n\n");
	struct gameState testGame, gameCopy;
	int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
	int numPlayers = 2;
	initializeGame(numPlayers, k, 10, &testGame);
	int currentPlayer = testGame.whoseTurn;
	int bonus = 0;
	
	//Have the first player gain a Council Room card into their hand
	printf("Giving the current player a Council Room card in the last position of their hand\n");
	gainCard(council_room, &testGame, 2, currentPlayer);
	printf("Testing that the current player has a Council Room card in the last position of their hand\n");
	assertion(testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == council_room);

	//Copying testGame state to gameCopy state
	memcpy(&gameCopy, &testGame, sizeof(struct gameState));
	
	//Play the Council Room card in the first players hand
	printf("Playing the Council Room card in the last position of the hand\n");
	//playCouncil_Room(&testGame, testGame.handCount[currentPlayer] - 1);
	cardEffect(council_room, 0, 0, 0, &testGame, testGame.handCount[currentPlayer] - 1, &bonus);
	
	//Checking that the played card (in the played cards array), is the Council Room card
	printf("Testing that the played card was the Council Room card.\n");
	assertion(testGame.playedCards[0] == council_room);
	
	//Checking that the players hand increased by 4 cards
	printf("Testing that the current player drew 4 cards (Gaining 3 cards overall, after discard)\n");
	assertion(testGame.handCount[currentPlayer] == gameCopy.handCount[currentPlayer] + 3);
	
	//Checking that 4 cards were drawn from the current players deck
	printf("Testing that 4 cards were taken from the current players deck\n");
	assertion(testGame.deckCount[currentPlayer] == gameCopy.deckCount[currentPlayer] - 4);
	
	//Checking that 1 card was drawn from the other players deck
	printf("Testing that 1 card was taken from the other players deck\n");
	assertion(testGame.deckCount[currentPlayer+1] == gameCopy.deckCount[currentPlayer+1] - 1);
	
	//Checking that the other player drew a card
	printf("Testing that the other player drew a card, increasing their handCount by 1\n");
	assertion(testGame.handCount[currentPlayer+1] == gameCopy.handCount[currentPlayer+1] + 1);
	
	//Checking if numBuys was incremented
	printf("Testing that numBuys was increased by 1\n");
	assertion(testGame.numBuys == gameCopy.numBuys+1);
	
	//Checking that 1, and only 1, cards have been played
	printf("Testing that only 1 card was played\n");
	assertion(testGame.playedCardCount == 1);
	
	//Checking that the other players deck has the same cards in it as at game initialization
	printf("Testing that the other players deck has the same cards in it as at game initialization \n(Card #0 should fail) \n");
	int i;
	for (i = 0; i < gameCopy.deckCount[1]; i++) 
	{
		printf("Card #%d ", i);
		assertion(testGame.hand[1][i] == gameCopy.hand[1][i]);
	}
	
	//Check that the other players discard pile has the same number of cards that it started with
	printf("Testing the the other players discard pile has the same number of cards that it started with\n");
	assertion(testGame.discardCount[1] == gameCopy.discardCount[1]);
	
	printf("***********FINISHING COUNCIL ROOM CARD TESTING**********\n\n");
	return 0;
}


