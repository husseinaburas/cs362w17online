#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

#define TEST_MAX 1000
#define NUM_PLAYERS 2
#define MAX_CARDS 27

int test_card_adventurer(int p, struct gameState *G)
{
  int i, r, c, d, t, r;
  int handPos = rand() % _G.handCount[p];
  int h[MAX_HAND];

  struct gameState _G;

  G->whoseTurn = p;

  memcpy(&_G, G, sizeof(gamestate));

  d = 0;
  t = 0; // treasure
  r = playAdventurer(G, p);

  while (t < 2)
  {
    if (pre.deckCount[p] <= 0) {
      for (i = 0; i < pre.discardCount[p], i++)
      {
        _G.deck[p][i] = _G.discard[p][i];
        _G.deckCount[p]++;
        _G.discard[p][i] = -1;
        _G.discardCount[p]--;
      }
      shuffle(p, &_G);
    }
    drawCard(p, &_G);
    c = _G.hand[p][_G.handCount[p]-1];
    if (c == copper || c == silver || c == gold)
      t++
    else
    {
      temphand[d] = c;
      _G.handCount[p]--;
      d++;
    }
  }

  while (z > 1)
  {
    _G.discard[p][_G.discardCount[p]++] = h[d-1];
    z--;
  }

  assert(r == 0);
  discardCard(handPos, p, _G);
  assert(memcmp(&_G, G, sizeof(struct gameState)) == 0);
}

int main()
{
  srand(time(NULL));

  int i, p, r_1, r_2, r_3;
  struct gameState G;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

  for (p = 0; p < NUM_PLAYERS; p++)
  {
    memset(&G, 23, sizeof(struct gameState));

    assert(initializeGame(NUM_PLAYERS, k, 0, &G) == 0);

    r_1 = rand() % MAX_HAND;
    r_2 = rand() % MAX_DECK;
    r_3 = rand() % MAX_DECK;

    G.handCount[p]    = r_1;
    G.deckCount[p]    = r_2;
    G.discardCount[p] = r_3;

    for (i = 0; i < r_1; i++)
      G.hand[p][i] = rand() % MAX_CARDS;
    for (i = 0; i < r_2; i++)
      G.hand[p][i] = rand() % MAX_DECK;
    for (i = 0; i < r_3; i++)
      G.hand[p][i] = rand() % MAX_DECK;

    test_card_adventurer(p, &G);

  }
}
