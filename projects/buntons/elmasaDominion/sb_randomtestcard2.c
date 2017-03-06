/*
Name: Shirley Bunton
Date: 02/19/2017
Assignment: Assignment 4
Course: CS362 Software Engineering II
Description: Random Test for Village card*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define DEBUG 0
#define ITER 10000

int main()
{
	struct gameState G, pre;
    int k[10] = { adventurer, smithy, village, great_hall, council_room, salvager, sea_hag, gardens, remodel, ambassador };
	int seedUsed = 0;
	seedUsed = time(NULL);
    srand(seedUsed);
	int i, r;
	int numPlayers = 2;
	int thisPlayer = 0;
	int handPos = 0;
	int pass = 1;


    r = initializeGame(numPlayers, k, 1, &G); // initialize a new game
    assert(r == 0);


	
    printf("TESTING village card with seed %d:\n", seedUsed);

	for(i = 0; i < ITER; i++){
        printf("\nTEST %d:\n", i);


		memcpy(&pre, &G, sizeof(struct gameState));
		G.hand[thisPlayer][0] = rand() % 27;
		G.hand[thisPlayer][1] = rand() % 27;
		G.hand[thisPlayer][2] = rand() % 27;
		G.hand[thisPlayer][3] = rand() % 27;
		G.hand[thisPlayer][4] = rand() % 27;

		G.hand[thisPlayer+1][0] = rand() % 27;
		G.hand[thisPlayer+1][1] = rand() % 27;
		G.hand[thisPlayer+1][2] = rand() % 27;
		G.hand[thisPlayer+1][3] = rand() % 27;
		G.hand[thisPlayer+1][4] = rand() % 27;

		G.deck[thisPlayer][0] = rand() % 27;
		G.deck[thisPlayer][1] = rand() % 27;
		G.deck[thisPlayer][2] = rand() % 27;
		G.deck[thisPlayer][3] = rand() % 27;
		G.deck[thisPlayer][4] = rand() % 27;

		G.deck[thisPlayer+1][0] = rand() % 27;
		G.deck[thisPlayer+1][1] = rand() % 27;
		G.deck[thisPlayer+1][2] = rand() % 27;
		G.deck[thisPlayer+1][3] = rand() % 27;
		G.deck[thisPlayer+1][4] = rand() % 27;

		memcpy(&pre, &G, sizeof(struct gameState));
	

		playVillage(&pre, handPos);

		if(pre.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 1)
		{
			printf("\nFailed Test: Player did not pick up extra card properly.\n");
			printf("Deck Count: %d, Pre-Deck Count: %d\n", pre.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);
			pass = 0;
		}

		if(pre.numActions != G.numActions + 2)
		{
			printf("\nFailed Test: Number of actions did not increase properly for Player 1.\n");
			pass = 0;
		}

		if(pre.discardCount[thisPlayer] != G.discardCount[thisPlayer] + 1) // should fail
		{
			printf("\nFailed Test: Number of cards discarded did not increase properly for Player 1.\n");
			printf("Deck Count: %d, Pre-Deck Count: %d\n", pre.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
			pass = 0;
		}

		endTurn(&pre);

		// Player 2 

		playVillage(&pre, handPos);

		if(pre.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 1)
		{
			printf("\nFailed Test: Player 2 did not pick up extra card properly.\n");
			printf("Deck Count: %d, Pre-Deck Count: %d\n", pre.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);
			pass = 0;
		}

		if(pre.numActions != G.numActions + 2)
		{
			printf("\nFailed Test: Number of actions did not increase properly for Player 2.\n");
			pass = 0;
		}

		if(pre.discardCount[thisPlayer] != G.discardCount[thisPlayer] - 6)
		{
			printf("\nFailed Test: Number of cards discarded did not increase properly for Player 2.\n");
			printf("Deck Count: %d, Pre-Deck Count: %d\n", pre.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
			pass = 0;

		}


	}
	if(pass)
        printf("village card tests passed!\n");
    else
        printf("village tests failed!\n");
	return 0;


}