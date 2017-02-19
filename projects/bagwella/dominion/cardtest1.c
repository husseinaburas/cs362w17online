/*
- Andrew Bagwell
- CS362 Assignment 3 
- bagwella@oregonGS.edu
- Test of dominion's smithy card via the playSmithy function 
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

//Testing smithy card

int main () {
  
  struct gameState GS;
  int c[10] = {adventurer, ambassador, gardens, great_hall, mine, minion, smithy, salvager, steward, village};
  
  printf("*************************************\n");
  printf("cardtest1:\n");
  printf("TESTING -- Smithy card -- BEGIN\n");
  
  //Standard initialization across all my tests...
  initializeGame(2, c, 5, &GS);
 
  //Set the current player's handcount to 1
  GS.handCount[0] = 1;

  //set the current player's card to Smithy
  GS.hand[0][0] = smithy; 

  //store the current deckCount
  int priorDeckCount = GS.deckCount[0];

  //Play the smithy card
  //test that it works at all
  printf("TESTING - playSmithy() executes successfully\n");
  assertTrue((playSmithy(&GS, 0, 0)), 0);

  //test that it works as intended 
  printf("TESTING - playSmithy()'s incrementing of handCount by drawing 3 cards \n");
  assertTrue(GS.handCount[0], 3);

  printf("TESTING - playSmity() decreases the deckCount\n");
  assertTrue((priorDeckCount - GS.deckCount[0]), 3);

  printf("TESTING - playSmithy() discarded the smithy card\n");
  assertTrue(GS.discard[0][0], smithy);

  printf("TESTING--Smithy card -- COMPLETE\n\n");
  
  return 0;
  
}