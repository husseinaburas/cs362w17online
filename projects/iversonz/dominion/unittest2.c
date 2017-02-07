#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
// gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c -o unittest2 -lm -g
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
  int a, b, number_of_cards;
  int randomSeed = 10;
  struct gameState game;
  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

// Initialize the game
  a = initializeGame(2,cards, randomSeed, &game);

// Count the number of cards of player one
  number_of_cards = numHandCards(&game);

  printf("Unit Test 2\n\n");

  if(number_of_cards == 5)
  {
    b = zdi_assert(1, "Player 1 had 5 cards check");
  }
  else
  {
    b = zdi_assert(2, "Player 1 had 5 cards check");
  }

  return 0;
}
