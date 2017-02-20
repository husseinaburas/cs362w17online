#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testing_assert(int expression, int should_print);

long sucesses = 0;
long failures = 0;

int main(int argc, char** argv) {
    // Get seed from command line arg and setup randomization or exit
    if(argc < 2){
        printf("Please enter a seed value for randomization.\n");
        printf("usage: %s [seed]\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    long seed = atoi(argv[1]);
    
    SelectStream(1);
    PutSeed(seed);
    
    // Game variables
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    
    // Initialize the game
    initializeGame(4, k, seed, &G);
    
    // Limiting variables
    unsigned int arbritray_num_tests = 1000000;
    unsigned int arbitrary_hand_count_max = MAX_HAND - 2;
    
    for(int z = 0 ; z < arbritray_num_tests ; z++){
        int turn = floor(Random() * MAX_PLAYERS);
        int starting_hand = floor(Random() * arbitrary_hand_count_max);
        
        G.handCount[turn] = starting_hand;
        G.whoseTurn = turn;

        int outpost_before = G.outpostPlayed;
        int handcount_before = G.handCount[turn];
        playOutpost(&G, turn);

        testing_assert(G.outpostPlayed == outpost_before + 1, 0);
        testing_assert(G.handCount[turn] == handcount_before - 1, 0);
    }
    
    printf("Run complete!\n");
    printf("SUCCESSES: %ld\n", sucesses);
    
    if(failures > 0){
        printf("Some tests failed!!!\n");
        printf("FAILURES: %ld\n", failures);
    }
    
    return (EXIT_SUCCESS);
}

int testing_assert(int expression, int should_print) {
    if (expression) {
        if(should_print){
            printf("TEST SUCCEEDED!\n");
        }
        sucesses++;
        return 1;
    } else {
        if(should_print){
            printf("TEST FAILED!\n");
        }
        failures++;
        return 0;
    }
}