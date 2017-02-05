/* unittest3.c
Function tested: numHandCards()

Requirements:
-- Fails if current player's hand count < 0
-- Returns number of cards in current player's hand. 
-- Number returned equals both current player's handCount
    and number of positive cards in current player's hand
-- Does not change game state after execution
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
// #include "test_helpers.h"

#define FUNC_NAME "numHandCards()"
#define NOISY_TEST 0


/*********************************************************************/
/* Main */
int main() {
    int seed = 1000;
    struct gameState G, testG;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
      remodel, smithy, village, baron, great_hall};
    int r;
    int r_main = 0;
    int testCount = 0;

    int player, count, i;

    printf("**********************************************************\n");
    printf("BEGIN testing %s\n", FUNC_NAME);
 
    /*********/
    printf("---------TEST %d: Returns -1 if handCount < 0\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.handCount[player] = -2;
    r = numHandCards(&G);
    asserttrue(r == -1, &r_main);
    if (NOISY_TEST) printf("Expected: %d\tReceived: %d\n", -1, r);

    /*********/
    printf("---------TEST %d: Case handCount == 0\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.handCount[player] = 0;
    r = numHandCards(&G);
    asserttrue(r == 0, &r_main);
    if (NOISY_TEST) printf("Expected: %d\tReceived: %d\n", 0, r);

    /*********/
    printf("---------TEST %d: Case handCount > 0\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    r = numHandCards(&G);
    asserttrue(r == G.handCount[player], &r_main);
    if (NOISY_TEST) printf("Expected: %d\tReceived: %d\n", G.handCount[player], r);

    /*********/
    printf("---------TEST %d: Check result == current player's handCount \n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    count = G.handCount[player];
    r = numHandCards(&G);  // should have r == count
    asserttrue(r == count, &r_main);
    if (NOISY_TEST) printf("Expected: %d\tReceived: %d\n", count, r);

    /*********/
    printf("---------TEST %d: Check result == number of positive cards in current player's hand\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    count = 0;  // count the number of positive cards in G.hand[player]
    for (i = 0; i < MAX_HAND; i++) {
        if (G.hand[player][i] > 0) {
            count++;
        }
    }
    r = numHandCards(&G);  // should have r == count
    asserttrue(r == count, &r_main);
    if (NOISY_TEST) printf("Expected: %d\tReceived: %d\n", count, r);

    /*********/
    printf("---------TEST %d: Game state unchanged after function executes\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);       
    memcpy(&testG, &G, sizeof(struct gameState));
    r = numHandCards(&G);
    asserttrue(memcmp(&G, &testG, sizeof(struct gameState))==0, &r_main);   

    /******** Result */
    printf("---------\n");
    printf("Function %s passed %d/%d tests.\n", FUNC_NAME, r_main, testCount);
    printf("END testing %s\n", FUNC_NAME);
    printf("**********************************************************\n");

    return 0;
}

