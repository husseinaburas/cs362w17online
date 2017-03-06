// Micheal Willard
// CS362 - Assignment #3
// Card Test 1
// Testing:  Smithy
// Note:  Used some code from cardtest4.c from class notes for consistency


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

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
  printf("\n >>>>> Precondition Set <<<<<\n");
  G.hand[0][0] = smithy;
  int handCountPre = G.handCount[0];
  int deckCountPre = G.deckCount[0];
  int discardCountPre = G.discardCount[0];
  int playedCardCountPre = G.playedCardCount;

  //  Play Card
  printf("\n >>>>> Card Played");
  cardEffect(smithy, 0, 0, 0, &G, 0, 0);
  // asserttrue((cardEffect(smithy, -1, -1, -1, &G, 0, 0) == 0), "Card Played");
  // asserttrue(playCard(0, 0, 0, 0, &G) == 0);

  //  Check Postconditions
  printf("\n >>>>> Postcondition Check <<<<<\n");
  //  Player 0 should have +3, -1 more cards now
  printf(" hand count:  %d\n", G.deckCount[0]);
  asserttrue((G.handCount[0] == (handCountPre + 2)), "+3 Cards in Hand");
  printf(" deck count:  %d\n", G.deckCount[0]);
  asserttrue((G.deckCount[0] == (deckCountPre - 3)), "3 less cards deck");
  printf(" discard count:  %d\n", G.discardCount[0]);
  asserttrue((G.discardCount[0] == (discardCountPre + 1)), "Discarded");
  printf(" played card count:  %d\n", G.playedCardCount);
  asserttrue((G.playedCardCount == (playedCardCountPre + 1)), "Played Count");

  printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

}
