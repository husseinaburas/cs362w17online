#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//UNIT TEST 2 - drawCard() function

int assertTrue(int a, int b, int* failed, int testNum)
{
    if (a == b)
        return 1;
    else
    {
        printf("drawCard TEST FAILED %d\n", testNum);
        *failed = 1;
        return 0;
    }
}


void testDrawCard(int player, struct gameState* testState)
{
    int failed = 0;
    //copy unchanged gamestate to preTest - all actions will be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    
    drawCard(player, testState); //run the function we are testing
    
    int deckCounter = preTest.deckCount[player];
    int count = preTest.handCount[player];
    
    /*************************************************
     TEST 1 - TOP OF DECK SHOULD BE ADDED TO HAND
     **************************************************/
    assertTrue(preTest.deck[player][deckCounter-1], testState->hand[player][count], &failed, 1);
    
    /*************************************************
     TEST 2 - DECKCOUNT SHOULD BE DECREMENTED
     **************************************************/
    assertTrue((preTest.deckCount[player])-1, testState->deckCount[player], &failed, 2);
    
    /*************************************************
     TEST 3 - HANDCOUNT SHOULD BE INCREMENTED
     **************************************************/
    assertTrue((preTest.handCount[player])+1, testState->handCount[player], &failed, 3);
    
    //test if no changes to other players
    int i = 0;
    int j = 1;
    for (j = 1; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        /*************************************************
         TEST 4 - OTHER PLAYER'S HANDS SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
        {
            assertTrue(preTest.hand[j][i], testState->hand[1][i], &failed, 4);
        }
        /*************************************************
         TEST 5 - OTHER PLAYER'S DECKS SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
        {
            assertTrue(preTest.deck[j][i], testState->deck[1][i], &failed, 5);
        }
        /*************************************************
         TEST 6 - OTHER PLAYER'S DISCARD PILES SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.discardCount[j]; i++) //check all cards in discard pile
        {
            assertTrue(preTest.discard[j][i], testState->discard[1][i], &failed, 6);
        }
    }

    
    if (failed == 0)
        printf("drawcard TEST PASSED\n");
}


int main(){
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    
    initializeGame(2, k, 1, &G);
    
    testDrawCard(0, &G);

    return 0;
}
