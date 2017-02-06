/* unittest2.c
Function tested: shuffle()

Requirements:
-- Fails if deck count < 1
-- Does not change game state after function execution, except deck of current player
-- The same cards remain in deck of current player after execution
-- Cards in deck of current player change positions after every execution
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
// #include "test_helpers.h"

#define FUNC_NAME "shuffle()"
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

    int player = 1;
    int card, i;
    int count = 0, count2 = 0;

    printf("**********************************************************\n");
    printf("BEGIN testing %s\n", FUNC_NAME);
 
    /*********/
    printf("---------TEST %d: Shuffle fails if deck count < 0\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    G.deckCount[player] = -2;
    r = shuffle(player, &G);
    asserttrue(r < 0, &r_main);

    /*********/
    printf("---------TEST %d: Shuffle fails if deck count == 0\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    G.deckCount[player] = 0;
    r = shuffle(player, &G);
    asserttrue(r < 0, &r_main);

    /*********/
    printf("---------TEST %d: Same cards remain in current player's deck\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    shuffle(player, &G);
    r = 1;
    for (card=curse; card<treasure_map+1; card++) {
        for (i=0; i < G.deckCount[player]; i++) {
            if (G.deck[player][i] == card) count++;
            if (testG.deck[player][i] == card) count2++;
        }
        if (NOISY_TEST) printf("Card=%d\tCount before shuffling=%d\tCount after shuffling=%d\n", card, count, count2);
        if (count != count2) {
            r = -1;
            break;
        }
    }
    asserttrue(r == 1, &r_main);

    /*********/
    printf("---------TEST %d: Cards in current player's deck change positions -- run 1\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    shuffle(player, &G);
    r = -1;
    for (i=0; i < G.deckCount[player]; i++) {
        if (G.deck[player][i] != testG.deck[player][i]) {
            r = 1;
            break;
        }
    }
    asserttrue(r == 1, &r_main);

    /*********/
    printf("---------TEST %d: Cards in current player's deck change positions -- run 2\n", ++testCount);
    memcpy(&testG, &G, sizeof(struct gameState));
    shuffle(player, &G);
    r = -1;
    for (i=0; i < G.deckCount[player]; i++) {
        if (G.deck[player][i] != testG.deck[player][i]) {
            r = 1;
            break;
        }
    }
    asserttrue(r == 1, &r_main);

    /*********/
    printf("---------TEST %d: Game state unchanged except current player's deck\n", ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    shuffle(player, &G);
    for (i=0; i<G.deckCount[player]; i++) {
        testG.deck[player][i] = G.deck[player][i];  // make testG.deck and G.deck equal      
    }
    asserttrue(memcmp(&G, &testG, sizeof(struct gameState))==0, &r_main);  

    /******** Result */
    printf("---------\n");
    printf("Function %s passed %d/%d tests.\n", FUNC_NAME, r_main, testCount);
    printf("END testing %s\n", FUNC_NAME);
    printf("**********************************************************\n");

    return 0;
}

