#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//RANDOM TEST - Village

int assertTrue(int a, int* failed, int* failures, int testNum)
{
    if (a == 1)
        return 1;
    else
    {
        //printf("playVillage TEST FAILED %d\n", testNum);
        failures[testNum-1]++;
        *failed = 1;
        return 0;
    }
}

void testVillage(int player, struct gameState* testState, int* failures)
{
    int failed = 0;
    int handCount = testState->handCount[player];
    testState->hand[player][handCount-1] = village; //set last card in hand to village

    //copy gamestate to preTest - all actions will now be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));

    playVillage(testState, player, handCount-1); //run function we are testing

    /***********************************************************************
     TEST 1 - HAND SHOULD BE THE SAME SIZE (DRAW 1, PLAY 1)
     ***********************************************************************/
    assertTrue(preTest.handCount[player] == testState->handCount[player], &failed, failures, 1);

    /***********************************************************************
     TEST 2 - NUMACTIONS SHOULD INCREASE BY 2
     ***********************************************************************/
    assertTrue(preTest.numActions+2 == testState->numActions, &failed, failures, 2);

    //NOTE: TESTS 3 AND 4 WILL FAIL DUE TO BUGS IN THE CODE - THIS IS INTENTIONAL (FOR NOW)!
    /***********************************************************************
     TEST 3 - PLAYED CARD COUNT SHOULD BE INCREMENTED
     ***********************************************************************/
    assertTrue(preTest.playedCardCount+1 == testState->playedCardCount, &failed, failures, 3);

    /***********************************************************************
     TEST 4 - TOP OF PLAYED CARDS SHOULD BE VILLAGE
     ***********************************************************************/
    int playedCount = testState->playedCardCount;
    assertTrue(testState->playedCards[playedCount] == village, &failed, failures, 4);

    /***********************************************************************
     TEST 5 - DECKCOUNT SHOULD BE DECREMENTED
     ***********************************************************************/
    assertTrue(preTest.deckCount[player]-1 == testState->deckCount[player], &failed, failures, 5);

    //test if no changes to other players
    int j = 1;
    int i = 0;
    for (j = 0; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        if (j != player)
        {
            /*************************************************
             TEST 6 - OTHER PLAYER'S HANDS SHOULD NOT CHANGE
             **************************************************/
            for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
            {
                assertTrue(preTest.hand[j][i] == testState->hand[j][i], &failed, failures, 6);
            }
            /*************************************************
             TEST 7 - OTHER PLAYER'S DECKS SHOULD NOT CHANGE
             **************************************************/
            for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
            {
                assertTrue(preTest.deck[j][i] == testState->deck[j][i], &failed, failures, 7);
            }
            /*************************************************
             TEST 8 - OTHER PLAYER'S DISCARD PILES SHOULD NOT CHANGE
             **************************************************/
            for (i = 0; i < preTest.discardCount[j]; i++) //check all cards in discard pile
            {
                assertTrue(preTest.discard[j][i] == testState->discard[j][i], &failed, failures, 8);
            }
        }
    }

    //if (failed == 0)
        //printf("playVillage TEST PASSED\n");
}

int main(int argc, char *argv[]){
    const int NUMTESTS = 8;
    if (argc !=2)
    {
        printf("USAGE: randomtestcard2 <RAND SEED>\n");
        exit(0);
    }
    srand(atoi(argv[1])); //seed random number generator with command line argument

    int failures[NUMTESTS]; //array to hold number of failures of each test
    int i = 0;
    for (i = 0; i < NUMTESTS; i++) //zero out array
    {
        failures[i] = 0;
    }

    //run tests 2000 times
    for (i = 0; i < 2000; i++)
    {
        //set up randomized game state
        int numPlayers = rand() % 3 + 2; //random in range 2-4
        int currPlayer = rand() % numPlayers; //random in range 0 to numPlayers-1 (valid player id)
        int randomSeed = rand() % 1000 + 1; //random in range 1-1000

        struct gameState G;
        int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy};

        initializeGame(numPlayers, k, randomSeed, &G);

        testVillage(currPlayer, &G, failures);
    }

    //print out results
    for (i = 0; i < NUMTESTS; i++)
    {
        printf("VILLAGE TEST #%d: %d FAILURES\n", i+1, failures[i]);
    }

    return 0;
}
