#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c -o cardtest2 -lm -g


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
  int a, b, c;
  int randomSeed = 10;
  struct gameState game;

  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  printf("\nCard Test 2\n-----------\n");

  a = initializeGame(2,cards, randomSeed, &game);

  b = numHandCards(&game);

  cardEffect(smithy, 0, 0, 0, &game, 0, 0);

  c = numHandCards(&game);
  b = b + 2; // add cards
  if(b == c) // make sure each have the same amount of cards
  {
    zdi_assert(1, "Card Effect - Smithy");
  }
  else
  {
    zdi_assert(2, "Card Effect - Smithy");

  }

return 0;
}
