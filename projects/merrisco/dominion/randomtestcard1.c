//This is for the first card to be tested 

/* 
Program: randomtestcard1.c
Author: Scott Merrill
Date: 02/18/2017
Description:
	this program is a random test for the card smithy. It creates a random gamestate,
	assigns a random person with the smithy card. Then that player plays the card and 
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
        gainCard(smithy, &G, 2, current);
        // make a copy of gamestate to check if tests pass
        struct gameState test;   //game state we will use to test against the original (G)
		memcpy(&test, &G, sizeof(struct gameState));  

        //Start random test generation
        cardEffect(smithy,0,0,0,&test,2,0);        //Play smithy card

        //test that the player drew 2 cards
       	printf("test that the player drew 2 cards\n"); 
		if(test.handCount[current] == G.handCount[current] + 2) //This was a bug, if you change to 4 it passes
			printf("PASS\n");
		else
			printf("FAIL\n");

		//test that a card was played
		printf("Testing that a card was played\n");
		if(test.playedCardCount == 1)
			printf("PASS\n");
		else
			printf("FAIL\n");

        // trest to see if the smithy card was played out of hand
        printf("test that the smithy card was played out of hand.\n");
		if(test.playedCards[0] == smithy)
			printf("PASS\n");
		else
			printf("FAIL\n");

		//test that 3 cards were drawn
		printf("Testing that 3 cards were taken from the current players deck\n");
		if(test.deckCount[current] == G.deckCount[current] - 3)
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



        return 0;
}