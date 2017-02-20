// Random tester for adventurer
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
  //int playAdventurer(struct gameState *state, int currentPlayer){

  struct gameState *state = newGame();
  int currentPlayer, seed;
  
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
    for (j = 0; j < MAX_DECK; j++)
      state->deck[currentPlayer][j] = rand()%10;

    // [re]fill hand
    for (j = 0; j < MAX_HAND; j++)
      state->hand[currentPlayer][j] = rand()%10;

    state->deckCount[currentPlayer] = rand()%MAX_DECK;
    state->handCount[currentPlayer] = rand()%MAX_HAND;

    i++;
    if (DBG){
      printf("currentPlayer: %d\ni: %d\n", currentPlayer, i);
      printf("deckCount: %d\n", state->deckCount[currentPlayer]);
      printf("handCount: %d\n", state->handCount[currentPlayer]);
    }

    playAdventurer(state, currentPlayer);
  }
  
  return 0;
}
