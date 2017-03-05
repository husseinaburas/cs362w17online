//
//  randomtestcard2.c
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

void great_hallRandomTest(int *passed, int *failed){

    //Create random seed
    int seed = rand() % 1000 +1;
    
    //Determine players between 1 - 4
    int numPlayers = rand() % 4 + 1;
    
    int currentPlayer = 0;
    int result;
    struct gameState G, test;
    
    //Kingdom cards
    int k[10] = {baron, great_hall, gardens, feast, remodel, mine, village, smithy, adventurer, council_room};
    
    printf("RANDOM TEST GREAT_HALL - BEGIN\n");
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
    
    //Increase hand by Great_Hall card
    test.hand[currentPlayer][test.handCount[currentPlayer]] = great_hall;       //places Great_Hall at last index
    test.handCount[currentPlayer]++;
    if(G.handCount[currentPlayer] + 1 != test.handCount[currentPlayer])
    {
        printf("Error - Great_Hall not successfully added to hand\n");
        printf("--------------------------------------\n");
        *failed = *failed + 1;                              //increment failed counter
        return;
    }
    
    //Play Great_Hall card
    cardEffect(great_hall, 0, 0, 0, &test, test.handCount[currentPlayer] - 1, 0);
    
    //Check if 1 card was drawn
    if(G.handCount[currentPlayer] + 1 != test.handCount[currentPlayer])
    {
        printf("Error - Player did not gain 1 card.\n");
        printf("--------------------------------------\n");
        *failed = *failed + 1;                              //increment failed counter
        return;
    }
    
    //Check if number of actions increased by 2
    if(G.numActions + 1 != test.numActions)
    {
        printf("Error - Number of Actions did not increase by 1.\n");
        printf("------------------------------------------------\n");
        *failed = *failed + 1;                              //increment failed counter
        return;
    }
    
    //If it got to this point, then all tests successfully passed!
    printf("RANDOM TEST GREAT_HALL - ALL TESTS PASSED!\n");
    printf("--------------------------------------\n");
    *passed = *passed + 1;
    return;

}

int main(){

    int passed = 0;
    int failed = 0;
    
    srand(time(NULL));
    
    //RANDOM TEST GENERATOR FOR GREAT_HALL CARD
    int i;
    for(i = 0; i < NUM_TESTS; i++)
    {
        great_hallRandomTest(&passed, &failed);
    }
    printf("**************************************\n");
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    printf("Total Random Tests Generated: %d\n", NUM_TESTS);
    printf("**************************************\n");
    
    return 0;

}

