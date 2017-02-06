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
	int playedCardsCount, handCount, cardPlayed, actionCount, cardsNum, treasureDrawn = 0, priorHandCount, cardsDiscounted, cardDrawn = 0, z=0;
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

	//set up the deck
	GS.deck[0][0] = copper;
	GS.deck[0][1] = council_room;
	GS.deck[0][2] = steward;
	GS.deck[0][4] = silver; 
	GS.deck[0][5] = minion;
	
	priorHandCount = GS.handCount[0];
	cardsDiscounted = GS.discardCount[0];
	
	printf("Calling playAdventurer..\n");
	playAdventurer(treasureDrawn, &GS, GS.whoseTurn, &tempH, cardDrawn, z);

	printf("TESTING - playAdventurer()'s incrementing of handCount\n");
	assertTrue((GS.handCount[0] - priorHandCount), 1);


	printf("TESTING - playAdventurer()'s incrementing of handCount\n");
	assertTrue((GS.discardCount[0] - cardsDiscounted), 3);

	printf("TESTING--adventurer card -- COMPLETE\n\n");
	
	return 0;
}