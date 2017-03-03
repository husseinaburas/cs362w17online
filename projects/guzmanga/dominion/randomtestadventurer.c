#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define MAX_TESTS 10

int main(int argc, char** argv){

  int k[10] = {adventurer, council_room, feast, gardens, mine,
         remodel, smithy, village, baron, great_hall};

  int i, game, errors = 0, players, player, handCount = 0, deckCount, randomSeed, rseed;
  struct gameState G;

  printf("Random Test for Adventurer");
  rseed = time(NULL);
  srand(rseed);
  for(i = 0; i < MAX_TESTS; i++){
    players = rand() % 3 + 2;
    player = 0;
    randomSeed = atoi(argv[1]);

    printf("Start game...\n");
    game = initializeGame(players, k, randomSeed, &G);
    if(game != 0){
      errors++;
    }

    G.deckCount[player] = rand() % MAX_DECK;
    G.discardCount[player] = rand() % MAX_DECK;
    G.handCount[player] = rand()% MAX_HAND;

    handCount = G.handCount[player];
    deckCount = G.deckCount[player];

    G.hand[player][0] = adventurer;

    if(randomSeed % 3 == 0){
      G.deckCount[player] = 0;

    cardEffect(adventurer, 1, 1, 1, &G, 0, 0);

    if((handCount+2) != G.handCount[player]){
      errors++;
      printf("%d, %d\n", handCount+2, G.handCount[player]);
    }

    }
    if(errors > 0){
      printf("%d errors", errors);
    }
    else{
      printf("ALL TESTS OK\n");
    }
  }

  return 0;
}
