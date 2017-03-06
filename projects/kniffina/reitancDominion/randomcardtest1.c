/***************************************************************
 * random testing for SMITHY card
 *
  *  TO COMPILE
 * type: make randtomtestcard1
 * type in compiler: randtomtestcard1 <number>
 *
 * to get the .out file
 * type: make randtomtestcard1.out
 ***************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>

//assertTrue takes a an int and int testNumber and if the test is true (equal to 1)
//  the string is returned to indicate that the test was successful, otherwise it failed.
int assertTrue(int test, int testNumber) {
    printf("Random card SMITHY - ");


    if (test == 1) {
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
        return 1;
    }
    else {
        printf("TEST %d FAILED.\n", testNumber);
        return 0;
    }
}

int main(int argc, char **argv) {

    if(argc != 2 || argv[1] < 0) {
        printf("Usage: randomtestcard1 <positive integer seed value>\n");
        exit(0);
    }
    struct gameState g1, g2;

    int k[10] = {adventurer, smithy, village, embargo, minion, mine, cutpurse, sea_hag, tribute, council_room};

    //get seed from command line
    srand(atoi(argv[1]));
    int seed = rand() % 5; //get seed int
    int i, testsFailed = 0, numberPlayers = 2, testAmounts = 50;

    for(i = 0; i < testAmounts; i++) {
        //initialize the game with the proper data
        initializeGame(numberPlayers, k, seed, &g1);

        g1.whoseTurn = 0; //set whose turn to start

        int p1deckCount, p1handCount = (rand() % 100) + 20; //used to make sure that random variable between 20-119

        //random test to decide to play with an empty deck or smithy card
        int decision = rand() % 2;
        if(decision == 1) {
            p1deckCount = 0; //set deckcount to 0
        }
        else {
            p1deckCount = (rand() % 100) + 20; //to create 20-119
        }

        int p1discardCount = (rand() % 100) + 20;
        int p2handCount = (rand() % 100) + 20;

        //set player 1s handCount and deckCount
        g1.handCount[0] = p1handCount;
        g1.deckCount[0] = p1deckCount;

        //set player 2s handCount
        g1.handCount[1] = p2handCount;

        //get a random hand for player 1
        for(i = 0; i < p1handCount; i++) {
            g1.hand[0][i] = rand() % treasure_map + 1;
        }

        //put smithy card at the start
        g1.hand[0][0] = smithy;

        //discard pile for player 1
        for(i = 0; i < p1discardCount; i++) {
            g1.discard[0][i] = rand() % treasure_map + 1;
            g1.discardCount[0]++;
        }

        //create deck for player 1
        for(i = 0; i < p1deckCount; i++) {
            g1.deck[0][i] = rand() % treasure_map + 1;
        }

        //call the smithy function
        playSmithy(&g1, 0, 0);

        //1 - Test player 1's hand count
        if(assertTrue((numHandCards(&g1) == p1handCount + 2), 1) == 0) { testsFailed++ ; }

        //2 - Test player 1's discardCard count
        if(assertTrue((g1.discardCount[0] == p1discardCount), 2) == 0) { testsFailed++ ; };

        //3 - Test player 1's deckCount
        if(assertTrue((g1.deckCount[0] == p1deckCount) , 3) == 0) { testsFailed++ ; };

        //4 - Test whose turn it is
        if(assertTrue((whoseTurn(&g1) == 0), 4) == 0) { testsFailed++ ; };

        //5 - Test player 2's handCount
        if(assertTrue((g1.handCount[1] == p2handCount), 5) == 0) { testsFailed++ ; };

        //6 - Test supply count of victory and curse cards
        if(assertTrue((g1.supplyCount[curse] == 10), 6) == 0) { testsFailed++ ; };

        //7 Test estate cards supply count
        if(assertTrue((g1.supplyCount[estate] == 8), 7) == 0) { testsFailed++ ; }

        //8 - Test duchy cards supply count
        if(assertTrue((g1.supplyCount[duchy] == 8), 8) == 0) { testsFailed++ ; }

    }
    printf("Failed test count for SMITHY card is: %d\n", testsFailed);

    return 0;
}

