/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a set of helper functions for test suite
 * **********************************************************************/
#include "testhelperfunctions.h"
#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int fillPlayerHand(int player, int card, int count, struct gameState *state) {
  int i;

  for (i = 0; i < count; i++) {
    state->hand[player][i] = card;
  }

  state->handCount[player] = count;

  return 1;
}

int placePlayerHand(int player, int card, int position, struct gameState *state) {
  state->hand[player][position] = card;
  return 1;
}

int fillPlayerDeck(int player, int card, int count, struct gameState *state) {
  int i;

  for (i = 0; i < count; i++) {
    state->deck[player][i] = card;
  }

  state->deckCount[player] = count;

  return 1;
}

int placePlayerDeck(int player, int card, int position, struct gameState *state) {
  state->deck[player][position] = card;
  return 1;
}

int fillPlayerDiscard(int player, int card, int count, struct gameState *state) {
  int i;

  for (i = 0; i < count; i++) {
    state->discard[player][i] = card;
  }

  state->discardCount[player] = count;

  return 1;
}

int placePlayerDiscard(int player, int card, int position, struct gameState *state) {
  state->discard[player][position] = card;
  return 1;
}

int assertTest(int result, int expected, int testNumber) {
  if (result == expected) {
    printf("TEST %d SUCCESSFULLY COMPLETED\n",testNumber);
    return 1;
  } else {
    printf("TEST %d FAILED\n",testNumber);
    printf("EXPECTED %d ---- ACTUAL %d\n",expected,result);
    return 0;
  }
}

