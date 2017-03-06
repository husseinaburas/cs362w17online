// Micheal Willard
// CS362 - Assignment #3
// Card Test 2
// Testing:  Adventurer


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void asserttrue (int bln, char* msg) {
  if (bln) {
    printf("%s: PASS\n", msg);
  }
  else {
    printf("%s: FAIL\n", msg);
  }
}

#define TESTCARD "adventurer"

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
  //  COME BACK TO THESE
  G.hand[0][0] = adventurer;
  int handCountPre = G.handCount[0];
  printf("hand pre:  %d  ", handCountPre);
  int deckCountPre = G.deckCount[0];
  printf("deck pre:  %d\n", deckCountPre);
  // int discardCountPre = G.discardCount[0];

  //  Need Pre-play # of Treasure Cards
  int sizeOfDeck = G.handCount[0];
  int numTreasurePre = 0;
  // printf("size of player 0 deck:  %d\n", sizeOfDeck);
  for (int i = 0; i < sizeOfDeck; i++) {
    char temp = G.hand[0][i];
    if (temp == copper || temp == silver || temp == gold) {
      numTreasurePre++;
    }
  }
  printf("Number of Treasure Cards Pre: %d\n", numTreasurePre);

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


  printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);
}
