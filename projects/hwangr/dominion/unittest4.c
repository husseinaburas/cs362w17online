//Unit test for buyCard() method in dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int customAssert(int condition, char *errorMsg)
{
	if (condition)
	{
		return 0;
	}
	else
	{
		printf("Error: %s\n", errorMsg);
		return 1;	
	}
}


int main()
{
	int numBugs = 0;	//Stores total number of bugs encountered by unit test
	struct gameState G;
	struct gameState copy;
	int returnValue;


	printf ("\n----------Starting Unit Test 4----------\n");

	//Testing for two players 
	G.numPlayers = 2;
	G.whoseTurn = 0;
	G.supplyCount[0] = 2;
	G.coins = 100;		//More than enough coins to buy a card

	//Player 1 will be buying cards, always a curse card (supplyPos = 0)
	//Player 2 is just a dummy hand used to see if updateCoins() unexpectedly changes/uses any cards in it
	G.handCount[0] = 0;
	G.discardCount[0] = 0;
	G.deckCount[0] = 0;

	G.handCount[1] = 4;
	G.discardCount[1] = 0;
	G.deckCount[1] = 0;

	G.hand[1][0] = copper;
	G.hand[1][1] = estate;
	G.hand[1][2] = gold;
	G.hand[1][3] = adventurer;


	//Make copy prior to calling function
	memcpy(&copy, &G, sizeof(struct gameState));	

	//Test buyCard() for numBuys < 1 (expected value = -1)
	G.numBuys = 0;
	returnValue = buyCard(0, &G);
	numBugs += customAssert( (returnValue == -1), "buyCard() is supposed to return 0 for numBuys < 1." );

	//Attempt to buy card that is out of range (i.e. not a valid card)
	returnValue = buyCard(-1, &G);
	numBugs += customAssert( (returnValue == -1), "buyCard() is supposed to return 0 when trying to buy an invalid card (supplyPos < 0)." );
	returnValue = buyCard(500, &G);
	numBugs += customAssert( (returnValue == -1), "buyCard() is supposed to return 0 when trying to buy an invalid card (supplyPos > treasure_map)." );

	
	//Call buyCard() for empty hand
	G.numBuys = 2;
	returnValue = buyCard(0, &G);

	//Check if function executed successfully
	numBugs += customAssert( (returnValue == 0), "Call to buyCard() failed." );

	//Check that hand, discard, and decks for players 1 and 2 were changed correctly
	numBugs += customAssert( (G.handCount[0] == 0), "Player 1's hand is not supposed to be changed." );
	numBugs += customAssert( (G.discardCount[0] == 1), "Player 1's discard pile not incremented correctly." );
	numBugs += customAssert( (G.deckCount[0] == 0), "Player 1's deck is not supposed to be changed." );
	numBugs += customAssert( (G.handCount[1] == 4), "Player 2's hand is not supposed to be changed." );
	numBugs += customAssert( (G.discardCount[1] == 0), "Player 2's discard pile is not supposed to be changed." );
	numBugs += customAssert( (G.deckCount[1] == 0), "Player 2's deck is not supposed to be changed." );

	//Buy card again, should still be successful since numBuys is now equal to 1 
	returnValue = buyCard(0, &G);

	//Check if function executed successfully
	numBugs += customAssert( (returnValue == 0), "Call to buyCard() failed." );

	//Check that hand, discard, and decks for players 1 and 2 were changed correctly
	numBugs += customAssert( (G.handCount[0] == 0), "Player 1's hand is not supposed to be changed." );
	numBugs += customAssert( (G.discardCount[0] == 2), "Player 1's discard pile not incremented correctly." );
	numBugs += customAssert( (G.deckCount[0] == 0), "Player 1's deck is not supposed to be changed." );
	numBugs += customAssert( (G.handCount[1] == 4), "Player 2's hand is not supposed to be changed." );
	numBugs += customAssert( (G.discardCount[1] == 0), "Player 2's discard pile is not supposed to be changed." );
	numBugs += customAssert( (G.deckCount[1] == 0), "Player 2's deck is not supposed to be changed." );


	//Buy card again, this time, it should fail since we are out of buys 
	returnValue = buyCard(0, &G);

	//Check if function executed successfully
	numBugs += customAssert( (returnValue == -1), "numBuys not decremented properly." );

	//Check that hand, discard, and decks for players 1 and 2 were left unchanged
	numBugs += customAssert( (G.handCount[0] == 0), "Player 1's hand is not supposed to be changed." );
	numBugs += customAssert( (G.discardCount[0] == 2), "Player 1's discard pile is not supposed to be changed." );
	numBugs += customAssert( (G.deckCount[0] == 0), "Player 1's deck is not supposed to be changed." );
	numBugs += customAssert( (G.handCount[1] == 4), "Player 2's hand is not supposed to be changed." );
	numBugs += customAssert( (G.discardCount[1] == 0), "Player 2's discard pile is not supposed to be changed." );
	numBugs += customAssert( (G.deckCount[1] == 0), "Player 2's deck is not supposed to be changed." );


	//Test buying card without enough coins 
	G.coins = 1;
	returnValue = buyCard(0, &G);

	//Check if function executed successfully
	numBugs += customAssert( (returnValue == -1), "buyCard() is not supposed to execute since there are not enough coins." );

	//Check that hand, discard, and decks for players 1 and 2 were left unchanged
	numBugs += customAssert( (G.handCount[0] == 0), "Player 1's hand is not supposed to be changed." );
	numBugs += customAssert( (G.discardCount[0] == 2), "Player 1's discard pile is not supposed to be changed." );
	numBugs += customAssert( (G.deckCount[0] == 0), "Player 1's deck is not supposed to be changed." );
	numBugs += customAssert( (G.handCount[1] == 4), "Player 2's hand is not supposed to be changed." );
	numBugs += customAssert( (G.discardCount[1] == 0), "Player 2's discard pile is not supposed to be changed." );
	numBugs += customAssert( (G.deckCount[1] == 0), "Player 2's deck is not supposed to be changed." );



	if(numBugs)
	{
		printf("\nUnit Test 4 - Total bugs: %d\n", numBugs);
	}	
	else
	{
		printf("\nUnit Test 4 - All tests for buyCard() successful\n");
	}

	printf("\n----------End of Unit Test 4----------\n");

	return 0;
}
