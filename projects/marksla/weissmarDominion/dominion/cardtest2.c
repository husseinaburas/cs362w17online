/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a unit test for the card Adventurer - Cost 5,
 * +2 Treasure Cards
 * **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelperfunctions.h"

int main (int argc, char** argv) {

  //Build Kindgom Selection
  int *k;
  k = kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy);

  //initialize gameState for testing of functions
  struct gameState *testGame;
  testGame = newGame();
  initializeGame(2, k, 7, testGame);

  //initialize gameState1 for testing of functions
  struct gameState *testGame1;
  testGame1 = newGame();
  initializeGame(2, k, 7, testGame1);

  int result, expected, i, oppHandCount, oppDeckCount, oppDiscardCount;

  //Save Opponent Game State
  oppHandCount = testGame->handCount[1];
  oppDeckCount = testGame->deckCount[1];
  oppDiscardCount = testGame->discardCount[1];


  //Place card in player hand
  placePlayerHand(0, adventurer, 0, testGame);
  placePlayerHand(0, adventurer, 0, testGame1);

  //Build a drawdeck gameState
  fillPlayerDeck(0, gold, 10, testGame);
  placePlayerDeck(0, estate, 0, testGame);
  placePlayerDeck(0, estate, 1, testGame);
  placePlayerDeck(0, estate, 2, testGame);
  placePlayerDeck(0, estate, 4, testGame);
  placePlayerDeck(0, estate, 5, testGame);
  placePlayerDeck(0, estate, 7, testGame);

  //Play Adventurer gameState
  playCard(0, -1, -1, -1, testGame);

  //Build a drawdeck gameState1
  fillPlayerDeck(0, estate, 10, testGame1);

  //Play Adventurer gameState1
  playCard(0, -1, -1, -1, testGame1);

  printf("**Test Card Functionality - Adventurer\n");
  printf("**Draw Deck Has Sufficient Treasure\n");

/* ----   Test 1 - 7 Cards In Hand  ---- */
  printf("*Test 1 - 6 Cards In Hand\n");
  
  expected = 6;

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

  //Set result to number of actions
  result = testGame->playedCardCount;

  assertTest(result, expected, 1);

/* ----   Test 4 - Adventurer Is In Played Pile ---- */
  printf("*Test 4 - Adventurer Is In Played Pile\n");

  expected = 1;

  //Set result to 1 if Adventurer in Played Pile
  result = 0;
  for (i = 0; i < testGame->playedCardCount; i++) {
    if (testGame->playedCards[i] == adventurer) {
      result = 1;
    } 
  }

  assertTest(result, expected, 4);

/* ----   Test 5 - Discard Pile Has 5 Cards ---- */
  printf("*Test 5 - Discard Pile Has 5 Cards\n");
  
  expected = 5;

  //Set result to number of cards in draw pile
  result = testGame->discardCount[whoseTurn(testGame)];

  assertTest(result, expected, 5);

  printf("**Draw Deck Has Insufficient Treasure\n");

/* ----   Test 6 - 4 Cards In Hand  ---- */
  printf("*Test 6 - 4 Cards In Hand\n");
  
  expected = 4;

  //Set result to number of hand cards
  result = numHandCards(testGame1);

  assertTest(result, expected, 6);

/* ----   Test 7 - Action Count is 0 ---- */
  printf("*Test 7 - Action Count is 0\n");

  expected = 0;

  //Set result to number of actions
  result = testGame1->numActions;

  assertTest(result, expected, 7);

/* ----   Test 8 - Played Pile Has 1 Card ---- */
  printf("*Test 8 - Played Pile Has 1 Card\n");

  expected = 1;

  //Set result to number of actions
  result = testGame1->playedCardCount;

  assertTest(result, expected, 8);

/* ----   Test 9 - Adventurer Is In Played Pile ---- */
  printf("*Test 9 - Adventurer Is In Played Pile\n");

  expected = 1;

  //Set result to 1 if Adventurer in Played Pile
  result = 0;
  for (i = 0; i < testGame1->playedCardCount; i++) {
    if (testGame1->playedCards[i] == adventurer) {
      result = 1;
    } 
  }

  assertTest(result, expected, 9);

/* ----   Test 10 - Discard Pile Has 10 Cards ---- */
  printf("*Test 10 - Discard Pile Has 10 Cards\n");
  
  expected = 10;

  //Set result to number of cards in draw pile
  result = testGame1->discardCount[whoseTurn(testGame1)];

  assertTest(result, expected, 10);

/* ----   Test 11 - Adventurer Cost 6 ---- */
  printf("*Test 11 - Adventurer Cost 6\n");

  expected = 6;

  //Set result to cost of Smithy
  result = getCost(adventurer);

  assertTest(result, expected, 11);

/* ----   Test 12 - Player Has 1 Buy ---- */
  printf("*Test 12 - Player Has 1 Buy\n");

  expected = 1;

  //Set result to player numBuys
  result = testGame->numBuys;

  assertTest(result, expected, 12);

/* ----   Test 13 - Opponent Has Same Hand Count ---- */
  printf("*Test 13 - Opponent Has Same Hand Count\n");

  expected = 0;

  //Set result to change in Opponent Hand Count
  result = testGame->handCount[1];
  result = result - oppHandCount;


  assertTest(result, expected, 13);

/* ----   Test 14 - Opponent Has Same Deck Count ---- */
  printf("*Test 14 - Opponent Has Same Deck Count\n");

  expected = 0;

  //Set result to change in Opponent Deck Count
  result = testGame->deckCount[1];
  result = result - oppDeckCount;


  assertTest(result, expected, 14);

/* ----   Test 15 - Opponent Has Same Discard Count ---- */
  printf("*Test 15 - Opponent Has Same Discard Count\n");

  expected = 0;

  //Set result to change in Opponent Discard Count
  result = testGame->discardCount[1];
  result = result - oppDiscardCount;


  assertTest(result, expected, 15);

  printf("** Testing Complete\n\n");

  return 0;

}

