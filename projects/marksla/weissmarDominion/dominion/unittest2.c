/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the function fullDeckCount()
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

  //Setup Player Hand Deck and Discard for Testing
  fillPlayerHand(0, province, 10, testGame);

  fillPlayerDeck(0, duchy, 20, testGame);

  fillPlayerDiscard(0, estate, 20, testGame);

  placePlayerHand(0, gold, 1, testGame);
  placePlayerHand(0, gold, 2, testGame);
  placePlayerHand(0, smithy, 3, testGame);
  placePlayerHand(0, smithy, 4, testGame);
  placePlayerHand(0, smithy, 5, testGame);
  placePlayerHand(0, smithy, 6, testGame);

  placePlayerDeck(0, gold, 1, testGame);
  placePlayerDeck(0, gold, 2, testGame);
  placePlayerDeck(0, smithy, 3, testGame);
  placePlayerDeck(0, smithy, 4, testGame);
  placePlayerDeck(0, smithy, 5, testGame);
  placePlayerDeck(0, smithy, 6, testGame);

  placePlayerDiscard(0, gold, 1, testGame);
  placePlayerDiscard(0, gold, 2, testGame);
  placePlayerDiscard(0, mine, 3, testGame);
  placePlayerDiscard(0, mine, 4, testGame);
  placePlayerDiscard(0, mine, 5, testGame);
  placePlayerDiscard(0, mine, 6, testGame);

  printf("**Test Unit Functionality - fullDeckCount()\n");

/* ----   Test 1 - No Silver Cards ---- */
  printf("*Test 1 - No Silver Cards\n");
  
  expected = 0;

  result = fullDeckCount(0, silver, testGame);

  assertTest(result, expected, 1);

/* ----   Test 2 - 6 Gold Cards ---- */
  printf("*Test 2 - 6 Gold Cards\n");

  expected = 6;

  result = fullDeckCount(0, gold, testGame);

  assertTest(result, expected, 2);

/* ----   Test 3 - 8 Smithy Cards ---- */
  printf("*Test 3 - 8 Smithy Cards\n");

  expected = 8;

  result = fullDeckCount(0, smithy, testGame);

  assertTest(result, expected, 3);

/* ----   Test 4 - 4 Mine Cards ---- */
  printf("*Test 4 - 4 Mine Cards\n");
  
  expected = 4;

  result = fullDeckCount(0, mine, testGame);

  assertTest(result, expected, 4);

/* ----   Test 5 - 4 Province Cards ---- */
  printf("*Test 5 - 4 Province Cards\n");

  expected = 4;

  result = fullDeckCount(0, province, testGame);

  assertTest(result, expected, 5);

/* ----   Test 6 - 14 Duchy Cards ---- */
  printf("*Test 6 - 14 Duchy Cards\n");

  expected = 14;

  result = fullDeckCount(0, duchy, testGame);

  assertTest(result, expected, 6);

/* ----   Test 7 - 14 Estate Cards ---- */
  printf("*Test 7 - 14 Estate Cards\n");

  expected = 14;

  result = fullDeckCount(0, estate, testGame);

  assertTest(result, expected, 7);

  printf("** Testing Complete\n\n");

  return 0;
}

