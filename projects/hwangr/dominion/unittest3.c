//Unit test for scoreFor() method in dominion.c

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


	printf ("\n----------Starting Unit Test 3----------\n\n");

	G.numPlayers = 2;
	G.handCount[0] = 0;
	G.discardCount[0] = 0;

	//Testing player hands only (no discards/decks)

	//Player 1 will have 1 scoring card at a time - 1st test = curse
	//Player 2 is just a dummy hand used to see if scoreFor() unexpectedly changes/uses any cards in it
	G.handCount[0] = 3;
	G.hand[0][0] = curse;
	G.hand[0][1] = adventurer;
	G.hand[0][2] = copper;

	G.handCount[1] = 4;
	G.hand[1][0] = curse;
	G.hand[1][1] = province;
	G.hand[1][2] = copper;
	G.hand[1][3] = adventurer;


	//Make copy prior to calling function
	memcpy(&copy, &G, sizeof(struct gameState));	
	
	//Call scoreFor() for player 0
	returnValue = scoreFor(0, &G);

	//Check if correct score was returned - Expected value = -1	
	//Also, scoreFor() should not use cards from Player 2's hand 
	numBugs += customAssert( (returnValue == -1), "Curse was not added from hand correctly." );


	//Testing if any members in the struct were incorrectly changed
	//Only coins should be changed by updateCoins(), so that was updated to the latest value
	//Also, other player's cards should not be modified
	returnValue = memcmp(&copy, &G, sizeof(struct gameState));
	
	numBugs += customAssert( (returnValue == 0), "Member in struct gameState incorrectly modified. No members should be changed." );


	//Test if estate card is applied correctly (expected score is 1)	
	G.hand[0][0] = estate;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 1), "Estate was not added from hand correctly." );

	//Test if duchy card is applied correctly (expected score is 3)	
	G.hand[0][0] = duchy;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 3), "Duchy was not added from hand correctly." );

	//Test if province card is applied correctly (expected score is 6)	
	G.hand[0][0] = province;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 6), "Province was not added from hand correctly." );

	//Test if great hall card is applied correctly (expected score is 1)	
	G.hand[0][0] = great_hall;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 1), "Great Hall was not added from hand correctly." );

	//Test if gardens card is applied correctly (expected score is 0, since less than 10 cards total)	
	G.hand[0][0] = gardens;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 0), "Gardens was not applied correctly for hand, handCount < 10." );

	//Gardens card checks total number of cards so we need to add more cards to hand (10 total)
	//Expected score is 1
	G.handCount[0] = 10;
	G.hand[0][0] = gardens;
	G.hand[0][1] = G.hand[0][2] = G.hand[0][3] = G.hand[0][4] = G.hand[0][5] = G.hand[0][6] = G.hand[0][7] 
	= G.hand[0][8] = G.hand[0][9] = copper;      

	returnValue = scoreFor(0, &G);
	
	numBugs += customAssert( (returnValue == 1), "Gardens was not applied correctly for handCount = 10." );


	//Test if two cards are added correctly (expected score is 4)	
	G.handCount[0] = 3;
	
	G.hand[0][0] = estate;
	G.hand[0][2] = duchy;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 4), "Multiple cards not added from hand correctly." );


	//Testing player discard

	//Player 1 will have 1 scoring card at a time - 1st test = curse
	//Player 2 is just a dummy hand used to see if scoreFor() unexpectedly changes/uses any cards in it
	G.handCount[0] = 0;
	G.discardCount[0] = 3;

	G.discard[0][0] = curse;
	G.discard[0][1] = adventurer;
	G.discard[0][2] = copper;
	//We don't want deck cards to affect results yet	
	G.deck[0][0] = copper;
	G.deck[0][1] = adventurer;
	G.deck[0][2] = copper;



	G.discardCount[1] = 4;
	G.discard[1][0] = curse;
	G.discard[1][1] = province;
	G.discard[1][2] = copper;
	G.discard[1][3] = adventurer;


	//Call scoreFor() for player 0
	returnValue = scoreFor(0, &G);

	//Check if correct score was returned - Expected value = -1	
	//Also, scoreFor() should not use cards from Player 2's hand 
	numBugs += customAssert( (returnValue == -1), "Curse was not added from discard correctly." );

	//Test if estate card is applied correctly (expected score is 1)	
	G.discard[0][0] = estate;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 1), "Estate was not added from discard correctly." );

	//Test if duchy card is applied correctly (expected score is 3)	
	G.discard[0][0] = duchy;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 3), "Duchy was not added from discard correctly." );

	//Test if province card is applied correctly (expected score is 6)	
	G.discard[0][0] = province;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 6), "Province was not added from discard correctly." );

	//Test if great hall card is applied correctly (expected score is 1)	
	G.discard[0][0] = great_hall;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 1), "Great Hall was not added from discard correctly." );

	//Test if gardens card is applied correctly (expected score is 0, since less than 10 cards total)	
	G.discard[0][0] = gardens;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 0), "Gardens was not applied correctly for discard, handCount < 10." );


	//Test if two cards are added correctly (expected score is 4)	
	G.discardCount[0] = 3;
	G.discard[0][0] = estate;
	G.discard[0][2] = duchy;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 4), "Multiple cards not added from discard correctly." );


	//Testing player deck 

	//Player 1 will have 1 scoring card at a time - 1st test = curse
	//Player 2 is just a dummy hand used to see if scoreFor() unexpectedly changes/uses any cards in it
	G.handCount[0] = 0;
	G.discardCount[0] = 3;

	//Only testing deck, so discard pile only has nonscoring cards
	G.discard[0][0] = copper;
	G.discard[0][1] = adventurer;
	G.discard[0][2] = copper;
	
	G.deck[0][0] = curse;
	G.deck[0][1] = adventurer;
	G.deck[0][2] = copper;



	G.discardCount[1] = 4;
	G.deck[1][0] = curse;
	G.deck[1][1] = province;
	G.deck[1][2] = copper;
	G.deck[1][3] = adventurer;

	//Call scoreFor() for player 0
	returnValue = scoreFor(0, &G);

	//Check if correct score was returned - Expected value = -1	
	//Also, scoreFor() should not use cards from Player 2's hand 
	numBugs += customAssert( (returnValue == -1), "Curse was not added from deck correctly." );

	//Test if estate card is applied correctly (expected score is 1)	
	G.deck[0][0] = estate;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 1), "Estate was not added from deck correctly." );

	//Test if duchy card is applied correctly (expected score is 3)	
	G.deck[0][0] = duchy;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 3), "Duchy was not added from deck correctly." );

	//Test if province card is applied correctly (expected score is 6)	
	G.deck[0][0] = province;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 6), "Province was not added from deck correctly." );

	//Test if great hall card is applied correctly (expected score is 1)	
	G.deck[0][0] = great_hall;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 1), "Great Hall was not added from deck correctly." );

	//Test if gardens card is applied correctly (expected score is 0, since less than 10 cards total)	
	G.deck[0][0] = gardens;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 0), "Gardens was not applied correctly for deck, handCount < 10." );


	//Test if two cards are added correctly (expected score is 4)	
	G.discardCount[0] = 3;
	G.deck[0][0] = estate;
	G.deck[0][2] = duchy;
	returnValue = scoreFor(0, &G);

	numBugs += customAssert( (returnValue == 4), "Multiple cards not added from deck correctly." );


	if(numBugs)
	{
		printf("Unit Test 3 - Total bugs: %d\n", numBugs);
	}	
	else
	{
		printf("Unit Test 3 - All tests for scoreFor() successful\n");
	}

	printf("\n----------End of Unit Test 3----------\n");

	return 0;
}
