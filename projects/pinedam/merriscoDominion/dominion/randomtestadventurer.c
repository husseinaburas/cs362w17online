/* 
Program: randomtestadventurer.c
Author: Scott Merrill
Date: 02/18/2017
Description:
	this program is a random test for the card adventurer. It creates a random gamestate,
	assigns a random person with the adventurer card. Then that player plays the card and 
	we check to how/if the game state has changed. All this information is printed out to the screen. 
*/

// required #includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>


#define NUM_TESTS 1000


int main(int argc, char *argv[]) {

	
	int i,j,l;

	//seed for random number generation
	if(argc == 2)
		srand(atoi(argv[1]));
	else
		srand(999);


	//Loop for the number of tests
	printf("BEGINNING %i RANDOM TESTS \n", NUM_TESTS);
	for(i=0; i<NUM_TESTS; i++){

		int Players = rand() % 3 + 2 ;    // selects a random number of players between 2 and 4
		int current = rand() % Players;   // select the current player
		int randomNumber = rand() % 2000 + 1;   // used to as a random number for initializeGame()


		struct gameState G;   //Create the game state
		// Create the cards counter
		int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy};

        // Create the beginning of the game to be tested 
        initializeGame(Players, k, randomNumber, &G);
        G.whoseTurn = current;   // set the turn to the current player
        int deckCount = G.deckCount[current];   // set the deck count for the current player
        G.deck[current][deckCount-1] = adventurer; // ensure the player will have the adventurer card in hand
        gainCard(adventurer, &G, 2, current);
        // make a copy of gamestate to check if tests pass
        struct gameState test;   //game state we will use to test against the original (G)
		memcpy(&test, &G, sizeof(struct gameState));  

        //Start random test generation
		cardEffect(adventurer,0,0,0,&test,5,0);        //Play adventure card


		//Test if the play has drawn 2 treasure cards
		printf("Testing whether the player gained 2 treasure cards\n");
		int oldNumTreasures = 0;
		for (j = 0; j < test.handCount[current]; j++) 
		{
			if (test.hand[current][j] == gold || test.hand[current][j] == silver || test.hand[current][j] == copper)
				oldNumTreasures++;
		}
		
		int curNumTreasures = 0;
		for (j = 0; j < G.handCount[current]; j++) 
		{
			if (G.hand[current][j] == gold || G.hand[current][j] == silver || G.hand[current][j] == copper)
				curNumTreasures++;
		}
		if(curNumTreasures == oldNumTreasures - 2)
			printf("PASS\n");
		else
			printf("FAIL\n");


		//Test that current player has discarded
		printf("Testing player %d has discarded.\n", current);
			if(test.discardCount[current] != G.discardCount[current])
				printf("PASS\n");
				else
					printf("FAIL\n");

		//Test that current player has 2 more cards in hand
		printf("Testing that the current player has 2 more cards in hand\n");
		if(test.handCount[current] == G.handCount[current] + 2)
			printf("PASS\n");
		else
			printf("FAIL\n");





		//tests for all other players, ensure nothing has changed in thier game state 	
		for (j = 0; j < Players; j++) {
			if (j != current) {
				//Test that they have the same discard count
				printf("Testing player %d has the same discard count.\n", j+1);
				if(test.discardCount[j] == G.discardCount[j])
					printf("PASS\n");
				else
					printf("FAIL\n");			
				
				
				//Test that their deck count is the same
				printf("Testing player %d has the same deck count.\n", j+1);
				if(test.deckCount[j] == G.deckCount[j])
					printf("PASS\n");
				else
					printf("FAIL\n");	
			
				//Test that they have the same nummber of card in hand 
				printf("Testing player %d has the same number of cards in hand.\n", j+1);
				if(test.handCount[j] == G.handCount[j])
					printf("PASS\n");				
				else
					printf("FAIL\n");

				//Test that they have the same cards 
				printf("Testing player %d has the same cards in hand.\n", j+1);
				if (test.handCount[j] == 0) {
					printf("Player %d has a handcount of 0\n", j+1);
				}
				else {
					for (l = 0; l < test.handCount[j]; l++) 
					{
						printf("Card #%d ", l);
						if(test.hand[j][l] == G.hand[j][l])
							printf("PASS\n");
						else
							printf("FAIL\n");
					}
				}
	
				
				
			}
			
		}

	
	}




	printf("exit program\n");
	return 0;
}
