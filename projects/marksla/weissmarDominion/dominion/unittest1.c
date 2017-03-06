/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the function updateCoins()
 * **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelperfunctions.h"

int main (int argc, char** argv) {

  //initialize gameState for testing of functions
  struct gameState *testGame;
  testGame = newGame();
  int *k;
  k = kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy);

  initializeGame(4, k, 7, testGame);

  int result, expected;

  printf("**Test Unit Functionality - updateCoins()\n");

/* ----   Test 1 - No Money Cards ---- */
  printf("*Test 1 - No Money Cards\n");
  
  expected = 0;

  // put 5 estates in the players hand
  fillPlayerHand(0, estate, 5, testGame);

  updateCoins(0, testGame, 0);

  result = testGame->coins;

  assertTest(result, expected, 1);

/* ----   Test 2 - One Copper Only ---- */
  printf("*Test 2 - One Copper Only\n");

  expected = 1;

  //put 1 copper in the players hand
  placePlayerHand(0, copper, 0, testGame);

  updateCoins(0, testGame, 0);

  result = testGame->coins;

  assertTest(result, expected, 2);

/* ----   Test 3 - Five Coppers ---- */
  printf("*Test 3 - Five Coppers\n");

  expected = 5;

  //put 5 coppers in the players hand
  fillPlayerHand(0, copper, 5, testGame);

  updateCoins(0, testGame, 0);

  result = testGame->coins;

  assertTest(result, expected, 3);

/* ----   Test 4 - One Silver Only ---- */
  printf("*Test 4 - One Silver Only\n");
  
  expected = 2;

  // put 5 estates in the players hand
  fillPlayerHand(0, estate, 5, testGame);

  //put 1 copper in the players hand
  placePlayerHand(0, silver, 0, testGame);

  updateCoins(0, testGame, 0);

  result = testGame->coins;

  assertTest(result, expected, 4);

/* ----   Test 5 - Five Silvers ---- */
  printf("*Test 5 - Five Silvers\n");

  expected = 10;

  // put 5 silvers in the players hand
  fillPlayerHand(0, silver, 5, testGame);

  updateCoins(0, testGame, 0);

  result = testGame->coins;

  assertTest(result, expected, 5);

/* ----   Test 6 - One Gold Only ---- */
  printf("*Test 6 - One Gold Only\n");
  
  expected = 3;

  // put 5 estates in the players hand
  fillPlayerHand(0, estate, 5, testGame);

  //put 1 copper in the players hand
  placePlayerHand(0, gold, 0, testGame);

  updateCoins(0, testGame, 0);

  result = testGame->coins;

  assertTest(result, expected, 6);

/* ----   Test 7 - Five Golds ---- */
  printf("*Test 7 - Five Golds\n");

  expected = 15;

  // put 5 silvers in the players hand
  fillPlayerHand(0, gold, 5, testGame);

  updateCoins(0, testGame, 0);

  result = testGame->coins;

  assertTest(result, expected, 7);

/* ----   Test 8 - Bonus Coins ---- */
  printf("*Test 8 - Bonus Coins\n");

  expected = 20;

  //put 5 estates in the players hand
  fillPlayerHand(0, estate, 5, testGame);

  updateCoins(0, testGame, 20);

  result = testGame->coins;

  assertTest(result, expected, 8);

/* ----   Test 9 - Edge Case ---- */
  printf("*Test 9 - Edge Case\n");

  expected = 1500;

  //put 500 gold in the players hand
  fillPlayerHand(0, gold, 500, testGame);

  updateCoins(0, testGame, 0);

  result = testGame->coins;

  assertTest(result, expected, 9);

  printf("** Testing Complete\n\n");

  return 0;
}

