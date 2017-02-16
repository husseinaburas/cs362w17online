//Unit test for the smithy card in dominion.c

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
	int returnValue;

	struct gameState G;
	G.numPlayers = 2;	
	G.whoseTurn = 0;
	G.numActions = 1;
	G.playedCardCount = 0;

	G.handCount[0] = 2;
	G.hand[0][0] = curse;
	G.hand[0][1] = smithy;
	G.discardCount[0] = 0;
	G.deckCount[0] = 5;
	G.deck[0][0] = copper;
	G.deck[0][1] = curse; 
	G.deck[0][2] = silver;
	G.deck[0][3] = estate;
	G.deck[0][4] = gold;

	//Player 2's cards are there as a dummy, to make sure they are not unintentially changed
	G.handCount[1] = 2;
	G.hand[1][0] = curse;
	G.hand[1][1] = smithy;
	G.discardCount[1] = 0;
	G.deckCount[1] = 5;
	G.deck[1][0] = copper;
	G.deck[1][1] = curse; 
	G.deck[1][2] = silver;
	G.deck[1][3] = estate;
	G.deck[1][4] = gold;


	printf ("\n----------Starting Card Test 2: Smithy----------\n\n");


	//Normal call to playSmithy() for Player 1	
	returnValue = playSmithy(&G, 0, 1);

	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "Standard test - Call to playSmithy() failed." );

	//Make sure player turn was not unintionally modified
	numBugs += customAssert( (G.whoseTurn == 0), "Player turn incorrectly changed." );

	//Make sure numActions was not unintionally modified
	numBugs += customAssert( (G.numActions == 1), "numActions incorrectly changed." );


	//Check that draw was done correctly for Player 1 (expected value of 4)
	numBugs += customAssert( (G.handCount[0] == 4), "Standard test - playSmithy() failed to draw the correct number of cards (3 cards)." );

	//Check that deck was decremented correctly for Player 1 (expected value of 2)
	numBugs += customAssert( (G.deckCount[0] == 2), "Standard test - playSmithy() failed to decrement deck count correctly." );

	//Check the smithy card was discarded correctly 
	numBugs += customAssert( (G.playedCards[0] == smithy), "Standard test - First card in discard pile should be smithy." );
	numBugs += customAssert( (G.playedCardCount == 1), "Standard test - playedCardCount not incremented correctly." );

	//Check that Player 2's cards were unchanged	
	numBugs += customAssert( (G.handCount[1] == 2), "playSmithy() should not modify Player 2's hand." );
	numBugs += customAssert( (G.discardCount[1] == 0), "playSmithy() should not modify Player 2's discard pile." );
	numBugs += customAssert( (G.deckCount[1] == 5), "playSmithy() should not modify Player 2's deck." );



	//Test playing smithy card with all cards in discard pile and no cards left in deck
	//Expect cards to be reshuffled and put back into deck
	G.handCount[0] = 2;
	G.hand[0][0] = curse;
	G.hand[0][1] = smithy;
	G.discardCount[0] = 5;
	G.deckCount[0] = 0;
	G.playedCardCount = 0;
	G.discard[0][0] = copper;
	G.discard[0][1] = curse; 
	G.discard[0][2] = silver;
	G.discard[0][3] = estate;
	G.discard[0][4] = gold;

	//Normal call to playSmithy() for Player 1	
	returnValue = playSmithy(&G, 0, 1);

	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "Shuffle test - Call to playSmithy() failed." );

	//Check that draw was done correctly for Player 1 (expected value of 3)
	numBugs += customAssert( (G.handCount[0] == 4), "Shuffle test - playSmithy() failed to draw the correct number of cards (3 cards)." );

	//Check the smithy card was discarded correctly 
	numBugs += customAssert( (G.playedCards[0] == smithy), "Shuffle test - First card in discard pile should be smithy." );
	numBugs += customAssert( (G.playedCardCount == 1), "Shuffle test - playedCardCount not incremented correctly." );


	//Check that deck was decremented correctly for Player 1 (expected value of 2)
	numBugs += customAssert( (G.deckCount[0] == 2), "Shuffle test - playSmithy() failed to decrement deck count correctly." );


	if(numBugs)
	{
		printf("\nCard Test 2 - Total bugs: %d\n", numBugs);
	}	
	else
	{
		printf("\nCard Test 2 - All tests for playSmithy() successful\n");
	}

	printf("\n----------End of Card Test 2----------\n");

	return 0;
}