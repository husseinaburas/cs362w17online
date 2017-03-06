/* Author: Bilal Saleem
 * Date: 2/1/17
 * Function to test: int getCost(int)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0


void assert(bool j, char * msg){
	if(j == false) {
		printf("Test Failed -- %s \n", msg);
	}
}

int main(){

	printf("unittest4.c\n");
	/*************** TEST ONE ***********************************
 	* Should return approriate cost for each card.
 	* All cost values used for comparison obtained
 	* from: http://wiki.dominionstrategy.com/index.php/Main_Page
 	* **********************************************************/
	assert(getCost(curse) == 0, " has wrong cost returned");	
	assert(getCost(estate) == 2, " has wrong cost returned");		
	assert(getCost(duchy) == 5, " has wrong cost returned");	
	assert(getCost(province) == 8, " has wrong cost returned");	
	assert(getCost(copper) == 0, " has wrong cost returned");	
	assert(getCost(silver) == 3, "silver has wrong cost returned");	
	assert(getCost(gold) == 6, "gold has wrong cost returned");	
	assert(getCost(adventurer) == 6, "adventurer has wrong cost returned");	
	assert(getCost(council_room) == 5, "council_room has wrong cost returned");	
	assert(getCost(feast) == 4, "feast has wrong cost returned");	
	assert(getCost(gardens) == 4, "gardens has wrong cost returned");	
	assert(getCost(mine) == 5, "mine has wrong cost returned");	
	assert(getCost(remodel) == 4, "remodel has wrong cost returned");	
	assert(getCost(smithy) == 4, "smithy has wrong cost returned");	
	assert(getCost(village) == 3, "village has wrong cost returned");	
	assert(getCost(baron) == 4, "baron has wrong cost returned");	
	assert(getCost(great_hall) == 3, "great_hall has wrong cost returned");	
	assert(getCost(minion) == 5, "minion has wrong cost returned");	
	assert(getCost(steward) == 3, "steward has wrong cost returned");	
	assert(getCost(tribute) == 5, "tribute has wrong cost returned");	
	assert(getCost(ambassador) == 3, "ambassador has wrong cost returned");	
	assert(getCost(cutpurse) == 4, "cutpurse has wrong cost returned");	
	assert(getCost(embargo) == 2, "embargo has wrong cost returned");	
	assert(getCost(outpost) == 5, "outpost has wrong cost returned");	
	assert(getCost(salvager) == 4, "salvager has wrong cost returned");
	assert(getCost(sea_hag) == 4, "sea_hag has wrong cost returned");	
	assert(getCost(treasure_map) == 4, "treasure_map has wrong cost returned");	
	
	/**************** TEST TWO *****************************
 	* Should return -1 if asked to get a cost for a card that
 	* isn't in the game or if function receives negative value
 	* ******************************************************/

	assert(getCost(100) == -1, "returned a cost for card that doesn't exist");
	assert(getCost(treasure_map + 1) == -1, "returned a cost for card that doesn't exist");
	assert(getCost(-1) == -1, "returned a cost for a card that doesn't exist (neg)");
	assert(getCost(-10) == -1, "returned a cost for a card that doesn't exist (neg)");

	return 0;
}
