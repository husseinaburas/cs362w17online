//cardtest2.c - smithy

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
  struct gameState state, state2;
  int seed = 667;
  int numPlayers = 2;
  int kingdom[10] = {adventurer, council_room, feast, gardens, mine, remodel,
    smithy, village, baron, great_hall};
  int result, currentPlayer, actions, oldHandCount, oldDiscardCount;

  printf("*** Unit testing smithyCard() ***\n");
  result = initializeGame(numPlayers, kingdom, seed, &state);

  memcpy(&state2, &state, sizeof(struct gameState));

  printf("Test game is initialized:\n");
  assertResult(result == 0);

  printf("Test player 1 is current player:\n");
  currentPlayer = whoseTurn(&state);
  assertResult(currentPlayer == 0);

  printf("Test action count:\n");
  actions = state.numActions;
  assertResult(actions > 0);

  printf("Test smithy in player hand:\n");
  // smithy is 13 in cards enum
  state.hand[currentPlayer][2] = smithy;
  assertResult(handCard(2, &state) == 13);

  oldDiscardCount = state.discardCount[currentPlayer];
  oldHandCount = numHandCards(&state);

  // initial state has 7 copper cards in deck
  printf("Test playing smithy card:\n");
  result = playCard(2, 0, 0, 0, &state);
  assertResult(result == 0);

  //for (int i = 0; i < numHandCards(&state); i++) {
    //printf("hand card %d: %d \n", i, handCard(i, &state));
  //}

  // smithy actually discards when done, so it's +2 cards in hand
  // but the bug introduced in assignment 2 actually draws 4 cards
  // which breaks this
  printf("Test hand has +3 cards:\n");
  assertResult((oldHandCount + 2) == numHandCards(&state));

  //printf("New hand count %d\n", numHandCards(&state));

  printf("*** Test empty deck + shuffle discard + play smithyCard:\n");
  state2.deckCount[currentPlayer] = 0;
  state2.discardCount[currentPlayer] = 5;
  state2.discard[currentPlayer][0] = mine;
  state2.discard[currentPlayer][1] = steward;
  state2.discard[currentPlayer][2] = village;
  state2.discard[currentPlayer][3] = gold;
  state2.discard[currentPlayer][4] = silver;
  state2.hand[currentPlayer][2] = smithy;
  oldHandCount = numHandCards(&state2);

  printf("Test playing smithy card:\n");
  result = playCard(2, 0, 0, 0, &state2);
  assertResult(result == 0);

  // smithy actually discards when done, so it's +2 cards in hand
  // but the bug introduced in assignment 2 actually draws 4 cards,
  // which breaks this
  printf("Test hand has +3 cards:\n");
  assertResult((oldHandCount + 2) == numHandCards(&state2));
  //printf("New hand count %d\n", numHandCards(&state2));




  return 0;
}
