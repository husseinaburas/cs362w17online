#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkAdventurerCard(int currentPlayer, struct gameState *post) {
  int r;
  int temphand[MAX_HAND];
  int drawntreasure=0;
  int cardDrawn;
  int z = 0;

  int prevHandCount = post->handCount[currentPlayer];
  int prevDiscardCount = post->discardCount[currentPlayer];
  int prevDeckCount = post->deckCount[currentPlayer];
  int handPos = prevHandCount - 1;
  post->hand[currentPlayer][handPos] = adventurer;
  r = adventurerCard(currentPlayer, post, cardDrawn, drawntreasure, temphand, z);

  int newHandCount = post->handCount[currentPlayer];
  int newDiscardCount = post->discardCount[currentPlayer];
  int newDeckCount = post->deckCount[currentPlayer];

  printf("adventurer card runs successfully:\n");
  asserttrue(r == 0);

  printf("Card count increased by 2\n");
  int cardCount = newHandCount - prevHandCount;
  asserttrue(cardCount == 2);

  printf("Discard count increased\n");
  int discardCount = newDiscardCount - prevDiscardCount;
  asserttrue(discardCount >= 0);

  printf("Deck count decreased\n");
  int deckCount = newDeckCount - prevDeckCount;
  asserttrue(deckCount < 0);

  printf("Make sure the same all drawn/discarded cards are accounted for\n");
  int difference = cardCount + discardCount + deckCount;
  asserttrue(difference == 0);

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

  printf ("_______Testing adventurer card_________\n");

  for (n = 0; n < 2000; n++) {
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(2, k, seed, &G); 
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    checkAdventurerCard(p, &G);
  }

  printf ("________________________________________\n");

  return 0;
}
