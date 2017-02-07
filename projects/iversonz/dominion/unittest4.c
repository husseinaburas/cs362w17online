#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

// gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
// gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c -o unittest4 -lm -g
int zdi_assert(int a, char * string)
{
  if(a == 1)
  {
    printf("Test Passed: \t %s \n\n", string);
    return 0;
  }
  else if( a == 2)
  {
    printf("Test Failed: \t %s\n\n", string);
  }
  return 0;

}

int main()
{
  int a, b;
  int randomSeed = 10;

  struct gameState game;

  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  printf("Unit Test 4\n\n");
  a = initializeGame(2,cards, randomSeed, &game);

  b = shuffle(1, &game);

  if(b == 0)
  {
    zdi_assert(1,"Shuffle Hand");
  }
  else
  {
    zdi_assert(2, "Shuffle Handd");
  }


}
