#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define MAX_TESTS 10

int main(int argc, char** argv){

  int k[10] = {adventurer, council_room, feast, gardens, mine,
         remodel, smithy, village, baron, great_hall};

  int i, player, handCount, deckCount, numActions, discardCount, randomSeed;
  struct gameState G;

  printf("Random Test for Village\n");

  srand(time(NULL));

  for(i = 0; i < MAX_TESTS; i++){
    player = rand() % 3 + 2;
    randomSeed = atoi(argv[1]);

    initializeGame(player,k, randomSeed, &G);

    G.deckCount[player] = rand() % MAX_DECK;
  	G.discardCount[player] = rand() % MAX_DECK;
  	G.handCount[player] = rand() % MAX_HAND;
  	G.numActions = (rand() % 10) + 1;

  	handCount = G.handCount[player];
  	deckCount = G.deckCount[player];
  	discardCount = G.handCount[player];
  	numActions = G.numActions;

    cardEffect(village, 0,0,0, &G);

    if((numActions == (G.numActions - 2)) && handCount == G.handCount[player]){
      printf("ALL TESTS OK\n");
    }else{
      printf("Village test has failed");
    }

    }

    return 0;
  }
