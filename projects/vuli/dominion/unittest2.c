/* unittest2.c
Function tested: shuffle()

Requirements:
-- Fails if deck count < 1
-- Successful execution if deck count > 1
-- The same cards remain in deck of current player
-- Cards in deck of current player change positions after every execution. Note this is a sticky 
    condition, e.g. it won't hold if deck has all the same cards before execution.
-- Does not change game state except deck of current player (note this includes deck count unchanged)

The following cases are tested:
-- Deck count < 0
-- Deck count == 0
-- Deck count > 0
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "unittests_helpers.h"

#define FUNC_NAME "shuffle()"


/*********************************************************************/
/* Main */
int main() {
    int seed = 1000;
    struct gameState G, preG, tempG;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
      remodel, smithy, village, baron, great_hall};
    int r;
    int r_main = 0;
    int testCount = 0, caseCount = 0;
    char* casename;

    int player, card, i, j;
    int count1, count2;
    int numShuffle = 5, minChange = 2, numChange;

    printf("**********************************************************\n");
    printf("BEGIN testing %s\n", FUNC_NAME);

/*-------------------------------------------------------------------------*/
    casename = "Deck count < 0";
    caseCount++;
 
    printf("---------CASE %d: %s -- TEST %d: Shuffle fails\n", caseCount, casename, ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.deckCount[player] = -2;
    r = shuffle(player, &G);
    asserttrue(r < 0, &r_main);

/*-------------------------------------------------------------------------*/
    casename = "Deck count == 0";
    caseCount++;
 
    printf("---------CASE %d: %s -- TEST %d: Shuffle fails\n", caseCount, casename, ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.deckCount[player] = 0;
    r = shuffle(player, &G);
    asserttrue(r < 0, &r_main);

/*-------------------------------------------------------------------------*/
    casename = "Deck count > 0";
    caseCount++;

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Successful execution\n", caseCount, casename, ++testCount);
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    memcpy(&preG, &G, sizeof(struct gameState));
    r = shuffle(player, &G);
    asserttrue(r == 0, &r_main);
    
    /*********/
    printf("---------CASE %d: %s -- TEST %d: Same cards remain in Deck\n", caseCount, casename, ++testCount);
    count1 = 0;
    count2 = 0;
    r = 1;
    for (card=curse; card<treasure_map+1; card++) {
        for (i=0; i < G.deckCount[player]; i++) {
            if (G.deck[player][i] == card) count1++;
            if (preG.deck[player][i] == card) count2++;
        }
        if (NOISY_TEST) printf("Card %s:\nCount before shuffling=%d\tCount after shuffling=%d\n", getCardName(card), count1, count2);
        if (count1 != count2) {
            r = -1;
            break;
        }
    }
    asserttrue(r == 1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards in Deck change positions at least %d times in %d runs\n", caseCount, casename, ++testCount, minChange, numShuffle);
    numChange = 0;
    for (i=0; i < numShuffle; i++) {  // Run shuffles at most numShuffle time, break when cards in player's deck changes position minChange times
        printf("RUN %d:\n", i+1);
        memcpy(&tempG, &G, sizeof(struct gameState));
        shuffle(player, &G);
        for (j=0; j < G.deckCount[player]; j++) {
            if (G.deck[player][j] != tempG.deck[player][j]) {
                numChange++;
                break;
            }
        }
        if (NOISY_TEST) {
            printf("Before execution:\n");
            printCurrentPlayer(player, &tempG);
            printf("After execution:\n");
            printCurrentPlayer(player, &G);
        }  
        if (numChange >= minChange) break; 
    }
    asserttrue(numChange >= minChange, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged except current player's deck\n", caseCount, casename, ++testCount);
    for (i=0; i<G.deckCount[player]; i++) {
        preG.deck[player][i] = G.deck[player][i];  // make preG.deck and G.deck equal      
    }
    asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);  

/*-------------------------------------------------------------------------*/
    /******** Result */
    printf("---------\n");
    printf("Function %s passed %d/%d tests.\n", FUNC_NAME, r_main, testCount);
    printf("END testing %s\n", FUNC_NAME);
    printf("**********************************************************\n");

    return 0;
}

