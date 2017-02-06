/*******************************************************************
 unittest3.c
 
 This Test Will test the funciton updateCoins()
 This test will test that the following condition(s) are true:
 
    1)  Bonus Coins will be added to current coin state
    2)  Coin State will Reflect change
 
 
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
    
  
    //Capture Variable
    int currentCoins = 0;
    int expectedCoins =0;
    int bonusCoins = 40;
    int postCoins = 0;
    
    
    //Capture Current Score:
    int playerScore = 0;
    
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
    printf(" ******** UNIT TEST: updateCoins() ************\n\n");
    
    //capture player score
    //playerScore = scoreFor(thisPlayer, &G);
    
//    //Output Hand..
//    for (i = 0; i < G.handCount[thisPlayer]; i++)
//    {
//        
//        printf("Card is: %d\n", G.hand[thisPlayer][i] );
//        
//        /*
//         if (state->hand[player][i] == copper)
//         {
//         state->coins += 1;
//         }
//         else if (state->hand[player][i] == silver)
//         {
//         state->coins += 2;
//         }
//         else if (state->hand[player][i] == gold)
//         {
//         state->coins += 3;
//         }	*/
//    }
    
    
    //Capture Current coin state
    currentCoins = G.coins;
    printf("Coin State: %d\n", G.coins);
    
    //expected value of coins..
    expectedCoins = currentCoins + bonusCoins;
    
    //Adding bonus coins and checking to see if its reflected...
    updateCoins(thisPlayer, &G, bonusCoins);
    postCoins = G.coins;
    
    
    
    
    if ( expectedCoins == postCoins )
    {
        printf("TEST PASSED\n");
        printf("*******************************\n");
        printf("EXPECTED COIN VALUE: %d\n", expectedCoins);
        printf("ACTUAL COIN VALUE: %d\n", postCoins );
    }
    else
    {
        printf("TEST FAILED....\n");
        printf("EXPECTED AND ACTUAL COIN VALUES NOT EQUAL\n");
        printf("EXPECTED COIN VALUE: %d\n", expectedCoins);
        printf("ACTUAL COIN VALUE: %d\n", postCoins );
    }
    
    
    
    //Check to see expected value...
    
    
//    for (i = 0; i < G.handCount[thisPlayer]; i++)
//    {
//        
//        printf("Card is: %d\n", G.hand[thisPlayer][i] );
//        
//        /*
//        if (state->hand[player][i] == copper)
//        {
//            state->coins += 1;
//        }
//        else if (state->hand[player][i] == silver)
//        {
//            state->coins += 2;
//        }
//        else if (state->hand[player][i] == gold)
//        {
//            state->coins += 3;
//        }	*/
//    }
//    
//    printf("Current Score: %d\n", playerScore);
//    cont();
    return 0;
    
    /*
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
     
     
     */
    
    
    
    
    
}


