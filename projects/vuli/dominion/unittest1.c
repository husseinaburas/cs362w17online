/* unittest1.c
Function tested: isGameOver()

Requirements:
-- Returns 1 if Supply pile of Province cards is empty
-- Returns 1 if any three Supply piles are empty
-- Returns 0 in all other cases
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

#define FUNC_NAME "isGameOver()"
#define NOISY_TEST 0

// /* Returns number of empty Supply piles */
// int countEmptySupply(struct gameState* state) {
//     int card, count = 0;

//     for (card=curse; card<=gold; card++) {
//         if (state->supplyCount[card] == 0) count++; 
//     }
//     return count;
// }


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

    printf("**********************************************************\n");
    printf("BEGIN testing %s\n", FUNC_NAME);
    
    /*********/
    printf("---------TEST %d: Game over if Province pile empty\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    G.supplyCount[province] = 0;
    r = isGameOver(&G);
    asserttrue(r == 1, &r_main);

    /*********/
    printf("---------TEST %d: Game over if 3 Supply piles empty -- case copper, silver, gold\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);   
    G.supplyCount[copper] = 0;
    G.supplyCount[silver] = 0;
    G.supplyCount[gold] = 0;
    r = isGameOver(&G);
    asserttrue(r == 1, &r_main);

    /*********/
    printf("---------TEST %d: Game over if 3 Supply piles empty -- case copper, duchy, curse\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);   
    G.supplyCount[copper] = 0;
    G.supplyCount[duchy] = 0;
    G.supplyCount[curse] = 0;
    r = isGameOver(&G);
    asserttrue(r == 1, &r_main);

    /*********/
    printf("---------TEST %d: Game over if 4 Supply piles empty\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);   
    G.supplyCount[copper] = 0;
    G.supplyCount[estate] = 0;
    G.supplyCount[duchy] = 0;
    G.supplyCount[curse] = 0;
    r = isGameOver(&G);
    asserttrue(r == 1, &r_main);

    /*********/
    printf("---------TEST %d: Game not over if no pile empty\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);   
    r = isGameOver(&G);
    asserttrue(r != 1, &r_main);

    /*********/
    printf("---------TEST %d: Game not over if 2 Supply piles empty\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);   
    G.supplyCount[copper] = 0;
    G.supplyCount[estate] = 0;
    r = isGameOver(&G);
    asserttrue(r != 1, &r_main);

    /*********/
    printf("---------TEST %d: Game not over if 2 Supply piles and 1 non-Supply pile empty\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);   
    G.supplyCount[copper] = 0;
    G.supplyCount[estate] = 0;
    G.supplyCount[adventurer] = 0;  // inject one non-Supply card
    r = isGameOver(&G);
    asserttrue(r != 1, &r_main);

    /*********/
    printf("---------TEST %d: Game not over if no Supply piles and 3 non-Supply piles empty\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);   
    G.supplyCount[adventurer] = 0;  // inject non-Supply card
    G.supplyCount[council_room] = 0;
    G.supplyCount[feast] = 0;
    r = isGameOver(&G);
    asserttrue(r != 1, &r_main);

    /*********/
    printf("---------TEST %d: Game state unchanged after function executes\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);       
    memcpy(&testG, &G, sizeof(struct gameState));
    r = isGameOver(&G);
    asserttrue(memcmp(&G, &testG, sizeof(struct gameState))==0, &r_main);    

    /******** Result */
    printf("---------\n");
    printf("Function %s passed %d/%d tests.\n", FUNC_NAME, r_main, testCount);
    printf("END testing %s\n", FUNC_NAME);
    printf("**********************************************************\n");

    return 0;
}

