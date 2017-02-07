/* File: unittest4.c
   Author: Daniel Eisenbach
   Date: 2/6/17

   Description: Tests the implementation of the dominion fullDeckCount() function.
   This function returns how many of a specific card a player has. Checks the
   player's  deck, hand, and discard piles.
    
   Pass Conditions:
     1. Returns quantity of a specific card owned by player
     2. Returns zero for invalid card input value
     3. Returns zero for invalid player input value
     4. No state change for player's hand, deck, or discard piles
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTFUNC "fullDeckCount()"

int main() {
  int pass_count;
  int pass_check;
  int i;
	
  int seed = 1000;  // sets the state of the current random number generator stream, bc seed > 0; used in shuffle()
  int numPlayers = 2;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize game state and player cards
  initializeGame(numPlayers, k, seed, &G);
	
  int thisPlayer = G.whoseTurn;

  printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNC);

  /**************************************** TEST 1 ****************************************************/
  printf("\n  TEST 1: Returns quantity of a specific card owned by player\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  printf("    NOTE: Putting a gold at top and bottom of hand, deck, and discard pile.\n");
  testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] = gold;  // set top of hand to gold
  testG.hand[thisPlayer][0] = gold;  // set bottom of hand to gold
  testG.deck[thisPlayer][testG.deckCount[thisPlayer] - 1] = gold;  // set top of deck to gold
  testG.deck[thisPlayer][0] = gold;  // set bottom of deck to gold
  testG.discardCount[thisPlayer] = 2;  // give player two discards
  testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1] = gold;  // set top of discard pile to gold
  testG.discard[thisPlayer][0] = gold; // set bottom of discard pile to gold
  
  printf("    gold cards owned = %d, expected = %d\n", fullDeckCount(thisPlayer, gold, &testG), 6);
  testAssert(1, &pass_count, fullDeckCount(thisPlayer, gold, &testG) == 6);

  /**************************************** TEST 2 ****************************************************/
  printf("\n  TEST 2: Returns zero for invalid card value input\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  // Max card value = 26, testing with 1000 should return 0
  printf("    NOTE: Calling %s with card input = 1000 \n", TESTFUNC);
  printf("    *1000* cards owned = %d, expected = %d\n", fullDeckCount(thisPlayer, 1000, &testG), 0);
  testAssert(2, &pass_count, fullDeckCount(thisPlayer, 1000, &testG) == 0);

  /**************************************** TEST 3 ****************************************************/
  printf("\n  TEST 3: Returns zero for invalid player input value\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  // Max card value = 26, testing with 1000 should return 0
  printf("    NOTE: Calling %s with player input = 50, and card input = copper\n", TESTFUNC);
  printf("    copper cards owned by player 50 = %d, expected = %d\n", fullDeckCount(50, copper, &testG), 0);
  testAssert(3, &pass_count, fullDeckCount(50, copper, &testG) == 0);

  /**************************************** TEST 4 ****************************************************/
  printf("\n  TEST 4: No state change for player's hand, deck, or discard piles\n");
  pass_check = 1;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  printf("    NOTE: Calling %s with card input = copper\n", TESTFUNC);

  // game setup gives each player seven copper
  int copper_owned = fullDeckCount(thisPlayer, copper, &testG);
  printf("    copper cards owned = %d, expected = %d\n", copper_owned, 7);

  // player's hand, deck and discard piles should not have changed after calling fullDeckCount()
  printf("    current player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("    current player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  printf("    current player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);

  // assert test passed
  // compare player's current deck to stored deck
  for (i = 0; i < G.discardCount[thisPlayer]; i++) {
    if (testG.discard[thisPlayer][i] != G.discard[thisPlayer][i]) {pass_check = 0; break;} 
  }

  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]) {pass_check = 0; break;} 
  }
	
  // compare player's current hand to stored hand
  for (i = 1; i < G.handCount[thisPlayer]; i++) {
    if (testG.hand[thisPlayer][i] != G.hand[thisPlayer][i]) {pass_check = 0; break;} 
  }

  // check that deck/hand counts didn't change
  if (
      (testG.handCount[thisPlayer] != G.handCount[thisPlayer]) ||
      (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer]) ||
      (testG.discardCount[thisPlayer] != G.discardCount[thisPlayer])) 
    {pass_check = 0;}

  // assert test 6 passed
  testAssert(4, &pass_count, pass_check);

  /**************************************** END OF TESTS ****************************************************/
  if (pass_count == 4) {printf("\n >>>>> TESTS COMPLETE. SUCCESS: All %s tests passed. <<<<<\n\n", TESTFUNC);}
  else {printf("\n >>>>> TESTS COMPLETE. FAILURE: Not all %s tests passed. <<<<<\n\n", TESTFUNC);}		 
	
  return 0;	
}	
