//gardens
//council_room
//smithy
//Treasure card
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 10

int main(int argc, char** argv){

  int k[10] = {adventurer, council_room, feast, gardens, mine,
         remodel, smithy, village, baron, great_hall};

  int i, players, player, handCount, deckCount , randomSeed;
  struct gameState G;

  randomSeed = atoi(argv[1]);

  printf("Random Test for Smithy\n");

  for(i = 0; i < MAX_TESTS; i++){

    player = 0;
    players = rand() % 3 + 2;

    initializeGame(player,k,randomSeed, &G);

    G.deckCount[player] = rand()%MAX_DECK;
    G.discardCount[player] = rand() % MAX_DECK;
		G.handCount[player] = rand() % MAX_HAND;

    handCount = G.handCount[player];
		deckCount = G.deckCount[player];

		printf("%d\n", i);

    cardEffect(smithy, 0, 0, 0, &G);

	  printf("%dB\n", i);
  }
  return 0;
}
