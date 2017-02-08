/**
 * Title:	Unit test for playCouncilRoom() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of playCouncilRoom card function.
 * Runs
 *  through several scenarios to ensure playCouncilRoom card draws 4 cards and
 *  gets 1 additional buy (all other players draw 1 card as well)
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

  printf("==============\tSTART TESTING\tplayCouncilRoom()\t==============\n");

  // Setting first card of first player's hand to be Smithy
  testState.hand[0][0] = council_room;
  // Playing smithy
  playCouncilRoom(&testState, 0);

  // Checking discard count to ensure the card was not discarded
  UNIT_ASSERT((testState.deckCount[0] != copyState.deckCount[0]),
              "TEST CASE:\tCheck deck count has changed\t\t\t\t\tRESULT:");

  // Checking player's hand has increased by 3 (4 draw - 1 played)
  UNIT_ASSERT((testState.handCount[0] == copyState.handCount[0] + 3),
              "TEST CASE:\tHand count has increased by 4\t\t\t\t\tRESULT:");

  // Card has made it into the played cards deck
  UNIT_ASSERT((testState.playedCards[0] == council_room),
              "TEST CASE:\tPlayed card is in played cards deck\t\t\t\tRESULT:");

  // Checking that the deck has decreased by 4 for
  UNIT_ASSERT((testState.deckCount[0] == copyState.deckCount[0] - 4),
              "TEST CASE:\tDeck has decreased by 4 cards\t\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.numBuys == copyState.numBuys + 1),
              "TEST CASE:\tCheck number of buys increase by 1\t\t\t\tRESULT:")

  UNIT_ASSERT((testState.deckCount[1] == copyState.deckCount[1] - 1),
              "TEST CASE:\tPlayer 2 deck count decrease by 1\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.handCount[1] == copyState.handCount[1] + 1),
              "TEST CASE:\tPlayer 2 hand count increase by 1\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.deckCount[2] == copyState.deckCount[2] - 1),
              "TEST CASE:\tPlayer 3 deck count decrease by 1\t\t\t\tRESULT:");

  UNIT_ASSERT((testState.handCount[2] == copyState.handCount[2] + 1),
              "TEST CASE:\tPlayer 3 hand count increase by 1\t\t\t\tRESULT:");

  UNIT_ASSERT(
      (testState.supplyCount[province] == copyState.supplyCount[province]),
      "TEST CASE:\tProvince piles have not changed\t\t\t\t\tRESULT:");

  printf("==============\tEnd TESTING\tplayCouncilRoom()\t==============\n");
  return 0;
};
