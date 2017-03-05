//randomtestcard2.c -- village

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include "assertresult.h"

void testVillage(int randHandPos, int playerNum, struct gameState* state) {

  int result;
  //handPos = randHandPos % MAX_HAND;
  state->hand[playerNum][randHandPos] = village;
  //state->numActions = 1;
  //printf("Actions remaining: %d, phase: %d\n", state->numActions, state->phase);
  printf("*** Test playing village card:\n");
  result = playCard(randHandPos, 0, 0, 0, state);
  assertResult(result == 0);
}

void test2Village(int oldHandCount, struct gameState* state) {
  //+1 cards from deck into hand
  // village actually discards when done, so it's no change in count
  printf("Player hand has +1 cards:\n");
  assertResult((oldHandCount) == numHandCards(state));
}

void test3Village(int playerNum, int oldDeckCount, struct gameState* state) {
  // this fails due to the bug causing us to draw 5 cards
  printf("Player deck has -1 cards:\n");
  assertResult((oldDeckCount - 1) == state->deckCount[playerNum]);
}

void test4Village(int actions, struct gameState* state) {
  // this is after playing village card, so it's +1 actions
  printf("Player has +1 actions:\n");
  //printf("old actions: %d, new actions: %d\n", actions, state->numActions);
  assertResult(actions + 1 == state->numActions);
}


int main (int argc, char *argv[]) {

  if (argc < 2) {
    printf("Not enough arguments.\n");
    EXIT_SUCCESS;
  }
  else if (argc > 2) {
    printf("Please provide only one number argument.\n");
    EXIT_SUCCESS;
  }

  if (argv[1] < 0) {
    printf("Please provide a non-negative number argument.\n");
    EXIT_SUCCESS;
  }

  struct gameState state;
  int numTests, currentPlayer, handPos, oldDeckCount, oldHandCount, actions;
  int kingdom[10] = {adventurer, council_room, steward, gardens, mine, remodel,
    smithy, village, baron, great_hall};

  int cliNum = atoi(argv[1]);

  for (numTests = 0; numTests < cliNum; numTests++) {
    int playerNum = (rand() % 2)+1;
    //printf("Clinum number is %d\n", cliNum);
    //printf("Player number is %d\n", playerNum);
    initializeGame(playerNum, kingdom, 667, &state);
    currentPlayer = whoseTurn(&state);
    state.deckCount[currentPlayer] = rand() % MAX_DECK;
    state.discardCount[currentPlayer] = rand() % MAX_DECK;
    state.handCount[currentPlayer] = rand() % MAX_HAND;

    for (int d = 0; d < state.deckCount[currentPlayer]; d++) {
      state.deck[currentPlayer][d] = rand() % 28;
    }

    for (int s = 0; s < state.discardCount[currentPlayer]; s++) {
      state.discard[currentPlayer][s] = rand() % 28;
    }

    for (int h = 0; h < state.handCount[currentPlayer]; h++) {
      state.hand[currentPlayer][h] = rand() % 28;
    }
    //printf("Deckcount is %d\n", state.deckCount[currentPlayer]);
    //printf("discardcount is %d\n", state.discardCount[currentPlayer]);
    //printf("handcount is %d\n", state.handCount[currentPlayer]);
    handPos = cliNum % MAX_HAND;
    if (cliNum % 2 == 0) {
      oldDeckCount = state.deckCount[currentPlayer];
      oldHandCount = numHandCards(&state);
      actions = state.numActions;
      testVillage(handPos, currentPlayer, &state);
      test2Village(oldHandCount, &state);
      test3Village(currentPlayer, oldDeckCount, &state);
      test4Village(actions, &state);

    }
    else if (cliNum % 3 == 0) {
      oldHandCount = numHandCards(&state);
      oldDeckCount = state.deckCount[currentPlayer];
      testVillage(handPos, currentPlayer, &state);
      test2Village(oldHandCount, &state);
      test3Village(currentPlayer, oldDeckCount, &state);
    }
    else {
      actions = state.numActions;
      testVillage(handPos, currentPlayer, &state);
      test4Village(actions, &state);
    }
  }

  return 0;
}
