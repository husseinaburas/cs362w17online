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
    
    /*
    
    
    
    
    
    
    
    
    //Copy over the initialized game state to test game state...
    memcpy(&postG, &preG, sizeof(struct gameState));
    
    //Calling CardEffect...
    cardEffect(smithy, choice1, choice2, choice3, &postG, handpos, &bonus);
    
    //printf("played card count: %d\n", preG.playedCardCount);
    //printf("played card count: %d\n", postG.playedCardCount);
    
    
    
    //*********************FIRST TEST*********************************************
    printf("FIRST TEST:  PLAYER RECEIVED THREE(3) CARDS...\n");
    
    
    //Capture Pre and Post Hand Count
    int pre = preG.handCount[thisPlayer] - discarded + smithyCards ;
    int post = postG.handCount[thisPlayer];
    
    //Expected to have this Number of cards
    printf("Current hand Count: %d\n", pre);
    printf("Expected hand Count: %d\n", post );
    
    //do an assertion check.
    if (pre == post)
        printf("\nPASSED:  THREE Cards added");
    else
        printf("\nTEST FAILURE.\n");
    
    printf("\nEnd first Test...\n");
    
    
    
    
    //***************TEST 2:  CHECK PLAYERS HAND *************************
    //check to see if those cards came from players deck...
    preDeck = preG.deckCount[thisPlayer] - smithyCards;
    postDeck = postG.deckCount[thisPlayer];
    
    printf("PreDeck value: %d\n", preDeck);
    printf("PostDeck Value: %d\n", postDeck);
    
    //Run Assertion Test...
    if (preDeck == postDeck)
    {
        printf("DECKCOUNT TEST PASSSED \n");
        printf("PreDeck value less 3: %d\n", preDeck);
        printf("PostDeck Value:       %d\n", postDeck);
    }
    else
    {
        printf("TEST FAILED....\n");
    }
    
    
    
    
    
    //***************** TEST 3: PLAYER STATE COUNT ***************
    printf("\n*******************************************\n");
    printf("\nThis test will check the state of other players' attributes.\n");
    
    int hcPre = preG.handCount[thisPlayer + 1];
    int hcPost = postG.handCount[thisPlayer + 1];
    
    int dcPre = preG.deckCount[thisPlayer + 1];
    int dcPost = postG.deckCount[thisPlayer + 1];
    
    int dsPre = preG.discardCount[thisPlayer + 1];
    int dsPost = postG.discardCount[thisPlayer + 1];
    
    
    
    
    if ( (hcPre == hcPost) && (dcPre == dcPost) && (dsPre == dsPost) )
    {
        printf("Expected handCount of other player:      %d\n", hcPre);
        printf("Actual handCount of other player:        %d\n\n", hcPost);
        
        printf("Expected deckCount of other player:      %d\n", dcPre);
        printf("Actual deckCount of other player:	     %d\n\n", dcPost);
        
        printf("Expected disCardCount of other player:   %d\n", dsPre);
        printf("Actual discardCount of other player:     %d\n", dsPost);
        
        printf("PASSED: PLAYER STATE...\n");
    }
    else
        printf("\nPLAYER STATE FAILED...\n");
    
    printf("\n**END SMITHY CARD TEST...\n");
    return 0;
    
    */
}


