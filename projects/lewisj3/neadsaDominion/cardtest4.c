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

void testCardEffectMine( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int mineHandPos, int discardHandChoice, int newCardChoice, int expectedOutput );

int main( int argc, char** argv )
{
	int deck1[4]	= { province, province, province, province };
	int hand1[4]	= { mine, copper, province, province };
	int *discard1	= NULL;

	// Test invalid discardHandChoice
	testCardEffectMine( deck1, 4, hand1, 4, discard1, 0, 0 /*mine pos*/, -1/*discard pos*/, silver, -1 );

	// Test invalid range of newCardChoice
	testCardEffectMine( deck1, 4, hand1, 4, discard1, 0, 0 /*mine pos*/, 1/*discard pos*/, 99, -1 );

	// Test too expensive newCardChoice
	testCardEffectMine( deck1, 4, hand1, 4, discard1, 0, 0 /*mine pos*/, 1/*discard pos*/, gold, -1 );

	// Test valid card purchase
	testCardEffectMine( deck1, 4, hand1, 4, discard1, 0, 0 /*mine pos*/, 1/*discard pos*/, silver, 0 );

}

void testCardEffectMine( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int mineHandPos, int discardHandChoice, int newCardChoice, int expectedOutput )
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

	memcpy( &oldState, state, sizeof(struct gameState) );

	int output = cardEffectMine( player, state, mineHandPos, discardHandChoice, newCardChoice );

	if ( output != expectedOutput ) {
		printf( "TEST FAILED for cardEffectMine with expected output of %d, but returned %d\n", expectedOutput, output );
	} else {
		if ( expectedOutput != -1 ) {
			if ( oldState.handCount[player] - 1 != state->handCount[player] ) {
				printf( "TEST FAILED for cardEffectMine with expected hand size of %d, but new hand size is %d\n", oldState.handCount[player] - 1, state->handCount[player] );

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
				printf( "TEST PASSED for cardEffectMine with expected output of %d and new hand size of %d\n", expectedOutput, oldState.handCount[player] + 1 );
			}
		} else {
			printf( "TEST PASSED for cardEffectMine with expected output of %d, which is indicates invalid inputs(this is good, given it was expected)!\n", expectedOutput );
		}
	}

	free(state);
}
