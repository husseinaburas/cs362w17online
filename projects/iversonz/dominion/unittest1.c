#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
// gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c -o unittest1 -lm -g
int zdi_assert(int a, char * string)
{
  if(a == 1)
  {
    printf("Test Passed: \t %s \n\n\n", string);
    return 0;
  }
  else if( a == 2)
  {
    printf("Test Failed: \t %s\n\n\n", string);
  }
  return 0;

}



int main()
{
  int a, b;
  int randomSeed = 10;
// Testing the zdi_assert function
//  a = 1;
//  b = zdi_assert(a, "init function");

  struct gameState game;

  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  printf("\n*****************************\n\nUnit Test 1\n\n");
  a = initializeGame(2,cards, randomSeed, &game);

  if(a == 0)
  {
    b = zdi_assert(1, "Initializng Game");
  }
  else
  {
    b = zdi_assert(2, "Initializng Game");
  }

  return 0;
}
