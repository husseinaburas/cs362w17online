/****************************************
Ambrelle Palmer
unittest1.c
Unit Test for Village card

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
*****************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/**********************************************
Functionality to test for:
	One card is added to player's hand from their deck
	Player's number of available actions is increased by 2
	Played card is discarded from hand
	No state change for other players
	No state change in victory or kingdom card files
**********************************************/

//#define TESTCARD "village"
#define NOISY_TEST 1

int main(){

	int choice1 =0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
	int numPlayers = 2;	
	int newCards = 0;
	int discarded = 1;
	int shuffledCards = 0;
	int newActions = 1;
	int thisPlayer = 0;
	int seed = 1000;
	int i;

	struct gameState G, testG;
	int  k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	//initialize game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing Village Card");
     //Test 1: Check that card count and action count have changed
     printf("TEST 1: 1 card is added to hand from deck and the player has been given two more actions to play \n");

	//copy game state to a test case
     memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;

//	printf("action count = %d, expected action count = %d\n", testG.numActions[thisPlayer], G.numActions[thisPlayer] + newActions);
//	assert(testG.numActions[thisPlayer] == G.numActions[thisPlayer] + newActions);

	printf("hand count = %d, expected hand count = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	printf("deck count = %d, expected deck count = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.deckCount[thisPlayer] == G.handCount[thisPlayer] - newCards + shuffledCards);

	//Test 2: Check that Village card is discarded
	printf("TEST 2: Check to see that number of cards in hand is correct after Village has been discarded\n");
	discarded = 1;

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);


	//Test 3: Check for no state change in victory or kingdom card piles
	printf("TEST 3: Check to see that there has been no change in victory or kingdom card piles\n");

	printf("copper count = %d, expected = %d \n", testG.supplyCount[copper], G.supplyCount[copper]);
     printf("silver count = %d, expected = %d \n", testG.supplyCount[silver], G.supplyCount[silver]);
     printf("gold count = %d, expected = %d \n", testG.supplyCount[gold], G.supplyCount[gold]);
     assert(testG.supplyCount[copper] == G.supplyCount[copper]);
     assert(testG.supplyCount[silver] == G.supplyCount[silver]);
     assert(testG.supplyCount[gold] == G.supplyCount[gold]);

	for(i = 0; i < treasure_map; i++)
		if(testG.supplyCount[i] != G.supplyCount[i])
		{
			printf("Test Failed. Supply count changed for %d card\n", i);
		}

	//Test 4: Check for no state changes in other players
	printf("TEST 4: Check to see that there are no state changes for other players\n");
	for(int i = 0; i < numPlayers; i++)
	{
		if(i != thisPlayer)
		{
			//check that player's deck count didn't change
			if(testG.deckCount[i] != G.deckCount[i])
			{
				printf("Test Failed. Incorrect deck count change for player %d\n", i);
			}

			if(testG.handCount[i] != G.handCount[i])
			{
				printf("Test Failed. Incorrect hand count change for player %d\n", i);
			}
						
		}
	}
	printf("\n TESTING OF VILLAGE CARD COMPLETED\n");

	return 0;
}






