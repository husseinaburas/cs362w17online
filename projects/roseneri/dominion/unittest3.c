/*
File: unittest3.c
Description: Unit testing of numHandsCards() function.

Erin Rosenbaum
cs_362 Winter 2017
February 7th, 2017
Assignment_3

The numHandsCards() function is a getter for the gameState handCount
Input: struct gameState state, which holds a pointer to a gameState
Returns: number of cards om the current player's hand.
Deps: whoseTurn()
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNITTEST "whoseTurn()"

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

    printf("******* Begin Test, UNITTEST3 testing %s ******\n\n", UNITTEST);

    // initialize game
    struct gameState *testG = newGame();
    int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(3, cards, 10, testG);

    printf("****** test 1, test whoseTurn() at beginning of 3-person game *****\n");
    int expected = 0;
    int returned;
    returned = whoseTurn(testG);
    printf("return value = %d, expected return value = %d\n", returned, expected);
    assert_true(returned == expected);

    printf("****** test 2, test whoseTurn() after calling endTurn(testG) *****\n");
    endTurn(testG);
    expected = 1;
    returned = whoseTurn(testG);
    printf("return value = %d, expected return value = %d\n", returned, expected);
    assert_true(returned == expected);

    printf("****** test 3, test whoseTurn() after calling endTurn(testG) again *****\n");
    endTurn(testG);
    expected = 2;
    returned = whoseTurn(testG);
    printf("return value = %d, expected return value = %d\n", returned, expected);
    assert_true(returned == expected);

    printf("****** test 4, test whoseTurn() after calling endTurn(testG) again *****\n");
    endTurn(testG);
    expected = 0;
    returned = whoseTurn(testG);
    printf("return value = %d, expected return value = %d\n", returned, expected);
    assert_true(returned == expected);


    printf("********** UNITTEST3 SUCCESSFULLY COMPLETED ****************\n\n");
    return 0;

}