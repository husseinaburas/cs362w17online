#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"

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

void testIsGameOver( int *modifiedCount, int *supplyIndexes, int length, int expectedValue );

int main( int argc, char** argv )
{
	int cardIndexes[4]	= { province, adventurer, smithy, council_room };

	// Test as if the game isn't over, should return 0
	int cardCount1[4] 	= { 1, 1, 1, 1 };
	testIsGameOver( cardCount1, cardIndexes, 4, 0 );

	// Test as if the game has no more provinces, should return 1
	int cardCount2[4] 	= { 0, 1, 1, 1 };
	testIsGameOver( cardCount2, cardIndexes, 4, 1 );

	// Test as if three kingdom card stacks are empty, should return 1
	int cardCount3[4] 	= { 1, 0, 0, 0 };
	testIsGameOver( cardCount3, cardIndexes, 4, 1 );

	return 0;
}

void testIsGameOver( int *modifiedCount, int *supplyIndexes, int length, int expectedValue )
{
	struct gameState *state = newGame();
	int *k = kingdomCards( adventurer, smithy, council_room, feast, gardens, mine, remodel, village, baron, great_hall );

	initializeGame( 2, k, 1, state );

	int i;
	for( i = 0; i < length; i++ ) {
		state->supplyCount[supplyIndexes[i]] = modifiedCount[i];
	}

	int output = isGameOver( state );

	if ( output != expectedValue ) {
		printf( "TEST FAILED for isGameOver with ");

		for( i = 0; i < length; i++ ) {
			printf( "%d %ss", modifiedCount[i], cardNames[supplyIndexes[i]] );

			if ( i != length - 1 ) {
				printf( ", " );
			}
		}

		printf( " with expected value of %d, but isGameOver returned %d\n", expectedValue, output );
	} else {
		printf( "TEST PASSED for isGameOver with ");

		for( i = 0; i < length; i++ ) {
			printf( "%d %ss", modifiedCount[i], cardNames[supplyIndexes[i]] );

			if ( i != length - 1 ) {
				printf( ", " );
			}
		}

		printf( " with expected value of %d\n", expectedValue );
	}

	free(state);
}
