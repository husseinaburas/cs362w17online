/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the card Council Room - Cost 5,
 * + 4 Cards, + 1 Buy, all others players +1 Card
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

  initializeGame(2, k, 7, testGame);

  int result, expected, oppHandCount, oppDeckCount, oppDiscardCount;

  //Place card in player hand
  placePlayerHand(0, council_room, 0, testGame);

  //Save Opponent Game State
  oppHandCount = testGame->handCount[1];
  oppDeckCount = testGame->deckCount[1];
  oppDiscardCount = testGame->discardCount[1];

  //Play Council Room
  playCard(0, -1, -1, -1, testGame);
  printf("**Test Card Functionality - Council Room\n");

/* ----   Test 1 - 8 Cards In Hand  ---- */
  printf("*Test 1 - 8 Cards In Hand\n");
  
  expected = 8;

  //Set result to number of hand cards
  result = numHandCards(testGame);

  assertTest(result, expected, 1);

/* ----   Test 2 - Action Count is 0 ---- */
  printf("*Test 2 - Action Count is 0\n");

  expected = 0;

  //Set result to number of actions
  result = testGame->numActions;

  assertTest(result, expected, 2);

/* ----   Test 3 - Played Pile Has 1 Card ---- */
  printf("*Test 3 - Played Pile Has 1 Card\n");

  expected = 1;

  //Set result to cards in Played Pile
  result = testGame->playedCardCount;

  assertTest(result, expected, 3);

/* ----   Test 4 - Council Room Is In Played Pile ---- */
  printf("*Test 4 - Council Room Is In Played Pile\n");

  expected = 1;

  //Set result to 1 if Council Room in Played Pile
  result = 0;
  int i;
  for (i = 0; i < testGame->playedCardCount; i++) {
    if (testGame->playedCards[i] == council_room) {
      result = 1;
    } 
  }

  assertTest(result, expected, 4);

/* ----   Test 5 - Draw Pile Has 1 Card ---- */
  printf("*Test 5 - Draw Pile Has 1 Card\n");
  
  expected = 1;

  //Set result to number of cards in draw pile
  result = testGame->deckCount[whoseTurn(testGame)];

  assertTest(result, expected, 5);

/* ----   Test 6 - Council Room Cost 5 ---- */
  printf("*Test 6 - Council Room Cost 5\n");

  expected = 5;

  //Set result to cost of Smithy
  result = getCost(council_room);

  assertTest(result, expected, 6);

/* ----   Test 7 - Player Has 2 Buy ---- */
  printf("*Test 7 - Player Has 2 Buy\n");

  expected = 2;

  //Set result to player numBuys
  result = testGame->numBuys;

  assertTest(result, expected, 7);

/* ----   Test 8 - Opponent Has +1 Hand Count ---- */
  printf("*Test 8 - Opponent Has +1 Hand Count\n");

  expected = 1;

  //Set result to change in Opponent Hand Count
  result = testGame->handCount[1];
  result = result - oppHandCount;


  assertTest(result, expected, 8);

/* ----   Test 9 - Opponent Has -1 Deck Count ---- */
  printf("*Test 9 - Opponent Has -1 Deck Count\n");

  expected = -1;

  //Set result to change in Opponent Deck Count
  result = testGame->deckCount[1];
  result = result - oppDeckCount;


  assertTest(result, expected, 9);

/* ----   Test 10 - Opponent Has Same Discard Count ---- */
  printf("*Test 10 - Opponent Has Same Discard Count\n");

  expected = 0;

  //Set result to change in Opponent Discard Count
  result = testGame->discardCount[1];
  result = result - oppDiscardCount;


  assertTest(result, expected, 10);

  printf("** Testing Complete\n\n");

  return 0;

}

