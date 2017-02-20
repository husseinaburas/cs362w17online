// Micheal Willard
// CS362 - Assignment #4
// Random Card Test
// Testing:  Adventurer
// Note:  Used some code from cardtest4.c from class notes for consistency

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"
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
  srand(atoi(argv[1]));
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  int n;
  int numPlayers, curPlayer;
  int seed;
  printf("----------------- Random Testing Card: %s ----------------\n", TESTCARD);

  //  As with the example from class, we loop
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
    int discardCountPre = G.discardCount[curPlayer];
    int sizeOfDeck = G.handCount[0];
    int numTreasurePre = 0;
    // printf("size of player 0 deck:  %d\n", sizeOfDeck);
    for (int i = 0; i < sizeOfDeck; i++) {
      char temp = G.hand[0][i];
      if (temp == copper || temp == silver || temp == gold) {
        numTreasurePre++;
      }
    }
    printf("Number of Treasure Cards Pre: %d", numTreasurePre);

    cardEffect(adventurer, 0, 0, 0, &G, 0, 0);

    //  Check Postconditions
    printf("\n >>>>> Postcondition Check <<<<<\n");
    //  Player should now have 2 Treasure Cards in Deck
    int sizeOfDeckPost = G.handCount[0];
    int numTreasurePost = 0;
    // printf("size of player 0 deck:  %d\n", sizeOfDeck);
    for (int i = 0; i < sizeOfDeckPost; i++) {
      char temp = G.hand[0][i];
      if (temp == copper || temp == silver || temp == gold) {
        numTreasurePost++;
      }
    }
    printf("Number of Treasure Cards Post: %d\n", numTreasurePost);
    asserttrue(numTreasurePost == (numTreasurePre + 2), "+2 Treasure Cards?  ");
    printf(" Hand Count Post:  %d  ", G.handCount[0]);
    printf(" Deck Count Post:  %d\n", G.deckCount[0]);
    asserttrue(((G.deckCount[0] + G.handCount[0]) == (deckCountPre + handCountPre)), "Cards from deck to hand?  ");

  }
  printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);
  return 0;
}
