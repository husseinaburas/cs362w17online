/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 2/7/17
* Assignment 3
* cardtest2.c 
* Testing: void playSmithy(int currentPlayer, struct gameState *state, int handPos)
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
    int count;

    /* initialize a game */
    initializeGame(numPlayers, kingdomCards, seed, &actualState);

    printf("Testing playSmithy()\n");

    /* TEST 1: Player 0 plays Smithy after game initialization */
    /* give player 0 a copy of smithy to play */
    actualState.hand[0][0] = smithy;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play smithy */
    playSmithy(0, &actualState, 0);
    success = 0;
    /* check that two cards were added (three cards added, one removed) to player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] + 2, 1.1);
    /* check that the three added hand cards for player 0 are the three cards from the deck */
    count = 0;
    for (i = 0; i < actualState.handCount[0]; i++){
        if ((actualState.hand[0][i] != copper) && (actualState.hand[0][i] != estate))
            count++;
    }
    success += asserttrue(count, 0, 1.2);
    /* check that the played copy of smithy was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], smithy, 1.3);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], smithy, 1.4);
    }
    /* check that player 0's discard + deck count has decreased by 3 */
    success += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0] - 3, 1.5);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 1.6);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 1.7);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 1.7);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 1.7);
    /* if all subtests passed, print success message */
    if (success == (8 + treasure_map + actualState.handCount[0])){
        printf("TEST 1 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 2: Player 0 plays Smithy with an empty deck and 5 cards in discard*/
    /* give player 0 a copy of smithy to play */
    actualState.hand[0][0] = smithy;
    /* empty player 0's deck */
    actualState.deckCount[0] = 0;
    /* put five silvers in player 0's discard */
    actualState.discard[0][0] = silver;
    actualState.discard[0][1] = silver;
    actualState.discard[0][2] = silver;
    actualState.discard[0][3] = silver;
    actualState.discard[0][4] = silver;
    actualState.discardCount[0] = 5;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play smithy */
    playSmithy(0, &actualState, 0);
    success = 0;
    /* check that two cards were added (three cards added, one removed) to player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] + 2, 2.1);
    /* check that the three added hand cards for player 0 are three cards from the discard */
    count = 0;
    for (i = 0; i < actualState.handCount[0]; i++){
        if (actualState.hand[0][i] == silver)
            count++;
    }
    success += asserttrue(count, 3, 2.2);
    /* check that the played copy of smithy was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], smithy, 2.3);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], smithy, 2.4);
    }
    /* check that player 0's discard + deck count has decreased by 3 */
    success += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0] - 3, 2.5);
    /* check that no supply counts have changed */
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], 2.6);
    }
    /* check that player 1's deck, hand, and discard haven't changed */
    success += asserttrue(actualState.deckCount[1], copyState.deckCount[1], 2.7);
    success += asserttrue(actualState.handCount[1], copyState.handCount[1], 2.7);
    success += asserttrue(actualState.discardCount[1], actualState.discardCount[1], 2.7);
    /* if all subtests passed, print success message */
    if (success == (8 + treasure_map + actualState.handCount[0])){
        printf("TEST 2 COMPLETED SUCCESSFULLY\n");
    }    

    /* TEST 3: Player 0 plays Smithy with an empty deck and 2 cards in discard */
    /* give player 0 a copy of smithy to play */
    actualState.hand[0][0] = smithy;
    /* empty player 0's deck */
    actualState.deckCount[0] = 0;
    /* put two gold in player 0's discard */
    actualState.discard[0][0] = gold;
    actualState.discard[0][1] = gold;
    actualState.discardCount[0] = 2;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play smithy */
    playSmithy(0, &actualState, 0);
    success = 0;
    /* check that one card was added (two cards added, one removed) to player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] + 1, 3.1);
    /* check that the two cards added to player 0's hand are the two cards from the discard */
    count = 0;
    for (i = 0; i < actualState.handCount[0]; i++){
        if (actualState.hand[0][i] == gold)
            count++;
    }
    success += asserttrue(count, 2, 3.2);
    /* check that the played copy of smithy was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], smithy, 3.3);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], smithy, 3.4);
    }
    /* check that player 0's discard + deck count has decreased by 2 */
    success += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0] - 2, 3.5);
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

    /* TEST 4: Player 0 plays Smithy with an empty deck and an empty discard */
    /* give player 0 a copy of smithy to play */
    actualState.hand[0][0] = smithy;
    /* empty player 0's deck */
    actualState.deckCount[0] = 0;
    /* empty player 0's discard */
    actualState.discardCount[0] = 0;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* play smithy */
    playSmithy(0, &actualState, 0);
    success = 0;
    /* check that one card was removed from player 0's hand */
    success += asserttrue(actualState.handCount[0], copyState.handCount[0] - 1, 4.1);
    /* check that the played copy of smithy was moved from hand to playedCards */
    success += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], smithy, 4.2);
    for (i = 0; i < actualState.handCount[0]; i++){
        success += assertfalse(actualState.hand[0][i], smithy, 4.3);
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