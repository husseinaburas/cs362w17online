/*
randomtestadventurer.c
Author: Brent Nolan
Date: 2/19/2017
Description:  This is a program to test the adventurer function in dominion.c.

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
//My adventurer function does not pull silver from deck, so must ensure there are 2 other treasure card in deck
int deckTreasureCardCount(int player, struct gameState G){
	int l;
	int t=0;
	for(l=0; l<(G.deckCount[player]); l++){
		if(G.deck[player][l] == copper || G.deck[player][l] == gold){
			t++;
		}
	}
	return t;
}

void testAdventurer(int player, struct gameState* testState, int* failures)
{
    int failed = 0;
    
    //int deckCount = testState->deckCount[player];
    //testState->deck[player][deckCount-1] = smithy; //set first card picked up to be non-treasure, ensuring one card should be discarded
    
    //copy gamestate to preTest - all actions will now be performed on testState
    struct gameState preTest;
    memcpy(&preTest, testState, sizeof(struct gameState));
    
	//printf("Pretest hand count before adventurer played %i \n", preTest.handCount[player]);
	//printf("testState hand count before adventurer played %i \n", testState->handCount[player]);
    playAdventurer(player, testState); 
   // printf("Pretest hand count after adventurer played %i\n", preTest.handCount[player]);
	//printf("testState hand count after adventurer played %i \n", testState->handCount[player]);
    
	//Test 1: Hand should only have 2 more cards
    assertTrue((preTest.handCount[player]+2) == testState->handCount[player], &failed, failures, 1);
    
    //Test 2: The cards drawn should be treasure cards
    int count = testState->handCount[player];
    int i = 1;
    for (i = 1; i <= 2; i++)
    {
        assertTrue(testState->hand[player][count - i] == copper || testState->hand[player][count - i] == silver || testState->hand[player][count - i] == gold, &failed, failures, 2);
    }
    //printf("Test3 \n");	
    
	//Test 3: Played count is increased by 1
	assertTrue(preTest.playedCardCount+1 == testState->playedCardCount, &failed, failures, 3);
	//printf("Test4 \n");	
	
	//Test 4: Card on the top of the discard pile should not be a treasure card 
    int discardCount = testState->discardCount[player];
    assertTrue(testState->discard[player][discardCount-1] != copper || testState->discard[player][discardCount-1] != silver || testState->discard[player][discardCount-1] != gold, &failed, failures, 4);
    
    
    //other player changes tests
    int j = 0;
    for (j = 0; j < (preTest.numPlayers)-1; j++) //loop through all other players
    {
        if (j != player) //only testing other players
        {
            //Test 5: Other player's Hands should be the same
			//printf("Test5 \n");	
			for (i = 0; i < preTest.handCount[j]; i++) //check all cards in hand
            {
                assertTrue(preTest.hand[j][i] == testState->hand[j][i], &failed, failures, 5);
            }
            //Test 6: Other player's Decks should be the same
			//printf("Test6 \n");	
            for (i = 0; i < preTest.deckCount[j]; i++) //check all cards in deck
            {
                assertTrue(preTest.deck[j][i] == testState->deck[j][i], &failed, failures, 6);
            }
            
        }
    }
    
    //if (failed == 0)
        //printf("playAdventurer TEST PASSED\n");
}


int main(int argc, char *argv[]){
    const int NUMTESTS = 6;
	int i, j;
	struct gameState G;
	int handPosTest;             //Random spot in hand for adventurer card
	int numPlayers;
	int currPlayer;
    if (argc !=2)
    {
        printf("USAGE: randomtestadventurer <RAND SEED>\n");
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
		//ensure 2 treasure cards are in the deck so the test does not hang
		if(deckTreasureCardCount(currPlayer, G) < 2){
			G.deckCount[G.whoseTurn] +=2;
			G.deck[G.whoseTurn][0] = copper;
			G.deck[G.whoseTurn][1] = copper;
								
		}
			
//printf("2 treasure \n");		
		//Put adventurer in random spot in hand
		handPosTest = rand() % (G.handCount[G.whoseTurn]);
		G.hand[G.whoseTurn][handPosTest] = adventurer;

		//More Game State setup
		G.playedCardCount = 0;
		G.discardCount[G.whoseTurn] = 0;
//printf("put adventurer \n");		


		

	testAdventurer(currPlayer, &G, failures);

	}
    
    //print out results
	printf("Test list: \n Test 1: Hand should only have 2 more cards \n Test 2: The top 2 cards should be treasure cards \n Test 3: Played count is increased by 1 \n Test 4: Card on the top of the discard pile should not be a treasure card \n Test 5: Other player's Hands should be the same \n Test 6: Other player's Decks should be the same \n");
    printf("Number of tests: %i \n", TEST_LENGTH);
	for (i = 0; i < NUMTESTS; i++)
    {
        printf("ADVENTURER TEST #%d: %d FAILURES\n", i+1, failures[i]);
    }

    return 0;
}