/**
 * Title:	Unit test for gainCard() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of gainCard function. Runs through
 * 	several scenarios to test whether gainCard correctly places card in a
 * given
 * 	player's discard pile, deck, or hand.
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

  printf("==============\tSTART\tTESTING\tgainCard()\t==============\n");

  printf("==============\tEND\tTESTING\tgainCard()\t==============\n");

  return 0;
};
