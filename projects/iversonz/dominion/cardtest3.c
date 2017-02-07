#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


// gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c -o cardtest3 -lm -g
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

  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  printf("\nCard Test 3\n-----------\n");

  a = initializeGame(2,cards, randomSeed, &game);

  cardEffect(village, 0, 0, 0, &game, 0, 0);

  b = numHandCards(&game);

  if(b == 5) //should have 5 cards in hand
  {
    zdi_assert(1, "Card Effect - Village");
  }
  else
  {
    zdi_assert(2, "Card Effect - Village");
  }

  return 0;

}
