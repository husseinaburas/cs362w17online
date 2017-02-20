#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

#define TEST_HANDS 10

int main()
{
  srand(time(NULL));
  int i, r;

  int h[TEST_HANDS];

  struct gameState G;

  printf ("Testing numHandCards()...\n");

  for(i = 0; i < TEST_HANDS; i++)
  {
    h[i] = rand()%TEST_HANDS;
    G.whoseTurn = i;
    G.handCount[i] = h[i];
    r = numHandCards(&G);

    assert(h[i] == r);
  }

  printf ("Finished.\n");

  return 0;
}
