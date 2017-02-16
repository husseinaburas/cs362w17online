#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"

const int cardValues[] = {
	0, //curse
	2, //estate
	5, //duchy
	8, //province
	0, //copper
	3, //silver
	6, //gold
	6, //adventurer
	5, //council_room
	4, //feast
	4, //gardens
	5, //mine
	4, //remodel
	4, //smithy
	3, //village
	4, //baron
	3, //great_hall
	5, //minion
	3, //steward
	5, //tribute
	3, //ambassador
	4, //cutpurse
	2, //embargo
	5, //outpost
	4, //salvager
	4, //sea_hag
	4  //treasure_map
};

const char *cardNames[] = {
	"Curse",
	"Estate",
	"Duchy",
	"Province",
	"Copper",
	"Silver",
	"Gold",
	"Adventurer",
	"Council Room",
	"Feast",
	"Gardens",
	"Mine",
	"Remodel",
	"Smithy",
	"Village",
	"Baron",
	"Great Hall",
	"Minion",
	"Steward",
	"Tribute",
	"Ambassador",
	"Cutpurse",
	"Embargo",
	"Outpost",
	"Salvager",
	"Sea Hag",
	"Treasure Map"
};

int main( int argc, char** argv )
{
	int i;
	for( i = curse; i <= treasure_map; i++ ) {
		int output = getCost(i);
		if ( output != cardValues[i] ) {
			printf( "TEST FAILED for getCost with %s with expected cost of %d, but getCost returned %d\n", cardNames[i], cardValues[i], output );
		} else {
			printf( "TEST PASSED for getCost with %s with expected cost of %d\n", cardNames[i], cardValues[i] );
		}
	}

	return 0;
}
