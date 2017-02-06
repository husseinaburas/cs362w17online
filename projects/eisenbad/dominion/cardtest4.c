/* File: cardtest4.c
   Author: Daniel Eisenbach
   Date: 2/5/17

   Description: Tests the implementation of the dominion Sea Hag action card. Sea Hag costs four coin to buy,
   and when played requires that other players discard the top card card of their deck, and then gain
   a curse card to put at the top of their deck.

   Pass Conditions:
     1. No extra coins are awarded to current player
     2. No extra actions are gained
     3. No state change occurs to victory card piles or kingdom card piles
     4. Curse supply decreases by number of opponents
     5. Other players' top of deck is added to their discard pile and replaced with curse
     6. Current player's deck is unaffected other than discard of played card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD sea_hag
#define TESTCARD_NAME "sea hag"

int main() {
  int pass_count = 0;

  // variables for comparing player's state after playing card
  int discarded = 1;
  int xtraCoins = 0;  // two extra actions should be awarded to the player
  int xtraActions = 0;

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
  // verify that no extra actions are gained
  testAssert(2, &pass_count, checkActions(2, card_state, xtraActions, G));

  /**************************************** TEST 3 ****************************************************/
  // verify that no state change occurs to victory card piles or kingdom card piles
  testAssert(3, &pass_count, checkSupplyCount(3, card_state, G));

  /**************************************** TEST 4 ****************************************************/
  printf("\n  TEST 4: Curse supply decreases by number of opponents\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(card_state[0], card_state[1], card_state[2], card_state[3], &testG, card_state[4], &card_state[5]);
	
  printf("    curse count = %d, expected = %d\n", testG.supplyCount[curse], G.supplyCount[curse] - numPlayers + 1);

  // assert test 4 passed
  testAssert(4, &pass_count, testG.supplyCount[curse] == G.supplyCount[curse] - numPlayers + 1);

  /**************************************** TEST 5 ****************************************************/
  printf("\n  TEST 5: Other players' top of deck is added to their discard pile and replaced with curse\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(card_state[0], card_state[1], card_state[2], card_state[3], &testG, card_state[4], &card_state[5]);
	
  printf("    next player's discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], 1); 
  printf("    top of next player's discard pile = %d, expected = %d\n", testG.discard[nextPlayer][testG.discardCount[nextPlayer] - 1], G.deck[nextPlayer][G.deckCount[nextPlayer] - 1]); 
  printf("    top of next player's hand = %d, expected = %d\n", testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1], curse); 

  // assert test 5 passed
  testAssert(5, &pass_count, 
      (testG.discardCount[nextPlayer] == 1) &&
      (testG.discard[nextPlayer][testG.discardCount[nextPlayer] - 1] == G.deck[nextPlayer][G.deckCount[nextPlayer] - 1]) &&
      (testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] == curse));



  /**************************************** TEST 6 ****************************************************/
  printf("\n  TEST 6: Current player's deck is unaffected other than discard of played card\n");
  int test6_pass = 1;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(card_state[0], card_state[1], card_state[2], card_state[3], &testG, card_state[4], &card_state[5]);

  // current player's deck should not change besides single discard
  printf("    current player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
  printf("    current player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);

  // assert test passed
  // compare player's current deck to stored deck (hand is drawn at start of turn, so all cards stored in deck)
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]) {test6_pass = 0; break;} 
  }

  // check that deck/hand counts didn't change
  if ((testG.handCount[thisPlayer] != 0) || (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer])) {test6_pass = 0;}

  // assert test 6 passed
  testAssert(6, &pass_count, test6_pass);

  /**************************************** END OF TESTS ****************************************************/
  if (pass_count == 6) {printf("\n >>>>> TESTS COMPLETE. SUCCESS: All %s tests passed. <<<<<\n\n", TESTCARD_NAME);}
  else {printf("\n >>>>> TESTS COMPLETE. FAILURE: Not all %s tests passed. <<<<<\n\n", TESTCARD_NAME);}

  return 0;
}
