#include "dominion.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* UNIT TESTS for shuffle(...) */

int main(){
  printf("START: testing shuffle...\n");

  struct gameState *s1 = newGame();
  struct gameState *s2 = malloc(sizeof(struct gameState));


  //initialize player deck
  int player = 0, i;
  s1->deckCount[player] = 0;
  int j;
  for (j = 0; j < 3; j++)
    {
      s1->deck[player][j] = estate;
      s1->deckCount[player]++;
    }
  for (j = 3; j < 10; j++)
    {
      s1->deck[player][j] = copper;
      s1->deckCount[player]++;		
    }
  
  // copy game state to another instance
  memcpy(s2, s1, sizeof(struct gameState));
  
// shuffle one of the game states' decks
  shuffle(0, s1);

  // compare decks te determine shuffle success
  int isSame=1; // start w/ assumption that they're equal
  for (i = 0; i < 10; i++){
    if (s1->deck[player][i] != s2->deck[player][i]){
      isSame = 0;
      break;
    }
  }
  
  // shuffle again
  shuffle(0, s1);

  // compare decks te determine shuffle success
  isSame=1; // start w/ assumption that they're equal
  for (i = 0; i < 10; i++){
    if (s1->deck[player][i] != s2->deck[player][i]){
      isSame = 0;
      break;
    }
  }

  if (!isSame)
    printf("TEST SUCCEEDED\n");
  else
    printf("TEST FAILED\n");

  return 0;
}
