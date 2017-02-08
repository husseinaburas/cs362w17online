/**
 * Title:	Unit test for playFeast() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of playFeast card function.
 * Runs through several scenarios to ensure playFeast card draws is trashed an
 * a card costing up to 5 is acquired.
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
  struct gameState testState, copyState;
  int kingdomCards[10] = {adventurer, gardens,  embargo, village, minion,
                          mine,       cutpurse, sea_hag, tribute, smithy};
  int randomSeed = 1000;
  int players = 3;

  initializeGame(players, kingdomCards, randomSeed, &testState);
  memcpy(&copyState, &testState, sizeof(struct gameState));

  printf("==============\tSTART TESTING\tplayFeast()\t==============\n");

  // Setting first card of first player's hand to be Feast rest to adventurer
  testState.hand[0][0] = feast;
  testState.hand[0][1] = adventurer;
  testState.hand[0][2] = adventurer;
  testState.hand[0][3] = adventurer;
  testState.hand[0][4] = adventurer;
  // Playing feast
  playFeast(&testState, 0, smithy);

  // Checking discard count to ensure the card was not discarded
  UNIT_ASSERT((testState.deckCount[0] == copyState.deckCount[0]),
              "TEST CASE:\tCheck deck count has not changed\t\t\t\tRESULT:");

  // Checking player's hand played one gained one
  UNIT_ASSERT((testState.handCount[0] == copyState.handCount[0]),
              "TEST CASE:\tHand count has not changed (play one, gain "
              "one)\t\t\tRESULT:");

  // Card has not made it into the played cards deck (supposed to trash it)
  UNIT_ASSERT(
      (testState.discard[0][0] != feast),
      "TEST CASE:\tPlayed card is not in played cards deck\t\t\t\tRESULT:");

  // Testing if Smithy was actually acquire using feast
  int foundSmithy = 0;
  for (int i = 0; i < 10; i++) {
    if (testState.hand[0][i] == smithy) {
      foundSmithy = 1;
    }
  }
  UNIT_ASSERT((foundSmithy == 1),
              "TEST CASE:\tSmithy was acquired using feast\t\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.playedCards[0] != smithy),
              "TEST CASE:\tSmithy is not in played cards deck\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.discard[0][0] != smithy),
              "TEST CASE:\tSmithy is not in discard cards deck\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.deckCount[1] == copyState.deckCount[1]),
              "TEST CASE:\tPlayer 2 deck count unchanged\t\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.handCount[1] == copyState.handCount[1]),
              "TEST CASE:\tPlayer 2 hand count unchanged\t\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.deckCount[2] == copyState.deckCount[2]),
              "TEST CASE:\tPlayer 3 deck count unchanged\t\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.handCount[2] == copyState.handCount[2]),
              "TEST CASE:\tPlayer 3 hand count unchanged\t\t\t\t\tRESULT:");

  UNIT_ASSERT(
      (testState.supplyCount[province] == copyState.supplyCount[province]),
      "TEST CASE:\tProvince piles have not changed\t\t\t\t\tRESULT:");

  printf("==============\tEnd TESTING\tplayFeast()\t==============\n");
  return 0;
};
