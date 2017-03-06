/*
	randomtestadventurer.c: Testing the Adventurer card.
	
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


int main(int argc, char* argv[]) {
	if (argc != 2 || argv[1] < 0) {
		printf("Correct Usage: randomtestadventurer <positive random seed>\n");
		exit(0);
	}
	int randSeed = atoi(argv[1]);
	srand(randSeed);
	printf("\n***********BEGINNING ADVENTURER RANDOM CARD TESTING**********\n\n");
	
	int i;
	for (i = 0; i < 1000; i++){
		
		printf("\nTest Iteration %d\n", i);
		printf("Randomizing number of players(2-4), who the current player is, and randomly seeding the game\n");
		struct gameState testGame, gameCopy;
		int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
		int numPlayers = rand() % 3 + 2;		//Random number of players from 2 - 4
		int currentPlayer = rand() % numPlayers;	//currentPlayer is random from 0 - numPlayers-1
		initializeGame(numPlayers, k, (rand() % 1000 + 1), &testGame);	//Initializing testGame with random number of players.
		testGame.whoseTurn = currentPlayer;	//Setting the games current player to match the number that we got randomly
		printf("Number of Players: %d\nCurrent Player: %d\n\n", numPlayers, currentPlayer+1);
		
		
		
		//Have the first player gain a Adventurer card into their hand
		printf("Giving the current player a Adventurer card in the last position of their hand\n");
		gainCard(adventurer, &testGame, 2, currentPlayer);
		printf("Testing that the current player has a Adventurer card in the last position of their hand\n");
		assertion(testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == adventurer);
		
		//Copying testGame state to gameCopy state
		memcpy(&gameCopy, &testGame, sizeof(struct gameState));
		
		
		//Setting up the players deck so that we know what should be in the playedCards pile
		//Based on this deck setup, when the adventurer card is played, the smithy should be discarded, then the cutpurse on top of that.
		int newDeck[10] = { village, copper, smithy, gold, great_hall, gardens, silver, cutpurse, gold, smithy };
		int j, m;
		testGame.deckCount[currentPlayer] = 0;
		for (j = 0; j < 10; j++)
		{
			testGame.deck[currentPlayer][j] = newDeck[j];
			testGame.deckCount[currentPlayer]++;
		}
		
		//Play the Adventurer card in the first players hand
		printf("Playing the Adventurer card\n");
		//playAdventurer(&testGame);
		adventurerCard(&testGame, testGame.handCount[currentPlayer] - 1, currentPlayer);
				
		//Checking if there is a cutpurse card on the top of the discard pile
		printf("Testing discard position 0 for cutpurse card\n");
		assertion(testGame.discard[currentPlayer][0] == cutpurse);
		
		//Checking if there is a smithy card under the cutpurse card
		printf("Testing discard position 1 for smithy card\n");
		assertion(testGame.discard[currentPlayer][1] == smithy);
		
		//Testing that the player gained two treasure cards
		printf("Testing whether the player gained 2 treasure cards\n");
		int oldNumTreasures = 0;
		for (j = 0; j < gameCopy.handCount[currentPlayer]; j++) 
		{
			if (gameCopy.hand[currentPlayer][j] == gold || gameCopy.hand[currentPlayer][j] == silver || gameCopy.hand[currentPlayer][j] == copper)
				oldNumTreasures++;
		}
		
		int curNumTreasures = 0;
		for (j = 0; j < testGame.handCount[currentPlayer]; j++) 
		{
			if (testGame.hand[currentPlayer][j] == gold || testGame.hand[currentPlayer][j] == silver || testGame.hand[currentPlayer][j] == copper)
				curNumTreasures++;
		}
		
		assertion(curNumTreasures == oldNumTreasures + 2);

		
		
		//Looping through the other players to test that their decks, discard piles, hands have not changed
		for (j = 0; j < numPlayers; j++) {
			if (j != currentPlayer) {
				//Testing that the other players hands have the same number of cards they started with
				printf("Testing player %d has the same number of cards in hand that they started with.\n", j+1);
				assertion(testGame.handCount[j] == gameCopy.handCount[j]);
				
				//Check that the other players deck count remained the same
				printf("Testing player %d has the same number of cards in deck that they started with.\n", j+1);
				assertion(testGame.deckCount[j] == gameCopy.deckCount[j]);
			
				
				//Check that the other players discard pile has the same number of cards that it started with
				printf("Testing player %d has the same number of cards in discard pile that they started with.\n", j+1);
				assertion(testGame.discardCount[j] == gameCopy.discardCount[j]);
				
				//Checking that the other players decks have the same cards in there as at game initialization
				printf("Testing player %d has the same cards in hand that they started with.\n", j+1);
				if (testGame.handCount[j] == 0) {
					printf("Player %d has a handcount of 0\n", j+1);
				}
				else {
					for (m = 0; m < testGame.handCount[j]; m++) 
					{
						printf("Card #%d ", m);
						assertion(testGame.hand[j][m] == gameCopy.hand[j][m]);
					}
				}
	
				
				
			}
			
		}
		
		//Check that the players hand has 2 more cards in it than at game start
		printf("Testing that the current players hand has 2 more cards in it than at game start\n");
		assertion(testGame.handCount[currentPlayer] == gameCopy.handCount[currentPlayer] + 2);
		
		
		//Check that the top two cards in the players hand are treasure cards
		int curCount = testGame.handCount[currentPlayer];
		printf("Testing that the top two cards in the current players hand are treasure cards\n");
		printf("Top Card\n");
		assertion(testGame.hand[currentPlayer][curCount - 1] == copper || testGame.hand[currentPlayer][curCount - 1] == silver || testGame.hand[currentPlayer][curCount - 1] == gold);
		printf("2nd Card\n");	
		assertion(testGame.hand[currentPlayer][curCount - 2] == copper || testGame.hand[currentPlayer][curCount - 2] == silver || testGame.hand[currentPlayer][curCount - 2] == gold);		
		
	}	
	
	
	printf("***********FINISHING ADVENTURER RANDOM CARD TESTING**********\n\n");
	return 0;
}