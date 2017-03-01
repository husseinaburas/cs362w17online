#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CARD TEST 1 - Smithy

int assertTrue(int a, int b, int* failed, int testNum)
{
    if (a == b)
        return 1;
    else
    {
        printf("playSmithy TEST FAILED %d\n", testNum);
        *failed = 1;
        return 0;
    }
}

void testSmithy(int player, struct gameState* testState)
{
    int failed = 0;
    int handCount = testState->handCount[player];
    int i = 0;
    for (i = 0; i < handCount; i++) //set all cards in hand to smithy
    {
        testState->hand[player][i] = smithy;
    }
    
    //copy gamestate to preTest - all actions will now be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    
    playSmithy(player, testState, 0); //run function we are testing
    
    //NOTE: TESTS 1 AND 2 WILL FAIL DUE TO BUGS IN THE CODE - THIS IS INTENTIONAL (FOR NOW)!
    
    /***********************************************************************
     TEST 1 - HAND SHOULD HAVE 2 MORE CARDS (DRAW 3 THEN DISCARD SMITHY)
     ***********************************************************************/
    assertTrue(preTest.handCount[player]+2, testState->handCount[player], &failed, 1);
    
    /***********************************************************************
     TEST 2 - DECK SHOULD BE DECREASED BY 3 CARDS
     ***********************************************************************/
    assertTrue(preTest.deckCount[player]-3, testState->deckCount[player], &failed, 2);
    
    //test if no changes to other players
    int j = 1;
    for (j = 1; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        /*************************************************
         TEST 3 - OTHER PLAYER'S HANDS SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
        {
            assertTrue(preTest.hand[j][i], testState->hand[j][i], &failed, 3);
        }
        /*************************************************
         TEST 4 - OTHER PLAYER'S DECKS SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
        {
            assertTrue(preTest.deck[j][i], testState->deck[j][i], &failed, 4);
        }
        /*************************************************
         TEST 5 - OTHER PLAYER'S DISCARD PILES SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.discardCount[j]; i++) //check all cards in discard pile
        {
            assertTrue(preTest.discard[j][i], testState->discard[j][i], &failed, 5);
        }
    }
    
    /***********************************************************************
     TEST 6 - PLAYEDCARDCOUNT SHOULD BE INCREMENTED
     ***********************************************************************/
    assertTrue(preTest.playedCardCount + 1, testState->playedCardCount, &failed, 6);
    
    /***********************************************************************
     TEST 7 - SMITHY SHOULD BE ON TOP OF PLAYED CARDS PILE
     ***********************************************************************/
    int playedCount = testState->playedCardCount;
    assertTrue(testState->playedCards[playedCount-1], smithy, &failed, 7);

    if (failed == 0)
        printf("playSmithy TEST PASSED\n");
}


int main(){
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    
    initializeGame(2, k, 1, &G);
    
    testSmithy(0, &G);
    
    return 0;
}
