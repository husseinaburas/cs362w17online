/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 03/05/17
* Assignment 5
* cardtest3.c 
* Testing: int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
*           (with baron as first parameter)
*
************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int asserttrue(int x, int y, float testNum);
int assertfalse(int x, int y, float testNum);

int main() {
    int numPlayers = 2;
    int kingdomCards[] = {adventurer, smithy, remodel, baron, feast, great_hall, gardens, mine, council_room, village};
    int seed = 100000;
    struct gameState actualState, copyState;
    int success;
    int i;
    int actualCount, copyCount;

    /* initialize a game */
    initializeGame(numPlayers, kingdomCards, seed, &actualState);

    printf("Testing playBaron()\n");

    /* TEST 1: Player 0 plays Baron after game initialization, chooses to discard an Estate */
    /* give player 0 a copy of Baron to play */
    actualState.hand[0][0] = baron;
    /* ensure that player 0 has an estate in hand */
    actualState.hand[0][1] = estate;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play Baron */
    cardEffect(baron, 1, -1, -1, &actualState, 0, NULL);
    success = 0;
    /* check that one estate and one baron were removed from player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] - 2, 1.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == estate)
            actualCount++;
        if (copyState.hand[0][i] == estate)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount - 1, 1.1);
    /* check that the played copy of Baron was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], baron, 1.2);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], baron, 1.2);
    }
    /* check that one estate was added to player 0's discard */
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0] + 1, 1.3);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < actualState.discardCount[0]; i++){
        if (actualState.discard[0][i] == estate)
            actualCount++;
        if (copyState.discard[0][i] == estate)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount + 1, 1.4);
    /* check that coins were increased by 4 */
    success += asserttrue(actualState.coins, copyState.coins + 4, 1.5);
    /* check that buys were increased by 1 */
    success += asserttrue(actualState.numBuys, copyState.numBuys + 1, 1.6);
    /* check that player 0's deck count hasn't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 1.7);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 1.8);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 1.9);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 1.9);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 1.9);
    /* if all subtests passed, print success message */
    if (success == (12 + treasure_map + actualState.handCount[0])){
        printf("TEST 1 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 2: Player 0 plays Baron, chooses not to discard an Estate */
    /* give player 0 a copy of Baron to play */
    actualState.hand[0][0] = baron;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play Baron */
    cardEffect(baron, 0, -1, -1, &actualState, 0, NULL);
    success = 0;
    /* check that one estate was added player 0's discard */
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0] + 1, 2.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < actualState.discardCount[0]; i++){
        if (actualState.discard[0][i] == estate)
            actualCount++;
        if (copyState.discard[0][i] == estate)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount + 1, 2.1);
    /* check that the played copy of Baron was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], baron, 2.2);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], baron, 2.2);
    }
    /* check that player 0's hand count decreased by one */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] - 1, 2.3);
    /* check that coins remained the same */
    success += asserttrue(actualState.coins, copyState.coins, 2.4);
    /* check that buys were increased by 1 */
    success += asserttrue(actualState.numBuys, copyState.numBuys + 1, 2.5);
    /* check that player 0's deck count hasn't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 2.6);
    /* check that the estate supply count has decreased by one */
    success += asserttrue(actualState.supplyCount[estate], copyState.supplyCount[estate] - 1, 2.7);
    /* check that no other supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        if (i != estate)
            success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 2.8);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 2.9);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 2.9);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 2.9);
    /* if all subtests passed, print success message */
    if (success == (11 + treasure_map + actualState.handCount[0])){
        printf("TEST 2 COMPLETED SUCCESSFULLY\n");
    }    

    /* TEST 3: Player 0 plays Baron, chooses not to discard an Estate, Estate supply empty */
    /* give player 0 a copy of Baron to play */
    actualState.hand[0][0] = baron;
    /* make Estate supply empty */
    actualState.supplyCount[estate] = 0;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play Baron */
    cardEffect(baron, 0, -1, -1, &actualState, 0, NULL);
    success = 0;
    /* check that no estates were added to or removed from player 0's hand, one Baron removed */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] - 1, 3.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == estate)
            actualCount++;
        if (copyState.hand[0][i] == estate)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount, 3.1);
    /* check that the played copy of Baron was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], baron, 3.2);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], baron, 3.2);
    }
    /* check that player 0's discard count didn't change */
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0], 3.3);
    /* check that coins remained the same */
    success += asserttrue(actualState.coins, copyState.coins, 3.4);
    /* check that buys were increased by 1 */
    success += asserttrue(actualState.numBuys, copyState.numBuys + 1, 3.5);
    /* check that player 0's deck count hasn't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 3.6);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 3.7);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 3.8);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 3.8);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 3.8);
    /* if all subtests passed, print success message */
    if (success == (11 + treasure_map + actualState.handCount[0])){
        printf("TEST 3 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 4: Player 0 plays Baron, chooses to discard an Estate, no Estate in hand, Estates available in supply */
    /* give player 0 a copy of Baron to play */
    actualState.hand[0][0] = baron;
    /* set player 0 hand to not have any Estates */
    actualState.hand[0][1] = copper;
    actualState.hand[0][2] = copper;
    actualState.hand[0][3] = copper;
    actualState.hand[0][4] = copper;
    actualState.handCount[0] = 5;
    /* make Estate supply not empty */
    actualState.supplyCount[estate] = 5;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play Baron */
    cardEffect(baron, 1, -1, -1, &actualState, 0, NULL);
    success = 0;
    /* check that one estate was added player 0's discard */
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0] + 1, 4.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < actualState.discardCount[0]; i++){
        if (actualState.discard[0][i] == estate)
            actualCount++;
        if (copyState.discard[0][i] == estate)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount + 1, 4.1);
    /* check that the played copy of Baron was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], baron, 4.2);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], baron, 4.2);
    }
    /* check that player 0's hand count decreased by one */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] - 1, 4.3);
    /* check that coins remained the same */
    success += asserttrue(actualState.coins, copyState.coins, 4.4);
    /* check that buys were increased by 1 */
    success += asserttrue(actualState.numBuys, copyState.numBuys + 1, 4.5);
    /* check that player 0's deck count hasn't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 4.6);
    /* check that the estate supply count has decreased by one */
    success += asserttrue(actualState.supplyCount[estate], copyState.supplyCount[estate] - 1, 4.7);
    /* check that no other supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        if (i != estate)
            success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 4.8);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 4.9);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 4.9);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 4.9);
    /* if all subtests passed, print success message */
    if (success == (11 + treasure_map + actualState.handCount[0])){
        printf("TEST 4 COMPLETED SUCCESSFULLY\n");
    }    
}

int asserttrue(int x, int y, float testNum) {
    if (x == y) {
        return 1;
    } else {
        fprintf(stdout, "TEST %.1f FAILED\n", testNum);
        return 0;
    }
}

int assertfalse(int x, int y, float testNum) {
    if (x != y) {
        return 1;
    } else {
        fprintf(stdout, "TEST %.1f FAILED\n", testNum);
        return 0;
    }
}
