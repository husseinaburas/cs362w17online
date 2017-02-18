/*
File: cardtest1.c
Description: Unit testing of Smithy card

Erin Rosenbaum
cs_362 Winter 2017
February 7th, 2017
Assignment_3

The Smithy card costs 4 monetary units and gives the player 3 additional cards

Requirements: 
1. Current player should receive exact 3 cards.
2. 3 cards should come from his own pile.
3. No state change should occur for other players.
4. No state change shdould occur to the victory card piles and kingdom card piles.
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TESTCARD "smithy"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int passed_tests = 0;
int failed_tests = 0;

void assert_true(int val) {
    if (val == 0) {
        //printf("TEST FAILED!\n\n");
        failed_tests++;
    }
    else
        //printf("TEST PASSED!\n\n");
        passed_tests++;
}

int main(int argc, char* args[]){

    // make sure there is a single input
    if(argc != 2){
        printf("Usage: randomtestcard1 seed \n");
    return -1;
    }

    int i, n; 
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = atoi(args[1]);
    //int time_remaining = atoi(args[2]);
    struct gameState G, testG;
    srand(seed);
    int num_players;
    int thisPlayer = 0;

    for (n=0; n < 2000 ; n++){

        // generate random number of players
        num_players = rand() % 4 + 1;

        // initialize game
        //printf("************************ Begin Test, testing %s *****************\n", TESTCARD);
        initializeGame(num_players, cards, seed, &G);

        G.whoseTurn = 0;
        G.hand[0][0] = smithy;

        // save initial state
        memcpy(&testG, &G, sizeof(struct gameState));

        //randomize state variables
        G.numActions = rand() % 5;
        G.coins = rand() % 5;
        G.numBuys = rand() % 5;
        cardEffect(smithy, 0, 0, 0, &testG, 0, 0);

        // test for count of actions
        //printf("action count before = %d, action count after = %d\n", G.numActions, testG.numActions);
        //assert_true(G.numActions == testG.numActions - 1);

        // test for number of coins
        //printf("coins before = %d, coins after = %d\n", G.coins, testG.coins);
        //assert_true(G.coins -4 == testG.coins);

        //test for number of buys
        //printf("numBuys before = %d, numBuys after = %d\n", G.numBuys, testG.numBuys);
        assert_true(G.numBuys == testG.numBuys);



        // test number of cards in hand
        //printf("**********************   test 1 handCount **************\n");
        //printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
        assert_true(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2);

        // test number of cards in deck
        //printf("**********************   test 2 deckCount **************\n");
        //printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 2);
        assert_true(testG.deckCount[thisPlayer] == testG.deckCount[thisPlayer] - 3);


        for (i=1; i < num_players ; i++){
            //printf("player %d deck count = %d, expected = %d\n", (i+1), testG.deckCount[i], G.deckCount[i]);
            assert_true(testG.deckCount[i] == G.deckCount[i]);

            //printf("player %d hand count = %d, expected = %d\n", (i+1), testG.handCount[i], G.handCount[i]);
            assert_true(testG.handCount[i] == G.handCount[i]);

            //printf("player %d discard count = %d, expected = %d\n", (i+1), testG.discardCount[i], G.discardCount[i]);
            assert_true(testG.discardCount[i] == G.discardCount[i]);


        }

    }
    printf("RANDOMTESTCARD2 successfully completed\n"); 
    printf("number of tests passed = %d \n", passed_tests);
    printf("number of tests failed = %d \n", failed_tests);


//************************* end of test **************************
    //printf("********** CARDTEST1 SUCCESSFULLY COMPLETED ****************\n\n");
    return 0;

}