/*
	cardtest2.c: Testing the Adventurer card.
	
	Description: Will test the implemetation of the playAdventurer function. The Adventurer card, 
	when played, causes the player to reveal cards from their deck until 2 treasure cards have been 
	revealed. Those 2 treasure cards are then added into the players hand. The code for this is 
	relatively simple, a while loop is initiated that will terminate when the drawntreasure variable, 
	initiated as 0, reaches 2. Each iteration of the while loop checks if the current players deck is empty, 
	if it is, the deck is reshuffled, a card is drawn and checked for treasure status. If the card drawn is 
	a treasure, the drawntreasure variable is incremented. Otherwise, the drawn card is put into a temphand 
	array to be discarded later. Once this while loop terminates (2 treasure cards drawn), the temporary 
	hand array is emptied/discarded and 0 is returned to exit the switch statement.
	
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assertion.h"

int main() {
	printf("\n***********BEGINNING ADVENTURER CARD TESTING**********\n\n");
	struct gameState testGame, gameCopy;
	int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
	int numPlayers = 2;
	initializeGame(numPlayers, k, 10, &testGame);
	int currentPlayer = testGame.whoseTurn;
	
	
	//Have the first player gain a Adventurer card into their hand
	printf("Giving the current player a Adventurer card in the last position of their hand\n");
	gainCard(adventurer, &testGame, 2, currentPlayer);
	printf("Testing that the current player has a Adventurer card in the last position of their hand\n");
	assertion(testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == adventurer);

	//Copying testGame state to gameCopy state
	memcpy(&gameCopy, &testGame, sizeof(struct gameState));
	
	//Setting up the players deck so that we know what should be in the playedCards pile
	printf("Setting up the players deck so that we know what is in it.\n");
	//Based on this deck setup, when the adventurer card is played, the smithy should be discarded, then the cutpurse on top of that.
	int newDeck[10] = { village, copper, smithy, gold, great_hall, gardens, silver, cutpurse, gold, smithy };
	int i;
	testGame.deckCount[currentPlayer] = 0;
	for (i = 0; i < 10; i++)
	{
		testGame.deck[currentPlayer][i] = newDeck[i];
		testGame.deckCount[currentPlayer]++;
	}
	//Play the Adventurer card in the first players hand
	printf("Playing the Adventurer card in the last position of the hand\n");
	adventurerCard(&testGame, testGame.handCount[currentPlayer] - 1, currentPlayer);
	
	//Checking if there is a cutpurse card on the top of the discard pile
	printf("Testing the top of the discard pile for a cutpurse card\n");
	assertion(testGame.discard[currentPlayer][0] == cutpurse);
	
	//Checking if there is a smithy card under the cutpurse card
	printf("Testing for a smithy card under the cutpurse card in the discard pile\n");
	assertion(testGame.discard[currentPlayer][1] == smithy);
	
	//Testing that the player gained two treasure cards
	printf("Testing whether the player gained 2 treasure cards\n");
	int oldNumTreasures = 0;
	for (i = 0; i < gameCopy.handCount[currentPlayer]; i++) 
	{
		if (gameCopy.hand[currentPlayer][i] == gold || gameCopy.hand[currentPlayer][i] == silver || gameCopy.hand[currentPlayer][i] == copper)
			oldNumTreasures++;
	}
	
	int curNumTreasures = 0;
	for (i = 0; i < testGame.handCount[currentPlayer]; i++) 
	{
		if (testGame.hand[currentPlayer][i] == gold || testGame.hand[currentPlayer][i] == silver || testGame.hand[currentPlayer][i] == copper)
			curNumTreasures++;
	}
	
	assertion(curNumTreasures == oldNumTreasures + 2);
	
	//Check that the other players hand has the same number of cards that it started with
	printf("Testing the the other players hand has the same number of cards that it started with\n");
	assertion(testGame.handCount[1] == gameCopy.handCount[1]);
	
	//Check that the other players deck count remained the same
	printf("Checking that the other players deck count remained the same\n");
	assertion(testGame.deckCount[1] == gameCopy.deckCount[1]);
	
	//Checking that the other players deck has the same cards in it as at game initialization
	printf("Testing that the other players deck has the same cards in it as at game initialization\n");
	for (i = 0; i < gameCopy.deckCount[1]; i++) 
	{
		printf("Card #%d ", i);
		assertion(testGame.hand[1][i] == gameCopy.hand[1][i]);
	}
	
	//Check that the other players discard pile has the same number of cards that it started with
	printf("Testing the the other players discard pile has the same number of cards that it started with\n");
	assertion(testGame.discardCount[1] == gameCopy.discardCount[1]);
	
	//Check that the players hand has 2 more cards in it than at game start
	printf("Testing that the players hand has 2 more cards in it than at game start\n");
	assertion(testGame.handCount[currentPlayer] == gameCopy.handCount[currentPlayer] + 2);
	
	//Check that the top two cards in the players hand are treasure cards
	printf("Testing that the top two cards in the players hand are treasure cards\n");
	printf("Top Card\n");
	assertion(testGame.hand[currentPlayer][0] == copper || testGame.hand[currentPlayer][0] == silver || testGame.hand[currentPlayer][0] == gold);
	printf("2nd Card\n");	
	assertion(testGame.hand[currentPlayer][1] == copper || testGame.hand[currentPlayer][1] == silver || testGame.hand[currentPlayer][1] == gold);		
	
	printf("***********FINISHING ADVENTURER CARD TESTING**********\n\n");
	return 0;
}


