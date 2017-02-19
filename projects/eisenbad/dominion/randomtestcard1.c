/* File: randomtestcard1.c
   Author: Daniel Eisenbach
   Date: 2/16/17

   Description: Tests the implementation of the dominion village action card. Village costs three coin to buy,
   and when played gives the current player an extra card and two extra actions.

   Pass Conditions:
     1. No extra coins are awarded to current player
     2. Two extra actions are gained
     3. One extra card is drawn
     4. No state change occurs to victory or kingdom card piles
     5. No state change occurs for other players
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

int main(int argc, char *argv[]) {
  int test_cases = 6;
  int iterations = 100;
  int tests = test_cases * iterations;
  int i, testnum;
  int randcard;
  int randomseed = atoi(argv[argc - 1]);  // get random seed from user input
  srand(randomseed);  // set seed value to random seed from user unput
	
  int pass_count = 0;

  // variables for comparing player's state after playing card
  int xtraCoins = 0;  
  int xtraActions = 2;  // two extra actions should be awarded to the player
  int xtraCards = 1;  // one card should be gained from the player's deck
  int discarded = 1;  // played card should be discarded

  // initialize array storing state of card being tested
  int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
	
  int seed = 1000;  // sets the state of the current random number generator stream, bc seed > 0; used in shuffle()
  int numPlayers = 2;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize game state and player cards
  initializeGame(numPlayers, k, seed, &G);
	
  int thisPlayer = G.whoseTurn;
	
	
  printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD_NAME);

  // perform 100 random tests
  for (testnum = 0; testnum < iterations; testnum++) {
    printf("\n----------- ITERATION: %d ----------\n", testnum);
    
    // fill player's hand with random cards
    for (i = 0; i < G.handCount[thisPlayer]; i++) {
      randcard = rand() % 27;  // get random test card (range of cards is 0:26)
      G.supplyCount[G.hand[thisPlayer][G.handCount[thisPlayer] - 1 - i]]++; // restore supply of card to be removed from deck
      G.hand[thisPlayer][G.handCount[thisPlayer] - 1 - i] = randcard;  // put random card in hand position i 
      G.supplyCount[randcard]--;  // decrease supply of random card that was selected
    }

    // fill player's deck with random cards
    for (i = 0; i < G.deckCount[thisPlayer]; i++) {
      randcard = rand() % 27;  // get random test card (range of cards is 0:26)
      G.supplyCount[G.deck[thisPlayer][G.deckCount[thisPlayer] - 1 - i]]++; // restore supply of card to be removed from deck
      G.deck[thisPlayer][G.deckCount[thisPlayer] - 1 - i] = randcard;  // put random card in deck position i
      G.supplyCount[randcard]--;  // decrease supply of random card that was selected
    }

    // place testcard in random position of player's hand
    handpos = rand() % 5;  // choose random hand position for testcard (player starts with 5 cards, thus range is 0:4)
    G.supplyCount[G.hand[thisPlayer][handpos]]++; // restore supply of card to be removed from hand
    G.hand[thisPlayer][handpos] = TESTCARD;  // put test card at random handpos location in hand
    G.supplyCount[TESTCARD]--;  // decrease supply of card being tested

    // reset bonus coins to zero
    bonus = 0;
        
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(TESTCARD, choice1, choice2, choice3, &testG, handpos, &bonus);

    randCheckCoins(1, &pass_count, G, testG, xtraCoins);
    randCheckActions(2, &pass_count, G, testG, xtraActions);
    randCheckHandCount(3, &pass_count, G, testG, xtraCards, discarded);
    randCheckSupplyCount(4, &pass_count, G, testG);
    randCheckOtherPlayerState(5, &pass_count, G, testG);
    randCheckExtraCards(6, &pass_count, G, testG, xtraCards);
  }

  /**************************************** END OF TESTS ****************************************************/
  if (pass_count == tests) {printf("\n >>>>> TESTS COMPLETE. SUCCESS: All %s tests passed. <<<<<\n\n", TESTCARD_NAME);}
  else {printf("\n >>>>> TESTS COMPLETE. FAILURE: %d/%d %s tests failed. <<<<<\n\n", tests - pass_count, tests, TESTCARD_NAME);}

  return 0;
}
