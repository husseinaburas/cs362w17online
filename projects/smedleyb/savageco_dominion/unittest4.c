#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/* UNIT TESTS for updateCoins(...) */

int main(){
  printf("START: testing updateCoins(...)\n");

  struct gameState *s = newGame();

  int player = 0;
  
  int i;
  for (i = 0; i < 5; i++){ // arbitrarily choosing to add 5 cards
    s->hand[player][i] = gold;
    s->handCount[player]++;
  }

  // Gold is worth 3; we have 5 cards; total value = 15


  // CASE 1: player has 5 golds in hand; coins should be 15
  updateCoins(player, s, 0); // bonus=0 for simplicity
  
  if (s->coins == 15)
    printf("TEST 1: SUCCESS\n");
  else
    printf("TEST 1: FAIL\n");


  // CASE 2 : player has 5 golds in hand and bonus is 3; coins should be 18
  updateCoins(player, s, 3); // bonus=0 for simplicity
  
  if (s->coins == 18)
    printf("TEST 2: SUCCESS\n");
  else
    printf("TEST 2: FAIL\n");


  return 0;
}
