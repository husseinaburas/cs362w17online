/*
- Andrew Bagwell
- CS362 Assignment 3 
- bagwella@oregonstate.edu
- Test of dominion's numHandCards function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

//custom assert function

void assertTrue(int val1, int val2) {

  if (val1 != val2)
    printf("Test Case - FAILED\n");
  else 
    printf("Test Case - PASSED\n");

}

//testing

int main() {
  
  struct gameState GS;
  int c[10] = {adventurer, ambassador, gardens, great_hall, mine, minion, smithy, salvager, steward, village};
  
  //Standard initialization across all my tests, 
  initializeGame(2, c, 5, &GS);

  printf("*************************************\n");
  printf("unitTest1:\n");
  printf("TESTING -- testing numHandCards -- BEGIN\n");
  

  printf("TESTING - if numHandCards returns valid number of start cards (5). \n");
  assertTrue((numHandCards(&GS)), 5);
  
  printf("TESTING - if numHandCards accurately returns additions to hand. \n");

  for (int i = 6; i < 25; i++) {
    GS.handCount[0] = i;
    printf("TESTING - if Player 1 has %d cards in hand.\n", i);
    assertTrue(numHandCards(&GS), i);

  }
    
  //end the turn, so the player referenced in numHandCards will increment because state changes  
  printf("Ending turn. \n");
  endTurn(&GS);
  
  printf("TESTING - if numHandCards returns valid number of start cards (5) after turn change \n");
  assertTrue(numHandCards(&GS),5);
  
  printf("TESTING - if numHandCards accurately returns additions to hand. \n");
  for (int i = 6; i < 25; i++) {

    GS.handCount[1] = i;
    printf("TESTING - if Player 2 has %d cards in hand.\n", i);
    assertTrue(numHandCards(&GS), i);

  }

  printf("Ending turn. \n");
  endTurn(&GS);

  printf("TESTING - if numHandCards returns valid number of start cards (5) after turn change \n");
  assertTrue(numHandCards(&GS),5);

  printf("TESTING - if numHandCards accurately returns additions to hand. \n");
  for (int i = 6; i < 25; i++) {

    GS.handCount[0] = i;
    printf("TESTING - if Player 1 has %d cards in hand.\n", i);
    assertTrue(numHandCards(&GS), i);

  }
  
  printf("TESTING--numHandCards -- COMPLETE\n\n");
  
  return 0;
  
}