/*
- Andrew Bagwell
- CS362 Assignment 3 
- bagwella@oregonstate.edu
- Test of dominion's getCost function
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

//Testing getCost 

int main() {

  printf("*************************************\n");
  printf("unitTest2:\n");
  printf("TESTING -- testing getCost() -- BEGIN\n");

  int cardNames[] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
  int cardCostCalculated[27];
  int cardCosts[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

  printf("TESTING - getCost function - cost of each card. \n");

  for (int i = 0; i < 27; i++) {
    //call getCost()
    cardCostCalculated[i] = getCost(cardNames[i]);
    printf("TESTING - cost for card # %d\n", cardNames[i]);
    assertTrue(cardCostCalculated[i], cardCosts[i]);
    
  }

 printf("TESTING--getCost() -- COMPLETE\n\n");
  
  return 0;
  
}