#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c -o unittest1 -lm -g

//ZDI assert is a function that receives a integer and a character.
// It checks if the integer is one or 2, if it is one that means the test Passed.
// If the integer is 2 it means the test failed
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
//
  struct gameState game;

  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  printf("\n*****************************\n\nUnit Test 1\n\n");
  a = initializeGame(2,cards, randomSeed, &game); // intiliaze the game with 2 playes, 10 cards, a random seed of 10 and the struct game.

  if(a == 0) // 0 means the test passed
  {
    b = zdi_assert(1, "Initializng Game");
  }
  else // otherwise the test failed
  {
    b = zdi_assert(2, "Initializng Game");
  }

  return 0;
}
