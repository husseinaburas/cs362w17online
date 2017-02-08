#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main() {

	printf("Unit Test 1 - getCost()\n");
  
	int card[] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
  
	int cost[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

    int i;
  for (i = 0; i < 27; i++) {
	printf("Testing %d - Cost from getCost = %d, Actual cost = %d \n", card[i], getCost(card[i]), cost[i]);
	
	if(getCost(card[i]) != cost[i]){
		printf("ERROR, card %d is incorrect", card[i]);
	}

  }

  return 0; 

}