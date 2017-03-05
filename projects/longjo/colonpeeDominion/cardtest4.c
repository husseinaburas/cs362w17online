/*******************************************************************
  cardtest4.c
  ADVENTURER Card Test.
 
  This test will test the following conditions 
    1>

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


	//capture handCounts
	int preHand = 0;
	int postHand = 0;
    
    //Capture deckCounts
    int preDeck = 0;
    int postDeck = 0;
    
    //expected difference of 2 between pre and post hand counts
    int expectedDiff = 2;

    //Game State Variables...
	int seed = 1000;
	struct gameState preG, postG;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int numPlayers = 2;
	int thisPlayer = 0;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };


	//Announce test...
	printf(" ******** ADVENTURER TEST by JOSEPH LONG ************\n\n");

	// initialize a game state and player cards
	printf("Initializing Game State...\n\n");
	initializeGame(numPlayers, k, seed, &preG);


	//Copy over the initialized game state to test game state...
	memcpy(&postG, &preG, sizeof(struct gameState));
    
	//Calling CardEffect...
	cardEffect(adventurer, choice1, choice2, choice3, &postG, handpos, &bonus);


    //********************* HANDCOUNT TEST ************************************
    printf("\n\nHANDCOUNT TEST:  ADVENTURER...\n");
    printf("----------------------------------------\n");
    preHand  = preG.handCount[thisPlayer];
    postHand = postG.handCount[thisPlayer];
    
	
    
    
    
    if ( (postHand - preHand ) == expectedDiff )
    {
        printf("TEST PASSED:  \n");
        printf("----------------------------------------\n");
        printf("(PRE)HAND count: %d\n", preHand);
        printf("(POST)HAND count: %d\n", postHand);
        printf("Expected difference of two ( 2 ) upward between pre and post.\n");
    }
    else
    {
        printf("TEST FAILED ( PRE/POST HAND COUNT NOT WITHIN PARAMETERS:  \n");
        printf("----------------------------------------\n");
        printf("(PRE)HAND count: %d\n", preHand);
        printf("(POST)HAND count: %d\n", postHand);
    }
    
    

    //********************* DECKCOUNT TEST ************************************
    printf("\n\nDECKCOUNT TEST:  ADVENTURER...\n");
    printf("----------------------------------------\n");
    
    preDeck = preG.deckCount[thisPlayer];
    postDeck = postG.deckCount[thisPlayer];
    
    if ( (preDeck - postDeck) == expectedDiff  )
    {
        printf("TEST PASSED:  \n");
        printf("----------------------------------------\n");
        printf("preDeck: %d\n", preDeck);
        printf("postDeck: %d\n", postDeck);
    }
    else
    {
        printf("TEST FAILED:  \n");
        printf("----------------------------------------\n");
        printf("preDeck: %d\n", preDeck);
        printf("postDeck: %d\n", postDeck);
    }


	return 0;
    
  
}


