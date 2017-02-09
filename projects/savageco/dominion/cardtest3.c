/*
 cardtest3.c
 Corey Savage
 Assignment 3
 
 Description: Testing for Village Card
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
    int expected;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf ("Testing Village Card.\n");
    
    initializeGame(2, k, 10, &G);
    
    // Set it to testing player's turn and put the Village Card in the player's hand
    G.whoseTurn = 0;
    G.hand[0][0] = village;
    
    // play Village Card
    playCard(0, -1, -1, -1, &G);
    
    // Testing players deck tests
 
    // Test 1 : handNum + newDraw - discard = newHandNum
    // Expected result : 5 + 1 - 1 = 5
    printf("Test 1: Correct number of cards in hand\n");
    expected = 5;
    printf("%d\n", G.handCount[0]);
    assert_true(G.handCount[0] == expected);
    
    // Test 2 : origPlayedCardCount + 1 = newPlayedCardCount
    // Expected result : 0 + 1 = 1
    printf("Test 2: Correct number of played  cards\n");
    expected = 1;
    printf("%d\n", G.playedCardCount);
    assert_true(G.playedCardCount == expected);
    
    // Test 3 : deckCount - draw = newDeckCount
    // Expected result : 5 - 1 = 4
    printf("Test 3: Correct number of cards in deck\n");
    expected = 4;
    printf("%d\n", G.deckCount[0]);
    assert_true(G.deckCount[0] == expected);
    
    // Test 4 : discardCount + newDiscard = newDiscardCount
    // Expected result : 0 + 1 = 1
    printf("Test 4: Correct number of cards in discard pile\n");
    expected = 1;
    printf("%d\n", G.discardCount[0]);
    assert_true(G.discardCount[0] == expected);
    
    // Test 5 : origActionCount - 1 + cardEffect
    // Expected result : 1 - 1 + 2 = 2
    printf("Test 5: Correct number of actions\n");
    expected = 2;
    printf("%d\n", G.numActions);
    assert_true(G.numActions == expected);
    
    
    
    // Opponent players deck tests
    
    // Test 6 : handNum + newDraw - discard = newHandNum
    // Expected result : 0 + 0 - 0 = 0
    printf("Test 6: Correct number of cards in opponent hand\n");
    expected = 0;
    printf("%d\n", G.handCount[1]);
    assert_true(G.handCount[1] == expected);
    
    // Test 7 : deckCount - draw = newDeckCount
    // Expected result : 10 - 0 = 10
    printf("Test 7: Correct number of cards in deck\n");
    expected = 10;
    printf("%d\n", G.deckCount[1]);
    assert_true(G.deckCount[1] == expected);
    
    // Test 8 : discardCount + newDiscard = newDiscardCount
    // Expected result : 0 + 0 = 0
    printf("Test 8: Correct number of cards in discard pile\n");
    expected = 0;
    printf("%d\n", G.discardCount[1]);
    assert_true(G.discardCount[1] == expected);

    
    return 0;
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

