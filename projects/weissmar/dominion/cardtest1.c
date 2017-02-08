/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 2/7/17
* Assignment 3
* cardtest1.c 
* Testing: void playAdventurer(int currentPlayer, struct gameState *state)
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

    /* initialize a game */
    initializeGame(numPlayers, kingdomCards, seed, &actualState);

    printf("Testing playAdventurer()\n");

    /* TEST 1: Player 0 plays Adventurer after game initialization */
    /* give player 0 a copy of adventurer to play */
    actualState.hand[0][0] = adventurer;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play adventurer */
    playAdventurer(0, &actualState);
    success = 0;
    /* check that one card was added (two cards added, one removed) to player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] + 1, 1.1);
    /* check that the two top hand cards for player 0 are treasure cards */
    success += asserttrue(actualState.hand[0][actualState.handCount[0] - 1], copper, 1.2);
    success += asserttrue(actualState.hand[0][actualState.handCount[0] - 2], copper, 1.3);
    /* check that the played copy of adventurer was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], adventurer, 1.4);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], adventurer, 1.5);
    }
    /* check that player 0's discard + deck count has decreased by 2 */
    success += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0] - 2, 1.6);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 1.7);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 1.8);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 1.8);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 1.8);
    /* if all subtests passed, print success message */
    if (success == (9 + treasure_map + actualState.handCount[0])){
        printf("TEST 1 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 2: Player 0 plays Adventurer with an empty deck and two treasure cards in discard */
    /* give player 0 a copy of adventurer to play */
    actualState.hand[0][0] = adventurer;
    /* empty player 0's deck */
    actualState.deckCount[0] = 0;
    /* put two silver and five estates in player 0's discard */
    actualState.discard[0][0] = silver;
    actualState.discard[0][1] = estate;
    actualState.discard[0][2] = estate;
    actualState.discard[0][3] = estate;
    actualState.discard[0][4] = estate;
    actualState.discard[0][5] = estate;
    actualState.discard[0][6] = silver;
    actualState.discardCount[0] = 7;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play adventurer */
    playAdventurer(0, &actualState);
    success = 0;
    /* check that one card was added (two cards added, one removed) to player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] + 1, 2.1);
    /* check that the two top hand cards for player 0 are treasure cards */
    success += asserttrue(actualState.hand[0][actualState.handCount[0] - 1], silver, 2.2);
    success += asserttrue(actualState.hand[0][actualState.handCount[0] - 2], silver, 2.3);
    /* check that the played copy of adventurer was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], adventurer, 2.4);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], adventurer, 2.5);
    }
    /* check that player 0's discard + deck count has decreased by 2 */
    success += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0] - 2, 2.6);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 2.7);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 2.8);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 2.8);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 2.8);
    /* if all subtests passed, print success message */
    if (success == (9 + treasure_map + actualState.handCount[0])){
        printf("TEST 2 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 3: Player 0 plays Adventurer with an empty deck and one treasure card in discard */
    /* give player 0 a copy of adventurer to play */
    actualState.hand[0][0] = adventurer;
    /* empty player 0's deck */
    actualState.deckCount[0] = 0;
    /* put one gold and five estates in player 0's discard */
    actualState.discard[0][0] = gold;
    actualState.discard[0][1] = estate;
    actualState.discard[0][2] = estate;
    actualState.discard[0][3] = estate;
    actualState.discard[0][4] = estate;
    actualState.discard[0][5] = estate;
    actualState.discardCount[0] = 6;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play adventurer */
    playAdventurer(0, &actualState);
    success = 0;
    /* check that no cards were added (one card added, one removed) to player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] + 1, 3.1);
    /* check that the top hand card for player 0 is a treasure card */
    success += asserttrue(actualState.hand[0][actualState.handCount[0] - 1], gold, 3.2);
    /* check that the played copy of adventurer was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], adventurer, 3.3);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], adventurer, 3.4);
    }
    /* check that player 0's discard + deck count has decreased by 1 */
    success += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0] - 1, 3.5);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 3.6);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 3.7);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 3.7);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 3.7);
    /* if all subtests passed, print success message */
    if (success == (8 + treasure_map + actualState.handCount[0])){
        printf("TEST 3 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 4: Player 0 plays Adventurer with an empty deck and no treasure cards in discard */
    /* give player 0 a copy of adventurer to play */
    actualState.hand[0][0] = adventurer;
    /* empty player 0's deck */
    actualState.deckCount[0] = 0;
    /* put five estates in player 0's discard */
    actualState.discard[0][0] = estate;
    actualState.discard[0][1] = estate;
    actualState.discard[0][2] = estate;
    actualState.discard[0][3] = estate;
    actualState.discard[0][4] = estate;
    actualState.discardCount[0] = 5;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play adventurer */
    playAdventurer(0, &actualState);
    success = 0;
    /* check that one card was removed from player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] - 1, 4.1);
    /* check that the played copy of adventurer was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], adventurer, 4.2);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], adventurer, 4.3);
    }
    /* check that player 0's discard + deck count hasn't changed */
    success += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0], 4.4);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 4.5);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 4.6);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 4.6);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 4.6);
    /* if all subtests passed, print success message */
    if (success == (7 + treasure_map + actualState.handCount[0])){
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