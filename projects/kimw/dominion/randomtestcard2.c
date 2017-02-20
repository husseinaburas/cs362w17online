#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkGreatHallCard(int currentPlayer, struct gameState *post) {
  int r;
  int prevHandCount = post->handCount[currentPlayer];
  int prevNumAction = post->numActions;
  int handPos = prevHandCount - 1;
  post->hand[currentPlayer][handPos] = great_hall;
  r = greatHallCard(handPos, currentPlayer, post);
  int newHandCount = post->handCount[currentPlayer];
  int newNumAction = post->numActions;

  printf("greatHallCard runs successfully:\n");
  asserttrue(r == 0);

  printf("player %f now has 1 more or max cards\n", currentPlayer);
  asserttrue((newHandCount - prevHandCount) == 1 || newHandCount == MAX_HAND);

  printf("Number of actions increased by 1\n");
  asserttrue((newNumAction - prevNumAction) == 1);

  printf("player %f no longer has great hall card\n", currentPlayer);
  asserttrue(post->hand[currentPlayer][handPos] != great_hall );

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

  printf ("_______Testing great hall card_________\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, seed, &G); 
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    checkGreatHallCard(p, &G);
  }

  printf ("________________________________________\n");

  return 0;
}
