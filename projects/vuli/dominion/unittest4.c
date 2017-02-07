/* unittest4.c
Function tested: whoseTurn()

Requirements:
-- Returns 0 immediately after initializing game
-- Returns correct current player in range 0..numPlayer
-- Does not change game state after execution

The following cases are tested:
-- Current player between 0..MAX_PLAYERS

*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "unittests_helpers.h"

#define FUNC_NAME "whoseTurn()"


/*********************************************************************/
/* Main */
int main() {
    int seed = 1000;
    struct gameState G, preG;
    int numPlayer = MAX_PLAYERS;
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
      remodel, smithy, village, baron, great_hall};
    int r;
    int r_main = 0;
    int testCount = 0, caseCount = 0;
    char* casename;

    int i;

    printf("**********************************************************\n");
    printf("BEGIN testing %s\n", FUNC_NAME);

/*-------------------------------------------------------------------------*/
    casename = "Game just initialized";
    caseCount++;

    /*********/ 
    printf("---------CASE %d: %s -- TEST %d: Returned value == 0\n", caseCount, casename, ++testCount);
    initializeGame(numPlayer, k, seed, &G);  
    memcpy(&preG, &G, sizeof(struct gameState)); 
    r = whoseTurn(&G);
    if (NOISY_TEST) printf("Expected: %d\nReceived: %d\n", 0, r);
    asserttrue(r == 0, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
    asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);  

/*-------------------------------------------------------------------------*/
    casename = "Current player between 0..max";
    caseCount++;

    for (i=0; i < numPlayer; i++) {
    /*********/ 
        printf("---------CASE %d: %s -- TEST %d: Current player == %d\n", caseCount, casename, ++testCount, i);
        G.whoseTurn = i;
        memcpy(&preG, &G, sizeof(struct gameState)); 
        r = whoseTurn(&G);
        if (NOISY_TEST) printf("Expected: %d\nReceived: %d\n", 0, r);
        asserttrue(r == i, &r_main);
    /*********/
        printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
        asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);  

    }

/*-------------------------------------------------------------------------*/
    /******** Result */
    printf("---------\n");
    printf("Function %s passed %d/%d tests.\n", FUNC_NAME, r_main, testCount);
    printf("END testing %s\n", FUNC_NAME);
    printf("**********************************************************\n");

    return 0;
}

