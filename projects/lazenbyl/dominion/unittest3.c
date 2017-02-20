#include<stdio.h>
#include<stdlib.h>

#include "dominion.h"


void testIsGameOver(){


  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy};

  initializeGame(2, k, 1, &G);

  
  /*************Test 1***************/
  //test when supply count for province is 0 returns 1
  G.supplyCount[province] = 0; 
  int gameOver = isGameOver(&G);

  if(gameOver==1){

    printf("Test 1 function testIsGameOver PASS after province cards are empty.\n");

  }
  else{

    printf("Test 1 function testIsGameOver FAIL after province cards are empty.\n");
  }

  /*************Test 2***************/
  //test when supply count for province is >0  and supply count for remaining cards > 0 returns 0 
  int i;
  for (i = 0; i < 25; i++) {

        G.supplyCount[i] = 3;  
  }
  G.supplyCount[province] = 9; 
  gameOver = isGameOver(&G);

  if(gameOver==0){

    printf("Test 2 function testIsGameOver PASS after supply count > 0 for all cards.\n");

  }
  else{

    printf("Test 2 function testIsGameOver FAIL after supply count > 0 for all cards.\n");
  }
  /*************Test 3***************/
  //test when supply count for province is >0  and supply count for remaining cards > 0 returns 0 
  for (i = 6; i < 10; i++) {

        G.supplyCount[i] = 0;  
  }
  G.supplyCount[province] = 9; 
  gameOver = isGameOver(&G);

  if(gameOver==1){

    printf("Test 3 function testIsGameOver PASS after supply count is 0 for 3 or more cards.\n");

  }
  else{

    printf("Test 3 function testIsGameOver FAIL after supply count is 0 for 3 or more cards.\n");
  }


}

int main(int argc, char *argv[])
{
    testIsGameOver();
    return 0;
}