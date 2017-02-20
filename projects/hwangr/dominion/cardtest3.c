//Unit test for the council room card in dominion.c

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
	G.numPlayers = 3;	
	G.whoseTurn = 0;
	G.numActions = 1;
	G.playedCardCount = 0;

	G.handCount[0] = 2;
	G.hand[0][0] = curse;
	G.hand[0][1] = council_room;
	G.discardCount[0] = 0;
	G.deckCount[0] = 5;
	G.deck[0][0] = copper;
	G.deck[0][1] = curse; 
	G.deck[0][2] = silver;
	G.deck[0][3] = estate;
	G.deck[0][4] = gold;

	//Player 2 will also be used, since this has multiple players drawing cards	
	G.handCount[1] = 2;
	G.hand[1][0] = curse;
	G.hand[1][1] = council_room;
	G.discardCount[1] = 0;
	G.deckCount[1] = 5;
	G.deck[1][0] = copper;
	G.deck[1][1] = curse; 
	G.deck[1][2] = silver;
	G.deck[1][3] = estate;
	G.deck[1][4] = gold;

	//Player 3 will also be used, since this has multiple players drawing cards	
	G.handCount[2] = 2;
	G.hand[2][0] = curse;
	G.hand[2][1] = council_room;
	G.discardCount[2] = 0;
	G.deckCount[2] = 5;
	G.deck[2][0] = copper;
	G.deck[2][1] = curse; 
	G.deck[2][2] = silver;
	G.deck[2][3] = estate;
	G.deck[2][4] = gold;


	printf ("\n----------Starting Card Test 3: Council Room----------\n\n");


	//Normal call to playCouncil_Room() for Player 1	
	returnValue = playCouncil_Room(&G, 0, 1);

	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "Player 1 test - Call to playCouncil_Room() failed." );

	//Make sure player turn was not unintionally modified
	numBugs += customAssert( (G.whoseTurn == 0), "Player turn incorrectly changed." );

	//Make sure numActions was not unintionally modified
	numBugs += customAssert( (G.numActions == 1), "numActions incorrectly changed." );


	//Check that draw was done correctly for Player 1 (expected value of 4)
	numBugs += customAssert( (G.handCount[0] == 5), "Player 1 test - failed to draw the correct number of cards for Player 1 (4 cards)." );

	//Check that deck was decremented correctly for Player 1 (expected value of 2)
	numBugs += customAssert( (G.deckCount[0] == 1), "Player 1 test - failed to decrement deck count correctly for Player 1." );

	//Check the smithy card was discarded correctly 
	numBugs += customAssert( (G.playedCards[0] == council_room), "Player 1 test - First card in discard pile should be council room." );
	numBugs += customAssert( (G.playedCardCount == 1), "Player 1 test - playedCardCount not incremented correctly." );

	//Check that Player 2 drew cards
	numBugs += customAssert( (G.handCount[1] == 3), "Player 1 test - Player 2 did not draw correct number of cards." );
	numBugs += customAssert( (G.discardCount[1] == 0), "Player 1 test - playCouncil_Room() should not modify Player 2's discard pile." );
	numBugs += customAssert( (G.deckCount[1] == 4), "Player 1 test - failed to decrement Player 2's deck count correctly." );

	//Check that Player 3 drew cards
	numBugs += customAssert( (G.handCount[2] == 3), "Player 1 test - Player 3 did not draw correct number of cards." );
	numBugs += customAssert( (G.discardCount[2] == 0), "Player 1 test - playCouncil_Room() should not modify Player 3's discard pile." );
	numBugs += customAssert( (G.deckCount[2] == 4), "Player 1 test - failed to decrement Player 3's deck count correctly." );


	//Repeat test for Player 2
	G.playedCardCount = 0;

	G.handCount[0] = 2;
	G.hand[0][0] = curse;
	G.hand[0][1] = council_room;
	G.discardCount[0] = 0;
	G.deckCount[0] = 5;
	G.deck[0][0] = copper;
	G.deck[0][1] = curse; 
	G.deck[0][2] = silver;
	G.deck[0][3] = estate;
	G.deck[0][4] = gold;

	G.handCount[1] = 2;
	G.hand[1][0] = curse;
	G.hand[1][1] = council_room;
	G.discardCount[1] = 0;
	G.deckCount[1] = 5;
	G.deck[1][0] = copper;
	G.deck[1][1] = curse; 
	G.deck[1][2] = silver;
	G.deck[1][3] = estate;
	G.deck[1][4] = gold;

	G.handCount[2] = 2;
	G.hand[2][0] = curse;
	G.hand[2][1] = council_room;
	G.discardCount[2] = 0;
	G.deckCount[2] = 5;
	G.deck[2][0] = copper;
	G.deck[2][1] = curse; 
	G.deck[2][2] = silver;
	G.deck[2][3] = estate;
	G.deck[2][4] = gold;

	//Normal call to playCouncil_Room() for Player 2	
	returnValue = playCouncil_Room(&G, 0, 1);

	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "Player 2 test - Call to playCouncil_Room() failed." );

	//Make sure player turn was not unintionally modified
	numBugs += customAssert( (G.whoseTurn == 0), "Player turn incorrectly changed." );

	//Make sure numActions was not unintionally modified
	numBugs += customAssert( (G.numActions == 1), "numActions incorrectly changed." );


	//Check that draw was done correctly for Player 2 (expected value of 4)
	numBugs += customAssert( (G.handCount[1] == 5), "Player 2 test - failed to draw the correct number of cards for Player 2 (4 cards)." );

	//Check that deck was decremented correctly for Player 2 (expected value of 2)
	numBugs += customAssert( (G.deckCount[1] == 1), "Player 2 test - failed to decrement deck count correctly for Player 2." );

	//Check the smithy card was discarded correctly 
	numBugs += customAssert( (G.playedCards[0] == council_room), "Player 2 test - First card in discard pile should be council room." );
	numBugs += customAssert( (G.playedCardCount == 1), "Player 2 test - playedCardCount not incremented correctly." );

	//Check that Player 1 drew cards
	numBugs += customAssert( (G.handCount[0] == 3), "Player 2 test - Player 1 did not draw correct number of cards." );
	numBugs += customAssert( (G.discardCount[0] == 0), "Player 2 test - playCouncil_Room() should not modify Player 1's discard pile." );
	numBugs += customAssert( (G.deckCount[0] == 4), "Player 2 test - failed to decrement Player 1's deck count correctly." );

	//Check that Player 3 drew cards
	numBugs += customAssert( (G.handCount[2] == 3), "Player 2 test - Player 3 did not draw the correct number of cards." );
	numBugs += customAssert( (G.discardCount[2] == 0), "Player 2 test - playCouncil_Room() should not modify Player 3's discard pile." );
	numBugs += customAssert( (G.deckCount[2] == 4), "Player 2 test - failed to decrement Player 3's deck count correctly." );




	if(numBugs)
	{
		printf("\nCard Test 3 - Total bugs: %d\n", numBugs);
	}	
	else
	{
		printf("\nCard Test 3 - All tests for playCouncil_Room() successful\n");
	}

	printf("\n----------End of Card Test 3----------\n");

	return 0;
}
