#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include <string.h>

/* unit tests for adventurer */

int main(){
  printf("START: testing adventurer...\n");
  // init game state
  struct gameState *s = newGame();

  int player = 0, handPos = 0;
  int i; // iterator

  // set up hand to contain no treasure cards
  for (i = 0; i < 5; i++){
    s->hand[player][i] = adventurer;
    s->handCount[player]++;
  }

  // set up deck to have a mixture of treasure and non-treasure cards,
  // 	so that we'll have to discard some during the draw process
  int cards[8] = { smithy, gold, smithy, adventurer, silver, smithy, gold, village };
  for (i = 0; i < 8; i++){
    s->deck[player][i] = cards[i];
    s->deckCount[player]++;
  }

  int numTreasures = 0;
  
  for (i = 0; i < s->handCount[player]; i++){
    int card = s->hand[player][i];
    if (card == gold || card == silver || card == copper)
      numTreasures++;
  }

  int oldNumTreasures = numTreasures;
  
  playAdventurer(s, player); // SEG-FAULTING
  /* adventurer post-condition expectations:
   * 1. 2 treasure cards added to hand
   * 2. any non-treasure cards are added to discard pile
   */

  for (i = 0; i < s->handCount[player]; i++){
    int card = s->hand[player][i];
    if (card == gold || card == silver || card == copper)
      numTreasures++;
  }

  // CASE 1: 2 treasure cards added to hand
  printf("TEST 1 - pass if 2 treasure cards added to hand\n");
  if (numTreasures == oldNumTreasures + 2)
    printf("TEST 1 - SUCCESS\n");
  else
    printf("TEST 1 - FAIL\n");

  // CASE 2: any non-treasure cards drawn got discarded
  // in our specific case, we know, given the deck we created, 
  // that we should have 2 smithys and an adventurer in the discard pile
  // as well as a gold and a silver in our hand
  printf("TEST 2 - pass if there is 1x smithy and 1x village in discard\n");
  int smithys=0, villages=0;
  for (i = 0; i < s->discardCount[player]; i++){
    if (s->discard[player][i] == smithy)
      smithys++;
    else if (s->discard[player][i] == village)
      villages++;
  }
  if (smithys == 1 && villages == 1)
    printf("TEST 2 - SUCCESS\n");
  else{
    printf("TEST 2 - FAIL\n");
    printf("discard contents:\n");
    for (i = 0; i < s->discardCount[player]; i++)
      printf("%d, ", s->discard[player][i]);
    printf("\n");
    printf("hand contents:\n");
    for (i = 0; i < s->handCount[player]; i++)
      printf("%d, ", s->hand[player][i]);
    printf("\n");
  }

  // CASE 3: we got a gold and a silver in our hand
  printf("TEST 3 - pass if hand contains one gold and one silver\n");
  int golds = 0, silvers = 0;
  for (i = 0; i < s->handCount[player]; i++){
    if (s->hand[player][i] == gold)
      golds++;
    else if (s->hand[player][i] == silver)
      silvers++;
  }

  if (golds == 1 && silvers == 1)
    printf("TEST 3 - SUCCESS\n");
  else
    printf("TEST 3 - FAIL\n");

  return 0;
}
