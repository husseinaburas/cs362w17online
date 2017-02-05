// Micheal Willard
// CS362 - Assignment #3
// Unit Test 2
// Testing: isGameover


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "isGameOver()"

void asserttrue (int bln, char* msg) {
  if (bln) {
    printf("%s:  PASS\n", msg);
  }
  else {
    printf("%s:  FAIL\n", msg);
  }
}

int main(int argc, char **argv) {
  printf("----------------- Testing Function:  %s ----------------\n", UNITTEST);
  //  Setup a gameState Obj
  struct gameState G;
  //  Preconditions
  //  Pseudo-initializt the supplyCount[] variables to not be 0
  G.supplyCount[copper] = 1;
  G.supplyCount[silver] = 1;
  G.supplyCount[gold] = 1;
  G.supplyCount[province] = 1;

  printf("Treasure Empty Check\n");
  //if three supply pile are at 0, the game ends return 1 = over
  G.supplyCount[copper] = 0;
  // int temp = isGameOver(&G);
  // printf("isGameOver: %d\n", temp);
  asserttrue((isGameOver(&G) == 0), "copper = 0, game not over: ");

  G.supplyCount[silver] = 0;
  asserttrue(isGameOver(&G) == 0, "silver = 0, game not over: ");

  G.supplyCount[gold] = 0;
  asserttrue(isGameOver(&G) == 1, "gold = 0, game is over: ");

  //if stack of Province cards is empty, the game ends
  printf("Province Empty Check\n");
  G.supplyCount[gold] = 1;
  G.supplyCount[province] = 0;
  asserttrue(isGameOver(&G) == 1, "province = 0, game is over: ");
  printf("\n >>>>> Testing complete %s <<<<<\n\n", UNITTEST);
}
