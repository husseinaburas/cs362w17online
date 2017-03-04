// Micheal Willard
// CS362 - Assignment #4
// Random Card Test 1
// Testing:  Smithy
// Note:  Used some code from cardtest4.c from class notes for consistency

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "smithy"
#define MAX_TESTS 64
//  from dominion.h
//  #define MAX_PLAYERS = 4
//  #define MAX_HAND 500
//  #define MAX_DECK 500

void asserttrue (int bln, char* msg) {
  if (bln) {
    printf("%s: PASS\n", msg);
  }
  else {
    printf("%s: FAIL\n", msg);
  }
}

int main(int argc, char **argv) {
  // srand(time(NULL));
  printf("----------------- Random Testing Card: %s ----------------\n", TESTCARD);
  srand(atoi(argv[1]));
	// struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
  int n;
  int numPlayers, curPlayer;
  int seed;
  for (n = 0; n < MAX_TESTS; n++) {
    printf("----------------- Test Round: %d ----------------\n", n);
    struct gameState G;
    numPlayers = 0, curPlayer = 0;
    seed = 0;
    seed = rand();
    numPlayers = 2;
    curPlayer = rand() % numPlayers;
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    //  Set Preconditions
    G.handCount[curPlayer] = rand() % MAX_HAND;
    G.deckCount[curPlayer] = rand() % MAX_DECK;
    G.discardCount[curPlayer] = rand() % MAX_DECK;
    G.whoseTurn = curPlayer;
    //  Store Preconditions
    int handCountPre = G.handCount[curPlayer];
    int deckCountPre = G.deckCount[curPlayer];
    int discardCountPre = G.discardCount[curPlayer];
    int playedCardCountPre = G.playedCardCount;
    cardEffect(smithy, 0, 0, 0, &G, 0, 0);
    //  Check Postconditions
    printf("\n >>>>> Postcondition Check <<<<<\n");
    //  Player 0 should have +3, -1 more cards now
    printf(" hand count:  %d\n", G.deckCount[curPlayer]);
    asserttrue((G.handCount[curPlayer] == (handCountPre + 2)), "+3 Cards in Hand");
    printf(" deck count:  %d\n", G.deckCount[0]);
    asserttrue((G.deckCount[curPlayer] == (deckCountPre - 3)), "3 less cards deck");
    printf(" discard count:  %d\n", G.discardCount[0]);
    asserttrue((G.discardCount[curPlayer] == (discardCountPre + 1)), "Discarded");
    printf(" played card count:  %d\n", G.playedCardCount);
    asserttrue((G.playedCardCount == (playedCardCountPre + 1)), "Played Count");

  }
  printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);
  return 0;
}
