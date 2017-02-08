/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 2/7/17
* Assignment 3
* unittest4.c 
* Testing: int scoreFor (int player, struct gameState *state)
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
    int score;

    /* initialize a game */
    initializeGame(numPlayers, kingdomCards, seed, &actualState);

    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));

    printf("Testing scoreFor()\n");

    /* TEST 1: The game has just been initialized, get score for player 0 */
    score = scoreFor(0, &actualState);
    success = 0;
    /* check that player 0's score is 3 */
    success += asserttrue(score, 3, 1.1);
    /* check that the game state wasn't changed */
    success += checkNoStateChange(&actualState, &copyState, 1.2);
    /* if all subtests passed, print success message */
    if (success == 2){
        printf("TEST 1 COMPLETED SUCCESSFULLY\n");
    }
    
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));

    /* TEST 2: The game has just been initialized, get score for player 1 */
    score = scoreFor(1, &actualState);
    success = 0;
    /* check that player 1's score is 3 */
    success += asserttrue(score, 3, 2.1);
    /* check that the game state wasn't changed */
    success += checkNoStateChange(&actualState, &copyState, 2.2);
    /* if all subtests passed, print success message */
    if (success == 2){
        printf("TEST 2 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 3: After initialization, player 0 gains one Province each to 
               deck, hand, and discard. Get score for player 0 */
    /* player 0 gains three provinces */
    gainCard(province, &actualState, 0, 0);
    gainCard(province, &actualState, 1, 0);
    gainCard(province, &actualState, 2, 0);
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* get score for player 0 */
    score = scoreFor(0, &actualState);
    success = 0;
    /* check that player 0's score is 21 */
    success += asserttrue(score, 21, 3.1);
    /* check that the game state wasn't changed */
    success += checkNoStateChange(&actualState, &copyState, 3.2);
    /* if all subtests passed, print success message */
    if (success == 2){
        printf("TEST 3 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 4: Player 0 has two estates and a province in their deck,
               a duchy in thier hand, and a great hall and a gardens
               in their discard. Get score for player 0. */
    /* player 0 has two estates and a province in thier deck */
    actualState.deck[0][0] = estate;
    actualState.deck[0][1] = estate;
    actualState.deck[0][2] = province;
    actualState.deckCount[0] = 3;
    /* player 0 has one duchy in their hand */
    actualState.hand[0][0] = duchy;
    actualState.handCount[0] = 1;
    /* player 0 has one great hall and one gardens in their discard */
    actualState.discard[0][0] = great_hall;
    actualState.discard[0][1] = gardens;
    actualState.discardCount[0] = 2;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* get score for player 0 */
    score = scoreFor(0, &actualState);
    success = 0;
    /* check that player 0's score is 12 */
    success += asserttrue(score, 12, 4.1);
    /* check that the game state wasn't changed */
    success += checkNoStateChange(&actualState, &copyState, 4.2);
    /* if all subtests passed, print success message */
    if (success == 2){
        printf("TEST 4 COMPLETED SUCCESSFULLY\n");
    }

    /* TEST 5: Player 0 has 1 curse, 5 estates, 2 feasts and 1 copper in their deck,
               7 duchys, 1 province, and 9 silver in thier hand, and 2 great halls, 
               4 adventurers, 2 council rooms and 3 gardens in their discard. Get 
               score for player 0. */
    /* player 0 has 1 curse, 5 estates, 2 feasts and 1 copper in thier deck */
    actualState.deck[0][0] = curse;
    actualState.deck[0][1] = estate;
    actualState.deck[0][2] = estate;
    actualState.deck[0][3] = estate;
    actualState.deck[0][4] = estate;
    actualState.deck[0][5] = estate;
    actualState.deck[0][6] = feast;
    actualState.deck[0][7] = feast;
    actualState.deck[0][8] = copper;
    actualState.deckCount[0] = 9;
    /* player 0 has 7 duchys, 1 province, and 9 silver in their hand */
    actualState.hand[0][0] = duchy;
    actualState.hand[0][1] = duchy;
    actualState.hand[0][2] = duchy;
    actualState.hand[0][3] = duchy;
    actualState.hand[0][4] = duchy;
    actualState.hand[0][5] = duchy;
    actualState.hand[0][6] = duchy;
    actualState.hand[0][7] = province;
    actualState.hand[0][8] = silver;
    actualState.hand[0][9] = silver;
    actualState.hand[0][10] = silver;
    actualState.hand[0][11] = silver;
    actualState.hand[0][12] = silver;
    actualState.hand[0][13] = silver;
    actualState.hand[0][14] = silver;
    actualState.hand[0][15] = silver;
    actualState.hand[0][16] = silver;
    actualState.handCount[0] = 17;
    /* player 0 has 2 great halls, 4 adventurers, 2 council rooms and 3 gardens in their discard */
    actualState.discard[0][0] = great_hall;
    actualState.discard[0][1] = great_hall;
    actualState.discard[0][2] = adventurer;
    actualState.discard[0][3] = adventurer;
    actualState.discard[0][4] = adventurer;
    actualState.discard[0][5] = adventurer;
    actualState.discard[0][6] = council_room;
    actualState.discard[0][7] = council_room;
    actualState.discard[0][8] = gardens;
    actualState.discard[0][9] = gardens;
    actualState.discard[0][10] = gardens;
    actualState.discardCount[0] = 11;
    /* copy game state */
    memcpy(&copyState, &actualState, sizeof(struct gameState));
    /* get score for player 0 */
    score = scoreFor(0, &actualState);
    success = 0;
    /* check that player 0's score is 42 */
    success += asserttrue(score, 42, 5.1);
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