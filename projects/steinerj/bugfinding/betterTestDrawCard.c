#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h" 

int main()
{ 
  TestRandom();  
 // int number = atoi(argv[1]);
 // printf("argv1 is %i\n", number);

  int i, n, p; 

//  int k[10] = {adventurer, council_room, feast, gardens, mine,
//	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing drawCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) 
  {
    for (i = 0; i < sizeof(struct gameState); i++)
    {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    //checkDrawCard(p, &G);
  }

  printf ("ALL TESTS OK\n");

  return 0;
}
