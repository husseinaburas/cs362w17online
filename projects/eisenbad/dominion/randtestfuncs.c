/* File: randtestFuncs.c
   Author: Daniel Eisenbach
   Date: 2/16/17
  
   Description: compilation of assert functions that test various aspects 
   of the game's state after performing a card/function test.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int randCheckCoins(int testNum, int *pass_count, struct gameState G, struct gameState testG, int xtraCoins) {
  if (testG.coins - G.coins == xtraCoins) {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: %d bonus coins are awarded to the current player\n", testNum, xtraCoins);
    printf("    STATUS: TEST %d FAILED\n", testNum);
    printf("   bonus coins = %d, expected = %d\n", testG.coins - G.coins, xtraCoins);
    return 0;
  }
}

int randCheckActions(int testNum, int *pass_count, struct gameState G, struct gameState testG, int xtraActions) {
  if (testG.numActions == G.numActions + xtraActions) {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: %d extra actions are gained\n", testNum, xtraActions);
    printf("    STATUS: TEST %d FAILED\n", testNum);
    printf("    actions = %d, expected = %d\n", testG.numActions , G.numActions + xtraActions);
    return 0;
  }
}

int randCheckHandCount(int testNum, int *pass_count, struct gameState G, struct gameState testG, int xtraCards, int discarded) {
  int thisPlayer = G.whoseTurn;

  if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + xtraCards - discarded) {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: %d extra cards are gained\n", testNum, xtraCards);
    printf("    STATUS: TEST %d FAILED\n", testNum);
    printf("    handcount = %d, expected = %d\n", testG.handCount[thisPlayer] , G.handCount[thisPlayer] + xtraCards - discarded);
    return 0;
  }
}

int randCheckSupplyCount(int testNum, int *pass_count, struct gameState G, struct gameState testG) {
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
  {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: No state change occurs to the victory or kingdom card piles\n", testNum);
    printf("    STATUS: TEST %d FAILED\n", testNum);

    // victory cards
    if (testG.supplyCount[estate] != G.supplyCount[estate]) {printf("    estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);}
    if (testG.supplyCount[duchy] != G.supplyCount[duchy]) {printf("    duchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);}
    if (testG.supplyCount[province] != G.supplyCount[province]) {printf("    province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);}
   
    // kingdom cards
    if (testG.supplyCount[adventurer] != G.supplyCount[adventurer]) {printf("    adventurer count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);}
    if (testG.supplyCount[embargo] != G.supplyCount[embargo]) {printf("    embargo count = %d, expected = %d\n", testG.supplyCount[embargo], G.supplyCount[embargo]);}
    if (testG.supplyCount[village] != G.supplyCount[village]) {printf("    village count = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village]);}
    if (testG.supplyCount[minion] != G.supplyCount[minion]) {printf("    minion count = %d, expected = %d\n", testG.supplyCount[minion], G.supplyCount[minion]);}
    if (testG.supplyCount[mine] != G.supplyCount[mine]) {printf("    mine count = %d, expected = %d\n", testG.supplyCount[mine], G.supplyCount[mine]);}
    if (testG.supplyCount[cutpurse] != G.supplyCount[cutpurse]) {printf("    cutpurse count = %d, expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);}
    if (testG.supplyCount[sea_hag] != G.supplyCount[sea_hag]) {printf("    sea_hag count = %d, expected = %d\n", testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);}
    if (testG.supplyCount[tribute] != G.supplyCount[tribute]) {printf("    tribute count = %d, expected = %d\n", testG.supplyCount[tribute], G.supplyCount[tribute]);}
    if (testG.supplyCount[smithy] != G.supplyCount[smithy]) {printf("    smithy count = %d, expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);}
    if (testG.supplyCount[council_room] != G.supplyCount[council_room]) {printf("    council_room count = %d, expected = %d\n", testG.supplyCount[council_room], G.supplyCount[council_room]);}

    return 0;
  }
}

int randCheckOtherPlayerState(int testNum, int *pass_count, struct gameState G, struct gameState testG) {
  int thisPlayer = G.whoseTurn;
  int nextPlayer = thisPlayer + 1;
  int pass_check = 1;
  int card_swapped = 0;
  int i;

  // compare next player's current deck to stored deck (hand is drawn at start of turn, so all cards stored in deck)
  for (i = 0; i < G.deckCount[nextPlayer]; i++) {
    if (testG.deck[nextPlayer][i] != G.deck[nextPlayer][i]) {pass_check = 0; card_swapped = 1; break;} 
  }

  // check that deck/hand counts didn't change
  if (testG.handCount[nextPlayer] != G.handCount[nextPlayer]) {pass_check = 0;}
  if (testG.deckCount[nextPlayer] != G.deckCount[nextPlayer]) {pass_check = 0;}
	
  if (pass_check) {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: No state change occurs for other players\n", testNum);
    printf("    STATUS: TEST %d FAILED\n", testNum);

    if (card_swapped) {
      printf("    Card in next player's deck swapped.\n");
    }   

    if (testG.handCount[nextPlayer] != G.handCount[nextPlayer]) {
      printf("    next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    }

    if (testG.deckCount[nextPlayer] != G.deckCount[nextPlayer]) {
      printf("    next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    }

    return 0;
  } 
}
