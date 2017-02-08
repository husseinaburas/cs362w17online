//cardtest4.c - council room

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
  int result, currentPlayer, actions, buys, oldHandCount, oldDeckCount, oldP2HandCount;

  printf("*** Unit testing councilRoomCard() ***\n");
  result = initializeGame(numPlayers, kingdom, seed, &state);

  printf("Test game is initialized:\n");
  assertResult(result == 0);

  printf("Test player 1 is current player:\n");
  currentPlayer = whoseTurn(&state);
  assertResult(currentPlayer == 0);

  printf("Test action count: 1\n");
  actions = state.numActions;
  assertResult(actions > 0);

  printf("Test council room in player hand:\n");
  // council room is 8 in cards enum
  state.hand[currentPlayer][0] = council_room;
  assertResult(handCard(0, &state) == 8);

  oldDeckCount = state.deckCount[currentPlayer];
  oldHandCount = numHandCards(&state);
  buys = state.numBuys;
  oldP2HandCount = state.handCount[currentPlayer+1];
  memcpy(&state2, &state, sizeof(struct gameState));
  memcpy(&state3, &state, sizeof(struct gameState));

  printf("*** Test playing council room card:\n");
  result = playCard(0, 0, 0, 0, &state);
  assertResult(result == 0);

  //+4 cards from deck into hand
  // council room actually discards when done, so it's +3 cards in hand
  // assignment 2 intentional bug has made original player draw 5 cards
  printf("Player hand has +4 cards:\n");
  assertResult((oldHandCount + 3) == numHandCards(&state));

  // this fails due to the bug causing us to draw 5 cards
  printf("Player deck has -4 cards:\n");
  assertResult((oldDeckCount - 4) == state.deckCount[currentPlayer]);

  printf("Player has +1 buys:\n");
  assertResult(buys + 1 == state.numBuys);

  printf("Other player has +1 cards:\n");
  assertResult(oldP2HandCount + 1 == state.handCount[currentPlayer+1]);

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


  printf("*** Test empty deck + shuffle discard + play councilRoomCard:\n");
  state2.deckCount[currentPlayer] = 0;
  state2.discardCount[currentPlayer] = 5;
  state2.discard[currentPlayer][0] = mine;
  state2.discard[currentPlayer][1] = steward;
  state2.discard[currentPlayer][2] = village;
  state2.discard[currentPlayer][3] = gold;
  state2.discard[currentPlayer][4] = silver;
  oldDeckCount = state2.deckCount[currentPlayer];
  oldHandCount = numHandCards(&state2);
  buys = state2.numBuys;
  oldP2HandCount = state2.handCount[currentPlayer+1];

  printf("Test playing council room card:\n");
  result = playCard(0, 0, 0, 0, &state2);
  assertResult(result == 0);

  //+4 cards from deck into hand
  // council room actually discards when done, so it's +3 cards in hand
  // assignment 2 intentional bug has made original player draw 5 cards
  printf("Player hand has +4 cards:\n");
  assertResult((oldHandCount + 3) == numHandCards(&state2));

  // this fails due to the bug causing us to draw 5 cards
  printf("Player deck has -4 cards:\n");
  assertResult((oldDeckCount - 4) == state2.deckCount[currentPlayer]);

  printf("Player has +1 buys:\n");
  assertResult(buys + 1 == state2.numBuys);

  printf("Other player has +1 cards:\n");
  assertResult(oldP2HandCount + 1 == state2.handCount[currentPlayer+1]);

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


  return 0;
}
