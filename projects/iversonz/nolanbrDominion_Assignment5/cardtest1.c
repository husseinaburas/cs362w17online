#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c -o cardtest1 -lm -g

//ZDI assert is a function that receives a integer and a character.
// It checks if the integer is one or 2, if it is one that means the test Passed.
// If the integer is 2 it means the test failed
int zdi_assert(int a, char * string)
{
  if(a == 1) // 1 == passed
  {
    printf("Test Passed: \t %s \n\n\n", string);
    return 0;
  }
  else if( a == 2) // 2 == failed
  {
    printf("Test Failed: \t %s\n\n\n", string);
  }
  return 0;

}

// Main
int main()
{
  int a, b;
  int randomSeed = 10;
  struct gameState game;
  printf("\nCard Test 1\n-----------\n");
  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  a = initializeGame(2,cards, randomSeed, &game); // intiiliaze the game

  b = cardEffect(adventurer, 0, 0, 0, &game, 0, 0); // call cardeffect function with adventurere

  if(b == 0) // 0 means test passed 
  {
    zdi_assert(1, "Card Effect - Adventurer");
  }
  else
  {
    zdi_assert(2, "Card Effect - Adventurer");

  }

return 0;
}
