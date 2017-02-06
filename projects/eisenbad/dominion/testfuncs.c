/* File: testFuncs.c
   Author: Daniel Eisenbach
   Date: 2/4/17
*/

// card_state[0] = card
// card_state[1] = choice1
// card_state[2] = choice2
// card_state[3] = choice3
// card_state[4] = handpos
// card_state[5] = bonus

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int checkCoins(int testNum, int card_state[6], int xtraCoins, struct gameState G) {
  struct gameState testG;

  printf("\n  TEST %d: %d extra coins are awarded to the current player\n", testNum, xtraCoins);

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(card_state[0], card_state[1], card_state[2], card_state[3], &testG, card_state[4], &card_state[5]);

  printf("    coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

  // assert test passed
  if (testG.coins == G.coins + xtraCoins) {return 1;}
  else {return 0;}
}

int checkActions(int testNum, int card_state[6], int xtraActions, struct gameState G) {
  struct gameState testG;

  printf("\n  TEST %d: %d extra actions are gained\n", testNum, xtraActions);

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(card_state[0], card_state[1], card_state[2], card_state[3], &testG, card_state[4], &card_state[5]);
	
  printf("    actions = %d, expected = %d\n", testG.numActions , G.numActions + xtraActions);

  // assert test passed
  if (testG.numActions == G.numActions + xtraActions) {return 1;}
  else {return 0;}
}

int checkSupplyCount(int testNum, int card_state[6], struct gameState G) {
  struct gameState testG;
	
  printf("\n  TEST %d: No state change occurs to the victory card piles or kingdom card piles\n", testNum);

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(card_state[0], card_state[1], card_state[2], card_state[3], &testG, card_state[4], &card_state[5]);
	
  // victory cards
  printf("    estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
  printf("    duchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
  printf("    province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);

  // kingdom cards
  printf("    adventurer count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
  printf("    embargo count = %d, expected = %d\n", testG.supplyCount[embargo], G.supplyCount[embargo]);
  printf("    village count = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village]);
  printf("    minion count = %d, expected = %d\n", testG.supplyCount[minion], G.supplyCount[minion]);
  printf("    mine count = %d, expected = %d\n", testG.supplyCount[mine], G.supplyCount[mine]);
  printf("    cutpurse count = %d, expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
  printf("    sea_hag count = %d, expected = %d\n", testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);
  printf("    tribute count = %d, expected = %d\n", testG.supplyCount[tribute], G.supplyCount[tribute]);
  printf("    smithy count = %d, expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);
  printf("    council_room count = %d, expected = %d\n", testG.supplyCount[council_room], G.supplyCount[council_room]);

  // assert test passed
  if ( 
      (testG.supplyCount[estate] == G.supplyCount[estate]) &&   
      (testG.supplyCount[duchy] == G.supplyCount[duchy]) &&
      (testG.supplyCount[province] == G.supplyCount[province]) &&
      (testG.supplyCount[adventurer] == G.supplyCount[adventurer]) &&
      (testG.supplyCount[embargo] == G.supplyCount[embargo]) &&
      (testG.supplyCount[village] == G.supplyCount[village]) &&
      (testG.supplyCount[minion] == G.supplyCount[minion]) &&
      (testG.supplyCount[mine] == G.supplyCount[mine]) &&
      (testG.supplyCount[cutpurse] == G.supplyCount[cutpurse]) &&
      (testG.supplyCount[sea_hag] == G.supplyCount[sea_hag]) &&
      (testG.supplyCount[tribute] == G.supplyCount[tribute]) &&
      (testG.supplyCount[smithy] == G.supplyCount[smithy]) &&
      (testG.supplyCount[council_room] == G.supplyCount[council_room]))
      {return 1;}
  else {return 0;}
}

int checkOtherPlayerState(int testNum, int card_state[6], struct gameState G) {
  struct gameState testG;
  int thisPlayer = G.whoseTurn;
  int nextPlayer = thisPlayer + 1;
  int pass_check = 1;
  int i;
	
  printf("\n  TEST %d: No state change occurs for other players\n", testNum);

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffect(card_state[0], card_state[1], card_state[2], card_state[3], &testG, card_state[4], &card_state[5]);

  // other players' decks should not change
  printf("    next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
  printf("    next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);

  // assert test passed
  // compare next player's current deck to stored deck (hand is drawn at start of turn, so all cards stored in deck)
  for (i = 0; i < G.deckCount[nextPlayer]; i++) {
    if (testG.deck[nextPlayer][i] != G.deck[nextPlayer][i]) {pass_check = 0; break;} 
  }

  // check that deck/hand counts didn't change
  if ((testG.handCount[nextPlayer] != 0) || (testG.deckCount[nextPlayer] != G.deckCount[nextPlayer])) {pass_check = 0;}
	
  return pass_check;
}
