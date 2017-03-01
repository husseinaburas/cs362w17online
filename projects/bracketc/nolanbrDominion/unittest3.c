#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

//UNIT TEST 3 - updateCoins() function

int assertTrue(int a, int b, int* failed, int testNum)
{
    if (a == b)
        return 1;
    else
    {
        printf("updateCoins TEST FAILED %d\n", testNum);
        *failed = 1;
        return 0;
    }
}


void testUpdateCoins(int player, struct gameState* testState, int bonus)
{
    int failed = 0;
    int i = 0;
    
    /*************************************************
     TEST 1 - COPPERS SHOULD GIVE 1 COIN
     **************************************************/
    testState->coins = 0;
    int count = testState->handCount[player]; //get number of cards in hand
    for (i = 0; i < count; i++) //set all cards to copper
    {
        testState->hand[player][i] = copper;
    }
    updateCoins(player, testState, bonus); //run the function we are testing
    assertTrue(count+bonus, testState->coins, &failed, 1); //coins should be 1*count + bonus
    
    /*************************************************
     TEST 2 - SILVERS SHOULD GIVE 2 COINS
     **************************************************/
    testState->coins = 0;
    count = testState->handCount[player]; //get number of cards in hand
    for (i = 0; i < count; i++) //set all cards to copper
    {
        testState->hand[player][i] = silver;
    }
    updateCoins(player, testState, bonus); //run the function we are testing
    assertTrue(2*count+bonus, testState->coins, &failed, 2); //coins should be 2*count + bonus
    
    /*************************************************
     TEST 3 - GOLDS SHOULD GIVE 3 COINS
     **************************************************/
    testState->coins = 0;
    count = testState->handCount[player]; //get number of cards in hand
    for (i = 0; i < count; i++) //set all cards to copper
    {
        testState->hand[player][i] = gold;
    }
    updateCoins(player, testState, bonus); //run the function we are testing
    assertTrue(3*count+bonus, testState->coins, &failed, 3); //coins should be 3*count + bonus
    
    if (failed == 0)
        printf("updateCoins TEST PASSED\n");
}


int main(){
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    
    initializeGame(2, k, 1, &G);
    
    testUpdateCoins(2, &G, 5); //testing with bonus of 5
    
    return 0;
}
