// test for updateCoins()
#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "rngs.c"
#include <stdlib.h>
#include <math.h>
#include "assertresult.h"

int main() {
  struct gameState state;
  int seed = 667;
  int numPlayers = 2;
  int kingdom[10] = {adventurer, council_room, feast, gardens, mine, remodel,
    smithy, village, baron, great_hall};
  int coinCheck = 0;

  initializeGame(numPlayers, kingdom, seed, &state);

  printf("*** Unit testing updateCoins() ***\n");

//  for (int i; i < numHandCards(&state); i++) {
//    printf("card at handpos: %d \n", handCard(i, &state));
//  }
  printf("Initial hand updateCoins():\n");

  for (int i = 0; i < numHandCards(&state); i++) {
    if (state.hand[0][i] == copper) {
      coinCheck += 1;
    }
    else if (state.hand[0][i] == silver) {
      coinCheck += 2;
    }
    else if (state.hand[0][i] == gold) {
      coinCheck += 3;
    }
  }
  updateCoins(0, &state, 0);
  printf("Coins for player 1: %d \n", state.coins);
  assertResult(state.coins == coinCheck);


  // use second player since hand is empty
  printf("Empty hand updateCoins():\n");
  coinCheck = 0;
  for (int i = 0; i < numHandCards(&state); i++) {
    if (state.hand[1][i] == copper) {
      coinCheck += 1;
    }
    else if (state.hand[1][i] == silver) {
      coinCheck += 2;
    }
    else if (state.hand[1][i] == gold) {
      coinCheck += 3;
    }
  }
  updateCoins(1, &state, 0);
  printf("Coins for player 2: %d \n", state.coins);
  assertResult(state.coins == coinCheck);

  // give player 2 some treasure cards
  printf("Modified hand updateCoins():\n");
  state.hand[1][0] = copper;
  state.hand[1][1] = silver;
  state.hand[1][2] = gold;
  state.hand[1][3] = gold;
  state.hand[1][4] = copper;
  state.handCount[1] = 5;
  coinCheck = 0;

  for (int i = 0; i < numHandCards(&state); i++) {
    if (state.hand[1][i] == copper) {
      coinCheck += 1;
    }
    else if (state.hand[1][i] == silver) {
      coinCheck += 2;
    }
    else if (state.hand[1][i] == gold) {
      coinCheck += 3;
    }
  }
  updateCoins(1, &state, 0);
  printf("Coins for player 2: %d \n", state.coins);
  assertResult(state.coins == coinCheck);

  // update player 1 hand to have all non-treasure cards
  printf("No treasure card hand updateCoins():\n");
  state.hand[0][0] = baron;
  state.hand[0][1] = council_room;
  state.hand[0][2] = province;
  state.hand[0][3] = smithy;
  state.hand[0][4] = gardens;
  state.handCount[0] = 5;
  coinCheck = 0;

  for (int i = 0; i < numHandCards(&state); i++) {
    if (state.hand[0][i] == copper) {
      coinCheck += 1;
    }
    else if (state.hand[0][i] == silver) {
      coinCheck += 2;
    }
    else if (state.hand[0][i] == gold) {
      coinCheck += 3;
    }
  }
  updateCoins(0, &state, 0);
  printf("Coins for player 1: %d \n", state.coins);
  assertResult(state.coins == coinCheck);

  // update player 1 hand to have treasure and invalid number cards
  printf("Treasure and invalid cards hand updateCoins():\n");
  state.hand[0][0] = treasure_map;
  state.hand[0][1] = -1;
  state.hand[0][2] = copper;
  state.hand[0][3] = gold;
  state.hand[0][4] = silver;
  state.handCount[0] = 5;
  coinCheck = 0;

  for (int i = 0; i < numHandCards(&state); i++) {
    if (state.hand[0][i] == copper) {
      coinCheck += 1;
    }
    else if (state.hand[0][i] == silver) {
      coinCheck += 2;
    }
    else if (state.hand[0][i] == gold) {
      coinCheck += 3;
    }
  }
  updateCoins(0, &state, 0);
  printf("Coins for player 1: %d \n", state.coins);
  assertResult(state.coins == coinCheck);

  return 0;
}
