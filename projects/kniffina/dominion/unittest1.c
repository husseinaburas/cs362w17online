/******************************************************************************
* unitTest1.c tests the function isGameOver() from dominion.c
******************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"


//assertTrue takes a an int and int testNumber and if the test is true (equal to 1)
//  the string is returned to indicate that the test was successful, otherwise it failed.
void assertTrue(int test, int testNumber) {
    printf("Function isGameOver() - ");
    if (test == 1)
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
    else
        printf("TEST %d FAILED.\n", testNumber);
}

int main() {
    int i;
    struct gameState g1, g2; //two gameStates. 1 for test, other to reset after.

    int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy };

    //set game with randomseed equal to 11
    initializeGame(2, k, 11, &g1);

    //copy G2 from G1
    memcpy(&g1, &g2, sizeof(struct gameState));

    //1 - Test if the province supplyCount is greater than 0 and if 1 is returned, then test passes
    int test = isGameOver(&g1);
    assertTrue((!test && g1.supplyCount[province] > 0), 1); //will return if the test passes

    //2 - Test if the province supply card equal to zero ends the game.
    g1.supplyCount[province] = 0;
    test = isGameOver(&g1);
    assertTrue((test && g1.supplyCount[province] == 0), 2); //will return if test passed

    //reset game
    memcpy(&g1, &g2, sizeof(struct gameState));

    //3 - Test to create 3 supp piles at 0. % 12 gets 3 supply card piles.
    for(i = 0; i < 25; i++) {
        if(i % 12 == 0)
            g1.supplyCount[i] = 0;
    }
    test = isGameOver(&g1);
    assertTrue((test && g1.supplyCount[0] == 0 && g1.supplyCount[12] == 0 && g1.supplyCount[24] == 0), 3);

    //reset gamestate - 4. Test supply piles edge case.
    memcpy(&g1, &g2, sizeof(struct gameState));

    //Create the state of two supply piles at 0. % 14 will give 2 supply card piles set to 0, thus game over.
    for(i = 0; i < 25; i++)
        if(i % 14 == 0)
            g1.supplyCount[i] = 0;

    test = isGameOver(&g1);

    int supplyTest = 0;
    for(i = 0; i < 25; i++)
        //test the state of the supply card piles
        if(g1.supplyCount[i] == 0)
            supplyTest++;

    assertTrue((!test && supplyTest < 3), 4);

    return 0;
}


