/* unittest1.c
Function tested: isGameOver()

Requirements:
-- Game not over if just started 
-- Returns 1 if Province Supply is empty
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
#include "unittests_helpers.h"

#define FUNC_NAME "isGameOver()"


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
    int card, count;


    printf("**********************************************************\n");
    printf("BEGIN testing %s\n", FUNC_NAME);

/*-------------------------------------------------------------------------*/
    casename = "Game just initialized";
    caseCount++;

    /*********/ 
    printf("---------CASE %d: %s -- TEST %d: Game not over\n", caseCount, casename, ++testCount);
    initializeGame(numPlayer, k, seed, &G);  
    memcpy(&preG, &G, sizeof(struct gameState)); 
    r = isGameOver(&G);
    asserttrue(r != 1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
    asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);  

/*-------------------------------------------------------------------------*/
    casename = "No Supply empty";
    caseCount++;

    /*********/ 
    printf("---------CASE %d: %s -- TEST %d: Game not over\n", caseCount, casename, ++testCount);
    initializeGame(numPlayer, k, seed, &G);   
    for (card = curse; card < treasure_map+1; card++) {
        G.supplyCount[card] = 1;
    }
    memcpy(&preG, &G, sizeof(struct gameState)); 
    r = isGameOver(&G);
    asserttrue(r != 1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
    asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);  

/*-------------------------------------------------------------------------*/
    casename = "Province empty";
    caseCount++;
 
    /*********/ 
    printf("---------CASE %d: %s -- TEST %d: Game over if no other Supply empty\n", caseCount, casename, ++testCount);
    for (card=curse; card<treasure_map+1; card++) {
        G.supplyCount[card] = 1;
    }
    G.supplyCount[province] = 0;
    memcpy(&preG, &G, sizeof(struct gameState)); 
    r = isGameOver(&G);
    asserttrue(r == 1, &r_main);    

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
    asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);  

    
    count = 0;
    for (card=curse; card<treasure_map+1; card++) {
        if (card != province) {
            G.supplyCount[card] = 0; 
            count++;               
            memcpy(&preG, &G, sizeof(struct gameState)); 
    /*********/ 
            printf("---------CASE %d: %s -- TEST %d: Game over if %d other Supply empty\n", caseCount, casename, ++testCount, count);
            r = isGameOver(&G);
            asserttrue(r == 1, &r_main); 
    /*********/
            printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
            asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);    
        }
    }

/*-------------------------------------------------------------------------*/
    casename = "Province not empty";
    caseCount++;

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game not over if no other Supply empty\n", caseCount, casename, ++testCount);
    for (card=curse; card<treasure_map+1; card++) {
        G.supplyCount[card] = 1;
    }
    memcpy(&preG, &G, sizeof(struct gameState)); 
    r = isGameOver(&G);
    asserttrue(r != 1, &r_main); 

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
    asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);  
   

    count = 0;
    for (card=curse; card<treasure_map+1; card++) {
        if (card != province) {
            G.supplyCount[card] = 0; 
            count++;   
            memcpy(&preG, &G, sizeof(struct gameState));            
            if (count < 3) {
    /*********/
                printf("---------CASE %d: %s -- TEST %d: Game not over if %d other Supply empty\n", caseCount, casename, ++testCount, count);
                r = isGameOver(&G);
                asserttrue(r != 1, &r_main);                   
            } else {
    /*********/
                printf("---------CASE %d: %s -- TEST %d: Game over if %d other Supply empty\n", caseCount, casename, ++testCount, count);
                r = isGameOver(&G);
                asserttrue(r == 1, &r_main);   
            }
    /*********/
            printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
            asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);
        }
    }

/*-------------------------------------------------------------------------*/
    casename = "All Supply empty";
    caseCount++;
 
    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game over\n", caseCount, casename, ++testCount);
    for (card=curse; card<treasure_map+1; card++) {
        G.supplyCount[card] = 0;
    }
    memcpy(&preG, &G, sizeof(struct gameState)); 
    r = isGameOver(&G);
    asserttrue(r == 1, &r_main);  

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged\n", caseCount, casename, ++testCount);
    asserttrue(memcmp(&G, &preG, sizeof(struct gameState))==0, &r_main);  


/*-------------------------------------------------------------------------*/
    /******** Result */
    printf("---------\n");
    printf("Function %s passed %d/%d tests.\n", FUNC_NAME, r_main, testCount);
    printf("END testing %s\n", FUNC_NAME);
    printf("**********************************************************\n");

    return 0;
}

