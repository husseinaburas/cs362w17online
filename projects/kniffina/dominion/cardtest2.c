/******************************************************************************
* cardTest2.c tests the adventurer card from dominion.c
******************************************************************************/
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


//assertTrue takes a an int and int testNumber and if the test is true (equal to 1)
//  the string is returned to indicate that the test was successful, otherwise it failed.
void assertTrue(int test, int testNumber) {
    printf("Card Test ADVENTURER - ");
    if (test == 1)
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
    else
        printf("TEST %d FAILED.\n", testNumber);
}
int main() {
    int temphand[MAX_HAND];
    struct gameState g1, g2;

    int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };

    //initialize game with random number
    initializeGame(2, k, 36, &g1);

    // Set gameState G2 to the initial settings following initialization of G1.
    memcpy(&g2, &g1, sizeof(struct gameState));

    //set the variables pre adventurer method call
    int test1a = g1.handCount[0], test2a = g1.deckCount[0], test3a = g1.discardCount[0],
        test4a = g1.playedCardCount;

    //run the adventurer function. Player 0
    playAdventurer(&g1, 0, temphand);

    //set variables post adventurer method call
    int test1b = g1.handCount[0], test2b = g1.deckCount[0], test3b = g1.discardCount[0],
            test4b = g1.playedCardCount;

    //1 - Test, handcount for player 1 should increase by 2
    assertTrue((test1a + 2 == test1b), 1);

    // 2 - Test, deckCount should decrease by 2.
    assertTrue((test2a - 2 == test2b), 2);

    // 3 - Test. discardCount should increment when cards are discarded. * may be bug b/c fails *
    assertTrue((test3a < test3b), 3);

    // 4 - Test playedCardCount should increment when adventurer is played. * may be bug b/c fails *
    assertTrue((test4a + 1 == test4b), 4);


    //set the variables pre adventurer method call
    test1a = g1.handCount[0], test2a = g1.deckCount[0], test3a = g1.discardCount[0],
            test4a = g1.playedCardCount;

    //run the adventurer function. Player 1
    playAdventurer(&g1, 1, temphand);

    //set variables post adventurer method call
    test1b = g1.handCount[0], test2b = g1.deckCount[0], test3b = g1.discardCount[0],
            test4b = g1.playedCardCount;

    // 5 - Test handCount. Test if it changes (if == then no)
    assertTrue((test1a == test1b), 5);

    // 6- Test deckCount. Test if it changes (if == then no)
    assertTrue((test2a == test2b), 6);

    // 7 - Test incrementing for discardCount when called for player 1.
    assertTrue((test3a == test3b), 7);

    // 8 - Test playedCardCount not incrementing
    assertTrue((test4a == test4b), 8);


    return 0;
}