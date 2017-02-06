#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"

/* UNIT TESTS for isGameOver(...) */

void populateSupply(struct gameState *s){
  int i;
  // just put 10 cards in supply for each card type;
  // this is the same as a non-game-end state
  for (i = 0; i < 25; i++){
    s->supplyCount[i] = 10;
  }
  //printf("INFO: All supply cards count set to 10\n");
}

int main(){
  struct gameState *s = newGame();

  printf("START: testing isGameOver()...\n");

  // CASE 1
  printf("TEST 1 - end case: province cards empty\n");

  populateSupply(s);
  
  s->supplyCount[province] = 0;
  
  //printf("province cards: %d\n", s->supplyCount[province]);
  
  if (isGameOver(s))
    printf("TEST 1 - PASS\n");
  else
    printf("TEST 1 - FAIL\n");
  

  // CASE 2
  printf("TEST 2 - end case: any 3 supply stacks empty, not including province\n");

  populateSupply(s);

  // Set 3 stacks to 0; Copper, Silver, and Gold
  int i;
  for (i = 4; i <= 6; i++)
    s->supplyCount[i] = 0;
  
  if (isGameOver(s))
    printf("TEST 2 - PASS\n");
  else
    printf("TEST 2 - FAIL\n");


  // CASE 3
  printf("TEST 3 - end case: province cards and 2 other supply stacks empty\n");

  s->supplyCount[province] = 0;
  s->supplyCount[4] = 10; // refill one of the stacks we previously emptied

  if (isGameOver(s))
    printf("TEST 3 - PASS\n");
  else
    printf("TEST 3 - FAIL\n");


  // CASE 4
  printf("TEST 4 - non-end case: only two suppply stacks are empty, not including province cards\n");
  populateSupply(s);

  // just set two stacks equal to 0
  s->supplyCount[5] = 0;
  s->supplyCount[6] = 0;

  if (!isGameOver(s))
    printf("TEST 4 - PASS\n");
  else
    printf("TEST 4 - FAIL\n");


  /*
  char* gameOver="not ";

  if (isGameOver(s))
    gameOver="";

  printf("game is %sended\n", gameOver);

  */

  return 0;
}

