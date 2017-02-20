#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//RANDOM TEST - Adventurer

int assertTrue(int a, int* failed, int* failures, int testNum)
{
    if (a == 1)
        return 1;
    else
    {
        //printf("playAdventurer TEST FAILED %d\n", testNum);
        failures[testNum-1]++;
        *failed = 1;
        return 0;
    }
}

void testAdventurer(int player, struct gameState* testState, int* failures)
{
    int failed = 0;
    
    int deckCount = testState->deckCount[player];
    testState->deck[player][deckCount-1] = smithy; //set first card picked up to be non-treasure, ensuring one card should be discarded
    
    //copy gamestate to preTest - all actions will now be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    
    playAdventurer(player, testState); //run function we are testing
    
    /***********************************************************************
     TEST 1 - HAND SHOULD HAVE 2 MORE CARDS
     ***********************************************************************/
    assertTrue(preTest.handCount[player]+2 == testState->handCount[player], &failed, failures, 1);
    
    /***********************************************************************
     TEST 2 - TOP 2 CARDS IN HAND SHOULD BE TREASURE CARDS
     ***********************************************************************/
    int count = testState->handCount[player];
    int i = 1;
    for (i = 1; i <= 2; i++)
    {
        assertTrue(testState->hand[player][count - i] == copper || testState->hand[player][count - i] == silver || testState->hand[player][count - i] == gold, &failed, failures, 2);
    }
    
    /***********************************************************************
     TEST 3 - AT LEAST ONE CARD SHOULD HAVE BEEN DISCARDED
     ***********************************************************************/
    assertTrue(preTest.discardCount[player] < testState->discardCount[player], &failed, failures, 3);
    
    /***********************************************************************
     TEST 4 - CARD ON TOP OF DISCARD PILE SHOULD NOT BE A TREASURE CARD
     ***********************************************************************/
    int discardCount = testState->discardCount[player];
    assertTrue(testState->discard[player][discardCount-1] != copper || testState->discard[player][discardCount-1] != silver || testState->discard[player][discardCount-1] != gold, &failed, failures, 4);
    
    
    //test if no changes to other players
    int j = 0;
    for (j = 0; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        if (j != player) //only testing other players
        {
            /*************************************************
             TEST 5 - OTHER PLAYER'S HANDS SHOULD NOT CHANGE
             **************************************************/
            for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
            {
                assertTrue(preTest.hand[j][i] == testState->hand[j][i], &failed, failures, 5);
            }
            /*************************************************
             TEST 6 - OTHER PLAYER'S DECKS SHOULD NOT CHANGE
             **************************************************/
            for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
            {
                assertTrue(preTest.deck[j][i] == testState->deck[j][i], &failed, failures, 6);
            }
            /*************************************************
             TEST 7 - OTHER PLAYER'S DISCARD PILES SHOULD NOT CHANGE
             **************************************************/
            for (i = 0; i < preTest.discardCount[j]; i++) //check all cards in discard pile
            {
                assertTrue(preTest.discard[j][i] == testState->discard[j][i], &failed, failures, 7);
            }
        }
    }
    
    //if (failed == 0)
        //printf("playAdventurer TEST PASSED\n");
}


int main(int argc, char *argv[]){
    const int NUMTESTS = 7;
    if (argc !=2)
    {
        printf("USAGE: randomtestadventurer <RAND SEED>\n");
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
        
        testAdventurer(currPlayer, &G, failures);
    }
    
    //print out results
    for (i = 0; i < NUMTESTS; i++)
    {
        printf("ADVENTURER TEST #%d: %d FAILURES\n", i+1, failures[i]);
    }

    return 0;
}
