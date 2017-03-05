/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 03/05/17
* Assignment 5
* unittest2.c 
* Testing: int drawCard(int player, struct gameState *state)
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

    printf("Testing drawCard()\n");

    /* TEST 1: Player 0 draws one card, deck not empty */
    drawCard(0, &actualState);
    success = 0;
    /* check that a card was removed from player 0's deck */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0] - 1, 1.1);
    /* check that a card was added to player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] + 1, 1.2);
    /* check that player 0's discard count hasn't changed */
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0], 1.3);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 1.4);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 1.5);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 1.6);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 1.7);
    /* if all subtests passed, print success message */
    if (success == (7 + treasure_map)){
        printf("TEST 1 COMPLETED SUCCESSFULLY\n");
    }

    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    
    /* TEST 2: Player 1 draws one card, deck not empty */
    drawCard(1, &actualState);
    success = 0;
    /* check that a card was removed from player 1's deck */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1] - 1, 2.1);
    /* check that a card was added to player 1's hand */
    success += asserttrue(actualState.handCount[1], copyState.handCount[1] + 1, 2.2);
    /* check that player 1's discard count hasn't changed */
    success += asserttrue(actualState.discardCount[1], copyState.discardCount[1], 2.3);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 2.4);
    }
    /* check that player 0's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 2.5);
    success += asserttrue(actualState.handCount[0], copyState.handCount[0], 2.6);
    success += asserttrue(actualState.discardCount[0], actualState.discardCount[0], 2.7);
    /* if all subtests passed, print success message */
    if (success == (7 + treasure_map)){
        printf("TEST 2 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 3: Player 0 draws one card, deck empty */
    /* empty player 0's deck */
    for (i = 0; i < actualState.deckCount[0]; i++){
        actualState.discard[0][i] = actualState.deck[0][i];
        actualState.deck[0][i] = -1;
    }
    actualState.discardCount[0] = actualState.deckCount[0];
    actualState.deckCount[0] = 0;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* draw one card */
    drawCard(0, &actualState);
    success = 0;
    /* check that player 0's discard is empty */
    success += asserttrue(actualState.discardCount[0], 0, 3.1);
    /* check that player 0's deck has the number of cards that were in the discard, minus one */
    success += asserttrue(actualState.deckCount[0], copyState.discardCount[0] - 1, 3.2);
    /* check that player 0's hand has one more card */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] + 1, 3.3);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 3.4);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 3.5);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 3.6);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 3.7);
    /* if all subtests passed, print success message */
    if (success == (7 + treasure_map)){
        printf("TEST 3 COMPLETED SUCCESSFULLY\n");
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