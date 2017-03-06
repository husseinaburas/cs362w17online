#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CARD TEST 4 - Council Room

int assertTrue(int a, int* failed, int testNum)
{
    if (a == 1)
        return 1;
    else
    {
        printf("Council Room TEST FAILED %d\n", testNum);
        *failed = 1;
        return 0;
    }
}

void testCouncilRoom(int player, struct gameState* testState)
{
    int failed = 0;
    int handCount = testState->handCount[player];
    int i = 0;
    for (i = 0; i < handCount; i++) //set all cards in hand to council room
    {
        testState->hand[player][i] = council_room;
    }
    
    //copy gamestate to preTest - all actions will now be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    
    cardEffect(council_room, 0, 0, 0, testState, 0, 0); //run function we are testing
    
    /***********************************************************************
     TEST 1 - HAND SIZE SHOULD INCREASE BY 3 (DRAW 4, PLAY ONE)
     ***********************************************************************/
    assertTrue(preTest.handCount[player]+3 == testState->handCount[player], &failed, 1);
    
    /***********************************************************************
     TEST 2 - DECK SIZE SHOULD BE DECREASED BY 4
     ***********************************************************************/
    assertTrue(preTest.deckCount[player]-4 == testState->deckCount[player], &failed, 2);
    
    /***********************************************************************
     TEST 3 - NUMBUYS SHOULD BE INCREMENTED
     ***********************************************************************/
    assertTrue(preTest.numBuys+1 == testState->numBuys, &failed, 3);
    
    /***********************************************************************
     TEST 4 - ALL OTHER PLAYERS' HAND SIZE SHOULD INCREASE BY 1
     ***********************************************************************/
    /***********************************************************************
     TEST 5 - ALL OTHER PLAYERS' DECK SIZE SHOULD DECREASE BY 1
     ***********************************************************************/
    for (i = 1; i < preTest.numPlayers-1; i++) //loop through all other players
    {
        assertTrue(preTest.handCount[i]+1 == testState->handCount[i], &failed, 4); //check hand size
        assertTrue(preTest.deckCount[i]-1 == testState->deckCount[i], &failed, 5); //check deck size
    }
    
    /***********************************************************************
     TEST 6 - PLAYED CARD COUNT SHOULD BE INCREMENTED
     ***********************************************************************/
    assertTrue(preTest.playedCardCount+1 == testState->playedCardCount, &failed, 6);
    
    /***********************************************************************
     TEST 7 - TOP OF PLAYED CARDS PILE SHOULD BE COUNCIL ROOM
     ***********************************************************************/
    int playedCount = testState->discardCount[player];
    assertTrue(testState->playedCards[playedCount] == council_room, &failed, 7);
    
    /***********************************************************************
     TEST 8 - ALL OTHER PLAYERS' DISCARD PILES SHOULD REMAIN UNCHANGED
     ***********************************************************************/
    int j = 1;
    for (j = 1; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        for (i = 0; i < preTest.discardCount[j]; i++) //check all cards in discard pile
        {
            assertTrue(preTest.discard[j][i] == testState->discard[j][i], &failed, 8);
        }
    }

    if (failed == 0)
        printf("Council Room TEST PASSED\n");
}


int main(){
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    
    initializeGame(2, k, 1, &G);
    
    testCouncilRoom(0, &G);
    
    return 0;
}
