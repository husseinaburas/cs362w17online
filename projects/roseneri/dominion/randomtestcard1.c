/*
File: cardtest2.c
Description: Unit testing of Village card

Erin Rosenbaum
cs_362 Winter 2017
February 7th, 2017
Assignment_3

The Village card adds a card to the players hand and adds two actions
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TESTCARD "Village"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

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
    // create a random number generator for each input variable

for (n=0; n < 2000 ; n++){

    // generate random number of players
    num_players = rand() % 4 + 1;

    // initialize game
    //printf("****************** Begin Test, testing %s ******\n", TESTCARD);
    initializeGame(num_players, cards, seed, &G);

    // had must contain adventurer card
    //G.hand[0][0] = village;

    // save initial state and call cardEffect
    memcpy(&testG, &G, sizeof(struct gameState));


    // int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
    cardEffect(village, 0, 0, 0, &testG, 0, 0);

    // test number of cards in hand
    //printf("hand count before = %d, hand count after = %d\n", G.handCount[0], testG.handCount[0]);
    assert_true(testG.handCount[0] == G.handCount[0]);

    // test number of cards in deck. In this test case, 
    //printf("deck count before = %d, deck count after = %d\n", G.deckCount[0], testG.deckCount[0]);
    assert_true(testG.deckCount[0] == G.deckCount[0] - 1);

    

    // test all players for state change 
    for (i=1; i < num_players ; i++){
        //printf("player %d deck count = %d, expected = %d\n", (i+1), testG.deckCount[i], G.deckCount[i]);
        assert_true(testG.deckCount[i] == G.deckCount[i]);

        //printf("player %d hand count = %d, expected = %d\n", (i+1), testG.handCount[i], G.handCount[i]);
        assert_true(testG.handCount[i] == G.handCount[i]);

        //printf("player %d discard count = %d, expected = %d\n", (i+1), testG.discardCount[i], G.discardCount[i]);
        assert_true(testG.discardCount[i] == G.discardCount[i]);


    }
}

    printf("RANDOMTESTCARD1 successfully completed\n");
    printf("number of tests passed = %d \n", passed_tests);
    printf("number of tests failed = %d \n", failed_tests);


    //printf("************* CARDTEST4 SUCCESSFULLY COMPLETED  ***************\n\n");
    return 0;

}