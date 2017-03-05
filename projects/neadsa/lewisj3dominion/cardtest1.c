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

void testCardEffectSmithy( int *deck, int deckLength, int *hand, int handLength, int smithyHandPos );

int main( int argc, char** argv )
{
	// Test when the smithy is the first card in the hand
	int deck1[8]	= { province, copper, copper, gold, gold, gold, gold, gold };
	int hand1[4]	= { smithy, copper, copper, gold };
	testCardEffectSmithy( deck1, 8, hand1, 4, 0 );

	// Test when the smithy is the second card in the hand
	int deck2[8]	= { province, copper, copper, gold, gold, gold, gold, gold };
	int hand2[4]	= { copper, smithy, copper, gold };
	testCardEffectSmithy( deck2, 8, hand2, 4, 1 );

	return 0;
}

void testCardEffectSmithy( int *deck, int deckLength, int *hand, int handLength, int smithyHandPos )
{
	struct gameState *state = newGame();
	struct gameState oldState;
	int *k = kingdomCards( adventurer, smithy, council_room, feast, gardens, mine, remodel, village, baron, great_hall );

	initializeGame( 2, k, 1, state );

	int player = 0;

	state->deckCount[player] = deckLength;
	state->handCount[player] = handLength;

	int i;
	for( i = 0; i < deckLength; i++ ) {
		state->deck[player][i] = deck[i];
	}

	for( i = 0; i < handLength; i++ ) {
		state->hand[player][i] = hand[i];
	}

	state->whoseTurn = player;

	memcpy( &oldState, state, sizeof(struct gameState) );

	playSmithy( state, smithyHandPos );

	if ( oldState.handCount[player] + 3 - 1 != state->handCount[player] ) {
		printf( "TEST FAILED for cardEffectSmithy with expected hand size of %d, but new hand size is %d\n", oldState.handCount[player] + 3 - 1, state->handCount[player] );

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
		printf( "TEST PASSED for cardEffectSmithy with expected hand size of %d\n", oldState.handCount[player] + 3 - 1 );
	}

	free(state);
}
