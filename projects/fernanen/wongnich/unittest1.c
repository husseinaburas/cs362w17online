/* -----------------------------------------------------------------------
 * Unit test of function isGameOver() from dominion.c
 * Will output into unittestresults.out along with other unit tests
 * We want to check if function works for:
 *    2 - 4 (min - max) num of players
 *    8 - 12 provinces depending on the num of players
 *    and the rest of the supply cards
 * to see if the function properly returns the state of the game
 * 2/1/17
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
    int i, p, r;
    int seed = 1000;
    int MIN_PLAYERS = 2;
    int returnValue;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf ("TESTING isGameOver():\n");
    for (p = MIN_PLAYERS; p < MAX_PLAYERS; p++){
        for (i = 1; i >=0; i--){

#if (NOISY_TEST == 1)
                printf("Testing %d players %d with %d province card(s) in game.\n", p, i);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(p, k, seed, &G); // initialize a new game
                G.supplyCount[province] = i;        //set the # of province cards to i in gamestate
                returnValue = isGameOver(&G);
#if (NOISY_TEST == 1)
                printf("returnValue = %d, expected = %d\n", returnValue, 1);
#endif

                if(i==0){ // check if game is over (true)
                  if(returnValue==1)  printf("isGameOver(): PASS when testing %d province cards\n", i);
                  else  printf("isGameOver(): FAIL when testing %d province cards\n", i);
                }
                else{  //check if game is not over (false)
                  if(returnValue==0)  printf("isGameOver(): PASS when testing %d province cards\n", i);
                  else  printf("isGameOver(): FAIL when testing %d province cards\n", i);
                }
            }
        }

        for (p = MIN_PLAYERS; p < MAX_PLAYERS; p++){
            for (i = 0; i<4; i++){

        #if (NOISY_TEST == 1)
                    printf("Testing %d players %d with %d supply card(s)=0 in game.\n", p, i);
        #endif
                    memset(&G, 23, sizeof(struct gameState));   // clear the game state
                    r = initializeGame(p, k, seed, &G); // initialize a new game
                    G.supplyCount[province] = 1;      //set to some nonzero number
                    G.supplyCount[i] = 0;        //Set one supply card = 0   (3 means exit game)
                    returnValue = isGameOver(&G);
        #if (NOISY_TEST == 1)
                    printf("returnValue = %d, expected = %d\n", returnValue, 1);
        #endif

                    if(i==0){ // check if game is over (false)
                      if(returnValue==0)  printf("isGameOver(): PASS when testing %d supply cards = 0\n", i);
                      else  printf("isGameOver(): FAIL when testing %d supply cards = 0\n", i);
                    }
                    else if(i==1){  //check if game is over (false)
                      if(returnValue==0)  printf("isGameOver(): PASS when testing %d supply cards = 0\n", i);
                      else  printf("isGameOver(): FAIL when testing %d supply cards = 0\n", i);
                    }
                    else if(i==2){  //check if game over (false)
                      if(returnValue==0)  printf("isGameOver(): PASS when testing %d supply cards = 0\n", i);
                      else  printf("isGameOver(): FAIL when testing %d supply cards = 0\n", i);
                    }
                    else if(i==3){  //check if game is over (true) because we have 3 supply cards = 0
                      if(returnValue==1)  printf("isGameOver(): PASS when testing %d supply cards = 0\n", i);
                      else  printf("isGameOver(): FAIL when testing %d supply cards = 0\n", i);
                    }
                }
            }

    return 0;
}
