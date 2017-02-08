/************************************************************************
* 
* Rachel Weissman-Hohler
* CS 362-400
* 2/7/17
* Assignment 3
* unittest1.c 
* Testing: int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
*
************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int asserttrue(int x, int y, float testNum);

int main() {
    int numPlayers = 2;
    int kingdomCards[] = {adventurer, smithy, remodel, baron, feast, great_hall, gardens, mine, council_room, village};
    int seed = 100000;
    struct gameState actualState, copyState;
    int success;
    int i;

    /* initialize a game */
    initializeGame(numPlayers, kingdomCards, seed, &actualState);

    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));

    printf("Testing gainCard()\n");

    /* TEST 1: Gain adventurer to discard for player 0 */
    gainCard(adventurer, &actualState, 0, 0);
    success = 0;
    /* check that a copy of adventurer was removed from the adventurer supply */
    success += asserttrue(actualState.supplyCount[adventurer], copyState.supplyCount[adventurer] - 1, 1.1);
    /* check that a card was added to player 0's discard */
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0] + 1, 1.2);
    /* check that player 0's deck count and hand count haven't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 1.3);
    success += asserttrue(actualState.handCount[0], copyState.handCount[0], 1.4);
    /* check that player 1's discard, deck, and hand counts haven't changed */
    success += asserttrue(actualState.discardCount[1], copyState.discardCount[1], 1.5);
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 1.6);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 1.7);
    /* check that supply counts for other cards haven't changed */
    for (i = 0; i <= treasure_map; i++){
        if (i != adventurer){
            success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 1.8);
        }
    }
    /* if all subtests passed, print success message */
    if (success == (7 + treasure_map)){
        printf("TEST 1 COMPLETED SUCCESSFULLY\n");
    }

    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));

    /* TEST 2: Gain baron to hand for player 1 */
    gainCard(baron, &actualState, 2, 1);
    success = 0;
    /* check that a copy of baron was removed from the baron supply */
    success += asserttrue(actualState.supplyCount[baron], copyState.supplyCount[baron] - 1, 2.1);
    /* check that a card was added to player 1's hand */
    success += asserttrue(actualState.handCount[1], copyState.handCount[1] + 1, 2.2);
    /* check that player 1's deck count and discard count haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 2.3);
    success += asserttrue(actualState.discardCount[1], copyState.discardCount[1], 2.4);
    /* check that player 0's discard, deck, and hand counts haven't changed */
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0], 2.5);
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 2.6);
    success += asserttrue(actualState.handCount[0], copyState.handCount[0], 2.7);
    /* check that supply counts for other cards haven't changed */
    for (i = 0; i <= treasure_map; i++){
        if (i != baron){
            success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 2.8);
        }
    }
    /* if all subtests passed, print success message */
    if (success == (7 + treasure_map)){
        printf("TEST 2 COMPLETED SUCCESSFULLY\n");
    }

    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));

    /* TEST 3: Gain village to deck for player 1 */
    gainCard(village, &actualState, 1, 1);
    success = 0;
    /* check that a copy of village was removed from the village supply */
    success += asserttrue(actualState.supplyCount[village], copyState.supplyCount[village] - 1, 3.1);
    /* check that a card was added to player 1's deck */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1] + 1, 3.2);
    /* check that player 1's hand count and discard count haven't changed */
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 3.3);
    success += asserttrue(actualState.discardCount[1], copyState.discardCount[1], 3.4);
    /* check that player 0's discard, deck, and hand counts haven't changed */
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0], 3.5);
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 3.6);
    success += asserttrue(actualState.handCount[0], copyState.handCount[0], 3.7);
    /* check that supply counts for other cards haven't changed */
    for (i = 0; i <= treasure_map; i++){
        if (i != village){
            success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 3.8);
        }
    }
    /* if all subtests passed, print success message */
    if (success == (7 + treasure_map)){
        printf("TEST 3 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 4: Gain village to deck for player 1, village supply empty */
    /* set village supply to empty */
    actualState.supplyCount[village] = 0;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* gain card */
    gainCard(village, &actualState, 1, 1);
    success = 0;
    /* check that no cards were added to player 1's deck */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 4.1);
    /* check that player 1's hand count and discard count haven't changed */
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 4.2);
    success += asserttrue(actualState.discardCount[1], copyState.discardCount[1], 4.3);
    /* check that player 0's discard, deck, and hand counts haven't changed */
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0], 4.4);
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 4.5);
    success += asserttrue(actualState.handCount[0], copyState.handCount[0], 4.6);
    /* check that supply counts haven't changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 4.7);
    }
    /* if all subtests passed, print success message */
    if (success == (7 + treasure_map)){
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