/******************************************************************************
* unitTest2.c tests the function playCard() from dominion.c
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
    printf("Function playCard() - ");
    if (test == 1)
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
    else
        printf("TEST %d FAILED.\n", testNumber);
}

int main() {
    //create new gameState we can use in our tests
    struct gameState g1, g2;

    //create variables for playCard (to stay uniform with dominion.c)
    int currentPlayer = 0, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, test;

    int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy };

    //set the game up
    initializeGame(2, k, 2000, &g2);

    memcpy(&g1, &g2, sizeof(struct gameState));

    // 1 - Test the card when the phase is 0
    g1.phase = 0;
    test = playCard(handpos, choice1, choice2, choice3, &g1);

    int returnValue = 0;
    if(test == -1)
        returnValue = 1;

    assertTrue(returnValue, 1);

    // 2- Test when numberAction = 0 in playCard
    memcpy(&g1, &g2, sizeof(struct gameState));
    g1.numActions = 0;
    test = playCard(handpos, choice1, choice2, choice3, &g1);
    returnValue = 0; //make returnValue equal to 0

    if(test == -1)
        returnValue = 1;

    assertTrue(returnValue, 2);

    return 0;
}

