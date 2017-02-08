/* unittest3.c
Function tested: numHandCards()

Requirements:
-- Fails if Hand count < 0
-- Returns correct number of cards in current player's Hand 
-- Number returned equals both current player's Hand count
    and number of positive cards in current player's Hand
-- Does not change game state after execution

The following cases are tested:
-- Hand count < 0
-- Hand count == 0
-- Hand count > 0
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "unittests_helpers.h"

#define FUNC_NAME "numHandCards()"


/*********************************************************************/
/* Main */
int main() {
    int seed = 1000;
    struct gameState G, preG;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
      remodel, smithy, village, baron, great_hall};
    int r;
    int r_main = 0;
    int testCount = 0, caseCount = 0;
    char* casename;

    int player, count, i;

    printf("**********************************************************\n");
    printf("BEGIN testing %s\n", FUNC_NAME);

/*-------------------------------------------------------------------------*/
    casename = "Hand count < 0";
    caseCount++;
 
    printf("---------CASE %d: %s -- TEST %d: Returns -1 (error)\n", caseCount, casename, ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.handCount[player] = -10;
    r = numHandCards(&G);
    if (NOISY_TEST) printf("Expected: %d\nReceived: %d\n", -1, r);
    asserttrue(r == -1, &r_main);

/*-------------------------------------------------------------------------*/
    casename = "Hand count == 0";
    caseCount++;

    printf("---------CASE %d: %s -- TEST %d: Returns correct Hand count\n", caseCount, casename, ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.handCount[player] = 0;
    r = numHandCards(&G);
    if (NOISY_TEST) printf("Expected: %d\nReceived: %d\n", 0, r);
    asserttrue(r == 0, &r_main);

/*-------------------------------------------------------------------------*/
    casename = "Hand count > 0";
    caseCount++;

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Returns correct Hand count\n", caseCount, casename, ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    memcpy(&preG, &G, sizeof(struct gameState));
    r = numHandCards(&G);
    if (NOISY_TEST) printf("Expected: %d\nReceived: %d\n", G.handCount[player], r);
    asserttrue(r == G.handCount[player], &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Returned value equals number of positive cards in Hand\n", caseCount, casename, ++testCount);
    count = 0;  // count the number of positive cards in G.hand[player]
    for (i = 0; i < MAX_HAND; i++) {
        if (G.hand[player][i] > 0) {
            count++;
        }
    }
    if (NOISY_TEST) printf("Expected: %d\nReceived: %d\n", count, r);
    asserttrue(r == count, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
    asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);   

/*-------------------------------------------------------------------------*/
    /******** Result */
    printf("---------\n");
    printf("Function %s passed %d/%d tests.\n", FUNC_NAME, r_main, testCount);
    printf("END testing %s\n", FUNC_NAME);
    printf("**********************************************************\n\n");

    return 0;
}

