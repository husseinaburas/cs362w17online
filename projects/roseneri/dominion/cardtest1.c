/*
File: cardtest1.c
Description: Unit testing of Smithy card

Erin Rosenbaum
cs_362 Winter 2017
February 7th, 2017
Assignment_3

The Smithy card costs 4 monetary units and gives the player 3 additional cards

Requirements: 
1. Current player should receive exact 3 cards.
2. 3 cards should come from his own pile.
3. No state change should occur for other players.
4. No state change should occur to the victory card piles and kingdom card piles.
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TESTCARD "smithy"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void assert_true(int val) {
    if (val == 0) {
        printf("TEST FAILED!\n\n");
    }
    else
        printf("TEST PASSED!\n\n");
}

int main() {

    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;

    int seed = 10;
    int thisPlayer = 0;
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState G, testG;

    // initialize game
    printf("******* Begin Test, testing %s ******\n", TESTCARD);
    initializeGame(2, cards, seed, &G);

    G.whoseTurn = 0;
    G.hand[0][0] = smithy;

    // save initial state
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(smithy, 0, 0, 0, &testG, 0, 0);

    newCards = 3;

    // test number of cards in hand
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assert_true(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2);

    // test number of cards in deck
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    assert_true(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3);

    printf("discard count = %d, expected = %d\n", testG.discardCount[0], G.discardCount[0]);
    assert_true(testG.discardCount[0] == G.discardCount[0]);

    // test other players for state change 
    printf("player 2 deck count = %d, expected = %d\n", testG.deckCount[1], G.deckCount[1]);
    assert_true(testG.deckCount[1] == G.deckCount[1]);

    printf("player 2 hand count = %d, expected = %d\n", testG.handCount[1], G.handCount[1]);
    assert_true(testG.handCount[1] == G.handCount[1]);

    printf("player 2 discard count = %d, expected = %d\n", testG.discardCount[1], G.discardCount[1]);
    assert_true(testG.discardCount[1] == G.discardCount[1]);

//************************* end of test **************************
    printf("**********CARDTEST1 SUCCESSFULLY COMPLETED *****************\n\n");
    return 0;

}