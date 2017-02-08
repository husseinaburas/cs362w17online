/* File: unittest1.c
   Author: Daniel Eisenbach
   Date: 2/5/17

   Description: Tests the implementation of the dominion updateCoins() function.
   This function searches through the player's hand and adds up the value of their treasure cards,
   in addition to any bonuses recieved during their turn.

   Case 1: No treasure cards in hand. No bonuses.
   Case 2: No treasure cards in hand. 4 bonus coins.
   Case 3: 1 copper, 2 silver, and 2 gold in hand. 2 bonus coins.
    
   Pass Conditions:
     1. Current player receives correct number of coins for treasure cards in hand and bonus
     2. No state change occurs to treasure card piles
     3. No state change occurs for other players
     4. Current player's hand/deck is unaffected
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "updateCoins()"

int main() {
  int pass_count = 0;
 
  int i;
  int pass_check;
  int xtraCoins = 0;
	
  int seed = 1000;  // sets the state of the current random number generator stream, bc seed > 0; used in shuffle()
  int numPlayers = 2;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize game state and player cards
  initializeGame(numPlayers, k, seed, &G);
	
  int thisPlayer = G.whoseTurn;
  int nextPlayer = thisPlayer + 1;

  printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNC);

  /**************************************** CASE 1 ****************************************************/
  printf("\n CASE 1: No treasure cards in hand, no bonus coins\n");
	
  // iterate through current player's hand and replace all cards with estates
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if (G.hand[thisPlayer][i] != estate) {  // check if card is estate
      G.supplyCount[G.hand[thisPlayer][i]]++;  // increase supply count of card removed from hand
      G.hand[thisPlayer][i] = estate; G.supplyCount[estate]--;  // decrease estate supply count
    }
  }

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  updateCoins(thisPlayer, &testG, xtraCoins);

  // TEST 1: verify player receives no coins
  printf("\n  TEST 1: Player receives no coins\n");
  printf("    coin count = %d, expected = %d\n", testG.coins, 0);  
  testAssert(1, &pass_count, testG.coins == 0);
	
  // TEST 2: verify player receives no coins
  printf("\n  TEST 2: No state change occurs to treasure card piles\n");
	
  // treasure cards
  printf("    copper count = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper]);
  printf("    silver count = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver]);
  printf("    gold count = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);
	
  // assert test 2 passed
  testAssert(2, &pass_count, 
      (testG.supplyCount[copper] == G.supplyCount[copper]) &&   
      (testG.supplyCount[silver] == G.supplyCount[silver]) &&
      (testG.supplyCount[gold] == G.supplyCount[gold]));
	
  // TEST 3: verify that no state change occurs for other players
  printf("\n  TEST 3: No state change occurs for other players\n");
  pass_check = 1;	
	
  // other players' decks should not change
  printf("    next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
  printf("    next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);

  // assert test passed
  // compare next player's current deck to stored deck (hand is drawn at start of turn, so all cards stored in deck)
  for (i = 0; i < G.deckCount[nextPlayer]; i++) {
    if (testG.deck[nextPlayer][i] != G.deck[nextPlayer][i]) {pass_check = 0; break;} 
  }

  // check that deck/hand counts didn't change
  if ((testG.handCount[nextPlayer] != G.handCount[nextPlayer]) || (testG.deckCount[nextPlayer] != G.deckCount[nextPlayer])) {pass_check = 0;}
	
  testAssert(3, &pass_count, pass_check);
	
  // TEST 4: Current player's hand/deck is unaffected
  printf("\n  TEST 4: Current player's hand/deck is unaffected\n");
  pass_check = 1;

  // current player's deck should not change
  printf("    current player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("    current player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);

  // assert test passed
  // compare player's current deck to stored deck
  for (i = 0; i < G.deckCount[thisPlayer] - 1; i++) {
    if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]) {pass_check = 0; break;} 
  }
	
  // compare player's current hand to stored hand
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if (testG.hand[thisPlayer][i] != G.hand[thisPlayer][i]) {pass_check = 0; break;} 
  }

  // check that deck/hand counts didn't change
  if ((testG.handCount[thisPlayer] != G.handCount[thisPlayer]) || (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer])) {pass_check = 0;}

  // assert test 6 passed
  testAssert(4, &pass_count, pass_check);
	
/**************************************** CASE 2 ****************************************************/
  printf("\n CASE 2: No treasure cards in hand, 4 bonus coins\n");
	
  xtraCoins = 4;
	
  // iterate through current player's hand and replace all cards with estates
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if (G.hand[thisPlayer][i] != estate) {  // check if card is estate
      G.supplyCount[G.hand[thisPlayer][i]]++;  // increase supply count of card removed from hand
      G.hand[thisPlayer][i] = estate; G.supplyCount[estate]--;  // decrease estate supply count
    }
  }

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  updateCoins(thisPlayer, &testG, xtraCoins);

  // TEST 1: verify player receives bonus coins
  printf("\n  TEST 1: Player receives 4 coins\n");
  printf("    coin count = %d, expected = %d\n", testG.coins, xtraCoins);  
  testAssert(1, &pass_count, testG.coins == xtraCoins);

  // TEST 2: verify player receives no coins
  printf("\n  TEST 2: No state change occurs to treasure card piles\n");
	
  // treasure cards
  printf("    copper count = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper]);
  printf("    silver count = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver]);
  printf("    gold count = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);
	
  // assert test 2 passed
  testAssert(2, &pass_count, 
      (testG.supplyCount[copper] == G.supplyCount[copper]) &&   
      (testG.supplyCount[silver] == G.supplyCount[silver]) &&
      (testG.supplyCount[gold] == G.supplyCount[gold]));

  // TEST 3: verify that no state change occurs for other players
  printf("\n  TEST 3: No state change occurs for other players\n");
  pass_check = 1;	
	
  // other players' decks should not change
  printf("    next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
  printf("    next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);

  // assert test passed
  // compare next player's current deck to stored deck (hand is drawn at start of turn, so all cards stored in deck)
  for (i = 0; i < G.deckCount[nextPlayer]; i++) {
    if (testG.deck[nextPlayer][i] != G.deck[nextPlayer][i]) {pass_check = 0; break;} 
  }

  // check that deck/hand counts didn't change
  if ((testG.handCount[nextPlayer] != G.handCount[nextPlayer]) || (testG.deckCount[nextPlayer] != G.deckCount[nextPlayer])) {pass_check = 0;}
	
  testAssert(3, &pass_count, pass_check);
	
  // TEST 4: Current player's hand/deck is unaffected
  printf("\n  TEST 4: Current player's hand/deck is unaffected\n");
  pass_check = 1;

  // current player's deck should not change
  printf("    current player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("    current player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);

  // assert test passed
  // compare player's current deck to stored deck
  for (i = 0; i < G.deckCount[thisPlayer] - 1; i++) {
    if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]) {pass_check = 0; break;} 
  }
	
  // compare player's current hand to stored hand
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if (testG.hand[thisPlayer][i] != G.hand[thisPlayer][i]) {pass_check = 0; break;} 
  }

  // check that deck/hand counts didn't change
  if ((testG.handCount[thisPlayer] != G.handCount[thisPlayer]) || (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer])) {pass_check = 0;}

  // assert test 6 passed
  testAssert(4, &pass_count, pass_check);
	
/**************************************** CASE 3 ****************************************************/
  printf("\n CASE 3: 1 copper, 2 silver, and 2 gold in hand, 2 bonus coins\n");
	
  xtraCoins = 2;
	
  // create player's hand: 1 copper, 2 silver, 2 gold
  if (G.hand[thisPlayer][0] != copper) {  // check if card is copper
	  G.supplyCount[G.hand[thisPlayer][0]]++;  // increase supply count of card removed from hand
	  G.hand[thisPlayer][0] = copper; G.supplyCount[copper]--;  // decrease copper supply count
  }
	  
  if (G.hand[thisPlayer][1] != silver) {  // check if card is silver
	  G.supplyCount[G.hand[thisPlayer][1]]++;  // increase supply count of card removed from hand
	  G.hand[thisPlayer][1] = silver; G.supplyCount[silver]--;  // decrease silver supply count
  }
  if (G.hand[thisPlayer][2] != silver) {  // check if card is silver
	  G.supplyCount[G.hand[thisPlayer][2]]++;  // increase supply count of card removed from hand
	  G.hand[thisPlayer][2] = silver; G.supplyCount[silver]--;  // decrease silver supply count
  }
	
  if (G.hand[thisPlayer][3] != gold) {  // check if card is gold
	  G.supplyCount[G.hand[thisPlayer][3]]++;  // increase supply count of card removed from hand
	  G.hand[thisPlayer][3] = gold; G.supplyCount[gold]--;  // decrease gold supply count
  }
  if (G.hand[thisPlayer][4] != gold) {  // check if card is gold
	  G.supplyCount[G.hand[thisPlayer][4]]++;  // increase supply count of card removed from hand
	  G.hand[thisPlayer][4] = gold; G.supplyCount[gold]--; // decrease gold supply count
  }	
	
  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  updateCoins(thisPlayer, &testG, xtraCoins);

  // TEST 1: verify player receives bonus coins
  printf("\n  TEST 1: Player receives 13 coins\n");
  printf("    coin count = %d, expected = %d\n", testG.coins, 11 + xtraCoins);  
  testAssert(1, &pass_count, testG.coins == 11 + xtraCoins);
	
  // TEST 2: verify player receives no coins
  printf("\n  TEST 2: No state change occurs to treasure card piles\n");
	
  // treasure cards
  printf("    copper count = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper]);
  printf("    silver count = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver]);
  printf("    gold count = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);
	
  // assert test 2 passed
  testAssert(2, &pass_count, 
      (testG.supplyCount[copper] == G.supplyCount[copper]) &&   
      (testG.supplyCount[silver] == G.supplyCount[silver]) &&
      (testG.supplyCount[gold] == G.supplyCount[gold]));

  // TEST 3: verify that no state change occurs for other players
  printf("\n  TEST 3: No state change occurs for other players\n");
  pass_check = 1;	
	
  // other players' decks should not change
  printf("    next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
  printf("    next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);

  // assert test passed
  // compare next player's current deck to stored deck (hand is drawn at start of turn, so all cards stored in deck)
  for (i = 0; i < G.deckCount[nextPlayer]; i++) {
    if (testG.deck[nextPlayer][i] != G.deck[nextPlayer][i]) {pass_check = 0; break;} 
  }

  // check that deck/hand counts didn't change
  if ((testG.handCount[nextPlayer] != G.handCount[nextPlayer]) || (testG.deckCount[nextPlayer] != G.deckCount[nextPlayer])) {pass_check = 0;}
	
  testAssert(3, &pass_count, pass_check);
	
  // TEST 4: Current player's hand/deck is unaffected
  printf("\n  TEST 4: Current player's hand/deck is unaffected\n");
  pass_check = 1;

  // current player's deck should not change
  printf("    current player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("    current player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);

  // assert test passed
  // compare player's current deck to stored deck
  for (i = 0; i < G.deckCount[thisPlayer] - 1; i++) {
    if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]) {pass_check = 0; break;} 
  }
	
  // compare player's current hand to stored hand
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if (testG.hand[thisPlayer][i] != G.hand[thisPlayer][i]) {pass_check = 0; break;} 
  }

  // check that deck/hand counts didn't change
  if ((testG.handCount[thisPlayer] != G.handCount[thisPlayer]) || (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer])) {pass_check = 0;}

  // assert test 6 passed
  testAssert(4, &pass_count, pass_check);
	
  /**************************************** END OF TESTS ****************************************************/
  if (pass_count == 12) {printf("\n >>>>> TESTS COMPLETE. SUCCESS: All %s tests passed. <<<<<\n\n", TESTFUNC);}
  else {printf("\n >>>>> TESTS COMPLETE. FAILURE: Not all %s tests passed. <<<<<\n\n", TESTFUNC);}

  return 0;
}
