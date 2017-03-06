/******************************************************************************
* cardTest3.c tests the village card from dominion.c
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
    printf("Card Test VILLAGE - ");
    if (test == 1)
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
    else
        printf("TEST %d FAILED.\n", testNumber);
}

int main() {
    //create variables from cardEffect
    int drawnCards = 1, discarded = 1, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0,
        bonus = 0, player = 0;

    struct gameState g1, g2;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                              sea_hag, tribute, smithy, council_room};

    initializeGame(2, k, 1000, &g1); //initalize game and cards

    //copy initialized game for later
    memcpy(&g2, &g1, sizeof(struct gameState));

    //call the cardEffect method with village
    cardEffect(village, choice1, choice2, choice3, &g2, handpos, &bonus);

    //1 - Test Check to see if additional card added to deck
    int pre = g1.handCount[player] + (drawnCards - discarded);
    int post = g2.handCount[player];



    assertTrue((pre == post), 1);

    // 2 - Test the difference in pre and post action (should be 1)
    int returnValue = 0;
    if(g2.numActions - g1.numActions == 1)
        returnValue = 1;

    assertTrue(returnValue, 2);

    //3 - Test that numOfActions increased by two
    assertTrue((g1.numActions == g2.numActions + 2), 3);

    return 0;

}