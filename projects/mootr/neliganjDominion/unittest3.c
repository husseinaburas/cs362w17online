/**
 * Title:	Unit test for handCard() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of handOver function. Runs through
 * 	several scenarios to test whether handOver correctly places card in a
 * given
 * 	player's hand in the correct hand position.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
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

  printf("==============\tSTART TESTING\thandCard()\t==============\n");

  // Copying first player's hand to compare to result of handCard
  int error = 0;
  int currentPlayerHand[5] = {0};
	int i;
  for (i = 0; i < 5; i++) {
    currentPlayerHand[i] = testState->hand[0][i];
  };
  // Checking that handCard() returns the same cards for the current player
  for (i = 0; i < 5; i++) {
    if (currentPlayerHand[i] != handCard(i, testState)) {
      error = 1;
    } else {
      continue;
    }
  };

  UNIT_ASSERT((error == 0),
              "TEST CASE:\tCheck function matches copied hand for first "
              "player\t\tRESULT:");
  // Resetting error flag
  error = 0;
  // Setting it as next player's turn, to ensure handCard() returns new players
  // cards
  testState->whoseTurn = 1;

  // Making a copy of next player's hand
  for (i = 0; i < 5; i++) {
    currentPlayerHand[i] = testState->hand[1][i];
  }
  // Checking if the hands match
  for (i = 0; i < 5; i++) {
    if (currentPlayerHand[i] != handCard(i, testState)) {
      error = 1;
    } else {
      continue;
    }
  };
  UNIT_ASSERT((error == 0),
              "TEST CASE:\tCheck function matches next player's hand "
              "after ending turn\tRESULT:");

  // Setting hand to ensure it pulls correct card at the correct position
  testState->hand[1][0] = smithy;
  testState->hand[1][1] = adventurer;
  testState->hand[1][2] = adventurer;
  testState->hand[1][3] = adventurer;
  testState->hand[1][4] = adventurer;

  UNIT_ASSERT((handCard(0, testState) != adventurer),
              "TEST CASE:\tCheck function returns correct card at 1st "
              "position out of 5\tRESULT:");
  UNIT_ASSERT((handCard(1, testState) == adventurer),
              "TEST CASE:\tCheck function returns correct card at 2nd "
              "position out of 5\tRESULT:");
  UNIT_ASSERT((handCard(2, testState) == adventurer),
              "TEST CASE:\tCheck function returns correct card at 3rd "
              "position out of 5\tRESULT:");
  UNIT_ASSERT((handCard(3, testState) == adventurer),
              "TEST CASE:\tCheck function returns correct card at 4th "
              "position out of 5\tRESULT:");
  UNIT_ASSERT((handCard(4, testState) == adventurer),
              "TEST CASE:\tCheck function returns correct card at 5th "
              "position out of 5\tRESULT:");

  printf("==============\tEND TESTING\thandCard()\t==============\n");

  return 0;
};
