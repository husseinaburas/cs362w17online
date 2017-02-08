/*******************************************************************
unittest1.c
 
 This Test Will test the funciton numHandCards()
 This test will test that the following conditions are true:
 
    1>  Ensure Card Count in players Hand is Accurate upon game
        initialization.
    2>  Ensure Card Count in players Hand is Accurate when certain
        cards are played.
    3>  Check to see if Other Players hand is accurate when turn is
        Changed to other player...
 
 
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
    
    
    //Catch variables for hand count.
    int p1HandCount = 0;
    int p2HandCount = 0;
    
    //Expected Values of turns
    int handTurn = 5;
    int handNotTurn = 0;
    
    
    
    //Game State Variables
    int seed = 1000;
    struct gameState G;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers = 2;
    int thisPlayer = 0;
    int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room };
    
    // initialize a game state and player cards
    printf("Initializing Game State...\n\n");
    initializeGame(numPlayers, k, seed, &G);
    
    //Announce test...
    printf(" ******** UNIT TEST: numHandCards() ************\n\n");
    
    //TEST ONE...
    printf("TEST ONE:  Hand Count of Players upon Initialization\n");
    
    printf("Whose turn: %d\n", G.whoseTurn);
    
    
    //Capture Pre and Post Hand Count
    p1HandCount = G.handCount[thisPlayer] ;
    p2HandCount = G.handCount[thisPlayer + 1];
    
    
    
    //Assert that Actual vs Expected Hand Counts are Accurate...
    if ( (p1HandCount == handTurn) && (p2HandCount == handNotTurn) )
    {
        printf("************TEST PASSED**************\n");
        printf("P1: EXPECTED Hand Count: %d\n", handTurn);
        printf("P1: ACTUAL   Hand Count: %d\n", p1HandCount);
        printf("P2: EXPECTED Hand Count: %d\n", handNotTurn);
        printf("P2: ACTUAL   Hand Count: %d\n", p2HandCount);
        
    }
    else
    {
        printf("TEST FAILED:  EXPECTED vs ACTUAL Hand Counts OFF\n");
        printf("************TEST PASSED**************\n");
        printf("P1: EXPECTED Hand Count: %d\n", handTurn);
        printf("P1: ACTUAL   Hand Count: %d\n", p1HandCount);
        printf("P2: EXPECTED Hand Count: %d\n", handNotTurn);
        printf("P2: ACTUAL   Hand Count: %d\n", p2HandCount);
    }
    
    //Toggle player state turn...
    endTurn(&G);
    
    printf("Whose turn: %d\n", G.whoseTurn);
    
    return 0;
    

}


