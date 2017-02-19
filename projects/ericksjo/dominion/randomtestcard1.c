/*
	randomtestcard1.c: Testing the Smithy card.
	
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

int main(int argc, char* argv[]) {
	
	if (argc != 2 || argv[1] < 0) {
		printf("Correct Usage: randomtestcard1 <positive random seed>\n");
		exit(0);
	}
	int randSeed = atoi(argv[1]);
	srand(randSeed);
	
	printf("\n***********BEGINNING SMITHY CARD TESTING**********\n\n");
	
	int i;
	for (i = 0; i < 1000; i++){
		
		printf("\nTest Iteration %d\n", i);
		printf("Randomizing number of players(2-4), who the current player is, and randomly seeding the game\n");
		struct gameState testGame, gameCopy;
		int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
		int j, m;
		int numPlayers = rand() % 3 + 2;		//Random number of players from 2 - 4
		int currentPlayer = rand() % numPlayers;	//currentPlayer is random from 0 - numPlayers-1
		initializeGame(numPlayers, k, (rand() % 1000 + 1), &testGame);	//Initializing testGame with random number of players.
		testGame.whoseTurn = currentPlayer;	//Setting the games current player to match the number that we got randomly
		printf("Number of Players: %d\nCurrent Player: %d\n\n", numPlayers, currentPlayer+1);
		
		
		//Have the current player gain a smithy card into their hand
		printf("Giving the current player a smithy card in the last position of their hand\n");
		gainCard(smithy, &testGame, 2, currentPlayer);
		printf("Testing that the current player has a smithy card in the last position of their hand\n");
		assertion(testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == smithy);

		//Copying testGame state to gameCopy state
		memcpy(&gameCopy, &testGame, sizeof(struct gameState));
		
		//Play the smithy card in the current players hand
		printf("Playing the Smithy card in the last position of the hand\n");
		playSmithy(&testGame, testGame.handCount[currentPlayer] - 1);
		
		//Checking that the played card (in the played cards array), is the smithy card
		printf("Testing that the played card was the Smithy card.\n");
		assertion(testGame.playedCards[0] == smithy);
				
		//Checking that the players hand increased by 2 cards
		printf("Testing that the player drew 3 cards (Gaining 2 cards overall, after discard)\n");
		assertion(testGame.handCount[currentPlayer] == gameCopy.handCount[currentPlayer] + 2);
		
		//Checking that 3 cards were drawn from the deck
		printf("Testing that 3 cards were taken from the current players deck\n");
		assertion(testGame.deckCount[currentPlayer] == gameCopy.deckCount[currentPlayer] - 3);
		
		//Checking that 1, and only 1, cards have been played
		printf("Testing that only 1 card was played\n");
		assertion(testGame.playedCardCount == 1);
		
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
	
	
	
	}
	
	
	
	printf("***********FINISHING SMITHY CARD TESTING**********\n\n");
	return 0;
}
