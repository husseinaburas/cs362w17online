#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "getCost"

int main(){
	int i;
	char* cards[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", 
			"adventurer", "council_room", "feast", "gardens", "mine", "remodel", "smithy", 
			"village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", 
			"cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	int card_costs[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 
				2, 5, 4, 4, 4};
			
	printf("--------------- Testing Card: %s ---------------\n", TESTCARD);
	
	// Is the cost of every card correctly returned?
	for(i = curse; i <= treasure_map; i++){
		printf("cost of ");
		asserttrue(cards[i], getCost(i), card_costs[i]);
	}
	
	// Is -1 correctly returned for non-possible card values?
	asserttrue("return value for non-existent card", getCost(30), -1);

	printf("--------------- Completed Card: %s ---------------\n", TESTCARD);	
	return 0;
}