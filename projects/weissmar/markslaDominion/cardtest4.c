/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 03/05/17
* Assignment 5
* cardtest4.c 
* Testing: int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
*           (with remodel as first argument)
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

    printf("Testing playRemodel()\n");

    /* TEST 1: Player 0 plays Remodel after game initialization, chooses to trash an Estate and gain a Baron */
    /* give player 0 a copy of Remodel to play */
    actualState.hand[0][0] = remodel;
    /* give player 0 a copy of Estate to trash */
    actualState.hand[0][1] = estate;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play Remodel */
    cardEffect(remodel, 1, baron, -1, &actualState, 0, NULL);
    success = 0;
    /* check that one estate and one remodel were removed from player 0's hand and one baron added */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] - 1, 1.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == estate)
            actualCount++;
        if (copyState.hand[0][i] == estate)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount - 1, 1.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == baron)
            actualCount++;
        if (copyState.hand[0][i] == baron)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount + 1, 1.1);
    /* check that the played copy of Remodel was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], remodel, 1.2);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], remodel, 1.2);
    }
    /* check that one Baron was removed from supply */
    success += asserttrue(actualState.supplyCount[baron], copyState.supplyCount[baron] - 1, 1.3);
    /* check that player 0's deck and discard counts haven't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 1.4);
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0], 1.5);
    /* check that no supply counts other than Baron have changed */
    for (i = 0; i <= treasure_map; i++){
        if (i != baron)
            success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 1.6);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 1.7);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 1.7);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 1.7);
    /* if all subtests passed, print success message */
    if (success == (10 + treasure_map + actualState.handCount[0])){
        printf("TEST 1 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 2: Player 0 plays Remodel, chooses to trash an Adventurer and gain a Province */
    /* give player 0 a copy of Remodel to play */
    actualState.hand[0][0] = remodel;
    /* give player 0 a copy of Adventurer to trash */
    actualState.hand[0][1] = adventurer;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play Remodel */
    cardEffect(remodel, 1, province, -1, &actualState, 0, NULL);
    success = 0;
    /* check that one adventurer and one remodel were removed from player 0's hand and one province added */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] - 1, 2.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == adventurer)
            actualCount++;
        if (copyState.hand[0][i] == adventurer)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount - 1, 2.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == province)
            actualCount++;
        if (copyState.hand[0][i] == province)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount + 1, 2.1);
    /* check that the played copy of Remodel was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], remodel, 2.2);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], remodel, 2.2);
    }
    /* check that one province was removed from supply */
    success += asserttrue(actualState.supplyCount[province], copyState.supplyCount[province] - 1, 2.3);
    /* check that player 0's deck and discard counts haven't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 2.4);
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0], 2.5);
    /* check that no supply counts other than Province have changed */
    for (i = 0; i <= treasure_map; i++){
        if (i != province)
            success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 2.6);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 2.7);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 2.7);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 2.7);
    /* if all subtests passed, print success message */
    if (success == (10 + treasure_map + actualState.handCount[0])){
        printf("TEST 2 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 3: Player 0 plays Remodel, chooses to trash a Council Room and gain a Province */
    /* give player 0 a copy of Remodel to play */
    actualState.hand[0][0] = remodel;
    /* give player 0 a copy of council_room to trash */
    actualState.hand[0][1] = council_room;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play Remodel */
    cardEffect(remodel, 1, province, -1, &actualState, 0, NULL);
    success = 0;
    /* check that player 0's hand hasn't changed */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0], 3.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == council_room)
            actualCount++;
        if (copyState.hand[0][i] == council_room)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount, 3.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == province)
            actualCount++;
        if (copyState.hand[0][i] == province)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount, 3.1);
    /* check that player 0's deck and discard counts haven't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 3.2);
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0], 3.3);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 3.4);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 3.5);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 3.6);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 3.7);
    /* if all subtests passed, print success message */
    if (success == (9 + treasure_map + actualState.handCount[0])){
        printf("TEST 3 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 4: Player 0 plays Remodel, chooses to trash an Adventurer and gain a Village */
    /* give player 0 a copy of Remodel to play */
    actualState.hand[0][0] = remodel;
    /* give player 0 a copy of Adventurer to trash */
    actualState.hand[0][1] = adventurer;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play Remodel */
    cardEffect(remodel, 1, village, -1, &actualState, 0, NULL);
    success = 0;
    /* check that one adventurer and one remodel were removed from player 0's hand and one village added */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] - 1, 4.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == adventurer)
            actualCount++;
        if (copyState.hand[0][i] == adventurer)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount - 1, 4.1);
    actualCount = 0;
    copyCount = 0;
    for (i = 0; i < copyState.handCount[0]; i++){
        if (actualState.hand[0][i] == village)
            actualCount++;
        if (copyState.hand[0][i] == village)
            copyCount++;
    }
    success += asserttrue(actualCount, copyCount + 1, 4.1);
    /* check that the played copy of Remodel was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], remodel, 4.2);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], remodel, 4.2);
    }
    /* check that one village was removed from supply */
    success += asserttrue(actualState.supplyCount[village], copyState.supplyCount[village] - 1, 4.3);
    /* check that player 0's deck and discard counts haven't changed */
    success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], 4.4);
    success += asserttrue(actualState.discardCount[0], copyState.discardCount[0], 4.5);
    /* check that no supply counts other than village have changed */
    for (i = 0; i <= treasure_map; i++){
        if (i != village)
            success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 4.6);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 4.7);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 4.7);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 4.7);
    /* if all subtests passed, print success message */
    if (success == (10 + treasure_map + actualState.handCount[0])){
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