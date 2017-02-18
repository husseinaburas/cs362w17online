//randomtestadventurer.c

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include "assertresult.h"

void testAdventurer(int randHandPos, int playerNum, struct gameState* state) {

  int result;
  //handPos = randHandPos % MAX_HAND;
  state->hand[playerNum][randHandPos] = adventurer;
  state->numActions = 1;
  //printf("Actions remaining: %d, phase: %d\n", state->numActions, state->phase);
  printf("*** Test playing adventurer card:\n");
  result = playCard(randHandPos, 0, 0, 0, state);
  assertResult(result == 0);
}

void test2Adventurer(int oldHandCount, int playerNum, struct gameState* state) {

  //there are instances where we might only draw 0 or 1 treasure cards
  printf("Test hand has +1 cards:\n");
  assertResult(oldHandCount+1 == numHandCards(state));
  printf("Test hand has +2 cards:\n");
  assertResult(oldHandCount+2 == numHandCards(state));
  printf("New cards are: %d, %d\n", handCard(numHandCards(state)-1, state),
    handCard(numHandCards(state)-2, state));
}

void test3Adventurer(int oldHandCount, int playerNum, struct gameState* state) {

  //top two cards in hand should be drawn treasure cards
  //if no treasure cards found in deck, this test will fail
  printf("Test hand has +2 treasure cards:\n");
  assertResult(handCard(oldHandCount, state) == copper ||
    handCard(oldHandCount, state) == silver ||
    handCard(oldHandCount, state) == gold);
  assertResult(handCard(oldHandCount+1, state) == copper ||
    handCard(oldHandCount+1, state) == silver ||
    handCard(oldHandCount+1, state) == gold);
  printf("New cards are: %d, %d\n", handCard(numHandCards(state)-1, state),
    handCard(numHandCards(state)-2, state));
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
  int numTests, currentPlayer, handPos;
  int kingdom[10] = {adventurer, council_room, steward, gardens, mine, remodel,
    smithy, village, baron, great_hall};

  int cliNum = atoi(argv[1]);

  for (numTests = 0; numTests < cliNum; numTests++) {
    int playerNum = rand() % 2;
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
      int oldHandCount = numHandCards(&state);
      testAdventurer(handPos, currentPlayer, &state);
      test2Adventurer(oldHandCount, currentPlayer, &state);
      test3Adventurer(oldHandCount, currentPlayer, &state);
    }
    else if (cliNum % 3 == 0) {
      int oldHandCount = numHandCards(&state);
      testAdventurer(handPos, currentPlayer, &state);
      test2Adventurer(oldHandCount, currentPlayer, &state);
    }
    else {
      int oldHandCount = numHandCards(&state);
      testAdventurer(handPos, currentPlayer, &state);
      test3Adventurer(oldHandCount, currentPlayer, &state);
    }
  }

  return 0;
}
