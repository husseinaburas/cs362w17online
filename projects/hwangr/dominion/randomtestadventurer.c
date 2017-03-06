//Random test for the adventurer card in dominion.c

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
	int returnValue, newCard, randSeed;
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
		
	printf ("\n----------Starting Random Card Test: Adventurer----------\n\n");

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
		G->handCount[0] = rand() % (MAX_HAND-1) + 1;
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
		
		//Guarantee that there is at least one adventurer card
		int adventurerPos = rand() % G->handCount[0];
		G->hand[0][adventurerPos] = adventurer;

		//Stores expected parameters
		int exp_deckCount[numPlayers];
		int exp_handCount[numPlayers];
		int exp_discardCount[numPlayers];
		int exp_playedCardCount = G->playedCardCount;
	
		for(j = 0; j < numPlayers; j++)
		{
			exp_deckCount[j] = G->deckCount[j];
			exp_handCount[j] = G->handCount[j];
			exp_discardCount[j] = G->discardCount[j];
		}

		//Calls the playAdventurer() method, since we are only testing this method,
		//and not the other associated functions such as playCard(), etc.
		returnValue = playAdventurer(G, 0);
		numBugs += customAssert( (returnValue == 0), "Call to playAdventurer() failed." );
		
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
		
		numBugs += customAssert( 	(exp_playedCardCount == G->playedCardCount),
						"playedCardCount was incorrectly updated." );
		
		//Checks for the presence of up to two treasure cards in hand
		int numCardsDrawn = G->handCount[0] - exp_handCount[0];
		
		numBugs += customAssert( (numCardsDrawn <= 2 && numCardsDrawn >= 0),
					 "Incorrect number of cards drawn." );

		//Check if last n cards are treasure cards
		for(j = 0; j < numCardsDrawn; j++)
		{
			int treasureCardPos = G->hand[0][G->handCount[0] - j];
			returnValue = (    treasureCardPos == copper 
					|| treasureCardPos == silver 
					|| treasureCardPos == gold ); 
			numBugs += customAssert( (returnValue == 1), 
						"Only treasure cards should be drawn.");
		}				


		if(DEBUG_MODE)
		{
			printf("New bugs this test: %d\n", numBugs - bugsThisTest);
			//Formatting purposes only
			printf("\n");
		}

		
	}	


	if(numBugs)
	{
		printf("Random Card Test: Adventurer - Summary\n");
		printf("Total Tests: %d\n", MAX_TESTS);
		printf("Total bugs: %d\n", numBugs);
		printf("To see debug messages for all lines, set DEBUG_MODE to 1\n");
	}	
	else
	{
		printf("\nRandom Card Test: Adventurer - All tests for playAdventurer() successful\n");
	}

	printf("\n----------End of Random Card Test: Adventurer----------\n");

	return 0;
}
