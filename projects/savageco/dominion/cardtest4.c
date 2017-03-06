/*
 cardtest4.c
 Corey Savage
 Assignment 3
 
 Description: Testing for Steward Card
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
    struct gameState G1;
    struct gameState G2;
    
    
    printf ("Testing Steward Card (+2 cards).\n");
    
    initializeGame(2, k, 10, &G);
    
    // Set it to testing player's turn and put the Steward Card in the player's hand
    G.whoseTurn = 0;
    G.hand[0][0] = steward;
    
    // play Steward - + 2 cards
    playCard(0, 1, -1, -1, &G);
    
    // Testing players deck tests
    
    // Test 1 : handNum + newDraw - discard = newHandNum
    // Expected result : 5 + 2 - 1 = 6
    printf("Test 1: Correct number of cards in hand\n");
    expected = 6;
    printf("%d\n", G.handCount[0]);
    assert_true(G.handCount[0] == expected);
    
    // Test 2 : origPlayedCardCount + 1 = newPlayedCardCount
    // Expected result : 0 + 1 = 1
    printf("Test 2: Correct number of played cards\n");
    expected = 1;
    printf("%d\n", G.playedCardCount);
    assert_true(G.playedCardCount == expected);
    
    // Test 3 : deckCount - draw = newDeckCount
    // Expected result : 5 - 2 = 3
    printf("Test 3: Correct number of cards in deck\n");
    expected = 3;
    printf("%d\n", G.deckCount[0]);
    assert_true(G.deckCount[0] == expected);
    
    // Test 4 : discardCount + newDiscard = newDiscardCount
    // Expected result : 0 + 1 = 1
    printf("Test 4: Correct number of cards in discard pile\n");
    expected = 1;
    printf("%d\n", G.discardCount[0]);
    assert_true(G.discardCount[0] == expected);
    
    // Test 5 : coins + 0
    // Expected result : 0 + 0 = 0
    printf("Test 5: Correct number of coins\n");
    expected = 0;
    printf("%d\n", G.coins);
    assert_true(G.coins == expected);



    printf ("Testing Steward Card (+2 gold).\n");

    initializeGame(2, k, 10, &G1);

    // Set it to testing player's turn and put the Steward Card in the player's hand
    G1.whoseTurn = 0;
    G1.hand[0][0] = steward;

    // play Steward - + 2 cards
    playCard(0, 2, -1, -1, &G1);

    // Testing players deck tests

    // Test 1 : handNum + newDraw - discard = newHandNum
    // Expected result : 5 + 0 - 1 = 4
    printf("Test 1: Correct number of cards in hand\n");
    expected = 4;
    printf("%d\n", G1.handCount[0]);
    assert_true(G1.handCount[0] == expected);

    // Test 2 : origPlayedCardCount + 1 = newPlayedCardCount
    // Expected result : 0 + 1 = 1
    printf("Test 2: Correct number of played cards\n");
    expected = 1;
    printf("%d\n", G1.playedCardCount);
    assert_true(G1.playedCardCount == expected);

    // Test 3 : deckCount - draw = newDeckCount
    // Expected result : 5 - 0 = 5
    printf("Test 3: Correct number of cards in deck\n");
    expected = 5;
    printf("%d\n", G1.deckCount[0]);
    assert_true(G1.deckCount[0] == expected);

    // Test 4 : discardCount + newDiscard = newDiscardCount
    // Expected result : 0 + 1 = 1
    printf("Test 4: Correct number of cards in discard pile\n");
    expected = 1;
    printf("%d\n", G1.discardCount[0]);
    assert_true(G1.discardCount[0] == expected);

    // Test 5 : coins + 2
    // Expected result : 0 + 2 = 2
    printf("Test 5: Correct number of coins\n");
    expected = 2;
    printf("%d\n", G1.coins);
    assert_true(G1.coins == expected);
    
    
    
    printf ("Testing Steward Card (2 trash).\n");
    
    initializeGame(2, k, 10, &G2);
    
    // Set it to testing player's turn and put the Steward Card in the player's hand
    G2.whoseTurn = 0;
    G2.hand[0][0] = steward;
    
    // play Steward - + 2 cards
    playCard(0, 3, 1, 2, &G2);
    
    // Testing players deck tests
    
    // Test 1 : handNum + newDraw - discard - trash = newHandNum
    // Expected result : 5 + 0 - 1 - 2 = 2
    printf("Test 1: Correct number of cards in hand\n");
    expected = 2;
    printf("%d\n", G2.handCount[0]);
    assert_true(G2.handCount[0] == expected);
    
    // Test 2 : origPlayedCardCount + 1 = newPlayedCardCount
    // Expected result : 0 + 1 = 1
    printf("Test 2: Correct number of played cards\n");
    expected = 1;
    printf("%d\n", G2.playedCardCount);
    assert_true(G2.playedCardCount == expected);
    
    // Test 3 : deckCount - draw = newDeckCount
    // Expected result : 5 - 0 = 5
    printf("Test 3: Correct number of cards in deck\n");
    expected = 5;
    printf("%d\n", G2.deckCount[0]);
    assert_true(G2.deckCount[0] == expected);
    
    // Test 4 : discardCount + newDiscard + trash= newDiscardCount
    // Expected result : 0 + 1 + 2 = 3
    printf("Test 4: Correct number of cards in discard pile\n");
    expected = 3;
    printf("%d\n", G2.discardCount[0]);
    assert_true(G2.discardCount[0] == expected);
    
    // Test 5 : coins + 0
    // Expected result : 0 + 0 = 0
    printf("Test 5: Correct number of coins\n");
    expected = 0;
    printf("%d\n", G2.coins);
    assert_true(G2.coins == expected);
    
    
    

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
