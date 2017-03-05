// Micheal Willard
// CS362 - Assignment #3
// Card Test 4
// Testing:  Village


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

void asserttrue (int bln, char* msg) {
  if (bln) {
    printf("%s: TRUE\n", msg);
  }
  else {
    printf("%s: FALSE\n", msg);
  }
}

int main(int argc, char **argv) {
  int seed = 1000;
  int numPlayers = 2;
  struct gameState G;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  //  Set Preconditions
  printf("\n >>>>> Precondition Set <<<<<\n\n");
  G.hand[0][0] = village;
  int handCountPre = G.handCount[0];
  int deckCountPre = G.deckCount[0];
  int numActionsPre = G.numActions;
  // int discardCountPre = G.discardCount[0];
  int playedCardCountPre = G.playedCardCount;

  cardEffect(village, 0, 0, 0, &G, 0, 0);

  //  Check Postconditions
  printf("\n >>>>> Postcondition Check <<<<<\n");
  //  Card was drawn, actions +2
  printf(" hand count:  %d\n", G.handCount[0]);
  asserttrue((G.handCount[0] == (handCountPre)), "Same Hand Count?  ");
  printf(" deck count:  %d\n", G.deckCount[0]);
  asserttrue((G.deckCount[0] == (deckCountPre - 1)), "1 less cards deck?  ");
  printf(" Action Count:  %d\n", G.numActions);
  asserttrue((G.numActions == (numActionsPre + 2)), "+2 Actions?  ");
  printf(" played card count:  %d\n", G.playedCardCount);
  asserttrue((G.playedCardCount == (playedCardCountPre + 1)), "Played Count");

  printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);
}
