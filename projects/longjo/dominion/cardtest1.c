/*******************************************************************
  cardtest1.c
  Village Card Test.
 
  This test will test the following conditions 
    1> Ensure that player has Drawn an additional Card
		-this serves as two tests, as adding a card will also trigger
		 a disgard.
    2> Ensure that Two action Cards were added to current game state

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

	
	int drawnCards = 1;
	int seed = 1000;
	struct gameState preG, postG;
    int newCards = 0;
    int discarded = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers = 2;
    int thisPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    //Announce test...
    printf(" ******** VILLAGE TEST by JOSEPH LONG ************\n\n");
    
    // initialize a game state and player cards
    printf("Initializing Game State...\n\n");
    initializeGame(numPlayers, k, seed, &preG);


    //Copy over the initialized game state to test game state...
    memcpy(&postG, &preG, sizeof(struct gameState));
    
    //Calling CardEffect...
    cardEffect(village, choice1, choice2, choice3, &postG, handpos, &bonus);

    //*********************FIRST TEST*********************************************
    printf("FIRST TEST:  \n\tCheck to see if an additional card was added to their deck...\n\n");


	//Capture Pre and Post Hand Count
	int pre = preG.handCount[thisPlayer] + (drawnCards - discarded);
	int post = postG.handCount[thisPlayer];
    
	//Expected to have this Number of cards
	printf("Current hand Count: %d\n", post);
	printf("Expected hand Count: %d\n", pre );

	//do an assertion check.
	if (pre == post)
		printf("\nADDITIONAL CARD ADDITION / DISGARD PASSED (one drawn/one disgarded");
	else
		printf("\nADDITION/DISGARD TEST FAILURE.\n");

	printf("\nEnd first Test...\n");



    
    //***************SECOND TEST, ACTION STATE INCREASE*************************
    printf("TEST TWO:  ACTION STATE SHOULD BE INCREASED BY TWO...\n");

    //Check that the difference in pre and post actions is two...
    if (  postG.numActions - preG.numActions  == 2 )
    {
        printf("\tPreAction Count: %d\n", preG.numActions);
        printf("\tPostAction Count: %d\n", postG.numActions);
        printf("TEST SUCCESSFULLY COMPLETED.\n");
    }
    else
    {
        printf("\tExpected a difference of two between pre/post number of Actions.\n");
        printf("\tPreAction Count: %d\n", preG.numActions);
        printf("\tPostAction Count: %d\n", postG.numActions);
        printf("TEST FAILED.\n");
    }
    

	printf("\nFINAL TEST FINISHED\n");
  

	return 0;
    
  
}


