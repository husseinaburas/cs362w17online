/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170219
 * Class: CS362 Software Development II
 * Description: This is a random tester of the Adventurer card from Dominion
 * **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dominion.h"
#include "testhelperfunctions.h"

int main (void) {

  int i, j;
  int thisPlayer, oppPlayer, cardUnderTest;
  int result, expected, counter;
  int *k;
  struct gameState *testGame;
  struct gameState *expectedGame;

  //set up random number generator
  srand(time(NULL)); 
  
for (j=0; j<50; j++) {
  
  //initialize gameState for testing of functions
  testGame = newGame();
  k = kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy);

  initializeGame(2, k, (rand() % 20 + 1), testGame);

  //Randomly set variables
  testGame->phase = (rand() % 3);
  testGame->numActions = (rand() % 100);
  testGame->coins = (rand() % 100);
  testGame->numBuys = (rand() % 100);
  
  //Randomize Decks and Hands for each player
  for (i=0; i<2; i++) {
    fillPlayerHandDeckDiscardRandom(i,testGame);
  }

  //Place Card Under Test in random player hand
  cardUnderTest = adventurer;
  thisPlayer = (int)(rand() % 2);

  placePlayerHand(thisPlayer, cardUnderTest, 0, testGame);

  if (thisPlayer==1) {
    oppPlayer = 0;
  } else {
    oppPlayer = 1;
  }
  testGame->whoseTurn = thisPlayer;

  //create a control gameState
  expectedGame = newGame();
  memcpy(expectedGame, testGame, sizeof(struct gameState));

  //Play Adventurer on testGame
  playCard(0, -1, -1, -1, testGame);

  //Play Control Adventurer on expectedGame
  controlPlayAdventurer(expectedGame, 0);

  printf("**Random Testing  - Adventurer\n");

/* ----   Test 1 - Player Count ---- */
  printf("*Test 1 - Player Count \n");

  expected = expectedGame->numPlayers;

  //Set result to number of players
  result = testGame->numPlayers;

  assertTest(result, expected, 1);

/* ----   Test 2 - Supply Count ---- */
  printf("*Test 2 - Supply Count \n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  for (i=0; i<27; i++) {
    if (supplyCount(i,expectedGame)!=supplyCount(i,testGame)) {
      result = 0;
    }
  }

  assertTest(result, expected, 2);

/* ----   Test 3 - Embargo Tokens ---- */
  printf("*Test 3 - Embargo Tokens \n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  for (i=0; i<27; i++) {
    if (expectedGame->embargoTokens[i]!=testGame->embargoTokens[i]) {
      result = 0;
    }
  }
  assertTest(result, expected, 3);

/* ----   Test 4 - Outpost Played ---- */
  printf("*Test 4 - Outpost Played \n");

  expected = expectedGame->outpostPlayed;

  //Set result to status of Outpost Played
  result = testGame->outpostPlayed;

  assertTest(result, expected, 4);

/* ----   Test 5 - Outpost Turn ---- */
  printf("*Test 5 - Outpost Turn \n");

  expected = expectedGame->outpostTurn;

  //Set result to number of actions
  result = testGame->outpostTurn;

  assertTest(result, expected, 5);

/* ----   Test 6 - Whose Turn ---- */
  printf("*Test 6 - Whose Turn \n");

  expected = whoseTurn(expectedGame);

  //Set result to whose turn
  result = whoseTurn(testGame);

  assertTest(result, expected, 6);

/* ----   Test 7 - Phase ---- */
  printf("*Test 7 - Phase \n");

  expected = expectedGame->phase;

  //Set result to number of actions
  result = testGame->phase;

  assertTest(result, expected, 7);

/* ----   Test 8 - Action Count  ---- */
  printf("*Test 8 - Action Count \n");

  expected = expectedGame->numActions;

  //Set result to number of actions
  result = testGame->numActions;

  assertTest(result, expected, 8);

/* ----   Test 9 - Coin Count  ---- */
  printf("*Test 9 - Coin Count \n");

  expected = expectedGame->coins;

  //Set result to number of coins
  result = testGame->coins;

  assertTest(result, expected, 9);

/* ----   Test 10 - updateCoin Count  ---- */
  printf("*Test 10 - updateCoin Count \n");

  updateCoins(thisPlayer,expectedGame,0);
  updateCoins(thisPlayer,testGame,0);
  
  expected = expectedGame->coins;

  //Set result to number of coins
  result = testGame->coins;

  assertTest(result, expected, 10);

/* ----   Test 11 - Buy Count ---- */
  printf("*Test 11 - Buy Count\n");

  expected = expectedGame->numBuys;

  //Set result to player numBuys
  result = testGame->numBuys;

  assertTest(result, expected, 11);

/* ----   Test 12 - Hand Count  ---- */
  printf("*Test 12 - Hand Count\n");
  
  expected = numHandCards(expectedGame);

  //Set result to number of hand cards
  result = numHandCards(testGame);

  assertTest(result, expected, 12);

/* ----   Test 13 - Hand Cards ---- */
  printf("*Test 13 - Hand Cards \n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  if (numHandCards(expectedGame)>numHandCards(testGame)) {
    counter = numHandCards(expectedGame);
  } else {
    counter = numHandCards(testGame);
  }

  for (i=0; i<counter; i++) {
    if (expectedGame->hand[thisPlayer][i]!=testGame->hand[thisPlayer][i]) {
      result = 0;
    }
  }
  assertTest(result, expected, 13);

/* ----   Test 14 - Deck Count  ---- */
  printf("*Test 14 - Deck Count\n");
  
  expected = expectedGame->deckCount[thisPlayer];

  //Set result to number of deck cards
  result = testGame->deckCount[thisPlayer];

  assertTest(result, expected, 14);

/* ----   Test 15 - Deck Cards ---- */
  printf("*Test 15 - Deck Cards \n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  if (expectedGame->deckCount[thisPlayer]>testGame->deckCount[thisPlayer]) {
    counter = expectedGame->deckCount[thisPlayer];
  } else {
    counter = testGame->deckCount[thisPlayer];
  }

  for (i=0; i<counter; i++) {
    if (expectedGame->deck[thisPlayer][i]!=testGame->deck[thisPlayer][i]) {
      result = 0;
    }
  }
  assertTest(result, expected, 15);

/* ----   Test 16 - Discard Count  ---- */
  printf("*Test 16 - Discard Count\n");
  
  expected = expectedGame->discardCount[thisPlayer];

  //Set result to number of discard cards
  result = testGame->discardCount[thisPlayer];

  assertTest(result, expected, 16);

/* ----   Test 17 - Discard Cards ---- */
  printf("*Test 17 - Discard Cards \n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  if (expectedGame->discardCount[thisPlayer]>testGame->discardCount[thisPlayer]) {
    counter = expectedGame->discardCount[thisPlayer];
  } else {
    counter = testGame->discardCount[thisPlayer];
  }

  for (i=0; i<counter; i++) {
    if (expectedGame->discard[thisPlayer][i]!=testGame->discard[thisPlayer][i]) {
      result = 0;
    }
  }
  assertTest(result, expected, 17);

/* ----   Test 18 - Played Count---- */
  printf("*Test 18 - Played Count\n");

  expected = expectedGame->playedCardCount;

  //Set result to cards in Played Pile
  result = testGame->playedCardCount;

  assertTest(result, expected, 18);

/* ----   Test 19 - Played Cards ---- */
  printf("*Test 19 - Played Cards \n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  if (expectedGame->playedCardCount>testGame->playedCardCount) {
    counter = expectedGame->playedCardCount;
  } else {
    counter = testGame->playedCardCount;
  }

  for (i=0; i<counter; i++) {
    if (expectedGame->playedCards[i]!=testGame->playedCards[i]) {
      result = 0;
    }
  }
  assertTest(result, expected, 19);

/* ----   Test 20 - Card Under Test Is In Played Pile ---- */
  printf("*Test 20 - Card Under Test Is In Played Pile\n");

  expected = 0;
  for (i = 0; i < expectedGame->playedCardCount; i++) {
    if (expectedGame->playedCards[i] == cardUnderTest) {
      result = 1;
    } 
  }

  //Set result to 1 if Card Under Test in Played Pile
  result = 0;
  for (i = 0; i < testGame->playedCardCount; i++) {
    if (testGame->playedCards[i] == cardUnderTest) {
      result = 1;
    } 
  }

  assertTest(result, expected, 20);

/* ----   Test 21 - Card Costs ---- */
  printf("*Test 21 - Card Costs\n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  for (i=0; i<26; i++) {
    if (getCost(i)!=getCost(i)) {
      result = 0;
    }
  }
  assertTest(result, expected, 21);

/* ----   Test 22 - Opponent Has Same Hand Count ---- */
  printf("*Test 22 - Opponent Has Same Hand Count\n");

  expected = expectedGame->handCount[oppPlayer];

  //Set result to change in Opponent Hand Count
  result = testGame->handCount[oppPlayer];

  assertTest(result, expected, 22);

/* ----   Test 23 - Opponent Hand Cards ---- */
  printf("*Test 23 - Opponent Hand Cards \n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  if (expectedGame->handCount[oppPlayer]>testGame->handCount[oppPlayer]) {
    counter = expectedGame->handCount[oppPlayer];
  } else {
    counter = testGame->handCount[oppPlayer];
  }

  for (i=0; i<counter; i++) {
    if (expectedGame->hand[oppPlayer][i]!=testGame->hand[oppPlayer][i]) {
      result = 0;
    }
  }
  assertTest(result, expected, 23);

/* ----   Test 24 - Opponent Has Same Deck Count ---- */
  printf("*Test 24 - Opponent Has Same Deck Count\n");

  expected = expectedGame->deckCount[oppPlayer];

  //Set result to change in Opponent Deck Count
  result = testGame->deckCount[oppPlayer];

  assertTest(result, expected, 24);

/* ----   Test 25 - Opponent Deck Cards ---- */
  printf("*Test 25 - Opponent Deck Cards \n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  if (expectedGame->deckCount[oppPlayer]>testGame->deckCount[oppPlayer]) {
    counter = expectedGame->deckCount[oppPlayer];
  } else {
    counter = testGame->deckCount[oppPlayer];
  }

  for (i=0; i<counter; i++) {
    if (expectedGame->deck[oppPlayer][i]!=testGame->deck[oppPlayer][i]) {
      result = 0;
    }
  }
  assertTest(result, expected, 25);

/* ----   Test 26 - Opponent Has Same Discard Count ---- */
  printf("*Test 26 - Opponent Has Same Discard Count\n");

  expected = expectedGame->discardCount[oppPlayer];

  //Set result to change in Opponent Discard Count
  result = testGame->discardCount[oppPlayer];

  assertTest(result, expected, 26);

/* ----   Test 27 - Opponent Discard Cards ---- */
  printf("*Test 27 - Opponent Discard Cards \n");

  expected = 1;

  //Set result to True then verify
  result = 1;

  if (expectedGame->discardCount[oppPlayer]>testGame->discardCount[oppPlayer]) {
    counter = expectedGame->discardCount[oppPlayer];
  } else {
    counter = testGame->discardCount[oppPlayer];
  }

  for (i=0; i<counter; i++) {
    if (expectedGame->discard[oppPlayer][i]!=testGame->discard[oppPlayer][i]) {
      result = 0;
    }
  }
  assertTest(result, expected, 27);

  printf("** Testing Complete\n\n");

  free (k);
  free (expectedGame);
  free (testGame);
}
  return 0;

}

