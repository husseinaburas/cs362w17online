// test for isGameOver()
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

    initializeGame(numPlayers, kingdom, seed, &state);

    printf("*** Unit testing isGameOver() ***\n");
    printf("Test initial state isGameOver():\n");
    assertResult(isGameOver(&state) == 0);

    printf("Test empty province cards isGameOver():\n");
    state.supplyCount[province] = 0;
    assertResult(isGameOver(&state) == 1);

    state.supplyCount[province] = 8;
    printf("Test 3 empty supply cards isGameOver():\n");
    state.supplyCount[gold] = 0;
    state.supplyCount[tribute] = 0;
    state.supplyCount[sea_hag] = 0;
    assertResult(isGameOver(&state) == 1);

    printf("Test 2 empty supply cards isGameOver():\n");
    state.supplyCount[gold] = 0;
    state.supplyCount[tribute] = 0;
    assertResult(isGameOver(&state) == 0);

    return 0;

  }
