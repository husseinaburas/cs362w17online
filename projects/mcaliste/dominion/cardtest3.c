//cardtest3.c - steward

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include "assertresult.h"

int main() {
  struct gameState state, state2, state3;
  int seed = 667;
  int numPlayers = 2;
  int kingdom[10] = {adventurer, council_room, steward, gardens, mine, remodel,
    smithy, village, baron, great_hall};
  int result, currentPlayer, actions, oldHandCount, oldDeckCount, oldCoinCount;

  printf("*** Unit testing stewardCard() ***\n");
  result = initializeGame(numPlayers, kingdom, seed, &state);

  printf("Test game is initialized:\n");
  assertResult(result == 0);

  printf("Test player 1 is current player:\n");
  currentPlayer = whoseTurn(&state);
  assertResult(currentPlayer == 0);

  printf("Test action count:\n");
  actions = state.numActions;
  assertResult(actions > 0);

  printf("Test steward in player hand:\n");
  // steward is 13 in cards enum
  state.hand[currentPlayer][4] = steward;
  state.hand[currentPlayer][0] = smithy;
  state.hand[currentPlayer][1] = gardens;
  state.hand[currentPlayer][2] = remodel;
  state.hand[currentPlayer][3] = village;
  assertResult(handCard(4, &state) == 18);

  oldDeckCount = state.deckCount[currentPlayer];
  oldHandCount = numHandCards(&state);
  oldCoinCount = 0;
  memcpy(&state2, &state, sizeof(struct gameState));
  memcpy(&state3, &state, sizeof(struct gameState));

  // conditional for choice1 has been broken by assignment 2
  // choice1 = 1 will give both +2 cards and +2 coins
  printf("*** Test playing steward card, choice1 = 1:\n");
  result = playCard(4, 1, 0, 0, &state);

  //+2 cards from deck into hand
  // steward actually discards when done, so it's +1 cards in hand
  printf("Player hand has +2 cards:\n");
  assertResult((oldHandCount + 1) == numHandCards(&state));
  //printf("New hand count %d\n", numHandCards(&state));

  printf("Player deck has -2 cards:\n");
  assertResult((oldDeckCount - 2) == state.deckCount[currentPlayer]);

  //chose to draw 2 cards, this should be the same as before
  //bug introduced in assignment 2 has broken this
  printf("Player coins are unchanged:\n");
  assertResult(oldCoinCount == state.coins);
  //printf("old player coins: %d\n", oldCoinCount);
  //printf("new player coins: %d\n", state.coins);

  printf("Test victory card count is unchanged:\n");
  assertResult(supplyCount(estate, &state) == 8);
  assertResult(supplyCount(duchy, &state) == 8);
  assertResult(supplyCount(province, &state) == 8);

  printf("Test kingdom card count is unchanged:\n");
  assertResult(supplyCount(council_room, &state) == 10);
  assertResult(supplyCount(steward, &state) == 10);
  assertResult(supplyCount(smithy, &state) == 10);
  assertResult(supplyCount(gardens, &state) == 8);
  assertResult(supplyCount(mine, &state) == 10);
  assertResult(supplyCount(remodel, &state) == 10);
  assertResult(supplyCount(adventurer, &state) == 10);
  assertResult(supplyCount(village, &state) == 10);
  assertResult(supplyCount(baron, &state) == 10);
  assertResult(supplyCount(great_hall, &state) == 8);

  //+2 coins
  //conditional for choice 1 has been broken by assignment 2
  // choice 1 = 2 will not execute since it does not exist
  // instead, cards will be trashed
  oldDeckCount = state2.deckCount[currentPlayer];
  oldHandCount = numHandCards(&state2);
  oldCoinCount = 0;
  printf("*** Test playing steward card, choice1 = 2:\n");
  result = playCard(4, 2, 0, 0, &state2);

  // steward is discarded after play, so should be same -1
  printf("Player hand has same number of cards:\n");
  assertResult(oldHandCount-1 == numHandCards(&state2));

  printf("Player deck has same number of cards:\n");
  assertResult(oldDeckCount == state2.deckCount[currentPlayer]);

  printf("Player coins are unchanged:\n");
  assertResult(oldCoinCount == state2.coins);
  //printf("old player coins: %d\n", oldCoinCount);
  //printf("new player coins: %d\n", state2.coins);

  printf("Test victory card count is unchanged:\n");
  assertResult(supplyCount(estate, &state) == 8);
  assertResult(supplyCount(duchy, &state) == 8);
  assertResult(supplyCount(province, &state) == 8);

  printf("Test kingdom card count is unchanged:\n");
  assertResult(supplyCount(council_room, &state) == 10);
  assertResult(supplyCount(steward, &state) == 10);
  assertResult(supplyCount(smithy, &state) == 10);
  assertResult(supplyCount(gardens, &state) == 8);
  assertResult(supplyCount(mine, &state) == 10);
  assertResult(supplyCount(remodel, &state) == 10);
  assertResult(supplyCount(adventurer, &state) == 10);
  assertResult(supplyCount(village, &state) == 10);
  assertResult(supplyCount(baron, &state) == 10);
  assertResult(supplyCount(great_hall, &state) == 8);


  //trash two cards from hand
  oldDeckCount = state3.deckCount[currentPlayer];
  oldHandCount = numHandCards(&state3);
  oldCoinCount = 0;
  printf("*** Test playing steward card, choice1 = 0, choice2, choice3:\n");
  result = playCard(4, 0, 1, 3, &state3);

  // steward is discarded after play, so should be -3
  printf("Player hand has -2 cards:\n");
  assertResult(oldHandCount-3 == numHandCards(&state3));

  printf("Player deck has same number of cards:\n");
  assertResult(oldDeckCount == state3.deckCount[currentPlayer]);

  printf("Player coins are unchanged:\n");
  assertResult(oldCoinCount == state3.coins);

  printf("Test victory card count is unchanged:\n");
  assertResult(supplyCount(estate, &state) == 8);
  assertResult(supplyCount(duchy, &state) == 8);
  assertResult(supplyCount(province, &state) == 8);

  printf("Test kingdom card count is unchanged:\n");
  assertResult(supplyCount(council_room, &state) == 10);
  assertResult(supplyCount(steward, &state) == 10);
  assertResult(supplyCount(smithy, &state) == 10);
  assertResult(supplyCount(gardens, &state) == 8);
  assertResult(supplyCount(mine, &state) == 10);
  assertResult(supplyCount(remodel, &state) == 10);
  assertResult(supplyCount(adventurer, &state) == 10);
  assertResult(supplyCount(village, &state) == 10);
  assertResult(supplyCount(baron, &state) == 10);
  assertResult(supplyCount(great_hall, &state) == 8);

  printf("Player hand no longer has card choice2:\n");
  assertResult(handCard(1, &state3) != gardens);

  printf("Player hand no longer has card choice3:\n");
  assertResult(handCard(3, &state3) != village);

  return 0;
}
