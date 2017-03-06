/******************************************************************************
* unitTest4.c tests the function discardCard() from dominion.c
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
    printf("Function discardCard() - ");
    if (test == 1)
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
    else
        printf("TEST %d FAILED.\n", testNumber);
}

int main() {
    struct gameState g1, g2;

    int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
                  sea_hag, tribute, smithy };

    initializeGame(2, k, 33, &g1); //set game

    memcpy(&g2, &g1, sizeof(struct gameState)); //copy over to g2 for later usage

    //1- Test get the first test from discardCard
    int test = discardCard(14, 0, &g1, 0);
    assertTrue((test == 0 && g1.playedCards[g1.playedCardCount] == 0 && g1.playedCardCount == 1), 1);

    //reset
    memcpy(&g2, &g1, sizeof(struct gameState));

    //2 - Test.
    test = discardCard(14, 0, &g1, 1);
    assertTrue((test == 0 && g1.playedCards[g1.playedCardCount] == 0 && g1.playedCardCount == 0), 2);

    //reset
    memcpy(&g2, &g1, sizeof(struct gameState));

    //create 3 new test variables that will be used later, we want to initialize them now
    int testLater1 = g1.handCount[0], testLater2 = g1.handCount[1], testLater3 = g1.playedCardCount;

    //3 - Test the last card in the hand is discarded, get to the last card first
    int i, temp = 0;
    for(i = 0; i < 26; i++)
        if(g1.hand[0][i] != 0)
            temp++;

    test = discardCard(temp - 1, 0, &g1, 0);
    assertTrue((test == 0 && g1.hand[0][temp - 1] == -1), 3);

    //4 - Test that a card was removed
    assertTrue((temp-1 == 0 && g1.handCount[0]), 4);

    //5 - Test that discarded card replaced the last card in hand
    assertTrue((g1.hand[0][temp - 2] == g1.hand[0][(g1.handCount[0] -1)]), 5);

    //6 - test make sure last card set to -1
    assertTrue((g1.hand[0][temp - 1] == -1), 6);

    //7 - Test, ensure decrement
    assertTrue((g1.handCount[0] == testLater1 - 1), 7);

    //8 - Test assure decrement player 2
    assertTrue((g1.handCount[1] == testLater2), 8);

    //9 - Test ensure that the played count increase
    assertTrue((g1.playedCardCount +1 == testLater3 ), 9);

    return 0;
}





