/*
File: cardtest2.c
Description: Unit testing of Adventurer card

Erin Rosenbaum
cs_362 Winter 2017
February 7th, 2017
Assignment_3

The Village card adds a card to the players hand and adds two actions
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TESTCARD "Village"

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

    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 20;
    struct gameState G, testG;

    // initialize game
    printf("****************** Begin Test, testing %s ******\n", TESTCARD);
    initializeGame(2, cards, seed, &G);

    // had must contain adventurer card
    //G.hand[0][0] = village;

    // save initial state and call cardEffect
    memcpy(&testG, &G, sizeof(struct gameState));

    // int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
    cardEffect(village, 0, 0, 0, &testG, 0, 0);

    // test number of cards in hand
    printf("hand count before = %d, hand count after = %d\n", G.handCount[0], testG.handCount[0]);
    assert_true(testG.handCount[0] == G.handCount[0]);

    // test number of cards in deck. In this test case, 
    printf("deck count before = %d, deck count after = %d\n", G.deckCount[0], testG.deckCount[0]);
    assert_true(testG.deckCount[0] == G.deckCount[0] - 1);

    // test other players for state change 
    printf("player 2 deck count = %d, expected = %d\n", testG.deckCount[1], G.deckCount[1]);
    assert_true(testG.deckCount[1] == G.deckCount[1]);

    printf("player 2 hand count = %d, expected = %d\n", testG.handCount[1], G.handCount[1]);
    assert_true(testG.handCount[1] == G.handCount[1]);

    printf("player 2 discard count = %d, expected = %d\n", testG.discardCount[1], G.discardCount[1]);
    assert_true(testG.discardCount[1] == G.discardCount[1]);


    printf("************* CARDTEST4 SUCCESSFULLY COMPLETED  ***************\n\n");
    return 0;

}