#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//RANDOM TEST - Smithy

int assertTrue(int a, int* failed, int* failures, int testNum)
{
    if (a == 1)
        return 1;
    else
    {
        //printf("playSmithy TEST FAILED %d\n", testNum);
        failures[testNum-1]++;
        *failed = 1;
        return 0;
    }
}

void testSmithy(int player, struct gameState* testState, int* failures)
{
    int failed = 0;
    int handCount = testState->handCount[player];
    testState->hand[player][handCount-1] = smithy; //set last card in hand to smithy so we can play it
    
    //copy gamestate to preTest - all actions will now be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    
    playSmithy(player, testState, handCount-1); //run function we are testing
    
    //NOTE: TESTS 1 AND 2 WILL FAIL DUE TO BUGS IN THE CODE - THIS IS INTENTIONAL (FOR NOW)!
    
    /***********************************************************************
     TEST 1 - HAND SHOULD HAVE 2 MORE CARDS (DRAW 3 THEN DISCARD SMITHY)
     ***********************************************************************/
    assertTrue(preTest.handCount[player]+2 == testState->handCount[player], &failed, failures, 1);
    
    /***********************************************************************
     TEST 2 - DECK SHOULD BE DECREASED BY 3 CARDS
     ***********************************************************************/
    assertTrue(preTest.deckCount[player]-3 == testState->deckCount[player], &failed, failures, 2);
    
    //test if no changes to other players
    int j = 0;
    int i = 0;
    for (j = 0; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        if (j != player) //only check other players
        {
            /*************************************************
             TEST 3 - OTHER PLAYER'S HANDS SHOULD NOT CHANGE
             **************************************************/
            for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
            {
                assertTrue(preTest.hand[j][i] == testState->hand[j][i], &failed, failures, 3);
            }
            /*************************************************
             TEST 4 - OTHER PLAYER'S DECKS SHOULD NOT CHANGE
             **************************************************/
            for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
            {
                assertTrue(preTest.deck[j][i] == testState->deck[j][i], &failed, failures, 4);
            }
            /*************************************************
             TEST 5 - OTHER PLAYER'S DISCARD PILES SHOULD NOT CHANGE
             **************************************************/
            for (i = 0; i < preTest.discardCount[j]; i++) //check all cards in discard pile
            {
                assertTrue(preTest.discard[j][i] == testState->discard[j][i], &failed, failures, 5);
            }
        }
    }
    
    /***********************************************************************
     TEST 6 - PLAYEDCARDCOUNT SHOULD BE INCREMENTED
     ***********************************************************************/
    assertTrue(preTest.playedCardCount + 1 == testState->playedCardCount, &failed, failures, 6);
    
    /***********************************************************************
     TEST 7 - SMITHY SHOULD BE ON TOP OF PLAYED CARDS PILE
     ***********************************************************************/
    int playedCount = testState->playedCardCount;
    assertTrue(testState->playedCards[playedCount-1] == smithy, &failed, failures, 7);
    
    //if (failed == 0)
        //printf("playSmithy TEST PASSED\n");
}

int main(int argc, char *argv[]){
    const int NUMTESTS = 7;
    if (argc !=2)
    {
        printf("USAGE: randomtestcard1 <RAND SEED>\n");
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
        
        testSmithy(currPlayer, &G, failures);
    }
    
    //print out results
    for (i = 0; i < NUMTESTS; i++)
    {
        printf("SMITHY TEST #%d: %d FAILURES\n", i+1, failures[i]);
    }
    
    return 0;
}
