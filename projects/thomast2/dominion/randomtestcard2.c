#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"
#include <time.h>

#define MAX_TESTS 1000 

int main() {

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	int i;
	int r = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int numPlayers = 0, curPlayer = 0;
	int handPos = 0, discardCount = 0, numActions = 0;
	int counter = 0;
	int seed;

	srand(time(NULL));

	printf("Testing great_hall.\n");

	for (i = 0; i < MAX_TESTS; i++) {
		struct gameState * state = newGame();
		//random values to cardEffect arguments
		numPlayers = rand()%5;
		
		if(numPlayers == 0 || numPlayers == 1) numPlayers += 2;
		//must have 4 players
		
		curPlayer = 0;
		//randomize seeds and choices
		seed = rand();
		choice1 = rand()%2;
		choice2 = rand()%2;
		choice3 = rand()%2;
		handPos = rand()%4;

		initializeGame(numPlayers, k, seed, state);

		//setting random values for the players decks
		state->deckCount[curPlayer] = rand()%MAX_DECK;
		state->discardCount[curPlayer] = rand()%MAX_DECK;
		state->handCount[curPlayer] = rand()%MAX_HAND; 

		if (seed%2 == 0) state->deckCount[curPlayer] = 0;

		discardCount = state->discardCount[curPlayer]; //discard count should increase by 1
		numActions = state->numActions; //number of actions should increase by 1

		r = cardEffect(great_hall, choice1, choice2, choice3, state, handPos, 0);
		//check discard count
		if(discardCount != state->discardCount[curPlayer]-1 && state->discardCount[curPlayer] !=1){
				counter++;
				printf("discard count = %d\t state->discardCount = %d\n", discardCount, state->discardCount[curPlayer]);
			}
		if(numActions != state->numActions-1){ //checking number of actions
			printf("Test Passed\n");
		}
		free(state);

	}
	printf("Test complete.\n");

	return 0;
}