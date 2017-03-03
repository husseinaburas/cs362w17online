#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

// gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c -o unittest4 -lm -g

//ZDI assert is a function that receives a integer and a character.
// It checks if the integer is one or 2, if it is one that means the test Passed.
// If the integer is 2 it means the test failed
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

//Testing the shuffle function
int main()
{
  int a, b;
  int randomSeed = 10;

  struct gameState game;

  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  printf("Unit Test 4\n\n");
  a = initializeGame(2,cards, randomSeed, &game);

  b = shuffle(1, &game); // shuffle player one hand

  if(b == 0) // 0 means the shuffe correction worked correctly
  {
    zdi_assert(1,"Shuffle Hand");
  }
  else // shuffle function did not pass tes
  {
    zdi_assert(2, "Shuffle Handd");
  }


}
