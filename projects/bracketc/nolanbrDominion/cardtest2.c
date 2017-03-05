#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CARD TEST 2 - Adventurer

int assertTrue(int a, int* failed, int testNum)
{
    if (a == 1)
        return 1;
    else
    {
        printf("playAdventurer TEST FAILED %d\n", testNum);
        *failed = 1;
        return 0;
    }
}

void testAdventurer(int player, struct gameState* testState)
{
    int failed = 0;
    
    int deckCount = testState->deckCount[player];
    testState->deck[player][deckCount-1] = smithy; //set first card picked up to be non-treasure, ensuring one card should be discarded
    
    //copy gamestate to preTest - all actions will now be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    
    playAdventurer(player, testState); //run function we are testing
    
    /***********************************************************************
     TEST 1 - HAND SHOULD HAVE 2 MORE CARDS
     ***********************************************************************/
    assertTrue(preTest.handCount[player]+2 == testState->handCount[player], &failed, 1);
    
    /***********************************************************************
     TEST 2 - TOP 2 CARDS IN HAND SHOULD BE TREASURE CARDS
     ***********************************************************************/
    int count = testState->handCount[player];
    int i = 1;
    for (i = 1; i <= 2; i++)
    {
        assertTrue(testState->hand[player][count - i] == copper || testState->hand[player][count - i] == silver || testState->hand[player][count - i] == gold, &failed, 2);
    }
    
    /***********************************************************************
     TEST 3 - AT LEAST ONE CARD SHOULD HAVE BEEN DISCARDED
     ***********************************************************************/
    assertTrue(preTest.discardCount[player] < testState->discardCount[player], &failed, 3);
    
    /***********************************************************************
     TEST 4 - CARD ON TOP OF DISCARD PILE SHOULD NOT BE A TREASURE CARD
     ***********************************************************************/
    int discardCount = testState->discardCount[player];
    assertTrue(testState->discard[player][discardCount-1] != copper || testState->discard[player][discardCount-1] != silver || testState->discard[player][discardCount-1] != gold, &failed, 4);

    
    //test if no changes to other players
    int j = 1;
    for (j = 1; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        /*************************************************
         TEST 5 - OTHER PLAYER'S HANDS SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
        {
            assertTrue(preTest.hand[j][i] == testState->hand[j][i], &failed, 5);
        }
        /*************************************************
         TEST 6 - OTHER PLAYER'S DECKS SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
        {
            assertTrue(preTest.deck[j][i] == testState->deck[j][i], &failed, 6);
        }
        /*************************************************
         TEST 7 - OTHER PLAYER'S DISCARD PILES SHOULD NOT CHANGE
         **************************************************/
        for (i = 0; i < preTest.discardCount[j]; i++) //check all cards in discard pile
        {
            assertTrue(preTest.discard[j][i] == testState->discard[j][i], &failed, 7);
        }
    }
    
    if (failed == 0)
        printf("playAdventurer TEST PASSED\n");
}


int main(){
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    
    initializeGame(2, k, 1, &G);
    
    testAdventurer(0, &G);
    
    return 0;
}
