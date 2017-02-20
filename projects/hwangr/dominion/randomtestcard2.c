//Random test for the steward card in dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_TESTS 100000	//Maximum number of tests we want to run
#define NUM_CARDTYPES 27
#define DEBUG_MODE 0

int customAssert(int condition, char *errorMsg)
{
	if (condition)
	{
		return 0;
	}
	else
	{
		if(DEBUG_MODE)
		{
			printf("Error: %s\n", errorMsg);
		}	

		return 1;	
	}
}


int main( int argc, char** argv )
{
	int numBugs = 0;	//Stores total number of bugs encountered by unit test
	int returnValue, newCard, randSeed, choice1, choice2, choice3;
	int numCardsDrawn;
	int i, j;

	struct gameState *G = newGame();

  	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};


	//If user has inputed a seed number for rand() from command line, use it
	//Otherwise, the default value is the value of time(NULL) 
	if (argc >= 2)
	{
		randSeed = atoi(argv[1]);		//User inputs rand seed from command line
		srand(randSeed);
	}
	else
	{
		randSeed = time(NULL);
		srand(randSeed);
	}
		
	printf ("\n----------Starting Random Card Test: Steward----------\n\n");

	for(i = 0; i < MAX_TESTS; i++)
	{
		if(DEBUG_MODE)
		{
			printf("Random Test %d\n", i+1);
		}	

		int bugsThisTest = numBugs;		//Tracks number of bugs introduced this test
	
		memset(G, 0, sizeof(struct gameState)); 	//Set all bits to 0 every iteration 

		int numPlayers = rand() % 3 + 2;	//In this Dominion implementation, number of
							//players must be between 2 and 4, inclusive

		//Initialize the game state	
		returnValue = initializeGame(numPlayers, k, randSeed, G); 
		numBugs += customAssert( (returnValue == 0), "Initialize game state failed." );


		//Randomize game state parameters for player 1, other players are just dummy values
		//that may or may not be modified by a particular card

		//Randomize Player 1's deck
		G->deckCount[0] = rand() % (MAX_DECK + 1);		
		for(j = 0; j < G->deckCount[0]; j++)
		{
			newCard = rand() % NUM_CARDTYPES;
			G->deck[0][j] = newCard;		
		}

		//Randomize Player 1's hand
		G->handCount[0] = rand() % (MAX_HAND - 1) + 1;
		for(j = 0; j < G->handCount[0]; j++)
		{
			newCard = rand() % NUM_CARDTYPES;
			G->hand[0][j] = newCard;		
		}

		//Randomize Player 1's discard pile
		G->discardCount[0] = rand() % 21;		//No maximum size for discard pile, so set
		for(j = 0; j < G->discardCount[0]; j++)		//it a reasonable maximum
		{
			newCard = rand() % NUM_CARDTYPES;
			G->discard[0][j] = newCard;		
		}				
	
		//Randomize played card pile
		G->playedCardCount = rand() % MAX_DECK;
		for(j = 0; j < G->playedCardCount; j++)
		{
			newCard = rand() % NUM_CARDTYPES;
			G->playedCards[j] = newCard;		
		}
		
		//Guarantee that there is at least one steward card
		int stewardPos = rand() % G->handCount[0];
		G->hand[0][stewardPos] = steward;

		//Stores expected parameters
		int exp_deckCount[numPlayers];
		int exp_handCount[numPlayers];
		int exp_discardCount[numPlayers];
		int exp_playedCardCount = G->playedCardCount;
		int exp_coins = G->coins;
		int exp_numCardsDrawn = 0;
	
		for(j = 0; j < numPlayers; j++)
		{
			exp_deckCount[j] = G->deckCount[j];
			exp_handCount[j] = G->handCount[j];
			exp_discardCount[j] = G->discardCount[j];
		}

		//Randomize choices for either cards, coins, or trash (1-3)
		choice1 = rand() % 3 + 1;

		//Only need to generate numbers for choice2 and choice3 if choice1 is 3
		if (choice1 == 3)
		{
			choice2 = rand() % G->handCount[0];
			choice3 = rand() % G->handCount[0];

			//Some edge cases where number of cards to trash is less than 2
			if (G->handCount[0] == 1)
			{
				choice2 = 0;
				choice3 = 0;
			}
			else
			{	
				while (choice2 == choice3)
				{
					choice3 = rand() % G->handCount[0];
				}
			}	
		} 
		else
		{
			choice2 = choice3 = 0;
		}

		//Debug statement to print choice1, choice2, and choice3
		if (DEBUG_MODE)
		{
			printf("choice1: %d\nchoice2: %d\nchoice3: %d\n", choice1, choice2, choice3);
		}
	
		//Calls the playSmithy() method, since we are only testing this method,
		//and not the other associated functions such as playCard(), etc.
		returnValue = playSteward(G, 0, stewardPos, choice1, choice2, choice3);
		numBugs += customAssert( (returnValue == 0), "Call to playSteward() failed." );
		
		//Make sure player turn was not unintionally modified
		numBugs += customAssert( (G->whoseTurn == 0), "Player turn incorrectly changed." );

		//Check if other players' parameters are still unchanged
		for(j = 1; j < numPlayers; j++)
		{
			numBugs += customAssert( 	(G->deckCount[j] == exp_deckCount[j]), 
							"Another player's deck count was incorrectly changed." );
			numBugs += customAssert( 	(G->handCount[j] == exp_handCount[j]), 
							"Another player's hand count was incorrectly changed." );
			numBugs += customAssert( 	(G->discardCount[j] == exp_discardCount[j]), 
							"Another player's discard count was incorrectly changed." );
		}

		//Base case: steward is played and discarded - if choice1 == 1, then two cards are drawn,
		//see below if statement for that case
		numCardsDrawn = G->handCount[0] - exp_handCount[0];
		exp_numCardsDrawn = -1;
		exp_playedCardCount++;

		//1st choice - draw 2 cards
		if (choice1 == 1)
		{	
			//Checks for the presence of up to two treasure cards in hand
			//Intended behavior: draw 2 cards, discard 1 (steward), so net change is +1 cards
			exp_numCardsDrawn = 1;	

		}
		else if (choice1 == 2)
		{
			exp_coins += 2;
		}
		else if (choice1 == 3)
		{
			//Need to account for the two cards trashed from hand
			exp_numCardsDrawn -= 2;
		}

		//Test for correct number of cards drawn
		numBugs += customAssert( (numCardsDrawn == exp_numCardsDrawn), "Incorrect number of cards drawn." );

		//Test for correct coin total
		numBugs += customAssert( (G->coins == exp_coins), "Incorrect coin total." );

		//Since steward card was played, should only increase by 1
		//Also, trashing should not affect the playedCardCount
		numBugs += customAssert( 	( exp_playedCardCount == G->playedCardCount),
						"playedCardCount was incorrectly updated." );


		if(DEBUG_MODE)
		{
			printf("New bugs this test: %d\n", numBugs - bugsThisTest);
			//Formatting purposes only
			printf("\n");
		}

		
	}	


	if(numBugs)
	{
		printf("Random Card Test: Steward - Summary\n");
		printf("Total Tests: %d\n", MAX_TESTS);
		printf("Total bugs: %d\n", numBugs);
		printf("To see debug messages for all lines, set DEBUG_MODE to 1\n");
	}	
	else
	{
		printf("\nRandom Card Test: Steward - All tests for playSteward() successful\n");
	}

	printf("\n----------End of Random Card Test: Steward----------\n");

	return 0;
}
