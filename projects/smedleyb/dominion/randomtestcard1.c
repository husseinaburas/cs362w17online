// Random tester for SMITHY
// Brock Smedley
// 2/17/2017 (lol neat date)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include <assert.h>
#include <time.h>

int DBG = 1;

int main(int argc, char *argv[]){
  //int playSmithy(struct gameState *state, int handPos, int currentPlayer);

  struct gameState *state = newGame();
  int handPos, currentPlayer, seed;
  
  // obtain a seed for random number generator
  if (argc > 0)
    seed = argv[1];
  else{
    time_t t;
    seed = (unsigned) time(&t);
  }

  // seed the random number generator
  srand(seed);

  int i = 0;
  while (1){
    //assert(i < 566);
    // generate random numbers for handPos and currentPlayer
    handPos = rand() % MAX_HAND;
    currentPlayer = 1; // = rand();

    state->handCount[currentPlayer] = rand() % MAX_HAND;

    i++;
    if (DBG)
      printf("handPos: %d\ncurrentPlayer: %d\nhandCount: %d\ni: %d\n\n", handPos, currentPlayer, state->handCount[currentPlayer], i);

    playSmithy(state, handPos, currentPlayer);
  }
  
  return 0;
}
