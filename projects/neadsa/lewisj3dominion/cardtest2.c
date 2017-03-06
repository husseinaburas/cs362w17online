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

void testCardEffectAdventurer( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int expectedTreasureCount );

int main( int argc, char** argv )
{
	// Test no treasures, should only have 0 treasures expected
	int deck1[4]	= { province, province, province, province };
	int hand1[4]	= { adventurer, province, province, province };
	int *discard1	= NULL;
	testCardEffectAdventurer( deck1, 4, hand1, 4, discard1, 0, 0 );

	// Test one treasure, should only have 1 treasure expected
	int deck2[4]	= { copper, province, province, province };
	int hand2[4]	= { adventurer, province, province, province };
	testCardEffectAdventurer( deck2, 4, hand2, 4, discard1, 0, 1 );

	// Test two treasures, should only have 2 treasures expected
	int deck3[4]	= { copper, copper, province, province };
	int hand3[4]	= { adventurer, province, province, province };
	testCardEffectAdventurer( deck3, 4, hand3, 4, discard1, 0, 2 );

	// Test three treasures, should only have 2 treasures expected
	int deck4[4]	= { copper, copper, copper, province };
	int hand4[4]	= { adventurer, province, province, province };
	testCardEffectAdventurer( deck4, 4, hand4, 4, discard1, 0, 2 );

	// Test shuffle discard for treasures, should only have 1 treasure expected
	int *deck5		= NULL;
	int hand5[4]	= { adventurer, province, province, province };
	int discard5[4]	= { copper, province, province, province };
	testCardEffectAdventurer( deck5, 0, hand5, 4, discard5, 4, 1 );

	return 0;
}

void testCardEffectAdventurer( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int expectedTreasureCount )
{
	struct gameState *state = newGame();
	struct gameState oldState;
	int *k = kingdomCards( adventurer, smithy, council_room, feast, gardens, mine, remodel, village, baron, great_hall );

	initializeGame( 2, k, 1, state );

	int player = 0;

	state->deckCount[player] = deckLength;
	state->handCount[player] = handLength;
	state->discardCount[player] = discardLength;

	int i;
	for( i = 0; i < deckLength; i++ ) {
		state->deck[player][i] = deck[i];
	}

	for( i = 0; i < handLength; i++ ) {
		state->hand[player][i] = hand[i];
	}

	for( i = 0; i < discardLength; i++ ) {
		state->discard[player][i] = discard[i];
	}

	state->whoseTurn = player;

	memcpy( &oldState, state, sizeof(struct gameState) );

	playAdventurer( state );

	if ( oldState.handCount[player] + expectedTreasureCount != state->handCount[player] ) {
		printf( "TEST FAILED for cardEffectAdventurer with expected hand size of %d, but new hand size is %d\n", oldState.handCount[player] + expectedTreasureCount, state->handCount[player] );

		printf("\tNew Hand(");

		for( i = 0; i < state->handCount[player]; i++ ) {
			printf( "%s", cardNames[state->hand[player][i]] );

			if ( i != state->handCount[player] - 1 ) {
				printf( ", " );
			}
		}

		printf(")\n\tOld Hand(");

		for( i = 0; i < oldState.handCount[player]; i++ ) {
			printf( "%s", cardNames[oldState.hand[player][i]] );

			if ( i != oldState.handCount[player] - 1 ) {
				printf( ", " );
			}
		}

		printf(")\n");
	} else {
		printf( "TEST PASSED for cardEffectAdventurer with expected hand size of %d\n", oldState.handCount[player] + expectedTreasureCount );
	}

	free(state);
}
