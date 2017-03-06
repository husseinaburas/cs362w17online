//adventurer random test
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 12

int main() {

	  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};

	  int i, j, n, players, player, handCount, deckCount, seed, address;
	  //struct gameState state;
	  struct gameState state1;
	  struct gameState state2;
	  struct gameState state3;

	  printf("Running Random Adventurer Test\n");

		players = 0;
	  for (i = 0; i < MAX_TESTS; i++) {

	   players = rand() % 4;
	   seed = rand();

	   initializeGame(players, k, seed, &state1);	//initialize Gamestate

	   //Initiate valid state variables
	   //generate random hand sizes etc...
		 for(int player = 0; j < players; player++){
			  state1.deckCount[player] = rand() % MAX_DECK; 
			  state1.discardCount[player] = rand() % MAX_DECK;
			  state1.handCount[player] = rand() % MAX_HAND;

			  handCount = state1.handCount[player];
			  deckCount = state1.deckCount[player];
		}
		  //1 in 3 chance of empty deck
		  if (seed % 3 == 0){
			state1.deckCount[player] = 0;
		  }
			//use the card
		  playCard(0, 1, 1, 1, &state1);
			printf("first loop\n");
	  }

	   for (i = 0; i < MAX_TESTS; i++){
		//random seed and players
  		  players = rand() % 4;
		  seed = rand();

		  initializeGame(players, k, seed, &state2);

		  //Initiate valid state variables
			for(int player = 0; j < players; player++){
			  state2.deckCount[player] = rand() % MAX_DECK;
			  state2.discardCount[player] = rand() % MAX_DECK;
			  state2.handCount[player] = rand() % MAX_HAND;


			  //Copy state variables
			  handCount = state2.handCount[player];
			  deckCount = state2.deckCount[player];
		}

		  //1 in 3 chance of making empty deck for coverage
		  if (seed % 3 == 0) {

			state2.deckCount[player] = 0;
		  }

		  playCard(adventurer, 1, 1, 1, &state2);
	  }

	   for (i = 0; i < MAX_TESTS; i++) {

  		players = rand() % 4;
		  seed = rand();

		  initializeGame(players, k, seed, &state3);

		  //Initiate valid state variables
			for(int player = 0; j < players; player++){
			  state3.deckCount[player] = rand() % MAX_DECK; 
			  state3.discardCount[player] = rand() % MAX_DECK;
			  state3.handCount[player] = rand() % MAX_HAND;

			  //Copy state variables
			  handCount = state3.handCount[player];
			  deckCount = state3.deckCount[player];
			}

		  //1 in 3 chance of making empty deck for coverage
		  if (seed % 3 == 0) {

			state3.deckCount[player] = 0;
		  }
		  playCard(adventurer, 1, 1, 1, &state3);
	   }

	  printf("Tests Complete\n");

	  return 0;
}