#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define TEST_MAX 100

int main()
{
  int i;

  printf ("Testing newGame()...\n");

  for(i = 0; i < TEST_MAX; i++)
  {
    // Create a new game
    struct gameState *G = (struct gameState*)newGame();
    assert(G); // ensure not null
    free(G);   // cleanup
    G = 0;
  }

  printf ("Finished.\n");

  return 0;
}
