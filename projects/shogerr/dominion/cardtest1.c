#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define TEST_MAX 1000
#define NUM_PLAYERS 2
#define ACTION_CARD 3

test_card_smithy(int handPos, struct gameState *G)
{
  int p;
  struct gameState _G;

  memcpy(&_G, G, sizeof(struct gameState));

  p = floor(Random()*MAX_PLAYERS);

  cardEffect(smithy, 0, 0, 0, &_G, handPos, 0);

  G->handCount[p] = G->handCount[p] + ACTION_CARD - 1;

  if (!compare(_G.handCount[p],G->handCount[p]))
    return 0;
  else
    return -1;
}

int main()
{
  struct gameState G;
  int handPos = 0;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

  printf("Testing Smithy card...\n");

  initializeGame(NUM_PLAYERS, k, TEST_MAX, &G);

  if (test_card_smithy(handPos, &G))
    printf("Something went wrong with the card.\n");

  printf("Finished.\n");
  return 0;
}
