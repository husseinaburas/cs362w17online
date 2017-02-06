#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"

/* UNIT TEST for discardCard(...) */

// SPOOKY ALERT: GLOBAL VARIABLES!!!!!!!!!1
// pre-cond vars
int player = 0;
int handPos = 3; // arbitrary choice
int trash = 0; // for now

void initGameState(struct gameState *s){
  int i;
  
  s->handCount[player] = 0; // start w/ 0 cards before creating hand

  // put cards in player's hand
  for (i = 0; i < 7; i++){ // arbitrarily choosing 7 as a hand size
    s->hand[player][i] = 5; // just give 'em some money
    s->handCount[player]++;
  }

  // set base conditions: empty discard pile, no cards discarded
  for (i = 0; i < MAX_DECK; i++)
    s->discard[player][i] = -1; // set all positions to -1 to denote no card

  s->discardCount[player] = 0;

  // make our card to discard a special card so we know when it's gone
  s->hand[player][handPos] = 9; // arbitrary 9; should be the only 9 in hand until discard
  // last card gets special value too, so we know if it replaces the discard
  s->hand[player][s->handCount[player]-1] = 12; // arbitrary 12; should be only 12

}

int main(){
  struct gameState *s = newGame();

  printf("START: testing discardCard(...)\n");

  // initialize base game state
  initGameState(s);
  printf("INFO: base game state initialized\n");

    
  /* pre-discard info */
  int cardToDiscard = s->hand[player][handPos];
  int handsize_orig = s->handCount[player];
  int lastCard_orig = s->hand[player][handsize_orig - 1]; // should be 12
  
  // now discard a card
  discardCard(handPos, player, s, trash);
 
  /* after discard, the following should be true (in this case):
   * 1. discarded card goes to discard pile
   * 2. discarded card removed from player's hand
   * 3. handCount[player] decremented by 1
   * 4. discarded card replaced with last card in hand
   */

  /* CASE 1: discard w/ no trash and hand containing 7 cards */
  // TEST 1a: discarded card goes to discard pile
  printf("\n");
  if (s->discard[player][0] == cardToDiscard)
    printf("TEST 1a - SUCCESS\n");
  else
    printf("TEST 1a - FAIL\n");

  // TEST 1b: card is removed from hand
  if (s->hand[player][handPos] != 9)
    printf("TEST 1b - SUCCESS\n");
  else
    printf("TEST 1b - FAIL\n");

  // TEST 1c: hand count is decremented
  if (s->handCount[player] == handsize_orig - 1)
    printf("TEST 1c - SUCCESS\n");
  else
    printf("TEST 1c - FAIL\n");

  // TEST 1d: discarded card replaced with last card in hand
  if (s->hand[player][handPos] == lastCard_orig)
    printf("TEST 1d - SUCCESS\n");
  else
    printf("TEST 1d - FAIL\n");


  initGameState(s);

  trash = 1;
  discardCard(handPos, player, s, trash);

  /* CASE 2: discard w/ trash and hand containing 7 cards */
  // TEST 2a: discarded card doesn't go to discard pile
  printf("\n");
  if (s->discard[player][0] != cardToDiscard)
    printf("TEST 2a - SUCCESS\n");
  else
    printf("TEST 2a - FAIL\n");

  // TEST 2b: played (discarded) card count should be 0
  if (s->discardCount == 0)
    printf("TEST 2b - SUCCESS\n");
  else
    printf("TEST 2b - FAIL\n");

  // TEST 2c: card is removed from hand
  if (s->hand[player][handPos] != 9)
    printf("TEST 2c - SUCCESS\n");
  else
    printf("TEST 2c - FAIL\n");

  // TEST 2d: hand count is decremented
  if (s->handCount[player] == handsize_orig - 1)
    printf("TEST 2d - SUCCESS\n");
  else
    printf("TEST 2d - FAIL\n");

  // TEST 2e: discarded card replaced with last card in hand
  if (s->hand[player][handPos] == lastCard_orig)
    printf("TEST 2e - SUCCESS\n");
  else
    printf("TEST 2e - FAIL\n");


  return 0;
}

