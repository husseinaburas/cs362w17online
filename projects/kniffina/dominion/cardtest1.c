/******************************************************************************
* cardTest1.c tests the smithy card from dominion.c
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
    printf("Card Test SMITHY - ");
    if (test == 1)
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
    else
        printf("TEST %d FAILED.\n", testNumber);
}

int main() {
    int discardedCards = 1, shuffledCards = 0;
    int player = 0, k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState g1, g2;

    //initialize the game
    initializeGame(2, k, 10, &g1);

    g1.whoseTurn = 0;
    g1.hand[0][0] = smithy; //set the card to smithy

    //save initial state
    memcpy(&g2, &g1, sizeof(struct gameState));

    //1 - Test that the cards were given correctly
    cardEffect(smithy, 0, 0, 0, &g2, 0, 0);

    //now test the number of the cards in the hand
    assertTrue((g2.handCount[player] == g1.handCount[player] + 3), 1);

    //2 - Test the number of cards in the deck
    assertTrue((g2.handCount[player] == g1.handCount[player] - 3), 2);

    //3 - test the amount of cards discarded
    assertTrue((g2.discardCount[0] == g1.discardCount[0]), 3);

    //4 - Test other players state change
    assertTrue((g2.deckCount[1] == g2.deckCount[1]), 4);

    //5 - Test hand count
    assertTrue((g2.handCount[1] == g1.handCount[1]), 5);

    //6 - Test discard
    assertTrue((g2.discardCount[1] == g1.discardCount[1]), 6);

    return 0;
}
