/*******************************************************************
unittest2.c
 
 This Test Will test the funciton endTurn()
 This test will test that the following conditions are true:
 
    1>  Player is toggled over when function is called.
    2>  Hand Counts are set appropriately when function is called.
 
 
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
    
    //Expected Values of turns
    int handTurn = 5;
    int handNotTurn = 0;
    
    //Counter variable
    int i = 0;
    
    //fail flag
    int flag = 1;
 
    
    //Game State Variables
    int seed = 1000;
    struct gameState G;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers = 4;
    int thisPlayer = 0;
    int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room };
    
    // initialize a game state and player cards
    printf("Initializing Game State...\n\n");
    initializeGame(numPlayers, k, seed, &G);
    
    //Announce test...
    printf(" ******** UNIT TEST: endTurn() ************\n\n");
    
    //TEST ONE...
    printf("TEST ONE:  Check to see current players turn: \n");
    printf("Testing for %d player(s)...\n", numPlayers);
    
    //Enter testing loop...
    for ( i = 0 ; i < numPlayers ; i++ )
    {
        printf("EXPECTED whoseTurn: %d\n", i);
        printf("  ACTUAL whoseTurn: %d\n", G.whoseTurn);
        //set fail flag if test fails..
        if ( i != G.whoseTurn )
        {
            flag = 0;
        }
        endTurn(&G);
    }
    
    
    //Output Results...
    if ( flag != 0 )
    {
        printf("TEST PASSED...EXPECTED TURN(S) = ACTUAL TURN(s) on ALL TESTS \n");
    }
    else
    {
        printf("TEST FAILURE\n");
    }
    
    
    printf("******** END TEST ********\n");
    
    return 0;
    
 
    
    
}


