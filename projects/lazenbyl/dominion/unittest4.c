#include<stdio.h>
#include<stdlib.h>

#include "dominion.h"

void testUpdateCoins(){


  struct gameState state;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy};

  initializeGame(2, k, 1, &state);

  int currentPlayer = whoseTurn(&state);

  /********Test 1**********/
  //test update coins with one copper, silver and gold and bonus of 2 
  state.hand[currentPlayer][0] = copper;
  state.hand[currentPlayer][1] = silver;
  state.hand[currentPlayer][2] = gold;
  state.handCount[currentPlayer] = 3;

  updateCoins(currentPlayer, &state, 2);

  if(state.coins==8){

        printf("Test 1 function testUpdateCoins PASS with one gold, one silver, one copper and two bonus coins.\n");
    }
  else{

  	printf("Test 1 function testUpdateCoins FAIL with one gold, one silver, one copper and two bonus coins.\n");	
  }

  /*********Test 2**********/
  //hand count 2, coins should be 0 due to no treasure in hand
  state.handCount[currentPlayer] = 2;
  state.hand[currentPlayer][0] = great_hall;
  state.hand[currentPlayer][1] = minion;
  updateCoins(currentPlayer, &state, 0);


  if(state.coins==0){

        printf("Test 2 function testUpdateCoins PASS when treasure count is 0.\n");
    }
  else{

  	printf("Test 2 function testUpdateCoins FAIL when treasure count is 0.\n");	
  }
}

int main(int argc, char *argv[])
{
    testUpdateCoins();
    return 0;
}
