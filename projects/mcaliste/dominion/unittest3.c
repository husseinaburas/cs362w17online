// test for gainCard()
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
  int oldHandCount, oldDiscardCount, oldDeckCount;

  initializeGame(numPlayers, kingdom, seed, &state);

  printf("*** Unit testing gainCard() ***\n");
  printf("Test card not in game gainCard():\n");
  assertResult(gainCard(ambassador, &state, 0, whoseTurn(&state)) == -1);

  printf("Test card supply depleted gainCard():\n");
  state.supplyCount[gardens] = 0;
  assertResult(gainCard(gardens, &state, 0, whoseTurn(&state)) == -1);

  printf("Test add card to hand gainCard():\n");
  oldHandCount = numHandCards(&state);

  gainCard(smithy, &state, 2, whoseTurn(&state));
  assertResult(oldHandCount == numHandCards(&state) - 1);
  assertResult(handCard(numHandCards(&state) - 1, &state) == smithy);

  printf("Test add card to discard gainCard():\n");
  oldDiscardCount = state.discardCount[whoseTurn(&state)];

  gainCard(baron, &state, 0, whoseTurn(&state));
  assertResult(oldDiscardCount == state.discardCount[whoseTurn(&state)] - 1);
  assertResult((state.discard[whoseTurn(&state)][oldDiscardCount]) == baron);

  printf("Test add card to deck gainCard():\n");
  oldDeckCount = state.deckCount[whoseTurn(&state)];

  gainCard(mine, &state, 1, whoseTurn(&state));
  assertResult(oldDeckCount == state.deckCount[whoseTurn(&state)] - 1);
  assertResult((state.deck[whoseTurn(&state)][oldDeckCount]) == mine);

  return 0;
}
