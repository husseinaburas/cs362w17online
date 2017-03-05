/*******************************************************************
  cardtest2.c
  COUNCIL ROOM Card Test.
 
  This test will test the following conditions 
    1> Ensure that player has Drawn Four Cards
		<less the discarded card>
    2> Ensure that State of Buys for player has increased by 1
	3> Ensured that other player(s) have drawn additional card.
	4> Played Card goes back to drawnCard pile.

 ********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>




//Added this function to help me with my testing....
//outputs "press any key to continue"...
void cont()
{
    char ch;
    printf("Press ENTER key to Continue\n");
    scanf("%c",&ch);
}

int main()

{

	//Placeholder to keep tabs on fact a card is drawn when cardEffect is called.
	int drawnCards = 4; 

	//Catch variables for drawCard() test.
	int expectedDeckCount = 0;
	int actualDeckCount = 0;

	int seed = 1000;
	struct gameState preG, postG;
	int discarded = 1;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int numPlayers = 2;
	int thisPlayer = 0;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };


	//Announce test...
	printf(" ******** COUNCIL ROOM TEST by JOSEPH LONG ************\n\n");

	// initialize a game state and player cards
	printf("Initializing Game State...\n\n");
	initializeGame(numPlayers, k, seed, &preG);


	//Copy over the initialized game state to test game state...
	memcpy(&postG, &preG, sizeof(struct gameState));

	//Calling CardEffect...
	cardEffect(council_room, choice1, choice2, choice3, &postG, handpos, &bonus);

	//capture buys...
	int buysPost = postG.numBuys;

    //*********************FIRST TEST*********************************************
    printf("FIRST TEST:  \n\tFOUR CARDS ADDED?...\n\n");


	//Capture Pre and Post Hand Count
	int pre = preG.handCount[thisPlayer] + (drawnCards - discarded);
	int post = postG.handCount[thisPlayer];
    
	//Expected to have this Number of cards
	printf("Current hand Count: %d\n", post);
	printf("Expected hand Count: %d\n", pre );

	//do an assertion check.
	if (pre == post)
		printf("\nPASSED:  Four Cards added");
	else
		printf("\nTEST FAILURE.\n");

	printf("\nEnd first Test...\n");



    
    //***************SECOND TEST, STATE CHANGE ( BUYS INC )*************************

	int buysPre = preG.numBuys;
	printf("Number of buys is: %d\n", buysPre);

	//Check to see if Amount of buys Increased by +1
	if (buysPost - buysPre == 1)
	{
		printf("\nPASSED:  BUY COUNT INCREASED BY +1, CURRENTLY AT: %d\n", buysPost);
	}
	else
	{
		printf("BUY COUNT FAILED, expected 2, at %d\n", buysPost);
	}
	

	//*****************THIRD TEST, OTHER PLAYER DRAW CARD COUNT ***************
	printf("\n*******************************************\n");
	printf("\nThis test will check that the other player(s) have drawn an additional card.\n");


	//CAPTURE pre and post deckCount values 
	expectedDeckCount = (preG.deckCount[thisPlayer + 1]) - 1;
	actualDeckCount = postG.deckCount[thisPlayer + 1];

	if (expectedDeckCount == actualDeckCount)
	{
		printf("Expected deckCount of other player: %d\n", expectedDeckCount);
		printf("Actual deckCount of other player:   %d\n", actualDeckCount);
		printf("PASSED: drawCard() exam\n");
	}
	else
		printf("\nDECK COUNT TEST FAILED...\n");

	printf("\n**END UNIT TEST COUNCIL ROOM CARD...\n");
	return 0;
    
  
}


