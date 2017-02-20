// Random tester for VILLAGE
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
  //int playVillage(struct gameState *state, int handPos, int currentPlayer){

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

  currentPlayer = 1; // = rand();
  
  int i = 0, j = 0;
    while (1){
    // [re]fill deck
    for (j = 0; j < MAX_DECK; j++){
      state->deck[currentPlayer][j] = rand()%10;
    }

    // generate random values for params
    state->deckCount[currentPlayer] = rand()%MAX_DECK;
    state->handCount[currentPlayer] = rand()%MAX_HAND;
    handPos = rand() % MAX_HAND;

    i++;
    if (DBG)
      printf("handPos: %d\ndeckCount: %d\nhandCount: %d\ni: %d\n", handPos, state->deckCount[currentPlayer], state->handCount[currentPlayer], i);

    playVillage(state, handPos, currentPlayer);
  }
  
  return 0;
}
