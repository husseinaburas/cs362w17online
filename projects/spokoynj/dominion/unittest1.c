// testing getCost()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define TESTUNIT "getCost()"

int assertTest(int actual, int expected, int testNo) {
	if (actual == expected) {
		printf("\tTEST %d SUCCESSFULLY COMPLETED\n",testNo);
		return 1;
	} 
	else {
		printf("\tTEST %d FAILED\n",testNo);
		printf("\tEXPECTED %d ---- ACTUAL %d\n",expected,actual);
		return 0;
	}
}

struct cards {
	char name[20];
	int id;
	int cost;
};

int main() {
		struct cards c[] = {
		{"curse", curse, 0},
		{"estate", estate, 2},
		{"duchy", duchy, 5},
		{"province", province, 8},
		{"copper", copper, 0},
		{"silver", silver, 3},
		{"gold", gold, 6},
		{"adventurer", adventurer, 6},
		{"council_room", council_room, 5},
		{"feast", feast, 4},
		{"gardens", gardens, 4},
		{"mine", mine, 5},
		{"remodel", remodel, 4},
		{"smithy", smithy, 4},
		{"village", village, 3},
		{"baron", baron, 4},
		{"great_hall", great_hall, 3},
		{"minion", minion, 5},
		{"steward", steward, 3},
		{"tribute", tribute, 5},
		{"ambassador", ambassador, 3},
		{"cutpurse", cutpurse, 4},
		{"embargo", embargo, 2},
		{"outpost", outpost, 5},
		{"salvager", salvager, 4},
		{"sea_hag", sea_hag, 4},
		{"treasure_map", treasure_map, 4}
	};
	
	int actual, expected;
	int i;
	
	printf("\n----------------- Testing Unit: %s ----------------\n", TESTUNIT);

	// ----   TEST - all valid cards  
	for (i = 0; i < 27; i++) {
		expected = c[i].cost;
		printf("TEST %d - %s card\n", (i+1), c[i].name);
		actual = getCost(c[i].id); 
		assertTest(actual, expected, (i+1));
	}
	
	// ----   Test - invalid cards  
	// too high
	expected = -1;
	printf("TEST 28 - invalid card (30)\n");
	actual = getCost(30); 
	assertTest(actual, expected, 28);
	
	// too low
	expected = -1;
	printf("TEST 29 - invalid card (-5)\n");
	actual = getCost(-5); 
	assertTest(actual, expected, 29);
	
	printf("\n-------------- Testing Complete: %s ----------------\n\n", TESTUNIT);
	
	return 0;
}
	