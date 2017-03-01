#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CARD TEST 3 - Village

int assertTrue(int a, int* failed, int testNum)
{
    if (a == 1)
        return 1;
    else
    {
        printf("playVillage TEST FAILED %d\n", testNum);
        *failed = 1;
        return 0;
    }
}

void testVillage(int player, struct gameState* testState)
{
    int failed = 0;
    int handCount = testState->handCount[player];
    int i = 0;
    for (i = 0; i < handCount; i++) //set all cards in hand to village
    {
        testState->hand[player][i] = village;
    }

    //copy gamestate to preTest - all actions will now be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    
    playVillage(player, testState, 0); //run function we are testing
    
    /***********************************************************************
     TEST 1 - HAND SHOULD BE THE SAME SIZE (DRAW 1, PLAY 1)
     ***********************************************************************/
    assertTrue(preTest.handCount[player] == testState->handCount[player], &failed, 1);
    
    /***********************************************************************
     TEST 2 - NUMACTIONS SHOULD INCREASE BY 2
     ***********************************************************************/
    assertTrue(preTest.numActions+2 == testState->numActions, &failed, 2);
    
    //NOTE: TESTS 3 AND 4 WILL FAIL DUE TO BUGS IN THE CODE - THIS IS INTENTIONAL (FOR NOW)!
    /***********************************************************************
     TEST 3 - PLAYED CARD COUNT SHOULD BE INCREMENTED
     ***********************************************************************/
    assertTrue(preTest.playedCardCount+1 == testState->playedCardCount, &failed, 3);
    
    /***********************************************************************
     TEST 4 - TOP OF PLAYED CARDS SHOULD BE VILLAGE
     ***********************************************************************/
    int playedCount = testState->playedCardCount;
    assertTrue(testState->playedCards[playedCount] == village, &failed, 4);

    /***********************************************************************
     TEST 5 - DECKCOUNT SHOULD BE DECREMENTED
     ***********************************************************************/
    assertTrue(preTest.deckCount[player]-1 == testState->deckCount[player], &failed, 5);
    
    //test if no changes to other players
    int j = 1;
    for (j = 1; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        /*************************************************
         TEST 6 - OTHER PLAYER'S HANDS SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
        {
            assertTrue(preTest.hand[j][i] == testState->hand[j][i], &failed, 6);
        }
        /*************************************************
         TEST 7 - OTHER PLAYER'S DECKS SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
        {
            assertTrue(preTest.deck[j][i] == testState->deck[j][i], &failed, 7);
        }
        /*************************************************
         TEST 8 - OTHER PLAYER'S DISCARD PILES SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.discardCount[j]; i++) //check all cards in discard pile
        {
            assertTrue(preTest.discard[j][i] == testState->discard[j][i], &failed, 8);
        }
    }

    if (failed == 0)
        printf("playVillage TEST PASSED\n");
}


int main(){
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    
    initializeGame(2, k, 1, &G);
    
    testVillage(0, &G);
    
    return 0;
}
