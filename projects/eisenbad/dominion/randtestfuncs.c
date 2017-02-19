/* File: randtestFuncs.c
   Author: Daniel Eisenbach
   Date: 2/18/17
  
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

// verify correct number of extra coins are awarded to current player
int randCheckCoins(int testNum, int *pass_count, struct gameState G, struct gameState testG, int xtraCoins) {
  if (testG.coins - G.coins == xtraCoins) {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: %d bonus coin/s awarded to the current player\n", testNum, xtraCoins);
    printf("    STATUS: TEST %d FAILED\n", testNum);
    printf("   bonus coins = %d, expected = %d\n", testG.coins - G.coins, xtraCoins);
    return 0;
  }
}

// verify correct number of extra actions are gained
int randCheckActions(int testNum, int *pass_count, struct gameState G, struct gameState testG, int xtraActions) {
  if (testG.numActions == G.numActions + xtraActions) {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: %d extra action/s gained\n", testNum, xtraActions);
    printf("    STATUS: TEST %d FAILED\n", testNum);
    printf("    actions = %d, expected = %d\n", testG.numActions , G.numActions + xtraActions);
    return 0;
  }
}

// verify correct number of extra cards are drawn
int randCheckHandCount(int testNum, int *pass_count, struct gameState G, struct gameState testG, int xtraCards, int discarded) {
  int thisPlayer = G.whoseTurn;

  if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + xtraCards - discarded) {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: %d extra card/s gained\n", testNum, xtraCards);
    printf("    STATUS: TEST %d FAILED\n", testNum);
    printf("    hand count = %d, expected = %d\n", testG.handCount[thisPlayer] , G.handCount[thisPlayer] + xtraCards - discarded);
    return 0;
  }
}

// verify correct number of cards are discarded
int randCheckDiscardCount(int testNum, int *pass_count, struct gameState G, struct gameState testG, int discarded) {
  int thisPlayer = G.whoseTurn;

  if (testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded) {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: %d card/s discarded\n", testNum, discarded);
    printf("    STATUS: TEST %d FAILED\n", testNum);
    printf("    discard count = %d, expected = %d\n", testG.discardCount[thisPlayer] , G.discardCount[thisPlayer] + discarded);
    return 0;
  }
}

// verify that no state change occurs to victory or kingdom card piles
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

// verify that no state change occurs for other players
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

// verify that extra cards drawn come from player's own deck
int randCheckExtraCards(int testNum, int *pass_count, struct gameState G, struct gameState testG, int xtraCards) {
  int thisPlayer = G.whoseTurn;
  int pass_check = 1;
  int i;

  for (i = 0; i < xtraCards; i++) {
    if (testG.hand[thisPlayer][testG.handCount[thisPlayer] - xtraCards + i] !=  G.deck[thisPlayer][G.deckCount[thisPlayer] - 1 - i]) {pass_check = 0;}
  }

  if (pass_check) {
    *pass_count = *pass_count + 1;     
    return 1;
  }
  else {
    printf("\n  TEST %d: Extra cards come from player's own deck\n", testNum);
    printf("    STATUS: TEST %d FAILED\n", testNum);

    for (i = 0; i < xtraCards; i++) {   
      if (testG.hand[thisPlayer][testG.handCount[thisPlayer] - xtraCards + i] !=  G.deck[thisPlayer][G.deckCount[thisPlayer] - 1 - i]) {
        printf("    card %d in hand = %d, expected = %d\n", i, testG.hand[thisPlayer][testG.handCount[thisPlayer] - xtraCards + i], G.deck[thisPlayer][G.deckCount[thisPlayer] - 1 - i]);
      }
    }
    return 0;
  }
}

// verify that the current player receives up to two treasures from their deck after playing adventurer (adventurer specific test function)
int randCheckExtraTreasures(int testNum, int *pass_count, struct gameState G, struct gameState testG, int *xtraCards, int *discard_pile_count) {
  int thisPlayer = G.whoseTurn;
  int pass_check = 1;
  int i;
  int init_hand_treasure_count = 0;
  int post_hand_treasure_count = 0;
  int init_deck_treasure_count = 0;
  int post_deck_treasure_count = 0;
  int rx_treasures = 0;
  int xtraDiscards = 0;

  // count initial number of treasure cards in player's hand
  for (i = 0; i < G.handCount[thisPlayer]; i++) {
    if ((G.hand[thisPlayer][i] == copper) ||
        (G.hand[thisPlayer][i] == silver) ||
        (G.hand[thisPlayer][i] == gold))
    {init_hand_treasure_count++;}
  }

  // count post number of treasure cards in player's hand
  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
    if ((testG.hand[thisPlayer][i] == copper) ||
        (testG.hand[thisPlayer][i] == silver) ||
        (testG.hand[thisPlayer][i] == gold))
    {post_hand_treasure_count++;}
  }

  // count initial number of treasure cards in player's deck, and number of cards to be discarded
  for (i = 0; i < G.deckCount[thisPlayer]; i++) {
    if ((G.deck[thisPlayer][i] == copper) ||
        (G.deck[thisPlayer][i] == silver) ||
        (G.deck[thisPlayer][i] == gold))
    {init_deck_treasure_count++;}
    else {
      if (init_deck_treasure_count < 2) {xtraDiscards++;}  // track how many cards are revealed before two treasures are found
    }
  }

  // count post number of treasure cards in player's deck
  for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
    if ((testG.deck[thisPlayer][i] == copper) ||
        (testG.deck[thisPlayer][i] == silver) ||
        (testG.deck[thisPlayer][i] == gold))
    {post_deck_treasure_count++;}
  }

  // flag how many cards should be discarded after playing adventurer
  *discard_pile_count = *discard_pile_count + xtraDiscards;

  // determine how many treasures player should receive from deck
  if (init_deck_treasure_count > 2) {rx_treasures = 2;}
  else {rx_treasures = init_deck_treasure_count;}
  *xtraCards = rx_treasures;  // flag how many extra cards should end up in player's hand

  if (post_hand_treasure_count != init_hand_treasure_count + rx_treasures) {pass_check = 0;}
  if (post_deck_treasure_count != init_deck_treasure_count - rx_treasures) {pass_check = 0;}

  if (pass_check) {
    *pass_count = *pass_count + 1;
    return 1;
  }
  else {
    printf("\n  TEST %d: Current player receives up to two treasures from their deck\n", testNum);
    printf("    STATUS: TEST %d FAILED\n", testNum);

    if (post_hand_treasure_count != init_hand_treasure_count + rx_treasures) {
      printf("    received treasures = %d, expected = %d\n", post_hand_treasure_count - init_hand_treasure_count, init_hand_treasure_count + rx_treasures); 
    }

    if (post_deck_treasure_count != init_deck_treasure_count - rx_treasures) {
      printf("    deck treasure count = %d, expected = %d\n", post_deck_treasure_count, init_deck_treasure_count - rx_treasures); 
    }
      
   return 0; 
  }
}
