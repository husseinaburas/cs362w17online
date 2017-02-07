#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c -o cardtest1 -lm -g

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
  struct gameState game;
  printf("\nCard Test 1\n-----------\n");
  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  a = initializeGame(2,cards, randomSeed, &game);

  b = cardEffect(adventurer, 0, 0, 0, &game, 0, 0);

  if(b == 0)
  {
    zdi_assert(1, "Card Effect - Adventurer");
  }
  else
  {
    zdi_assert(2, "Card Effect - Adventurer");

  }

return 0;
}
