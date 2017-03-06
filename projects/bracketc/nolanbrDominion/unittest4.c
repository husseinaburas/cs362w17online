#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

//UNIT TEST 4 - numHandCards() function

int assertTrue(int a, int b, int* failed, int testNum)
{
    if (a == b)
        return 1;
    else
    {
        printf("numHandCards TEST FAILED %d\n", testNum);
        *failed = 1;
        return 0;
    }
}


void testNumHandCards(struct gameState *state)
{
    int failed = 0;
    
    int handCount0 = state->handCount[0];
    int handCount1 = state->handCount[1];
    
    /*************************************************
     TEST 1 - PLAYER ONE'S HANDCOUNT
     **************************************************/
    state->whoseTurn = 0;
    int returned0 = numHandCards(state);
    assertTrue(handCount0, returned0, &failed, 1);
    
    
    /*************************************************
     TEST 2 - PLAYER TWO'S HANDCOUNT
     **************************************************/
    state->whoseTurn = 1;
    int returned1 = numHandCards(state);
    assertTrue(handCount1, returned1, &failed, 2);
   
    if (failed == 0)
        printf("numHandCards TEST PASSED\n");
}


int main(){
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    
    initializeGame(2, k, 1, &G);
    
    testNumHandCards(&G);
    
    return 0;
}
