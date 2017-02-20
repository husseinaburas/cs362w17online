//Unit test for the steward card in dominion.c

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
	G.coins = 0;

	G.handCount[0] = 2;
	G.hand[0][0] = curse;
	G.hand[0][1] = steward;
	G.discardCount[0] = 0;
	G.deckCount[0] = 5;
	G.deck[0][0] = copper;
	G.deck[0][1] = curse; 
	G.deck[0][2] = silver;
	G.deck[0][3] = estate;
	G.deck[0][4] = gold;

	//Player 2 will act as a dummy to ensure values are not unintentionally modified 
	G.handCount[1] = 0;
	G.discardCount[1] = 0;
	G.deckCount[1] = 5;
	G.deck[1][0] = copper;
	G.deck[1][1] = curse; 
	G.deck[1][2] = silver;
	G.deck[1][3] = estate;
	G.deck[1][4] = gold;


	printf ("\n----------Starting Card Test 4: Steward----------\n\n");


	//Test choice 1 - draw 2 cards	
	returnValue = playSteward(&G, 0, 1, 1, -1, -1);

	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "Draw test - Call to playSteward() failed." );

	//Make sure player turn was not unintionally modified
	numBugs += customAssert( (G.whoseTurn == 0), "Player turn incorrectly changed." );

	//Make sure numActions was not unintionally modified
	numBugs += customAssert( (G.numActions == 1), "numActions incorrectly changed." );

	//Make sure coins was not unintionally modified
	numBugs += customAssert( (G.coins == 0), "coins incorrectly changed." );


	//Check that draw was done correctly for Player 1 (expected value of 4)
	numBugs += customAssert( (G.handCount[0] == 3), "Draw test - failed to draw the correct number of cards for Player 1 (2 cards)." );

	//Check that deck was decremented correctly for Player 1 (expected value of 3)
	numBugs += customAssert( (G.deckCount[0] == 3), "Draw test - failed to decrement deck count correctly for Player 1." );

	//Check the smithy card was discarded correctly 
	numBugs += customAssert( (G.playedCards[0] == steward), "Draw test - First card in discard pile should be steward." );
	numBugs += customAssert( (G.playedCardCount == 1), "Draw test - playedCardCount not incremented correctly." );

	//Check that Player 2's hand, discard and deck were not modified 
	numBugs += customAssert( (G.handCount[1] == 0), "Draw test - Player 2's hand should not be modified." );
	numBugs += customAssert( (G.discardCount[1] == 0), "Draw test - Player 2's discard pile should not be modified." );
	numBugs += customAssert( (G.deckCount[1] == 5), "Draw test - Player 2's deck should not be modified." );

	//Check that playedCard pile is not changed
	numBugs += customAssert( (G.playedCardCount == 1), "Draw test - Card discard not done properly." );


	//Reset gamestate
	G.numPlayers = 2;	
	G.whoseTurn = 0;
	G.numActions = 1;
	G.playedCardCount = 0;
	G.coins = 0;

	G.handCount[0] = 2;
	G.hand[0][0] = curse;
	G.hand[0][1] = steward;
	G.discardCount[0] = 0;
	G.deckCount[0] = 5;
	G.deck[0][0] = copper;
	G.deck[0][1] = curse; 
	G.deck[0][2] = silver;
	G.deck[0][3] = estate;
	G.deck[0][4] = gold;

	G.handCount[1] = 0;
	G.discardCount[1] = 0;
	G.deckCount[1] = 5;
	G.deck[1][0] = copper;
	G.deck[1][1] = curse; 
	G.deck[1][2] = silver;
	G.deck[1][3] = estate;
	G.deck[1][4] = gold;


	//Test choice 2 - get 2 coins	
	returnValue = playSteward(&G, 0, 1, 2, -1, -1);

	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "Coin test - Call to playSteward() failed." );

	//Make sure player turn was not unintionally modified
	numBugs += customAssert( (G.whoseTurn == 0), "Player turn incorrectly changed." );

	//Make sure numActions was not unintionally modified
	numBugs += customAssert( (G.numActions == 1), "numActions incorrectly changed." );

	//Make sure coins was correctly incremented by 2 
	numBugs += customAssert( (G.coins == 2), "Coins not added correctly." );

	//Check that Player 1's hand, discard and deck were not modified 
	numBugs += customAssert( (G.handCount[0] == 1), "Coin test - Player 1's hand not modified correctly." );
	numBugs += customAssert( (G.discardCount[0] == 0), "Coin test - Player 1's discard pile should not be modified." );
	numBugs += customAssert( (G.deckCount[0] == 5), "Coin test - Player 1's deck should not be modified." );

	//Check that Player 2's hand, discard and deck were not modified 
	numBugs += customAssert( (G.handCount[1] == 0), "Coin test - Player 2's hand should not be modified." );
	numBugs += customAssert( (G.discardCount[1] == 0), "Coin test - Player 2's discard pile should not be modified." );
	numBugs += customAssert( (G.deckCount[1] == 5), "Coin test - Player 2's deck should not be modified." );

	//Check that playedCard pile is not changed
	numBugs += customAssert( (G.playedCardCount == 1), "Coin test - Card discard not done properly." );


	//Reset gamestate
	G.numPlayers = 2;	
	G.whoseTurn = 0;
	G.numActions = 1;
	G.playedCardCount = 0;
	G.coins = 0;

	G.handCount[0] = 4;
	G.hand[0][0] = curse;
	G.hand[0][1] = steward;
	G.hand[0][2] = copper;
	G.hand[0][3] = copper;
	G.discardCount[0] = 0;
	G.deckCount[0] = 5;
	G.deck[0][0] = copper;
	G.deck[0][1] = curse; 
	G.deck[0][2] = silver;
	G.deck[0][3] = estate;
	G.deck[0][4] = gold;

	G.handCount[1] = 0;
	G.discardCount[1] = 0;
	G.deckCount[1] = 5;
	G.deck[1][0] = copper;
	G.deck[1][1] = curse; 
	G.deck[1][2] = silver;
	G.deck[1][3] = estate;
	G.deck[1][4] = gold;


	//Test choice - trash 2 cards 
	returnValue = playSteward(&G, 0, 1, 3, 0, 3);

	//Make sure function called and exited successfully
	numBugs += customAssert( (returnValue == 0), "Trash test - Call to playSteward() failed." );

	//Make sure player turn was not unintionally modified
	numBugs += customAssert( (G.whoseTurn == 0), "Player turn incorrectly changed." );

	//Make sure numActions was not unintionally modified
	numBugs += customAssert( (G.numActions == 1), "numActions incorrectly changed." );

	//Make sure coins was not changed 
	numBugs += customAssert( (G.coins == 0), "Coins not added correctly." );

	//Check that Player 1's hand, discard and deck were not modified 
	numBugs += customAssert( (G.handCount[0] == 1), "Trash test - Player 1's hand not modified correctly." );
	numBugs += customAssert( (G.discardCount[0] == 0), "Trash test - Player 1's discard pile should not be modified." );
	numBugs += customAssert( (G.deckCount[0] == 5), "Trash test - Player 1's deck should not be modified." );

	//Check that Player 2's hand, discard and deck were not modified 
	numBugs += customAssert( (G.handCount[1] == 0), "Trash test - Player 2's hand should not be modified." );
	numBugs += customAssert( (G.discardCount[1] == 0), "Trash test - Player 2's discard pile should not be modified." );
	numBugs += customAssert( (G.deckCount[1] == 5), "Trash test - Player 2's deck should not be modified." );

	//Check that playedCard pile is not changed
	numBugs += customAssert( (G.playedCardCount == 1), "Trash test - Card discard not done properly." );


	if(numBugs)
	{
		printf("\nCard Test 4 - Total bugs: %d\n", numBugs);
	}	
	else
	{
		printf("\nCard Test 4 - All tests for playSteward() successful\n");
	}

	printf("\n----------End of Card Test 4----------\n");

	return 0;
}
