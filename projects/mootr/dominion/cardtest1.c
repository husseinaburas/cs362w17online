/**
 * Title:	Unit test for playSmithy() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of playSmithy card function. Runs
 *  through several scenarios to ensure playSmithy correctly draws 3 new cards
 *  into a player's hand (and the other rules of the game are followed)
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argv, char** argc) {
  struct gameState* testState = newGame();
  struct gameState* copyState = newGame();
  int kingdomCards[10] = {adventurer, gardens,  embargo, village, minion,
                          mine,       cutpurse, sea_hag, tribute, smithy};
  int randomSeed = 1000;
  int players = 3;

  initializeGame(players, kingdomCards, randomSeed, testState);
  copyState = testState;

  printf("==============\tSTART TESTING\tplaySmithy()\t==============\n");

  // Setting first card of first player's hand to be Smithy
  testState->hand[0][0] = smithy;
  // Playing smithy
  playSmithy(testState, 0);

  UNIT_ASSERT(
      (testState->hand[0][1] == -1),
      "TEST CASE:\tCheck card is no longer in hand of player\t\t\tRESULT:");
  UNIT_ASSERT((testState->handCount[0] == copyState->handCount[0] + 3),
              "TEST CASE:\tHand count has increased by 2 (1 played, 3 "
              "gained)\t\tRESULT:");

  printf("==============\tSTART TESTING\tplaySmithy()\t==============\n");
  return 0;
};
