/* File: cardtest2.c
   Author: Daniel Eisenbach
   Date: 2/4/17

   Description: Tests the implementation of the dominion adventurer action card. Adventurer costs six coin to buy, 
   and when used the player will reveal cards from their deck until two treasure cards are revealed, which will
   be placed into the players hand. The remaining revealed cards are discarded.

   Pass Conditions:
     1. No extra coins are awarded to the current player
     2. No extra actions are gained
     3. No state change occurs to the victory card piles or kingdom card piles
     4. No state change occurs for other players
     5. Current player receives up to two treasures from their deck
     6. Cards revealed while searching for treasures are in the discard pile
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD adventurer
#define TESTCARD_NAME "adventurer"

int main() {
  int pass_count = 0;

  // variables for comparing player's state after playing card
  int newCards = 0;
  int discarded = 1;
  int xtraCoins = 0;
  int xtraActions = 0;
	
  int deck_treasure_count = 0;
  int rx_treasures= 0;  // number of treasure cards player should receive from deck
  int init_hand_treasure_count = 0;
  int post_hand_treasure_count = 0;

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

  /**************************************** CASE 1 ****************************************************/
  deck_treasure_count = 0;
  rx_treasures = 0;  // number of treasure cards player should receive from deck
  init_hand_treasure_count = 0;
  post_hand_treasure_count = 0;
	
  printf("\n CASE 1: No treasure cards in deck\n");
  
  // iterate through current player's deck and replace all cards with estates
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    if (G.deck[thisPlayer][i] != estate) {  // check if card is estate
      G.supplyCount[G.deck[thisPlayer][i]]++;  // increase supply count of card removed from hand
      G.deck[thisPlayer][i] = estate; G.supplyCount[estate]--;  // decrease estate supply count
    }
  }

  // count number of treasure cards in player's hand and deck before playing adventurer
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    if ((G.deck[thisPlayer][i] == copper) ||
        (G.deck[thisPlayer][i] == silver) ||
        (G.deck[thisPlayer][i] == gold))
    {deck_treasure_count++;}
  }
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if ((G.hand[thisPlayer][i] == copper) ||
        (G.hand[thisPlayer][i] == silver) ||
        (G.hand[thisPlayer][i] == gold))
    {init_hand_treasure_count++;}
  }

  // determine how many treasures player should receive from deck
  if (deck_treasure_count > 2) {rx_treasures = 2;}
  else {rx_treasures = deck_treasure_count;}

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  // TEST 1: verify that no extra coins are awarded to the current player
  testAssert(1, &pass_count, checkCoins(1, card_state, xtraCoins, G));

  // TEST 2: verify that no extra actions are gained
  testAssert(2, &pass_count, checkActions(2, card_state, xtraActions, G));

  // TEST 3: verify that no state change occurs to the victory card piles or kingdom card piles
  testAssert(3, &pass_count, checkSupplyCount(3, card_state, G));

  // TEST 4: verify that no state change occurs for other players
  testAssert(4, &pass_count, checkOtherPlayerState(4, card_state, G));
	
  // TEST 5: verify no treasures found
  printf("\n  TEST 5: Current player receives no treasures from their deck\n");
  // count number of treasure cards in player's hand after playing adventurer
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ((testG.hand[thisPlayer][i] == copper) ||
        (testG.hand[thisPlayer][i] == silver) ||
        (testG.hand[thisPlayer][i] == gold))
    {post_hand_treasure_count++;}
  }
  printf("    treasure count in hand = %d, expected = %d\n", post_hand_treasure_count, init_hand_treasure_count + rx_treasures);
  testAssert(5, &pass_count, post_hand_treasure_count == init_hand_treasure_count + rx_treasures);

  // TEST 6: verify entire deck has been discarded	
  printf("\n  TEST 6: Entire deck revealed/discarded while searching for treasures\n");
  printf("    discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.deckCount[thisPlayer]);
  testAssert(6, &pass_count, testG.discardCount[thisPlayer] == G.deckCount[thisPlayer]);

  /**************************************** CASE 2 ****************************************************/
  deck_treasure_count = 0;
  rx_treasures = 0;  // number of treasure cards player should receive from deck
  init_hand_treasure_count = 0;
  post_hand_treasure_count = 0;
	
  printf("\n CASE 2: One treasure card at bottom of deck\n");

  // iterate through current player's deck and replace all cards with estates
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    if (G.deck[thisPlayer][i] != estate) {  // check if card is estate
      G.supplyCount[G.deck[thisPlayer][i]]++;  // increase supply count of card removed from hand
      G.deck[thisPlayer][i] = estate; G.supplyCount[estate]--;  // decrease estate supply count
    }
  }

  // replace bottom of deck with a silver treasure card
  G.deck[thisPlayer][0] = silver;
  G.supplyCount[estate]++; G.supplyCount[silver]--;

  // count number of treasure cards in player's hand and deck before playing adventurer
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    if ((G.deck[thisPlayer][i] == copper) ||
        (G.deck[thisPlayer][i] == silver) ||
        (G.deck[thisPlayer][i] == gold))
    {deck_treasure_count++;}
  }
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if ((G.hand[thisPlayer][i] == copper) ||
        (G.hand[thisPlayer][i] == silver) ||
        (G.hand[thisPlayer][i] == gold))
    {init_hand_treasure_count++;}
  }

  // determine how many treasures player should receive from deck
  if (deck_treasure_count > 2) {rx_treasures = 2;}
  else {rx_treasures = deck_treasure_count;}

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  // TEST 1: verify that no extra coins are awarded to the current player
  testAssert(1, &pass_count, checkCoins(1, card_state, xtraCoins, G));

  // TEST 2: verify that no extra actions are gained
  testAssert(2, &pass_count, checkActions(2, card_state, xtraActions, G));

  // TEST 3: verify that no state change occurs to the victory card piles or kingdom card piles
  testAssert(3, &pass_count, checkSupplyCount(3, card_state, G));

  // TEST 4: verify that no state change occurs for other players
  testAssert(4, &pass_count, checkOtherPlayerState(4, card_state, G));
	
  // TEST 5: verify no treasures found	
  printf("\n  TEST 5: Current player receives one treasure from their deck\n");
  // count number of treasure cards in player's hand after playing adventurer
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ((testG.hand[thisPlayer][i] == copper) ||
        (testG.hand[thisPlayer][i] == silver) ||
        (testG.hand[thisPlayer][i] == gold))
    {post_hand_treasure_count++;}
  }
  printf("    treasure count in hand = %d, expected = %d\n", post_hand_treasure_count, init_hand_treasure_count + rx_treasures);
  testAssert(5, &pass_count, post_hand_treasure_count == init_hand_treasure_count + rx_treasures);

  // TEST 6: verify one card less than deck count has been discarded	
  printf("\n  TEST 6: One card less than deck count revealed/discarded while searching for treasures\n");
  printf("    discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.deckCount[thisPlayer] - 1);
  testAssert(6, &pass_count, testG.discardCount[thisPlayer] == G.deckCount[thisPlayer] - 1);

  /**************************************** CASE 3 ****************************************************/
  deck_treasure_count = 0;
  rx_treasures = 0;  // number of treasure cards player should receive from deck
  init_hand_treasure_count = 0;
  post_hand_treasure_count = 0;
	
  printf("\n CASE 3: Five treasure cards in deck\n");

  // iterate through current player's deck and replace all cards with copper
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    if (G.deck[thisPlayer][i] != copper) {  // check if card is copper
      G.supplyCount[G.deck[thisPlayer][i]]++;  // increase supply count of card removed from hand
      G.deck[thisPlayer][i] = copper; G.supplyCount[copper]--;  // decrease copper supply count
    }
  }

  // replace decks's second copper card with a silver treasure card
  G.deck[thisPlayer][G.deckCount[thisPlayer] - 2] = silver;
  G.supplyCount[copper]++; G.supplyCount[silver]--;

  // count number of treasure cards in player's hand and deck before playing adventurer
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    if ((G.deck[thisPlayer][i] == copper) ||
        (G.deck[thisPlayer][i] == silver) ||
        (G.deck[thisPlayer][i] == gold))
    {deck_treasure_count++;}
  }
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if ((G.hand[thisPlayer][i] == copper) ||
        (G.hand[thisPlayer][i] == silver) ||
        (G.hand[thisPlayer][i] == gold))
    {init_hand_treasure_count++;}
  }

  // determine how many treasures player should receive from deck
  if (deck_treasure_count > 2) {rx_treasures = 2;}
  else {rx_treasures = deck_treasure_count;}

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  // TEST 1: verify that no extra coins are awarded to the current player
  testAssert(1, &pass_count, checkCoins(1, card_state, xtraCoins, G));

  // TEST 2: verify that no extra actions are gained
  testAssert(2, &pass_count, checkActions(2, card_state, xtraActions, G));

  // TEST 3: verify that no state change occurs to the victory card piles or kingdom card piles
  testAssert(3, &pass_count, checkSupplyCount(3, card_state, G));

  // TEST 4: verify that no state change occurs for other players
  testAssert(4, &pass_count, checkOtherPlayerState(4, card_state, G));
	
  // TEST 5: verify no treasures found	
  printf("\n  TEST 5: Current player receives two treasures from their deck\n");	
  // count number of treasure cards in player's hand after playing adventurer
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ((testG.hand[thisPlayer][i] == copper) ||
        (testG.hand[thisPlayer][i] == silver) ||
        (testG.hand[thisPlayer][i] == gold))
    {post_hand_treasure_count++;}
  }
  printf("    treasure count in hand = %d, expected = %d\n", post_hand_treasure_count, init_hand_treasure_count + rx_treasures);
  printf("    top card in hand = %d, expected = %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1], G.deck[thisPlayer][G.deckCount[thisPlayer] - 2]);						
  testAssert(5, &pass_count, 
      (post_hand_treasure_count == init_hand_treasure_count + rx_treasures) &&
      (testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == G.deck[thisPlayer][G.deckCount[thisPlayer] - 2]));

  // TEST 6: verify no extra cards have been discarded	
  printf("\n  TEST 6: No cards revealed/discarded while searching for treasures\n");
  printf("    discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], discarded);
  testAssert(6, &pass_count, testG.discardCount[thisPlayer] == discarded);

  /**************************************** END OF TESTS ****************************************************/
  if (pass_count == 18) {printf("\n >>>>> TESTS COMPLETE. SUCCESS: All %s tests passed. <<<<<\n\n", TESTCARD_NAME);}
  else {printf("\n >>>>> TESTS COMPLETE. FAILURE: Not all %s tests passed. <<<<<\n\n", TESTCARD_NAME);}

  return 0;
}
