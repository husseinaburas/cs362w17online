// Micheal Willard
// CS362 - Assignment #3
// Unit Test 4
// Testing:  Update Coins


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define UNITTEST "updateCoins()"

void asserttrue (int bln, char* msg) {
  if (bln) {
    printf("%s:  PASS\n", msg);
  }
  else {
    printf("%s:  FAIL\n", msg);
  }
}

int main(int argc, char **argv) {
  printf("----------------- Testing Function:  %s ----------------\n", UNITTEST);
  //  Setup a gameState Obj
  struct gameState G;

  //  int updateCoins(int player, struct gameState *state, int bonus)
  //  add coins for each Treasure card in player's hand
  //  Initialize Preconditions
  G.handCount[0] = 3;
  G.hand[0][0] = copper;
  G.hand[0][1] = silver;
  G.hand[0][2] = gold;
  updateCoins(0, &G, 0);
  asserttrue(G.coins == 6, "Testing treasure card additions:  ");
  // printf("Coins:  %d\n", G.coins);
  updateCoins(0, &G, 7);
  // printf("Coins:  %d\n", G.coins);
  asserttrue(G.coins == 13, "Testing bonus of 7 updates:  ");
  printf("\n >>>>> Testing complete %s <<<<<\n\n", UNITTEST);
}
