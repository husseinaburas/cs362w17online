#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include <string.h>

/* unit tests for smithy */

int main(){
  printf("START: Testing smithy...\n");

  // init game state
  struct gameState *s = newGame();

  int player = 0, handPos = 0;
  int i; // iterator
  
  
  // give player 5 smithys
  for (i = 0; i < 5; i++){
    s->hand[player][i] = smithy;
    s->handCount[player]++;
  }

  // start off making sure discard pile is empty and deck is full
  for (i = 0; i < MAX_DECK; i++)
    s->discard[player][i] = -1;
  s->discardCount[player] = 0;
  
  // fill deck with cards
  s->deckCount[player] = 0;
  for (i = 0; i < MAX_DECK; i++){
    s->deck[player][i] = 17; // arbitrary 17; just filling deck with it
    s->deckCount[player]++;
  }

  int oldhandcount = s->handCount[player];

  s->whoseTurn = 0;
  s->numActions = 1; // give player an action in order to draw card
  handPos = 0; // first card should be a smithy
  // int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state);
  playCard(handPos, 0, 0, 0, s);

  /* expectation: post-conditions:
   * 1. OG smithy card will be discarded
   * 2. 3 cards will be drawn into hand
   */

  // CASE 1: smithy card will be discarded
  printf("TEST 1 - pass if smithy card was discarded to discard pile\n");
  printf("discard[player0]:\n");
  if (s->playedCards[player] == -1)
    printf("empty\n");
  else{
    int i = 0;
    while (s->playedCards[i]){
      printf("%d\n", s->playedCards[i]);
      i++;
    }
  }
  if (s->playedCards[0] == smithy)
    printf("TEST 1 - SUCCESS\n");
  else
    printf("TEST 1 - FAIL\n");

  // CASE 2: player now has (5-1+3=) 7 cards in hand
  printf("TEST 2 - pass if player has 7 cards in hand; started w/ 5\n");
  printf("handCount: %d\n", s->handCount[player]);
  if (s->handCount[player] == 7)
    printf("TEST 2 - SUCCESS\n");
  else
    printf("TEST 2 - FAIL\n");

  // CASE 3: discard count is 1
  printf("TEST 3 - pass if discard count is 1\n");
  if (s->playedCardCount == 1)
    printf("TEST 3 - SUCCESS\n");
  else
    printf("TEST 3 - FAIL\n");

  // CASE 4: player drew 3 cards into hand and discarded 1
  printf("TEST 4 - pass if hand size is >= original-1+3; discard 1 and draw 3\n");
  if (s->handCount[player] >= oldhandcount + 2)
    printf("TEST 4 - SUCCESS\n");
  else
    printf("TEST 4 - FAIL\n");
  return 0;
}
