/* File: cardtest1.c
   Author: Daniel Eisenbach
   Date: 2/3/17

   Description: Tests the implementation of the dominion smithy action card. Smithy costs four coin to buy, 
   and when played lets the player draw three additional cards from the top of their deck into their hand.

   Pass Conditions:
     1. No extra coins are awarded to the current player
     2. Two extra actions are gained
     3. No state change occurs to the victory card piles or kingdom card piles
     4. No state change occurs for other players
     5. Current player receives exactly 1 card
     6. Extra card comes from player's own deck
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD village
#define TESTCARD_NAME "village"

int main() {
  int pass_count = 0;

  // variables for comparing player's state after playing card
  int newCards = 1;
  int discarded = 1;
  int xtraCoins = 0;  // two extra actions should be awarded to the player
  int xtraActions = 2;

  // initialize array storing state of card being tested
  int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
  card_state[0] = TESTCARD; card_state[1] = choice1; card_state[2] = choice2;
  card_state[3] = choice3; card_state[4] = handpos; card_state[5] = bonus;
	
  int i;
  int seed = 1000;  // sets the state of the current random number generator stream, bc seed > 0; used in shuffle()
  int numPlayers = 2;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize game state and player cards
  initializeGame(numPlayers, k, seed, &G);
	
  int thisPlayer = G.whoseTurn;
  int nextPlayer = thisPlayer + 1;
	
  // put testcard in 0th position of player's hand
  G.supplyCount[G.hand[thisPlayer][0]]++; // restore supply of card to be removed from hand
  G.hand[thisPlayer][0] = TESTCARD;  // put test card at bottom of hand
  G.supplyCount[TESTCARD]--;  // decrease supply of card being tested
	
  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD_NAME);

  // put a council_room card at the top of the current player's deck
  G.supplyCount[G.deck[thisPlayer][G.deckCount[thisPlayer] - 1]]++; // restore supply of card to be removed from deck
  G.deck[thisPlayer][G.deckCount[thisPlayer] - 1] = council_room;  // put council_room card at top of deck
  G.supplyCount[council_room]--;  // decrease council_room supply
	
  /**************************************** TEST 1 ****************************************************/
  // verify that no extra coins are awarded to the current player
  testAssert(1, &pass_count, checkCoins(1, card_state, xtraCoins, G));

  /**************************************** TEST 2 ****************************************************/
  // verify that two extra actions are gained
  testAssert(2, &pass_count, checkActions(2, card_state, xtraActions, G));

  /**************************************** TEST 3 ****************************************************/
  // verify that no state change occurs to the victory card piles or kingdom card piles
  testAssert(3, &pass_count, checkSupplyCount(3, card_state, G));

  /**************************************** TEST 4 ****************************************************/
  // verify that no state change occurs for other players
  testAssert(4, &pass_count, checkOtherPlayerState(4, card_state, G));
	
  /**************************************** TEST 5 ****************************************************/
  printf("\n  TEST 5: Current player receives exactly one card\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(card_state[0], card_state[1], card_state[2], card_state[3], &testG, card_state[4], &card_state[5]);

  printf("    hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);

  // assert test 5 passed
  testAssert(5, &pass_count, (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded));

  /**************************************** TEST 6 ****************************************************/
  printf("\n  TEST 6: Extra card comes from player's own pile\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(card_state[0], card_state[1], card_state[2], card_state[3], &testG, card_state[4], &card_state[5]);

  printf("    top card in hand = %d, expected = %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1], G.deck[thisPlayer][G.deckCount[thisPlayer] - 1]);

  // assert test 6 passed
  testAssert(6, &pass_count, testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == G.deck[thisPlayer][G.deckCount[thisPlayer] - 1]);

  /**************************************** END OF TESTS ****************************************************/
  if (pass_count == 6) {printf("\n >>>>> TESTS COMPLETE. SUCCESS: All %s tests passed. <<<<<\n\n", TESTCARD_NAME);}
  else {printf("\n >>>>> TESTS COMPLETE. FAILURE: Not all %s tests passed. <<<<<\n\n", TESTCARD_NAME);}

  return 0;
}
