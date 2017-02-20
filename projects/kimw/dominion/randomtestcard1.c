#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkSmithyCard(int currentPlayer, struct gameState *post) {
  int r;
  int prevHandCount = post->handCount[currentPlayer];
  int handPos = prevHandCount - 1;
  post->hand[currentPlayer][handPos] = smithy;
  r = smithyCard (handPos, currentPlayer, post);
  int newHandCount = post->handCount[currentPlayer];

  printf("smithyCard runs successfully:\n");
  asserttrue(r == 0);

  printf("player %d now has 3 more or max cards\n", currentPlayer);
  asserttrue((newHandCount - prevHandCount) == 3 || newHandCount == MAX_HAND);

  printf("player %d no longer has smithy card\n", currentPlayer);
  asserttrue(post->hand[currentPlayer][handPos] != smithy );

}

int main (int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "usage: randomtestcard1 takes 1 argument for seed");
    exit(1);
  }

  int i, n, r, p, deckCount, discardCount, handCount, seed;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  seed = atoi(argv[1]);

  printf ("__________Testing smithy card____________\n");

  for (n = 0; n < 2000; n++) {
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, seed, &G); 
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    checkSmithyCard(p, &G);
  }

  printf ("________________________________________\n");

  return 0;
}
