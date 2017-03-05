/*
randomtestcard1.c
Author: Brent Nolan
Date: 2/19/2017
Description:  This is a program to test the Smithy function in dominion.c.

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


void testSmithy(int player, struct gameState* testState, int* failures, int handPosTest)
{
           
    //copy gamestate to preTest 
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    //printf("Calling playSmithy \n");
    
	playSmithy(testState, player, handPosTest); 
    //printf("out of playSmithy \n");
    
    //printf("Test 1 \n");
    //Test 1: Hand should only have 2 more cards.  
    assertTrue(preTest.handCount[player]+2 == testState->handCount[player], &failed, failures, 1);
    //printf("Test 2 \n");
    //Test 2: Deck should be decreased by 3 cards.  
    assertTrue(preTest.deckCount[player]-3 == testState->deckCount[player], &failed, failures, 2);
    
    
    //printf("Test 3 \n");
    //Test 3: Played card count should be increased by 1. **This test should fail**
    assertTrue(preTest.playedCardCount + 1 == testState->playedCardCount, &failed, failures, 3);
    //printf("Test 4 \n");
    //Test 4: Smithy should be on the top of played cards pile
    int playedCount = testState->playedCardCount;
    assertTrue(testState->playedCards[playedCount-1] == smithy, &failed, failures, 4);
    
	
	//test 5 & 6 no changes to other players
    int j = 0;
    int i = 0;
    for (j = 0; j < preTest.numPlayers-1; j++) //loop through all other players
    {
        if (j != player) //only check other players
        {
			//printf("Test 5 \n");
            //Test 5: The other player's hand count should be the same.  
            for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
            {
                assertTrue(preTest.hand[j][i] == testState->hand[j][i], &failed, failures, 5);
            }
			//printf("Test 6 \n");
            //Test 6: The other player's decks should be the same.
            for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
            {
                assertTrue(preTest.deck[j][i] == testState->deck[j][i], &failed, failures, 6);
            }
			
        }
    }
   
}



int main(int argc, char *argv[]){
    const int NUMTESTS = 6;
	int i, j;
	struct gameState G;
	int handPosTest;             //Random spot in hand for smithy card
	int numPlayers;
	int currPlayer;
    if (argc !=2)
    {
        printf("USAGE: randomtestcard1 <RAND SEED>\n");
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
		G.hand[G.whoseTurn][handPosTest] = smithy;

		//More Game State setup
		G.playedCardCount = 0;
		G.discardCount[G.whoseTurn] = 0;
//printf("put adventurer \n");		


		
//printf("Calling testSmithy \n");
	testSmithy(currPlayer, &G, failures, handPosTest);
//printf("Out of testSmithy \n");
	}
    
    //print out results
	printf("Test list: \n Test 1: Hand should only have 2 more cards.  \n Test 2: Deck should be decreased by 3 cards.  \n Test 3: Played card count should be increased by 1.  \n Test 4: Smithy should be on the top of played cards pile \n Test 5: The other player's hand count should be the same.  \n Test 6: The other player's decks should be the same.\n");
    printf("Number of tests: %i \n", TEST_LENGTH);
	for (i = 0; i < NUMTESTS; i++)
    {
        printf("ADVENTURER TEST #%d: %d FAILURES\n", i+1, failures[i]);
    }

    return 0;
}