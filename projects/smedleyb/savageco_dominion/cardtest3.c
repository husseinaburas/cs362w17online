#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include <string.h>

/* unit tests for village */

int main(){
  printf("START: testing village...\n");
  
  // init game state
  struct gameState *s = newGame();

  int player = 0, handPos = 0;
  int i; // iterator

  // set up deck to have some gold cards we can draw
  for (i = 0; i < 5; i++){ // arbitrarily adding 5 cards to deck
    s->deck[player][i] = gold;
    s->deckCount[player]++;
  }

  // set up hand so that we can play the village card
  for (i = 0; i < 5; i++){
    s->hand[player][i] = village;
    s->handCount[player]++;
  }

  int handcount_orig = s->handCount[player];
  int actions_orig = s->numActions;

  playVillage(s, handPos, player);

  // CASE 1: 1 card drawn into hand
  printf("TEST 1 - pass if hand size is same after playing village; discard 1 and draw 1\n");
  if (s->handCount[player] == handcount_orig)
    printf("TEST 1 - SUCCESS\n");
  else
    printf("TEST 1 - FAIL\n");
  
  // CASE 2: player granted 2 actions
  printf("TEST 2 - pass if player has two more actions than before playing village\n");
  if (s->numActions == actions_orig + 2)
    printf("TEST 2 - SUCCESS\n");
  else
    printf("TEST 2 - FAIL\n");

  // CASE 3: village is discarded
  printf("TEST 3 - pass if village in discard pile\n");
  if (s->discard[player][0] == village)
    printf("TEST 3 - SUCCESS\n");
  else
    printf("TEST 3 - FAIL\n"); 

  return 0;
}
