/**
 * Title:	Unit test for playAdventurer() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of playAdventurer card function. Runs
 *  through several scenarios to ensure playAdventurer card draws carrds until
 *  2 treasure cards have been revealed and are in the player's hand.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
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

  printf("==============\tSTART TESTING\tplayAdventurer()\t==============\n");

  // Setting first card of first player's hand to be adventurer
  testState.hand[0][0] = adventurer;
  // Playing adventurer
  playAdventurer(&testState, 0);
  updateCoins(0, &testState, 0);
  // Checking discard count to ensure the card was not discarded
  UNIT_ASSERT((testState.deckCount[0] != copyState.deckCount[0]),
              "TEST CASE:\tCheck deck count has changed\t\t\t\t\tRESULT:");

  // Checking player's hand has increased by 2 (for both treasure cards)
  UNIT_ASSERT((testState.handCount[0] == copyState.handCount[0] + 2),
              "TEST CASE:\tHand count has increased by 2\t\t\t\t\tRESULT:");

  // Card has made it into the played cards deck
  UNIT_ASSERT((testState.playedCards[0] == adventurer),
              "TEST CASE:\tPlayed card is in played cards deck\t\t\t\tRESULT:");

  //
  UNIT_ASSERT(
      (testState.deckCount[0] < copyState.deckCount[0] + 1),
      "TEST CASE:\tDeck has decreased by atleast two cards\t\t\t\tRESULT:");

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

  printf("==============\tEnd TESTING\tplayAdventurer()\t==============\n");
  return 0;
};
