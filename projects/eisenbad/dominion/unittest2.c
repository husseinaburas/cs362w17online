/* File: unittest2.c
   Author: Daniel Eisenbach
   Date: 2/6/17

   Description: Tests the implementation of the dominion getCost() function.
   This function returns the coin fost for all victory and kingdom cards.
    
   Pass Conditions:
     1. Correct coin cost for all victory and kingdom cards is returned
     2. Negative values return -1
     3. Large positive values not in map return -1
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTFUNC "getCost()"

int main() {
  int pass_count;
  int pass_check;
	
  printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNC);

  /**************************************** TEST 1 ****************************************************/
  printf("\n  TEST 1: Correct coin cost for all victory and kingdom cards is returned\n");
 
  pass_check = 1; 

  printf("    curse cost = %d, expected = %d\n", getCost(curse), 0);
  if (getCost(curse) != 0) {pass_check = 0;}

  printf("    estate cost = %d, expected = %d\n", getCost(estate), 2);
  if (getCost(estate) != 2) {pass_check = 0;}

  printf("    duchy cost = %d, expected = %d\n", getCost(duchy), 5);
  if (getCost(duchy) != 5) {pass_check = 0;}

  printf("    province cost = %d, expected = %d\n", getCost(province), 8);
  if (getCost(province) != 8) {pass_check = 0;}

  printf("    copper cost = %d, expected = %d\n", getCost(copper), 0);
  if (getCost(copper) != 0) {pass_check = 0;}

  printf("    silver cost = %d, expected = %d\n", getCost(silver), 3);
  if (getCost(silver) != 3) {pass_check = 0;}

  printf("    gold cost = %d, expected = %d\n", getCost(gold), 6);
  if (getCost(gold) != 6) {pass_check = 0;}

  printf("    adventurer cost = %d, expected = %d\n", getCost(adventurer), 6);
  if (getCost(adventurer) != 6) {pass_check = 0;}

  printf("    council_room cost = %d, expected = %d\n", getCost(council_room), 5);
  if (getCost(council_room) != 5) {pass_check = 0;}

  printf("    feast cost = %d, expected = %d\n", getCost(feast), 4);
  if (getCost(feast) != 4) {pass_check = 0;}

  printf("    gardens cost = %d, expected = %d\n", getCost(gardens), 4);
  if (getCost(gardens) != 4) {pass_check = 0;}

  printf("    mine cost = %d, expected = %d\n", getCost(mine), 5);
  if (getCost(mine) != 5) {pass_check = 0;}

  printf("    remodel cost = %d, expected = %d\n", getCost(remodel), 4);
  if (getCost(remodel) != 4) {pass_check = 0;}

  printf("    smithy cost = %d, expected = %d\n", getCost(smithy), 4);
  if (getCost(smithy) != 4) {pass_check = 0;}

  printf("    village cost = %d, expected = %d\n", getCost(village), 3);
  if (getCost(village) != 3) {pass_check = 0;}

  printf("    baron cost = %d, expected = %d\n", getCost(baron), 4);
  if (getCost(baron) != 4) {pass_check = 0;}

  printf("    great_hall cost = %d, expected = %d\n", getCost(great_hall), 3);
  if (getCost(great_hall) != 3) {pass_check = 0;}

  printf("    minion cost = %d, expected = %d\n", getCost(minion), 5);
  if (getCost(minion) != 5) {pass_check = 0;}

  printf("    steward cost = %d, expected = %d\n", getCost(steward), 3);
  if (getCost(steward) != 3) {pass_check = 0;}

  printf("    tribute cost = %d, expected = %d\n", getCost(tribute), 5);
  if (getCost(tribute) != 5) {pass_check = 0;}

  printf("    ambassador cost = %d, expected = %d\n", getCost(ambassador), 3);
  if (getCost(ambassador) != 3) {pass_check = 0;}

  printf("    cutpurse cost = %d, expected = %d\n", getCost(cutpurse), 4);
  if (getCost(cutpurse) != 4) {pass_check = 0;}

  printf("    embargo cost = %d, expected = %d\n", getCost(embargo), 2);
  if (getCost(embargo) != 2) {pass_check = 0;}

  printf("    outpost cost = %d, expected = %d\n", getCost(outpost), 5);
  if (getCost(outpost) != 5) {pass_check = 0;}

  printf("    salvager cost = %d, expected = %d\n", getCost(salvager), 4);
  if (getCost(salvager) != 4) {pass_check = 0;}

  printf("    sea_hag cost = %d, expected = %d\n", getCost(sea_hag), 4);
  if (getCost(sea_hag) != 4) {pass_check = 0;}

  printf("    treasure_map cost = %d, expected = %d\n", getCost(treasure_map), 4);
  if (getCost(treasure_map) != 4) {pass_check = 0;}

  // assert test 1 passes
  testAssert(1, &pass_count, pass_check);

  /**************************************** TEST 2 ****************************************************/
  printf("\n  TEST 2: Negative values return -1\n");
  testAssert(2, &pass_count, getCost(-1000) == -1);
			 
  /**************************************** TEST 3 ****************************************************/
  printf("\n  TEST 3: Large positive values return -1\n");
  testAssert(3, &pass_count, getCost(1000) == -1);
	
  /**************************************** END OF TESTS ****************************************************/
  if (pass_count == 3) {printf("\n >>>>> TESTS COMPLETE. SUCCESS: All %s tests passed. <<<<<\n\n", TESTFUNC);}
  else {printf("\n >>>>> TESTS COMPLETE. FAILURE: Not all %s tests passed. <<<<<\n\n", TESTFUNC);}		 
	
  return 0;	
}