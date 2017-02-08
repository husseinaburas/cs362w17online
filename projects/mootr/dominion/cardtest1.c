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
  struct gameState testState, copyState;
  int kingdomCards[10] = {adventurer, gardens,  embargo, village, minion,
                          mine,       cutpurse, sea_hag, tribute, smithy};
  int randomSeed = 1000;
  int players = 3;

  initializeGame(players, kingdomCards, randomSeed, &testState);
  memcpy(&copyState, &testState, sizeof(struct gameState));

  printf("==============\tSTART TESTING\tplaySmithy()\t==============\n");

  // Setting first card of first player's hand to be Smithy
  testState.hand[0][0] = smithy;
  // Playing smithy
  playSmithy(&testState, 0);

  // Checking discard count to ensure the card was not discarded
  UNIT_ASSERT((testState.discardCount[0] == 0),
              "TEST CASE:\tCheck card has not been discarded\t\t\t\tRESULT:");

  // Checking player's hand has increased by 2 (3 from drawing, played 1)
  UNIT_ASSERT((testState.handCount[0] == copyState.handCount[0] + 2),
              "TEST CASE:\tHand count has increased by 2 (1 played, 3 "
              "gained)\t\tRESULT:");

  // Card has made it into the played cards deck
  UNIT_ASSERT((testState.playedCards[0] == 13),
              "TEST CASE:\tPlayed card is in played cards deck\t\t\t\tRESULT:");

  // Player's deck has decreased by 3
  UNIT_ASSERT((testState.deckCount[0] == copyState.deckCount[0] - 3),
              "TEST CASE:\tDeck has decreased by 3 cards\t\t\t\t\tRESULT:");

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

  printf("==============\tEnd TESTING\tplaySmithy()\t==============\n");
  return 0;
};
