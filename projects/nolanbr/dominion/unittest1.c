/*
File: unittest1.c
Author: Brent Nolan
Description:  This is a unit test for the isGameOver function in dominion.c


*/

#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"
#include <time.h>



int main(){

  struct gameState state;
  int s;
  int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int pass1 = 0;
  int pass2 = 0;
  int pass3 = 0;

  initializeGame(2, k, 2, &state);
  
  //test game that should not be over
  s = isGameOver(&state);
  if(s == 0){
	  pass1 = 1;
	  printf("isGameOver Test 1 passed\n");
	  
  }
  else{
	  
	  printf("isGameOver Test 1 failed\n");
	  
  }
  
  
//test provice reaching 0
  state.supplyCount[province] = 0;

  s = isGameOver(&state);
  if(s == 1){
	  pass1 = 1;
	  printf("isGameOver Test 2 passed\n");
	  
  }
  else{
	  
	  printf("isGameOver Test 2 failed\n");
	  
  }
  
  state.supplyCount[province] = 1;
  
//test 3 supply counts empty
  state.supplyCount[1] = 0;
  state.supplyCount[2] = 0;
  state.supplyCount[3] = 0;

  s = isGameOver(&state);

  if(s == 1){
	  pass1 = 1;
	  printf("isGameOver Test 3 passed\n");
	  
  }
  else{
	  
	  printf("isGameOver Test 3 failed\n");
	  
  }
  
  if(pass1 == 0 || pass2 == 0 || pass3 == 0)
	  printf("isGameOver TEST FAILED");
  else
	  printf("isGameOver TEST SUCCESSFULLY COMPLETED");

  return 0;
}