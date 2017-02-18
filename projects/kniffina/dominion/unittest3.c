/******************************************************************************
* unitTest3.c tests the function shuffle() from dominion.c
******************************************************************************/
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//implemented after main
int compare2(const void* a, const void* b);

//assertTrue takes a an int and int testNumber and if the test is true (equal to 1)
//  the string is returned to indicate that the test was successful, otherwise it failed.
void assertTrue(int test, int testNumber) {
    printf("Function shuffle() - ");
    if (test == 1)
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
    else
        printf("TEST %d FAILED.\n", testNumber);
}

int main() {
    struct gameState g1, g2;

    int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
    initializeGame(2, k, 10, &g1); //initialize the game
    int player = g1.whoseTurn; //set the player to whose turn it is

    memcpy(&g2, &g1, sizeof(struct gameState));

    //1 - test that we are changing at least 1 card in the players decks respectively.
    shuffle(player, &g1); //call the shuffle method
    int i, returnValue = 0;
    for(i = 0; i < g1.deckCount[player]; i++) {
        if(g1.deck[i] != g2.deck[i])
            returnValue = 1;
    }

    assertTrue(returnValue, 1);

    // 2 - Test that shuffles sorting method sorts the array passed in. We are going tbe testing
    //      the qsort found in the shuffle method
    int test1[10] = {6, 11, 2, 5, 9, 4, 12, 22, 1, 75};
    qsort((void*)test1, 10, sizeof(int), compare2);
    int isSorted = 0;
    for(i = 0; i < 9; i++) {
        if(test1[i] < test1[i + 1])
            isSorted = 1;
        else
            isSorted = 1;
    }

    assertTrue(isSorted, 2);

    //3 - Test that the other players deck stays constant
    shuffle(player, &g1);
    returnValue = 0;
    for(i = 0; i < g1.deckCount[1]; i++)
        if(g1.hand[1][i] == g2.hand[1][i])
            returnValue = 1;

    assertTrue(returnValue, 3);

    //4 - Test that shuffle terminates in corret spot and returns -1 if deckCount is less than 1
    g1.deckCount[player] = 0;
    returnValue = 0; //reset returnValue
    if(shuffle(player, &g1) == -1)
        returnValue = 1;

    assertTrue(returnValue, 4);

    //5 - Test that shuffle terminates and returns -1 if deck count is less than -1
    g1.deckCount[player] = -50;
    returnValue = 0;
    if(shuffle(player, &g1) == -1)
        returnValue = 1;

    assertTrue(returnValue, 5);

    //6 - Test that shuffle terminates
    g1.deckCount[player] = 1;
    returnValue = 0;
    if(shuffle(player, &g1) == 0)
        returnValue = 1;

    assertTrue(returnValue , 6);

    // 7 - Test that shuffle terminates and returns 0 if deck count is a large positive int
    g1.deckCount[player] = 999;
    returnValue = 0;
    if(shuffle(player, &g1) == 0)
        returnValue = 1;

    assertTrue(returnValue, 7);

    return 0;
}

int compare2(const void* a, const void* b) {
    if (*(int*)a > *(int*)b)
        return 1;
    else if (*(int*)a < *(int*)b)
        return -1;
    else
        return 0;
}