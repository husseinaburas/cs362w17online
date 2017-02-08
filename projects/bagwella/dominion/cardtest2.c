/*
- Andrew Bagwell
- CS362 Assignment 3 
- bagwella@oregonGS.edu
- Test of dominion's adventurer card via the playAdventurer function 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

//custom assert function

void assertTrue(int val1, int val2) {

	if (val1 != val2)
		printf("Test Case - FAILED\n");
	else 
		printf("Test Case - PASSED\n");

}


//Testing adventurer card

int main()
{
	//set up variables for testing
	struct gameState GS;
	int c[10] = {adventurer, ambassador, gardens, great_hall, mine, minion, smithy, salvager, steward, village};
	//another list of cards to put on the deck for testing
	int deckCards[6] = {silver, council_room, gold, baron, mine, copper};
	int treasureDrawn = 0, priorHandCount, cardsDiscounted, cardDrawn = 0, z=0;
	int tempH[MAX_HAND];

	printf("*************************************\n");
	printf("cardtest2:\n");
  	printf("TESTING -- adventurer card -- BEGIN\n");

   //Standard initialization across all my tests...
	initializeGame(2, c, 5, &GS);

	//Set the current player's handcount to 1
  	GS.handCount[0] = 1;

	//set the current player's card to adventurer
	GS.hand[0][0] = adventurer;

	//set up the deck with some treasure cards spaced out so card will have to be discarded
	for (int i = 0; i < 6; i++) {

		GS.deck[0][i] = deckCards[i];
		GS.deckCount[0]++;
	}
	
	priorHandCount = GS.handCount[0];
	cardsDiscounted = GS.discardCount[0];
	
	printf("Calling playAdventurer..\n");
	printf("TESTING - playAdventurer() executes properly\n");
	assertTrue(playAdventurer(treasureDrawn, &GS, GS.whoseTurn, &tempH, cardDrawn, z), 0);

	printf("TESTING - playAdventurer()'s incrementing of handCount\n");
	assertTrue((GS.handCount[0] - priorHandCount), 1);

	printf("TESTING - playAdventurer adding treasure cards to player's hand\n");

	int treasureCount = 0;
	for (int x = 0; x < GS.handCount[0]; x++) {

		if (GS.hand[0][x]==gold || GS.hand[0][x]==silver || GS.hand[0][x]==copper) 
			treasureCount++;
	}

	assertTrue(treasureCount, 2);

	printf("TESTING - playAdventurer()'s discarding until 2 treasure cards are found\n");
	assertTrue((GS.discardCount[0] - cardsDiscounted), 2);

	printf("TESTING--adventurer card -- COMPLETE\n\n");
	
	return 0;
}