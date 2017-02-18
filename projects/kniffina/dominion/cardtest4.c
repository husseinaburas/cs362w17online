/******************************************************************************
* cardTest4.c tests the council room card from dominion.c
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
    printf("Card Test COUNCIL_ROOM - ");
    if (test == 1)
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
    else
        printf("TEST %d FAILED.\n", testNumber);
}

int main() {
    //create variables from cardEffect
    int drawnCards = 4, discarded = 1, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0,
            bonus = 0, player = 0;

    struct gameState g1, g2;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    //initialize gamestate and cards
    initializeGame(2, k, 1000, &g1);

    //copy to other gameState
    memcpy(&g2, &g1, sizeof(struct gameState));

    //call cardEffect with our council room
    cardEffect(council_room, choice1, choice2, choice3, &g2, handpos, &bonus);

    //get the number of buys after we called council room in cardEffect and before
    int beforeEffectsBuys = g1.numBuys;
    int afterEffectBuys = g2.numBuys;

    //get the bandcount for the before cardEffect and after
    int pre = g1.handCount[player] + (drawnCards - discarded);
    int post = g2.handCount[player];

    //1 - Test that 4 cards were added.
    assertTrue((pre == post), 1);

    //2 - Test that number of buys was increased by 1
    if((afterEffectBuys - beforeEffectsBuys), 2);

    //get the deck counts from before call to council and after
    int projectedDeckCount = (g1.deckCount[player + 1]) - 1;
    int actualDeckCount = g2.deckCount[player + 1];

    //3 - Test that the other player have drawn an additional card
    assertTrue((projectedDeckCount == actualDeckCount), 3);


    return 0;
}