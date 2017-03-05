//
//  randomtestadventurer.c
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

void adventurerRandomTest(int *passed, int *failed){

    //Create random seed
    int seed = rand() % 1000 +1;
    
    //Determine players between 1 - 4
    int numPlayers = rand() % 4 + 1;
    
    //Hold treasure count for each player
    int j;
    int treasureCount[numPlayers];
    for(j = 0; j < numPlayers; j++)
    {
        treasureCount[j] = 0;
    }
    
    int currentPlayer = 0;
    int result;
    struct gameState G, test;
    int cardDrawn1;
    int temphand[MAX_HAND];
    
    //Kingdom cards
    int k[10] = {baron, great_hall, gardens, feast, remodel, mine, village, smithy, adventurer, council_room};
    
    printf("RANDOM TEST ADVENTURER - BEGIN\n");
    printf("Seed: %d, Number of Players: %d\n", seed, numPlayers);
    printf("Current Player: %d\n", currentPlayer);
    
    //Initialize gamestate (original struct, G)
    result = initializeGame(numPlayers, k, seed, &G);
    if(result == -1)
    {
        //There was an error initializing
        printf("Error - Game could not initialize.\n");
        printf("--------------------------------------------------------------\n");
        *failed = *failed + 1;                              //increment failed counter
        return;
    }
    memcpy(&test, &G, sizeof(struct gameState));            //clone G into test
    
    //Increase hand by Adventurer card
    test.hand[currentPlayer][test.handCount[currentPlayer]] = adventurer;       //places Smithy at last index
    test.handCount[currentPlayer]++;
    if(G.handCount[currentPlayer] + 1 != test.handCount[currentPlayer])
    {
        printf("Error - Adventurer not successfully added to hand\n");
        printf("--------------------------------------------------------------\n");
        *failed = *failed + 1;                              //increment failed counter
        return;
    }
    
    //Play Adventurer card
    playAdventurer(0, &test, currentPlayer, 0, temphand ,0);
    
    //Verify that 2 treasure cards were revealed
    int i;
    for(i = 0; i < test.handCount[currentPlayer]; i++)
    {
        cardDrawn1 = test.hand[currentPlayer][i];
        if(cardDrawn1 == copper || cardDrawn1 == silver || cardDrawn1 == gold)
        {
            treasureCount[currentPlayer] =+ 1;
        }
    }
    
    if(treasureCount[currentPlayer] != 1)
    {
        printf("Error - Adventurer did not add 2 treasure cards  successfully\n");
        printf("--------------------------------------------------------------\n");
        *failed = *failed + 1;                              //increment failed counter
        return;

    }
    
    //If it got to this point, then all tests successfully passed!
    printf("RANDOM TEST ADVENTURER - ALL TESTS PASSED!\n");
    printf("--------------------------------------------------------------\n");
    *passed = *passed + 1;
    return;

}

int main(){

    int passed = 0;
    int failed = 0;
    
    srand(time(NULL));
    
    //RANDOM TEST GENERATOR FOR ADVENTURER CARD
    int i;
    for(i = 0; i < NUM_TESTS; i++)
    {
        adventurerRandomTest(&passed, &failed);
    }
    printf("***********************************************\n");
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    printf("Total Random Tests Generated for ADVENTURER: %d\n", NUM_TESTS);
    printf("***********************************************\n");
    
    return 0;

}

