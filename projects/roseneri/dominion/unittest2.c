/*
File: unittest2.c
Description: Unit testing of getCost() function.

Erin Rosenbaum
cs_362 Winter 2017
February 7th, 2017
Assignment_3

buyCard takes as input int supplyPost, and *state
rand returns -1 upon failure and 0 for success
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    printf("****** begin UNITTEST2 testing buyCard()  *** \n\n");

    struct gameState *testG = newGame();
    int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    // Initialize game
    initializeGame(2, cards, 10, testG);

    int bought_card;
    int expected_buy;
    //int coins;

    printf("****** test 1, call buyCard() at start of game  *****\n");
    bought_card=(buyCard(1, testG));
    expected_buy = 0;
    printf("return value expected = %d, actual return value = %d\n", expected_buy, bought_card);
    assert_true(bought_card == expected_buy);

    printf("****** test 2, call buyCard() after setting coins to zero  *****\n");
    initializeGame(2, cards, 10, testG);
    testG->coins=0;
    bought_card=(buyCard(1, testG));
    expected_buy = -1;
    printf("return value expected = %d, actual return value = %d\n", expected_buy, bought_card);
    assert_true(bought_card == expected_buy);

    printf("****** test 3, call buyCard() on province after setting coins to 5  *****\n");
    initializeGame(2, cards, 10, testG);
    testG->coins=5;
    bought_card=(buyCard(3, testG));
    expected_buy = -1;
    printf("return value expected = %d, actual return value = %d\n", expected_buy, bought_card);
    assert_true(bought_card == expected_buy);

    printf("****** test 4, call buyCard() on province after setting coins to 10  *****\n");
    initializeGame(2, cards, 10, testG);
    testG->coins=10;
    bought_card=(buyCard(3, testG));
    expected_buy = 0;
    printf("return value expected = %d, actual return value = %d\n", expected_buy, bought_card);
    assert_true(bought_card == expected_buy);

    printf("****** test 5, call buyCard() after setting coins to 10 and buys to 0  *****\n");
    initializeGame(2, cards, 10, testG);
    testG->coins=10;
    testG->numBuys=0;
    bought_card=(buyCard(3, testG));
    expected_buy = -1;
    printf("return value expected = %d, actual return value = %d\n", expected_buy, bought_card);
    assert_true(bought_card == expected_buy);

    printf("******  UNITTEST2 SUCCESSFULLY COMPLETED   *** \n\n");
    return 0;

}