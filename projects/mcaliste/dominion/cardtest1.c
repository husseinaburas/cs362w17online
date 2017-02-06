//cardtest1.c - adventurer

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
  int result, currentPlayer, actions, oldDiscardCount;

  printf("*** Unit testing adventurerCard() ***\n");
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

  //printf("Testing deck count > 0:\n");
  //oldDeckCount = state.deckCount[currentPlayer];
  //assertResult(oldDeckCount > 0);

  printf("Test adventurer in player hand:\n");
  // adventurer is 7 in cards enum
  state.hand[currentPlayer][3] = adventurer;
  assertResult(handCard(3, &state) == 7);

  //printf("Current hand count %d\n", numHandCards(&state));
  oldDiscardCount = state.discardCount[currentPlayer];

  // initial state has 7 copper cards in deck
  printf("*** Test playing adventurer card:\n");
  result = playCard(3, 0, 0, 0, &state);
  assertResult(result == 0);

  printf("Test hand has +2 treasure cards:\n");
  assertResult(handCard(numHandCards(&state)-1, &state) == copper ||
    handCard(numHandCards(&state)-1, &state) == silver ||
    handCard(numHandCards(&state)-1, &state) == gold);
  assertResult(handCard(numHandCards(&state)-2, &state) == copper ||
    handCard(numHandCards(&state)-2, &state) == silver ||
    handCard(numHandCards(&state)-2, &state) == gold);
  //printf("New hand count %d\n", numHandCards(&state));


  printf("*** Test empty deck + shuffle discard + play adventurerCard:\n");
  state2.deckCount[currentPlayer] = 0;
  state2.discardCount[currentPlayer] = 5;
  state2.discard[currentPlayer][0] = mine;
  state2.discard[currentPlayer][1] = steward;
  state2.discard[currentPlayer][2] = village;
  state2.discard[currentPlayer][3] = gold;
  state2.discard[currentPlayer][4] = silver;
  state2.hand[currentPlayer][3] = adventurer;
  oldDiscardCount = state2.discardCount[currentPlayer];

  printf("Test playing adventurer card:\n");
  result = playCard(3, 0, 0, 0, &state2);
  assertResult(result == 0);
  printf("Test hand has +2 treasure cards:\n");
  assertResult(handCard(numHandCards(&state2)-1, &state2) == copper ||
    handCard(numHandCards(&state2)-1, &state2) == silver ||
    handCard(numHandCards(&state2)-1, &state2) == gold);
  assertResult(handCard(numHandCards(&state2)-2, &state2) == copper ||
    handCard(numHandCards(&state2)-2, &state2) == silver ||
    handCard(numHandCards(&state2)-2, &state2) == gold);

  //printf("New hand count %d\n", numHandCards(&state2));

  // this is being broken by the bug introduced in assignment 2
  printf("Test discard has 2 fewer cards:\n");
  assertResult(oldDiscardCount == state2.discardCount[currentPlayer]+2);
  printf("New discard count: %d\n", state2.discardCount[currentPlayer]);
  printf("Old discard count: %d\n", oldDiscardCount);

  //for (int i = 0; i < 5; i++) {
    //printf("discarded card: %d \n", state2.discard[currentPlayer][i]);
  //}


  return 0;
}
