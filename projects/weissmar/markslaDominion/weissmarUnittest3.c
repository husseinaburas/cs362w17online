/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 03/05/17
* Assignment 5
* unittest3.c 
* Testing: int isGameOver(struct gameState *state)
*
************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int asserttrue(int x, int y, float testNum);
int checkNoStateChange(struct gameState* checkState, struct gameState* origState, float testNum);

int main() {
    int numPlayers = 2;
    int kingdomCards[] = {adventurer, smithy, remodel, baron, feast, great_hall, gardens, mine, council_room, village};
    int seed = 100000;
    struct gameState actualState, copyState;
    int success;
    int isOver;

    /* initialize a game */
    initializeGame(numPlayers, kingdomCards, seed, &actualState);

    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));

    printf("Testing isGameOver()\n");

    /* TEST 1: The game has just been initialized */
    isOver = isGameOver(&actualState);
    success = 0;
    /* check that isGameOver returned 0 */
    success += asserttrue(isOver, 0, 1.1);
    /* check that the game state wasn't changed */
    success += checkNoStateChange(&actualState, &copyState, 1.2);
    /* if all subtests passed, print success message */
    if (success == 2){
        printf("TEST 1 COMPLETED SUCCESSFULLY\n");
    }
    
    /* TEST 2: The Province supply is empty */
    /* set province supply to 0 */
    actualState.supplyCount[province] = 0;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* check isGameOver() */
    isOver = isGameOver(&actualState);
    success = 0;
    /* check that isGameOver returned 1 */
    success += asserttrue(isOver, 1, 2.1);
    /* check that the game state wasn't changed */
    success += checkNoStateChange(&actualState, &copyState, 2.2);
    /* if all subtests passed, print success message */
    if (success == 2){
        printf("TEST 2 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 3: The province supply is not empty, but two other supplies are empty */
    /* set province supply to 5 */
    actualState.supplyCount[province] = 5;
    /* set Baron and Mine supplies to 0 */
    actualState.supplyCount[baron] = 0;
    actualState.supplyCount[mine] = 0;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* check isGameOver() */
    isOver = isGameOver(&actualState);
    success = 0;
    /* check that isGameOver returned 0 */
    success += asserttrue(isOver, 0, 3.1);
    /* check that the game state wasn't changed */
    success += checkNoStateChange(&actualState, &copyState, 3.2);
    /* if all subtests passed, print success message */
    if (success == 2){
        printf("TEST 3 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 4: The province supply is not empty, but three other supplies are empty */
    /* set province supply to 5 */
    actualState.supplyCount[province] = 5;
    /* set Baron, Mine, and Remodel supplies to 0 */
    actualState.supplyCount[baron] = 0;
    actualState.supplyCount[mine] = 0;
    actualState.supplyCount[remodel] = 0;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* check isGameOver() */
    isOver = isGameOver(&actualState);
    success = 0;
    /* check that isGameOver returned 1 */
    success += asserttrue(isOver, 1, 4.1);
    /* check that the game state wasn't changed */
    success += checkNoStateChange(&actualState, &copyState, 4.2);
    /* if all subtests passed, print success message */
    if (success == 2){
        printf("TEST 4 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 5: The province supply is not empty, but four other supplies are empty */
    /* set province supply to 5 */
    actualState.supplyCount[province] = 5;
    /* set Baron, Mine, Remodel, and Village supplies to 0 */
    actualState.supplyCount[baron] = 0;
    actualState.supplyCount[mine] = 0;
    actualState.supplyCount[remodel] = 0;
    actualState.supplyCount[village] = 0;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* check isGameOver() */
    isOver = isGameOver(&actualState);
    success = 0;
    /* check that isGameOver returned 1 */
    success += asserttrue(isOver, 1, 5.1);
    /* check that the game state wasn't changed */
    success += checkNoStateChange(&actualState, &copyState, 5.2);
    /* if all subtests passed, print success message */
    if (success == 2){
        printf("TEST 5 COMPLETED SUCCESSFULLY\n");
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

int checkNoStateChange(struct gameState* checkState, struct gameState* origState, float testNum){
    int success = 0;
    int totalSuccess = 9 + (2 * (treasure_map + 1)) + (3 * MAX_PLAYERS) + (MAX_PLAYERS * MAX_HAND) + (3 * MAX_PLAYERS * MAX_DECK);
    int i, j, k;

    success += asserttrue(checkState->numPlayers, origState->numPlayers, testNum);
    for (i = 0; i <= treasure_map; i++){
        success += asserttrue(checkState->supplyCount[i], origState->supplyCount[i], testNum);
        success += asserttrue(checkState->embargoTokens[i], origState->embargoTokens[i], testNum);
    }
    success += asserttrue(checkState->outpostPlayed, origState->outpostPlayed, testNum);
    success += asserttrue(checkState->outpostTurn, origState->outpostTurn, testNum);
    success += asserttrue(checkState->whoseTurn, origState->whoseTurn, testNum);
    success += asserttrue(checkState->phase, origState->phase, testNum);
    success += asserttrue(checkState->numActions, origState->numActions, testNum);
    success += asserttrue(checkState->coins, origState->coins, testNum);
    success += asserttrue(checkState->numBuys, origState->numBuys, testNum);
    for (i = 0; i < MAX_PLAYERS; i++){
        success += asserttrue(checkState->handCount[i], origState->handCount[i], testNum);
        success += asserttrue(checkState->deckCount[i], origState->deckCount[i], testNum);
        success += asserttrue(checkState->discardCount[i], origState->discardCount[i], testNum);
        for (j = 0; j < MAX_HAND; j++){
            success += asserttrue(checkState->hand[i][j], origState->hand[i][j], testNum);
        }
        for (k = 0; k < MAX_DECK; k++){
            success += asserttrue(checkState->deck[i][k], origState->deck[i][k], testNum);
            success += asserttrue(checkState->discard[i][k], origState->discard[i][k], testNum);
            success += asserttrue(checkState->playedCards[k], origState->playedCards[k], testNum);
        }
    }
    success += asserttrue(checkState->playedCardCount, origState->playedCardCount, testNum);

    if (success == totalSuccess){
        return 1;
    } else {
        return 0;
    }
}
