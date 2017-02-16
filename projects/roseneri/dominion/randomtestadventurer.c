/*
File: cardtest2.c
Description: Unit testing of Adventurer card

Erin Rosenbaum
cs_362 Winter 2017
February 7th, 2017
Assignment_3

The Adventure card costs 6 monetary units.
Playing the card allows the player to reveal cards
from their deck one-at-a-time until 2 treasure cards
have been revealed. The player keeps the treasure cards
and discards the other revealed cards. 

Preconditions: 

*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TESTCARD "adventurer"



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
        printf("Usage: randomtestadventurer seed \n");
    return -1;
    }
    int n; 
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = atoi(args[1]);
    //int time_remaining = atoi(args[2]);
    struct gameState G, testG;
    struct gameState G1, testG1;
    srand(seed);
    int num_players;


    // create a random number generator for each input variable

    for (n=0; n < 2000 ; n++){
        // generate random number of players
        num_players = rand() % 4 + 1;



        // initialize game
        //printf("******* Begin Test, testing %s ******\n", TESTCARD);
        initializeGame(num_players, cards, seed, &G);

        // had must contain adventurer card
        G.hand[0][0] = adventurer;

        // set up player's deck
        G.deck[0][4] = smithy;
        G.deck[0][3] = silver;
        G.deck[0][2] = tribute;
        G.deck[0][1] = embargo;
        G.deck[0][0] = gold;

        //randomize state variables
        G.numActions = rand() % 5;
        G.coins = rand() % 5;
        G.numBuys = rand() % 5;

        // save initial state and call cardEffect
        memcpy(&testG, &G, sizeof(struct gameState));

        // int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
        cardEffect(adventurer, 0, 0, 0, &testG, 0, 0);

        // test number of cards in hand
        //printf("hand count before = %d, hand count after = %d\n", G.handCount[0], testG.handCount[0]);
        assert_true(testG.handCount[0] == G.handCount[0] + 2);

        // test number of cards in deck. In this test case, 
        //printf("deck count before = %d, deck count after = %d\n", G.deckCount[0], testG.deckCount[0]);
        assert_true(testG.deckCount[0] == G.deckCount[0] - 5);

        // test discard count. The three non-treasure card hands should be discarded  
        //printf("expected discard count after = 3\n");
        //printf("discard count before = %d, discard counter after = %d\n", G.discardCount[0], testG.discardCount[0]);
        //assert_true(testG.discardCount[0] == G.discardCount[0] + 3);

        // test other players for state change 
        //printf("player 2 deck count = %d, expected = %d\n", testG.deckCount[1], G.deckCount[1]);
        assert_true(testG.deckCount[1] == G.deckCount[1]);

        //printf("player 2 hand count = %d, expected = %d\n", testG.handCount[1], G.handCount[1]);
        assert_true(testG.handCount[1] == G.handCount[1]);

        //printf("player 2 discard count = %d, expected = %d\n", testG.discardCount[1], G.discardCount[1]);
        assert_true(testG.discardCount[1] == G.discardCount[1]);

        //printf("\nAdventurer card test 2: only one treasure card in deck\n");
        initializeGame(2, cards, seed, &G1);

        // had must contain adventurer card
        G.hand[0][0] = adventurer;

        // set up player's deck
        G1.deck[0][4] = smithy;
        G1.deck[0][3] = silver;
        G1.deck[0][2] = tribute;
        G1.deck[0][1] = embargo;
        G1.deck[0][0] = smithy;

        // save initial state and call cardEffect
        memcpy(&testG1, &G1, sizeof(struct gameState));

        // int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
        cardEffect(adventurer, 0, 0, 0, &testG1, 0, 0);

        // test number of cards in hand
        //printf("hand count before = %d, hand count after = %d\n", G1.handCount[0], testG1.handCount[0]);
        assert_true(testG1.handCount[0] == G1.handCount[0] + 1);

        //printf("deck count before = %d, deck count after = %d\n", G1.deckCount[0], testG1.deckCount[0]);
        assert_true(testG1.deckCount[0] == G1.deckCount[0] - 5);

        // test discard count. The three non-treasure card hands should be discarded  
        //printf("expected discard count after = 4\n");
        //printf("discard count before = %d, discard counter after = %d\n", G1.discardCount[0], testG1.discardCount[0]);
        //assert_true(testG1.discardCount[0] == G1.discardCount[0] + 4);

        // test other players for state change 
        //printf("player 2 deck count = %d, expected = %d\n", testG1.deckCount[1], G1.deckCount[1]);
        assert_true(testG1.deckCount[1] == G1.deckCount[1]);

        //printf("player 2 hand count = %d, expected = %d\n", testG1.handCount[1], G1.handCount[1]);
        assert_true(testG1.handCount[1] == G1.handCount[1]);

        //printf("player 2 discard count = %d, expected = %d\n", testG1.discardCount[1], G1.discardCount[1]);
        assert_true(testG1.discardCount[1] == G1.discardCount[1]);

	
    }
    printf("RANDOMTESTADVENTURER successfully completed\n");
    printf("number of tests passed = %d \n", passed_tests);
    printf("number of tests failed = %d \n", failed_tests);


    //printf("CARDTEST2 SUCCESSFULLY COMPLETED\n");
    return 0;

}