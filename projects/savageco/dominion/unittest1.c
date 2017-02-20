/*
 unittest1.c
 Corey Savage
 Assignment 3
 
 Description: Testing for isGameOver()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void assert_true(int);

int main() {
    // Used from BetterTestCardDraw.c
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    struct gameState G1;
    struct gameState G2;
    struct gameState G3;
    
    printf ("Testing isGameOver()\n");
    
    initializeGame(2, k, 10, &G);
    initializeGame(2, k, 10, &G1);
    initializeGame(2, k, 10, &G2);
    initializeGame(2, k, 10, &G3);
    
    // Set up
    G.supplyCount[province] = 0;
    G1.supplyCount[estate] = 0;
    G1.supplyCount[gold] = 0;
    G1.supplyCount[silver] = 0;
    G2.supplyCount[estate] = 0;
    
    
    // Test 1 : no province cards
    // Expected result : game over - true
    printf("Test 1: No Province Cards\n");
    assert_true(isGameOver(&G));
    
    // Test 2 : 3 supply plies are at 0
    // Expected result : game over - true
    printf("Test 2: 3 supply piles are empty\n");
    assert_true(isGameOver(&G1));
    
    // Test 3 : One empty supply pile
    // Expected result : game over - false
    printf("Test 3: 1 supply pile is empty\n");
    assert_true(!(isGameOver(&G2)));
    
    // Test 4: All supply piles are not empty
    // Expected result : game over - false
    printf("Test 4: No supply piles are empty\n");
    assert_true(!(isGameOver(&G3)));
    
}

// Used to print success or failure messages for test. Comparisons will be made within the
// function parameters to test results.
void assert_true(int bool) {
    
    if (bool != 0) {
        printf("      -Test Passed\n");
    }
    else {
        printf("      -Test Failed\n");
    }
    return;
}
