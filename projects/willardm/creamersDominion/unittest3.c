// Micheal Willard
// CS362 - Assignment #3
// Unit Test 3
// Testing:  Buy Card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "buyCard()"

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

  //  You do not have any buys left
  G.numBuys = 0;
  G.coins = 12;
  asserttrue(buyCard(2, &G) == -1, "0 buys left:  ");

  //  There are not any of that type of card left
  // G.numBuys = 5;
  // asserttrue()

  //  You do not have enough money to buy that. You have %d coins.
  G.coins = 2;
  G.numBuys = 5;
  asserttrue(buyCard(2, &G) == -1, "Not enough coins:  ");

  //  Good purchase
  G.numBuys = 5;
  G.coins = 12;
  // int temp = buyCard(2, &G);
  // printf("Good Purchase:  %d\n", temp);
  asserttrue(buyCard(2, &G) == 0, "Correct Buy:  ");

  printf("\n >>>>> Testing complete %s <<<<<\n\n", UNITTEST);
}
