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

void testUpdateCoins( int *cards, int cardCount, int expectedValue, int bonusCoins );

int main( int argc, char** argv )
{
	// Test no coins, should be zero
	int cards1[4] = { curse, curse, curse, curse };
	testUpdateCoins( cards1, 4, 0, 0 );

	// Test just a copper, should be one
	int cards2[4] = { copper, curse, curse, curse };
	testUpdateCoins( cards2, 4, 1, 0 );

	// Test just a silver, should be two
	int cards3[4] = { silver, curse, curse, curse };
	testUpdateCoins( cards3, 4, 2, 0 );

	// Test just a gold, should be three
	int cards4[4] = { gold, curse, curse, curse };
	testUpdateCoins( cards4, 4, 3, 0 );

	// Test one of each, should be six
	int cards5[4] = { copper, silver, gold, curse };
	testUpdateCoins( cards5, 4, 6, 0 );

	return 0;
}

void testUpdateCoins( int *cards, int cardCount, int expectedValue, int bonusCoins )
{
	struct gameState *state = newGame();
	int *k = kingdomCards( adventurer, smithy, council_room, feast, gardens, mine, remodel, village, baron, great_hall );

	initializeGame( 2, k, 1, state );

	int player = 0;

	state->handCount[player] = cardCount;
	int i;
	for( i = 0; i < cardCount; i++ ) {
		state->hand[player][i] = cards[i];
	}

	updateCoins( player, state, bonusCoins );

	if ( state->coins != expectedValue ) {
		printf( "TEST FAILED for updateCoins with ");

		for( i = 0; i < cardCount; i++ ) {
			printf( "%s", cardNames[cards[i]] );

			if ( i != cardCount - 1 ) {
				printf( ", " );
			}
		}

		printf( " with expected value of %d, but updateCoins returned %d\n", expectedValue, state->coins );
	} else {
		printf( "TEST PASSED for updateCoins with " );

		for( i = 0; i < cardCount; i++ ) {
			printf( "%s", cardNames[cards[i]] );

			if ( i != cardCount - 1 ) {
				printf( ", " );
			}
		}

		printf( " with expected value of %d\n", expectedValue );
	}

	free(state);
}
