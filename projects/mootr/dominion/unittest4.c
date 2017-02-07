/**
 * Title:	Unit test for updateCoins() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of updateCoins function.
 *  Runs through several scenarios to test whether updateCoins
 *  correctly sets the amount of coins based on the treasure cards
 *  in a given player's hand.
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
  int playerOne = 0;
  initializeGame(players, kingdomCards, randomSeed, testState);

  printf("==============\tSTART TESTING\tupdateCoins()\t==============\n");

  // Testing copper are being properly calculated
  for (int i = 0; i < 5; i++) {
    testState->hand[playerOne][i] = copper;
  }
  updateCoins(playerOne, testState, 0);
  UNIT_ASSERT((testState->coins == 5),
              "TEST CASE:\tCheck just copper correctly "
              "calculated\t\t\t\tRESULT:");

  // Testing silver are being properly calculated
  for (int i = 0; i < 5; i++) {
    testState->hand[playerOne][i] = silver;
  }
  updateCoins(playerOne, testState, 0);
  UNIT_ASSERT((testState->coins == 10),
              "TEST CASE:\tCheck just silver correctly "
              "calculated\t\t\t\tRESULT:");

  // Testing gold are being properly calculated
  for (int i = 0; i < 5; i++) {
    testState->hand[playerOne][i] = gold;
  }
  updateCoins(playerOne, testState, 0);
  UNIT_ASSERT((testState->coins == 15),
              "TEST CASE:\tCheck just gold correctly "
              "calculated\t\t\t\tRESULT:");

  // Testing bonus is calculated correctly
  for (int i = 0; i < 5; i++) {
    testState->hand[playerOne][i] = smithy;
  }
  updateCoins(playerOne, testState, 5);
  UNIT_ASSERT((testState->coins == 5),
              "TEST CASE:\tCheck just bonus coins are correct (no "
              "treasure)\t\tRESULT:");

  // Test hand with no treasure and no bonus sets to zero coins
  for (int i = 0; i < 5; i++) {
    testState->hand[playerOne][i] = smithy;
  }
  updateCoins(playerOne, testState, 0);
  UNIT_ASSERT((testState->coins == 0),
              "TEST CASE:\tCheck coins set to zero with no treasures or "
              "bonus\t\tRESULT:");

  // Testing combinations of copper, silver, gold, and bonus
  testState->hand[playerOne][0] = copper;
  testState->hand[playerOne][1] = silver;
  testState->hand[playerOne][2] = gold;
  testState->hand[playerOne][3] = silver;
  testState->hand[playerOne][4] = gold;
  updateCoins(playerOne, testState, 4);
  UNIT_ASSERT((testState->coins == 15),
              "TEST CASE:\tCheck copper, silver, gold, and "
              "bonus in combination\t\tRESULT:");

  printf("==============\tEND TESTING\tupdateCoins()\t==============\n");

  return 0;
};
