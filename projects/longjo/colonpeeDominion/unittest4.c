/*******************************************************************
 unittest4.c
 
 This Test Will test the funciton scoreFor()
 This test will test that the following condition(s) are true:
 
    1)  Given a players pre-set hand ( manually set by developer )
        the score will be equal to what is expected.
 
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
    
    //Capture Current Score:
    int playerScore = 0;
    
    //Expected Score, all provinces
    int allProvinces = 30;
    
    //index variable
    int i = 0;
    
    //Game State Variables
    int seed = 1000;
    struct gameState G;
    int numPlayers = 4;
    int thisPlayer = 0;
    int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room };
    
    
    
    // initialize a game state and player cards
    printf("Initializing Game State...\n\n");
    initializeGame(numPlayers, k, seed, &G);
    
    //Announce test...
    printf(" ******** UNIT TEST: scoreFor() ************\n\n");
    

    //capture player score
    playerScore = scoreFor(thisPlayer, &G);
    //output player score
    printf("Player's score is: %d\n", playerScore);
    
    //Output Hand..
    for (i = 0; i < G.handCount[thisPlayer]; i++)
    {
        
        printf("Card is: %d\n", G.hand[thisPlayer][i] );
    }
    
    //set players hand to all provinces.
    for (i = 0; i < G.handCount[thisPlayer]; i++)
    {
        //Set equal to province
        G.hand[thisPlayer][i] = province;
        
        printf("Card is: %d\n", G.hand[thisPlayer][i] );
    }

    //capture player score
    playerScore = scoreFor(thisPlayer, &G);
    //output player score
    printf("Player's score is: %d\n", playerScore);
    
    if ( playerScore == allProvinces)
    {
        printf("TEST PASSED\n");
        printf("----------------------\n");
        printf("EXPECTED SCORE:  %d\n", allProvinces);
        printf("  ACTUAL SCORE:  %d\n", playerScore);
    }
    else
    {
        printf("TEST FAILED\n");
        printf("----------------------\n");
        printf("EXPECTED SCORE:  %d\n", allProvinces);
        printf("  ACTUAL SCORE:  %d\n", playerScore);
    }

    return 0;
   
}


