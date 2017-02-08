#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"
#include <math.h>

#define DEBUG 0
#define NOISY_TEST 1

#define MAX_ROUNDS 1000

int test_updateCoins(int p, struct gameState *G, int c)
{
  int i;
  struct gameState _G;

  memcpy(&_G, G, sizeof(struct gameState));

  for (i = 0; i < _G.handCount[p]; i++)
  {
    switch (_G.hand[p][i])
    {
      case copper:
        _G.coins++;
        break;
      case silver:
        _G.coins += 2;
        break;
      case gold:
        _G.coins +=3;
        break;
    }
  }

  assert(memcmp(&_G, G, sizeof(struct gameState)) == 0);

  return 0;
}

int main()
{
  srand(time(NULL));

  int c, p, i, j;

  struct gameState G;

  printf("Testing getCost()\n");

  for (i = 0; i < MAX_ROUNDS; i++)
  {
    // Create a gameState
    for (j = 0; j < sizeof(struct gameState); j++)
      ((char*)&G)[j] = floor(Random()*256);

    c                 = 0;
    p                 = floor(Random()*MAX_PLAYERS); // set some players
    G.deckCount[p]    = floor(Random()*MAX_DECK);    // set some decks
    G.discardCount[p] = floor(Random()*MAX_DECK);    // create a discard pile
    G.handCount[p]    = floor(Random()*MAX_HAND);    // create some hands

    test_updateCoins(p, &G, c);
  }

  printf("Finished.\n");

  return 0;
}
