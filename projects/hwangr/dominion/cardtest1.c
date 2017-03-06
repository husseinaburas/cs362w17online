//Unit test for the adventurer card in dominion.c

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

	G.handCount[0] = 0;
	G.discardCount[0] = 0;
	G.deckCount[0] = 5;
	G.deck[0][0] = copper;
	G.deck[0][1] = curse; 
	G.deck[0][2] = silver;
	G.deck[0][3] = estate;
	G.deck[0][4] = gold;

	//Player 2's cards are there as a dummy, to make sure they are not unintentially changed
	G.handCount[1] = 0;
	G.discardCount[1] = 0;
	G.deckCount[1] = 5;
	G.deck[1][0] = copper;
	G.deck[1][1] = curse; 
	G.deck[1][2] = silver;
	G.deck[1][3] = estate;
	G.deck[1][4] = gold;


	printf ("\n----------Starting Card Test 1: Adventurer----------\n\n");


	//Normall call to playAdventurer() for Player 1	
	returnValue = playAdventurer(&G, 0);

	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "Standard test - Call to playAdventurer() failed." );

	//Make sure player turn was not unintionally modified
	numBugs += customAssert( (G.whoseTurn == 0), "Player turn incorrectly changed." );

	//Make sure numActions was not unintionally modified
	numBugs += customAssert( (G.numActions == 1), "numActions incorrectly changed." );


	//Check that draw was done correctly for Player 1 (expected value of 2)
	numBugs += customAssert( (G.handCount[0] == 2), "Standard test - playAdventurer() failed to draw 2 treasure cards." );

	//Check the correct treasure cards were drawn for Player 1
	numBugs += customAssert( (G.hand[0][0] == copper), "Standard test - First card drawn should be copper." );
	numBugs += customAssert( (G.hand[0][1] == silver), "Standard test - Second card drawn should be silver." );

	//Check that deck was decremented correctly for Player 1 (expected value of 2)
	numBugs += customAssert( (G.deckCount[0] == 2), "Standard test - playAdventurer() failed to decrement deck count correctly." );

	
	//Check that Player 2's cards were unchanged	
	numBugs += customAssert( (G.handCount[1] == 0), "playAdventurer() should not modify Player 2's hand." );
	numBugs += customAssert( (G.discardCount[1] == 0), "playAdventurer() should not modify Player 2's discard pile." );
	numBugs += customAssert( (G.deckCount[1] == 5), "playAdventurer() should not modify Player 2's deck." );


	//Call to playAdventurer() with only one treasure card
	G.deck[0][0] = curse;
	G.deck[0][4] = estate;
	
	returnValue = playAdventurer(&G, 0);	
	
	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "1 treasure test - Call to playAdventurer() failed." );

	//Check that draw was done correctly for Player 1 (expected value of 1)
	numBugs += customAssert( (G.handCount[0] == 1), "1 treasure test - playAdventurer() failed to draw 1 treasure card." );

	//Check the correct treasure cards were drawn for Player 1
	numBugs += customAssert( (G.hand[0][0] == silver), "1 treasure test - card drawn should be silver." );

	//Check that deck was decremented correctly for Player 1 (expected value of 2)
	numBugs += customAssert( (G.deckCount[0] == 0), "1 treasure test - playAdventurer() failed to decrement deck count correctly." );

	//Call to playAdventurer() with 0 treasure cards
	G.deck[0][0] = curse;
	G.deck[0][2] = curse;
	G.deck[0][4] = estate;
	
	returnValue = playAdventurer(&G, 0);	
	
	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "0 treasure test - Call to playAdventurer() failed." );

	//Check that draw was done correctly for Player 1 (expected value of 0)
	numBugs += customAssert( (G.handCount[0] == 0), "0 treasure test - playAdventurer() failed to draw 0 treasure cards." );

	//Check that deck was decremented correctly for Player 1 (expected value of 2)
	numBugs += customAssert( (G.deckCount[0] == 0), "0 treasure test - playAdventurer() failed to decrement deck count correctly." );


	//Test shuffle functionality - deck size is set to 0, and all its cards are moved into discard pile
	G.discardCount[0] = 5;
	G.deckCount[0] = 0;
	G.discard[0][0] = copper;
	G.discard[0][1] = curse; 
	G.discard[0][2] = silver;
	G.discard[0][3] = estate;
	G.discard[0][4] = estate;

	returnValue = playAdventurer(&G, 0);	
	
	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "Shuffle test - Call to playAdventurer() failed." );

	//Check that draw was done correctly for Player 1 (expected value of 2)
	numBugs += customAssert( (G.handCount[0] == 2), "Shuffle test - playAdventurer() failed to draw 2 treasure cards." );

	//Check that deck was decremented correctly for Player 1 (expected value of 2)
	numBugs += customAssert( (G.deckCount[0] < 5), "Shuffle test - playAdventurer() failed to decrement deck count correctly." );



	if(numBugs)
	{
		printf("\nCard Test 1 - Total bugs: %d\n", numBugs);
	}	
	else
	{
		printf("\nCard Test 1 - All tests for playAdventurer() successful\n");
	}

	printf("\n----------End of Card Test 1----------\n");

	return 0;
}
