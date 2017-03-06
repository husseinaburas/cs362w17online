#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include <string.h>

/* unit tests for council room */

int main(){
  printf("START: testing council room...\n");
  
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
    s->hand[player][i] = council_room;
    s->handCount[player]++;
  }

  int handcount_orig = s->handCount[player];
  int buys_orig = s->numBuys;

  playCouncil_Room(s, handPos, player);

  // CASE 1: 4 cards added to hand (+4 -1 = +3 b/c discard)
  printf("TEST 1 - pass if 4 cards added to hand\n");
  if (s->handCount[player] == handcount_orig + 3)
    printf("TEST 1 - SUCCESS\n");
  else
    printf("TEST 1 - FAIL\n");

  // CASE 2: player gains 1 buy
  printf("TEST 2 - pass if player gains 1 buy\n");
  if (s->numBuys == buys_orig + 1)
    printf("TEST 2 - SUCCESS\n");
  else
    printf("TEST 2 - FAIL\n");

  // CASE 3: council room discarded
  printf("TEST 3 - pass if council room in discard pile\n");
  if (s->discard[player][0] == council_room)
    printf("TEST 3 - SUCCESS\n");
  else
    printf("TEST 3 - FAIL\n");



  return 0;
}
