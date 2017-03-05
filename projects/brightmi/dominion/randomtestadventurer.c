/**
 * Miles Bright
 * CS 362-400 Assignment 4
 * randomtestcardadventurer.c - test file for adventurer card
 * 2/19/2017
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1
#define NUMBER_TESTS 1000

// test playAdventurer()
int main(int argc, char* argv[]) {
  // record random seed input
  int inputSeed = atoi(argv[1]);
  srand(inputSeed);

  // randomize game states

  // make calls to playAdventurer()

  struct gameState gs;

  int i;
  for (i = 0; i < NUMBER_TESTS; i++) {
    // randomize game states
    // assign states to gs object

    // call playVillage()
  }

  return 0;
}
