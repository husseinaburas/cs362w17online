/*
randomtestcard1.c
Author: Brent Nolan
Date: 2/19/2017
Description:  This is a program to test the Village function in dominion.c.

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEST_LENGTH 1000


int assertTrue(int a, int* failed, int* failures, int testNum)
{
    if (a == 1)
        return 1;
    else
    {
       
        failures[testNum-1]++;
        *failed = 1;
        return 0;
    }
}

void testVillage(int player, struct gameState* testState, int* failures, int handPosTest)
{
    int failed = 0;
      

    //copy gamestate to preTest - all actions will now be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    
    playVillage(testState, player, handPosTest); //run function we are testing
    
   //Test 1: Hand should be the same size 
    assertTrue(preTest.handCount[player] == testState->handCount[player], &failed, failures, 1);
        
    
    //Test 2: Played card count should be increased by 1. 
    assertTrue(preTest.playedCardCount+1 == testState->playedCardCount, &failed, failures, 2);
	
	//Test 3:  Number of actions should be increased by 2 **This test should fail**
    assertTrue(preTest.numActions+2 == testState->numActions, &failed, failures, 3);
	
    
	//Test 4: Deck should be decreased by 1 card 
    assertTrue(preTest.deckCount[player]-1 == testState->deckCount[player], &failed, failures, 4);
    //Test 5: Village should be the top card on the discard
    int playedCount = testState->playedCardCount;
    assertTrue(testState->playedCards[playedCount-1] == village, &failed, failures, 5);
	
    //test if no changes to other players
    int j = 1;
    int i = 0;
    for (j = 0; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        if (j != player)
        {
            //Test 5: The other player's hand count should be the same. 
            for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
            {
                assertTrue(preTest.hand[j][i] == testState->hand[j][i], &failed, failures, 6);
            }
            //Test 6: The other player's decks should be the same.
            for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
            {
                assertTrue(preTest.deck[j][i] == testState->deck[j][i], &failed, failures, 7);
            }
            
        }
    }
}

int main(int argc, char *argv[]){
    const int NUMTESTS = 7;
	int i, j;
	struct gameState G;
	int handPosTest;             //Random spot in hand for smithy card
	int numPlayers;
	int currPlayer;
    if (argc !=2)
    {
        printf("USAGE: randomtestcard2 <RAND SEED>\n");
        exit(0);
    }
    srand(atoi(argv[1])); //seed random number generator with command line argument
    
    int failures[NUMTESTS]; //array to hold number of failures of each test
    
    for (i = 0; i < NUMTESTS; i++) //zero out array
    {
        failures[i] = 0;
    }
    
		
	
    for(i=0; i<TEST_LENGTH; i++)
	{

		//Setup Game State with 1 action in the correct phase
		G.numActions = 1;
		G.phase = 0;
//printf("Actions/phase \n");
		//Random Game Players 2 - 4
		numPlayers = G.numPlayers = rand() % 3 + 2; 
//printf("num players \n");
		//Random Player for Test
		currPlayer = G.whoseTurn = rand() % numPlayers; 
//printf("curr player \n");
		//Random Hand
		G.handCount[G.whoseTurn]= rand() % 100 + 4;
		for(j=0; j<G.handCount[G.whoseTurn]; j++){
			G.hand[G.whoseTurn][j] = rand() % (treasure_map+1);
		}
//printf("rand hand \n");
		//Random Deck
		G.deckCount[G.whoseTurn] = rand() % 100 + 4;
		for(j=0; j<G.deckCount[G.whoseTurn]; j++){
			G.deck[G.whoseTurn][j] = rand() % (treasure_map+1);
		}
//printf("rand deck \n");
			
		//Put smithy in random spot in hand
		handPosTest = rand() % (G.handCount[G.whoseTurn]);
		G.hand[G.whoseTurn][handPosTest] = village;

		//More Game State setup
		G.playedCardCount = 0;
		G.discardCount[G.whoseTurn] = 0;
//printf("put adventurer \n");		


		
//printf("Calling testSmithy \n");
	testVillage(currPlayer, &G, failures, handPosTest);
//printf("Out of testSmithy \n");
	}
    
    //print out results
	printf("Test list: \n Test 1: Hand should be the same size  \n Test 2: Played card count should be increased by 1. \n Test 3: Number of actions should be increased by 2 \n Test 4: Deck should be decreased by 1 card \n Test 5: Village should be the top card on the discard \n Test 6: The other player's hand count should be the same.  \n Test 7: The other player's decks should be the same.\n");
    printf("Number of tests: %i \n", TEST_LENGTH);
	for (i = 0; i < NUMTESTS; i++)
    {
        printf("ADVENTURER TEST #%d: %d FAILURES\n", i+1, failures[i]);
    }

    return 0;
}