// Micheal Willard
// CS362 - Assignment #4
// Random Card Test 2
// Testing:  Village
// Note:  Used some code from cardtest4.c from class notes for consistency

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "village"
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
  srand(atoi(argv[1]));
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
  int n;
  int numPlayers, curPlayer;
  int seed;
  printf("----------------- Random Testing Card: %s ----------------\n", TESTCARD);

  for (n = 0; n < MAX_TESTS; n++) {
    printf("----------------- Test Round: %d ----------------\n", n);
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
    int numActionsPre = G.numActions;
    int playedCardCountPre = G.playedCardCount;
    cardEffect(village, 0, 0, 0, &G, 0, 0);

    //  Check Postconditions
    printf("\n >>>>> Postcondition Check <<<<<\n");
    //  Card was drawn, actions +2
    printf(" hand count:  %d\n", G.handCount[curPlayer]);
    asserttrue((G.handCount[curPlayer] == (handCountPre)), "Same Hand Count?  ");
    printf(" deck count:  %d\n", G.deckCount[curPlayer]);
    asserttrue((G.deckCount[curPlayer] == (deckCountPre - 1)), "1 less cards deck?  ");
    printf(" Action Count:  %d\n", G.numActions);
    asserttrue((G.numActions == (numActionsPre + 2)), "+2 Actions?  ");
    printf(" played card count:  %d\n", G.playedCardCount);
    asserttrue((G.playedCardCount == (playedCardCountPre + 1)), "Played Count");
  }
    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);
    return 0;
}
