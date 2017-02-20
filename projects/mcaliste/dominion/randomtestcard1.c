//randomtestcard1.c -- council room

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include "assertresult.h"

void testCouncilRoom(int randHandPos, int playerNum, struct gameState* state) {

  int result;
  //handPos = randHandPos % MAX_HAND;
  state->hand[playerNum][randHandPos] = council_room;
  state->numActions = 1;
  //printf("Actions remaining: %d, phase: %d\n", state->numActions, state->phase);
  printf("*** Test playing council room card:\n");
  result = playCard(randHandPos, 0, 0, 0, state);
  assertResult(result == 0);
}

void test2CouncilRoom(int oldHandCount, struct gameState* state) {
  //+4 cards from deck into hand
  // council room actually discards when done, so it's +3 cards in hand
  // assignment 2 intentional bug has made original player draw 5 cards
  printf("Player hand has +4 cards:\n");
  assertResult((oldHandCount + 3) == numHandCards(state));
}

void test3CouncilRoom(int playerNum, int oldDeckCount, struct gameState* state) {
  // this fails due to the bug causing us to draw 5 cards
  printf("Player deck has -4 cards:\n");
  assertResult((oldDeckCount - 4) == state->deckCount[playerNum]);
}

void test4CouncilRoom(int buys, struct gameState* state) {
  printf("Player has +1 buys:\n");
  assertResult(buys + 1 == state->numBuys);
}

void test5CouncilRoom(int playerNum, int oldP2HandCount, struct gameState* state){
  printf("Other player has +1 cards:\n");
  assertResult(oldP2HandCount + 1 == state->handCount[playerNum+1]);
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
    int numTests, currentPlayer, handPos, oldDeckCount, oldHandCount, oldP2HandCount, buys;
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
        buys = state.numBuys;
        oldP2HandCount = state.handCount[currentPlayer+1];
        testCouncilRoom(handPos, currentPlayer, &state);
        test2CouncilRoom(oldHandCount, &state);
        test3CouncilRoom(currentPlayer, oldDeckCount, &state);
        test4CouncilRoom(buys, &state);
        test5CouncilRoom(currentPlayer, oldP2HandCount, &state);
      }
      else if (cliNum % 3 == 0) {
        oldHandCount = numHandCards(&state);
        oldDeckCount = state.deckCount[currentPlayer];
        testCouncilRoom(handPos, currentPlayer, &state);
        test2CouncilRoom(oldHandCount, &state);
        test3CouncilRoom(currentPlayer, oldDeckCount, &state);
      }
      else if (cliNum % 5 == 0) {
        buys = state.numBuys;
        oldP2HandCount = state.handCount[currentPlayer+1];
        testCouncilRoom(handPos, currentPlayer, &state);
        test4CouncilRoom(buys, &state);
        test5CouncilRoom(currentPlayer, oldP2HandCount, &state);
      }
      else {
        oldDeckCount = state.deckCount[currentPlayer];
        oldHandCount = numHandCards(&state);
        oldP2HandCount = state.handCount[currentPlayer+1];
        testCouncilRoom(handPos, currentPlayer, &state);
        test2CouncilRoom(oldHandCount, &state);
        test3CouncilRoom(currentPlayer, oldDeckCount, &state);
        test5CouncilRoom(currentPlayer, oldP2HandCount, &state);
      }
    }

    return 0;
  }
