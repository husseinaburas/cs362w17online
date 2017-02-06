/**
 * Title:	Unit test for handOver() function
 * Author: Richard Moot
 * Description:	Tests proper functionality of handOver function. Runs through
 * 	several scenarios to test whether handOver correctly places card in a
 * given
 * 	player's hand in the correct hand position.
 */
#include "dominion.c"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.c"
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define UNIT_ASSERT(conditional, message)                                      \
  if (!conditional) {                                                          \
    printf("%s FAIL\n", message);                                              \
  } else {                                                                     \
    printf("%s PASS\n", message);                                              \
  }

int main(int argv, char **argc) {
  struct gameState *testState = newGame();
  int kingdomCards[10] = {adventurer, gardens,  embargo, village, minion,
                          mine,       cutpurse, sea_hag, tribute, smithy};
  int randomSeed = 1000;
  int players = 3;
  initializeGame(players, kingdomCards, randomSeed, testState);

  printf("==============\tSTART\tTESTING\thandCard()\t==============\n");

  printf("==============\tEND\tTESTING\thandCard()\t==============\n");

  return 0;
};
