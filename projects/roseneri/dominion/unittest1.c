/*
File: unittest1.c
Description: Unit testing of isGameOver function.

Erin Rosenbaum
cs_362 Winter 2017
February 7th, 2017
Assignment_3

The isGameOver function takes the game state as an input
and should return 1 if the game is over, and it should retunr zero 
if the game is not over. The game should end when the supply of 
provinces runs out or three other supply piles have run out. 

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

    printf("*************** start UNITTEST1, testing isGameOver *******\n\n");
    struct gameState *testG = newGame();
    int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    // Initialize game
    initializeGame(2, cards, 10, testG);

    printf("****** test 1, test new game for if it is over *****\n");
    printf("return value = %d, expected return value = %d\n", isGameOver(testG), 0);
    assert_true(isGameOver(testG) == 0);


    printf("****** test 2, set Province pile to 0 *****\n");
    testG->supplyCount[province] = 0;
    printf("return value = %d, expected return value = %d\n", isGameOver(testG), 1);
    assert_true(isGameOver(testG) == 1);

    printf("****** test 3, test game after resetting province pile back to 8 *****\n");
    testG->supplyCount[province] = 8;
    printf("return value = %d, expected return value = %d\n", isGameOver(testG), 0);
    assert_true(isGameOver(testG) == 0);


    printf("****** test 4, set three supply piles to 0 *****\n");
    testG->supplyCount[embargo] = 0;
    testG->supplyCount[smithy] = 0;
    testG->supplyCount[silver] = 0;
    printf("return value = %d, expected return value = %d\n", isGameOver(testG), 1);
    assert_true(isGameOver(testG) == 1);
    

    printf("******** UNITTEST1 SUCCESSFULLY COMPLETED *******\n\n");
    return 0;

}