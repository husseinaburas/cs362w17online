/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the function buyCard()
 * **********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "testhelperfunctions.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {

  //initialize gameState for testing of functions
  struct gameState *testGame;
  testGame = newGame();
  int *k;
  k = kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy);

  initializeGame(2, k, 7, testGame);

  int result, expected;

  printf("**Test Unit Functionality - buyCard()\n");

/* ----   Test 1 - Not Enough Buys ---- */
  printf("*Test 1 - Not Enough Buys\n");

  expected = -1;

  //Set numBuys to 0
  testGame->numBuys = 0;

  //Give player hand of gold
  testGame->coins = 15;

  //Buy a village - supplyPos 14 cost 3
  result = buyCard(14, testGame);

  assertTest(result, expected, 1);

/* ----   Test 2 - 10 Villages Remain ---- */
  printf("*Test 2 - 10 Villages Remain\n");

  expected = 10;

  //Set result to village supplyPos 14 count
  result = testGame->supplyCount[14];

  assertTest(result, expected, 2);

/* ----   Test 3 - Not Enough Coins ---- */
  printf("*Test 3 - Not Enough Coins\n");

  expected = -1;

  //Set numBuys to 1
  testGame->numBuys = 1;

  //Give player hand of estates
  testGame->coins = 0;

  //Buy a village - supplyPos 14 cost 3
  result = buyCard(14, testGame);

  assertTest(result, expected, 3);

/* ----   Test 4 - 10 Villages Remain ---- */
  printf("*Test 4 - 10 Villages Remain\n");

  expected = 10;

  //Set result to village supplyPos 14 count
  result = testGame->supplyCount[14];

  assertTest(result, expected, 4);

/* ----   Test 5 - Not Enough Supply ---- */
  printf("*Test 5 - Not Enough Supply\n");

  expected = -1;

  //Set numBuys to 1
  testGame->numBuys = 1;

  //Give player hand of gold
  testGame->coins = 15;

  //Set supply count to 0
  testGame->supplyCount[14] = 0;

  //Buy a village - supplyPos 14 cost 3
  result = buyCard(14, testGame);

  assertTest(result, expected, 5);

/* ----   Test 6 - 0 Villages Remain ---- */
  printf("*Test 6 - 0 Villages Remain\n");

  expected = 0;

  //Set result to village supplyPos 14 count
  result = testGame->supplyCount[14];

  assertTest(result, expected, 6);


/* ----   Test 7 - All Requirements Met ---- */
  printf("*Test 7 - All Requirements Met\n");

  expected = 0;

  //Set numBuys to 1
  testGame->numBuys = 1;

  //Give player hand of gold
  testGame->coins = 15;

  //Set supply count to 10
  testGame->supplyCount[14] = 10;

  //Buy a village - supplyPos 14 cost 3
  result = buyCard(14, testGame);

  assertTest(result, expected, 7);

/* ----   Test 8 - 9 Villages Remain ---- */
  printf("*Test 8 - 9 Villages Remain\n");

  expected = 9;

  //Set result to village supplyPos 14 count
  result = testGame->supplyCount[14];

  assertTest(result, expected, 8);

/* ----   Test 9 - 0 Buys Remain ---- */
  printf("*Test 9 - 0 Buys Remain\n");

  expected = 0;

  //Set result to village supplyPos 14 count
  result = testGame->numBuys;

  assertTest(result, expected, 9);

/* ----   Test 10 - 12 Coins Remain ---- */
  printf("*Test 10 - 12 Coins Remain\n");

  expected = 12;

  //Set result to village supplyPos 14 count
  result = testGame->coins;

  assertTest(result, expected, 10);

  printf("** Testing Complete\n\n");

  return 0;
}
