/**
 * Title:	Unit test for isGameOver() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of isGameOver function. Runs through
 * 	several scenarios to test whether isGameOver can properly detect that
 * the
 * 	Dominion game should end. A game ends if isGameOver return 1, otherwise,
 * it
 * 	should return 0.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.c"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.c"
#include "rngs.h"

#define UNIT_ASSERT(conditional, message) \
  if (!conditional) {                     \
    printf("%s FAIL\n", message);         \
  } else {                                \
    printf("%s PASS\n", message);         \
  }

int main(int argv, char **argc) {
  struct gameState *testState = newGame();
  int kingdomCards[10] = {adventurer, gardens,  embargo, village, minion,
                          mine,       cutpurse, sea_hag, tribute, smithy};
  int randomSeed = 1000;
  int players = 3;
  initializeGame(players, kingdomCards, randomSeed, testState);

  // Testing that game isn't over when it is started
  printf("==============\tSTART TESTING\tisGameOver()\t==============\n");
  UNIT_ASSERT(
      (isGameOver(testState) == 0),
      "TEST CASE:\tGame initialized, test that game isn't over\t\t\tRESULT:");

  // Testing that game ends when province count == 0
  int provinceCount = testState->supplyCount[province];
  testState->supplyCount[province] = 0;
  UNIT_ASSERT(
      (isGameOver(testState) == 1),
      "TEST CASE:\tSet province cards to zero, game should end\t\t\tRESULT:");

  // Reseting province count to original value
  testState->supplyCount[province] = provinceCount;

  // Testing 3 supply card piles being empty to end game
  int originalSupplyCounts[3] = {0};
  for (int i = 3; i > 0; i--) {
    originalSupplyCounts[i] = testState->supplyCount[i];
    testState->supplyCount[i] = 0;
  }
  UNIT_ASSERT(
      (isGameOver(testState) == 1),
      "TEST CASE:\t3 Supply piles empty, game should be over\t\t\tRESULT:");

  // Reset supply cards to original values
  for (int i = 3; i > 0; i--) {
    testState->supplyCount[i] = originalSupplyCounts[i];
  }

  // Both proince cards and supply scenario
  for (int i = 3; i > 0; i--) {
    testState->supplyCount[i] = 0;
  }
  testState->supplyCount[province] = 0;
  UNIT_ASSERT(
      (isGameOver(testState) == 1),
      "TEST CASE:\tBoth province empty & 3 supply piles empty\t\t\tRESULT:");

  // Reset supply piles
  for (int i = 3; i > 0; i--) {
    testState->supplyCount[i] = originalSupplyCounts[i];
  }

  // Only 2 supply piles are empty
  for (int i = 2; i > 0; i--) {
    testState->supplyCount[i] = 0;
  }
  UNIT_ASSERT(
      (isGameOver(testState) == 0),
      "TEST CASE:\tOnly 2 supply piles empty, game shouldn't end\t\t\tRESULT:");

  printf("==============\tEND TESTING\tisGameOver()\t==============\n");

  return 0;
};
