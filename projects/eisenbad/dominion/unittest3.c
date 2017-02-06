/* File: unittest2.c
   Author: Daniel Eisenbach
   Date: 2/6/17

   Description: Tests the implementation of the dominion isGameOver() function.
   This function returns one if the province card supply is zero, or if three supply piles are at zero.
    
   Pass Conditions:
     1. Returns one if province supply is zero
     2. Returns one if three supply piles are zero
	 3. First and last cards in card array are in range of isGameOver() supply checks
     4. Returns zero if the province supply, and less than three supply piles, aren't zero
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTFUNC "isGameOver()"

int main() {
  int pass_count;
  int pass_check;
	
  int seed = 1000;  // sets the state of the current random number generator stream, bc seed > 0; used in shuffle()
  int numPlayers = 2;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize game state and player cards
  initializeGame(numPlayers, k, seed, &G);
	
  printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNC);

  /**************************************** TEST 1 ****************************************************/
  printf("\n  TEST 1: Returns one if province supply is zero\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
	
  // set province supply to zero
  testG.supplyCount[province] = 0;
	
  printf("    game over = %d, expected = %d\n", isGameOver(&testG), 1);
  testAssert(1, &pass_count, isGameOver(&testG) == 1);
	
  /**************************************** TEST 2 ****************************************************/
  printf("\n  TEST 2: Returns one if three supply piles are zero\n");
	
  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
	
  printf("    NOTE: Setting copper, adventurer, and smithy supplies to zero\n");
	
  // set copper, adventurer, and smithy supplies to zero
  testG.supplyCount[copper] = 0;
  testG.supplyCount[adventurer] = 0;
  testG.supplyCount[smithy] = 0;
	
  printf("    game over = %d, expected = %d\n", isGameOver(&testG), 1);

  // assert test 2 passed
  testAssert(2, &pass_count, isGameOver(&testG) == 1);
	
  /**************************************** TEST 3 ****************************************************/
  printf("\n  TEST 3: First and last cards in card array are in range of isGameOver() supply checks\n");
	
  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
	
  printf("    NOTE: Setting curse, minion and duchy piles to zero\n");
	
  // set curse, minion, and duchy supplies to zero
  testG.supplyCount[curse] = 0;
  testG.supplyCount[minion] = 0;
  testG.supplyCount[treasure_map] = 0;
	
  printf("    game over = %d, expected = %d\n", isGameOver(&testG), 1);
  if (isGameOver(&testG) != 1) {pass_check = 0;}
	
  testAssert(3, &pass_count, pass_check);
	
  /**************************************** TEST 4 ****************************************************/
  printf("\n  TEST 4: Returns zero if the province supply, and less than three supply piles, aren't zero\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
	
  printf("    NOTE: Setting adventurer and smithy piles to zero\n");
	
  // set adventurer and smithy piles to zero
  testG.supplyCount[curse] = 0;
  testG.supplyCount[minion] = 0;
	
  printf("    game over = %d, expected = %d\n", isGameOver(&testG), 0);
  testAssert(4, &pass_count, isGameOver(&testG) == 0);
	

  /**************************************** END OF TESTS ****************************************************/
  if (pass_count == 4) {printf("\n >>>>> TESTS COMPLETE. SUCCESS: All %s tests passed. <<<<<\n\n", TESTFUNC);}
  else {printf("\n >>>>> TESTS COMPLETE. FAILURE: Not all %s tests passed. <<<<<\n\n", TESTFUNC);}		 
	
  return 0;	
}	