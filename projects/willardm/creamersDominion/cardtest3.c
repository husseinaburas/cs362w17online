// Micheal Willard
// CS362 - Assignment #3
// Card Test 3
// Testing: Feast


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "feast"

void asserttrue (int bln, char* msg) {
  if (bln) {
    printf("%s: PASS\n", msg);
  }
  else {
    printf("%s: FAIL\n", msg);
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
  G.hand[0][0] = feast;
  int handCountPre = G.handCount[0];
  int deckCountPre = G.deckCount[0];
  int discardCountPre = G.discardCount[0];

  cardEffect(feast, 0, 0, 0, &G, 0, 0);

  //  Check Postconditions
  printf("\n >>>>> Postcondition Check <<<<<\n");
  //  Feast gets discarded and you get a card from the Supply
  printf(" Hand Count:  %d\n", G.handCount[0]);
  asserttrue((G.handCount[0] == (handCountPre)), "Same Hand Count?  ");
  printf(" Deck Count:  %d\n", G.deckCount[0]);
  asserttrue((G.deckCount[0] == (deckCountPre)), "Same # cards deck?  ");
  printf(" Discard Count:  %d\n", G.discardCount[0]);
  asserttrue((G.discardCount[0] == (discardCountPre + 1)), "# Discard Correct?  ");
  printf(" Discard Deck:  %d\n", G.discard[0][0]);
  asserttrue((G.discard[0][0] == (feast)), "Feast Discard?  ");

  printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);
}
