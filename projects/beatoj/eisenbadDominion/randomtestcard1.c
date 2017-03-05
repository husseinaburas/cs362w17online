//
//  randomtestcard1.c
//  
//
//  Created by Jeanvally Galing Beato on 2/15/17.
//
//

#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

//Set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

//Set number of tests
#define NUM_TESTS 1000

void smithyRandomTest(int *passed, int *failed){

    //Create random seed
    int seed = rand() % 1000 +1;
    
    //Determine players between 1 - 4
    int numPlayers = rand() % 4 + 1;
    
    int currentPlayer = 0;
    int result;
    struct gameState G, test;
    
    //Kingdom cards
    int k[10] = {baron, great_hall, gardens, feast, remodel, mine, village, smithy, adventurer, council_room};
    
    printf("RANDOM TEST SMITHY - BEGIN\n");
    printf("Seed: %d, Number of Players: %d\n", seed, numPlayers);
    
    //Initialize gamestate (original struct, G)
    result = initializeGame(numPlayers, k, seed, &G);
    if(result == -1)
    {
        //There was an error initializing
        printf("Error - Game could not initialize.\n");
        printf("--------------------------------------\n");
        *failed = *failed + 1;                              //increment failed counter
        return;
    }
    memcpy(&test, &G, sizeof(struct gameState));            //clone G into test
    
    //Increase hand by Smithy card
    test.hand[currentPlayer][test.handCount[currentPlayer]] = smithy;       //places Smithy at last index
    test.handCount[currentPlayer]++;
    if(G.handCount[currentPlayer] + 1 != test.handCount[currentPlayer])
    {
        printf("Error - Smithy not successfully added to hand\n");
        printf("--------------------------------------\n");
        *failed = *failed + 1;                              //increment failed counter
        return;
    }
    
    //Play Smithy card
    //playSmithy(&test, currentPlayer, test.handCount[currentPlayer] - 1);
    
    smithy_refact(&test, test.handCount[currentPlayer] - 1);                //A5 - REFACTORED:  Removed arg 2 (current player)
    
    if(G.handCount[currentPlayer] + 3 != test.handCount[currentPlayer])
    {
        printf("Error - Player did not gain 3 cards.\n");
        printf("--------------------------------------\n");
        *failed = *failed + 1;                              //increment failed counter
        return;
    }
    
    //If it got to this point, then all tests successfully passed!
    printf("RANDOM TEST SMITHY - ALL TESTS PASSED!\n");
    printf("--------------------------------------\n");
    *passed = *passed + 1;
    return;

}

int main(){

    int passed = 0;
    int failed = 0;
    
    srand(time(NULL));
    
    //RANDOM TEST GENERATOR FOR SMITHY CARD
    int i;
    for(i = 0; i < NUM_TESTS; i++)
    {
        smithyRandomTest(&passed, &failed);
    }
    printf("**************************************\n");
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    printf("Total Random Tests Generated: %d\n", NUM_TESTS);
    printf("**************************************\n");
    
    return 0;

}

