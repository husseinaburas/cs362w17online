/**
 * Miles Bright
 * CS 362-400 Assignment 4
 * randomtestcard1.c - Test file for Smithy card
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

// test playSmithy()
int main(int argc, char* argv[]) {
  // record random seed input
  int inputSeed = atoi(argv[1]);
  srand(inputSeed);

  // make calls to playSmithy()

  struct gameState gs;

  int i;
  for (i = 0; i < NUMBER_TESTS; i++) {
    // randomize game states
    // assign states to gs object

    // call playSmithy()
  }

  
  return 0;
}
