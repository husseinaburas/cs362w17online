/*
 unittest2.c
 Corey Savage
 Assignment 3
 
 Description: Testing for scoreFor
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
    
    int i;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    struct gameState G1;
    
    printf ("Testing scoreFor\n");
    
    initializeGame(2, k, 10, &G);
    initializeGame(2, k, 10, &G1);
    
    // Set up
    G.hand[0][1] = estate;
    G.hand[0][2] = province;
    G.hand[0][3] = estate;
    G.hand[0][4] = curse;
    G.deck[0][0] = great_hall;
    G.deck[0][1] = duchy;
    G.deck[0][2] = smithy;
    G.deck[0][3] = village;
    G.deck[0][4] = estate;
    G.discard[0][0] = gardens;
    
    for (i=0; i<5; i++) {
        G1.hand[0][i] = gold;
    }
    for (i=0; i<5; i++) {
        G1.deck[0][i] = gold;
    }
    
    
    // Test 1 : Every type of card, in hand, deck, and discard
    // Expected result : 1 + 6 + 1 - 1 + 1 + 3 + 1 + (10/10) = 13
    printf("Test 1: All victory points cards spread in hand, deck, and discard\n");
    printf("%d\n", scoreFor(0,&G));
    assert_true(scoreFor(0, &G) == 13);
    
    // Test 2 : no victory cards
    // Expected result : 0
    printf("Test 2: No victory cards\n");
    printf("%d\n", scoreFor(0,&G1));
    assert_true(scoreFor(0, &G1) == 0);


    
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
