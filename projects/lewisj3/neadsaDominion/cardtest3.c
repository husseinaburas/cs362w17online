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

void testCardEffectCouncilRoom( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int councilRoomHandPos );

int main( int argc, char** argv )
{
	int deck1[4]	= { province, province, province, province };
	int hand1[4]	= { council_room, province, province, province };
	int *discard1	= NULL;
	testCardEffectCouncilRoom( deck1, 4, hand1, 4, discard1, 0, 0 );
}

void testCardEffectCouncilRoom( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int councilRoomHandPos )
{
	struct gameState *state = newGame();
	struct gameState oldState;
	int *k = kingdomCards( adventurer, smithy, council_room, feast, gardens, mine, remodel, village, baron, great_hall );

	initializeGame( 2, k, 1, state );

	int player = 0;
	int i;
	for( player = 0; player < state->numPlayers; player++ ) {
		state->deckCount[player] = deckLength;
		state->handCount[player] = handLength;
		state->discardCount[player] = discardLength;

		for( i = 0; i < deckLength; i++ ) {
			state->deck[player][i] = deck[i];
		}

		for( i = 0; i < handLength; i++ ) {
			state->hand[player][i] = hand[i];
		}

		for( i = 0; i < discardLength; i++ ) {
			state->discard[player][i] = discard[i];
		}
	}

	memcpy( &oldState, state, sizeof(struct gameState) );

	cardEffectCouncilRoom( 0, state, councilRoomHandPos );

	player = 0;
	if ( oldState.handCount[player] + 4 - 1 != state->handCount[player] ) {
		printf( "TEST FAILED for cardEffectCouncilRoom on player 0 with expected hand size of %d, but new hand size is %d\n", oldState.handCount[player] + 4 - 1, state->handCount[player] );

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
	} else if ( oldState.numBuys + 1 != state->numBuys ) {
		printf( "TEST FAILED for cardEffectCouncilRoom on player 0 with expected buy of %d, but new buy is %d\n", oldState.numBuys + 1, state->numBuys );
	} else {
		int invalidCount = 0;

		for( player = 1; player < state->numPlayers; player++ ) {
			if ( oldState.handCount[player] + 1 != state->handCount[player] ) {
				printf( "TEST FAILED for cardEffectCouncilRoom on player %d with expected hand size of %d, but new hand size is %d\n", player, oldState.handCount[player] + 1, state->handCount[player] );

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

				invalidCount = 1;
			}
		}

		if ( invalidCount == 0 ) {
			printf( "TEST PASSED for cardEffectCouncilRoom with expected hand sizes and buy count\n" );
		}
	}

	free(state);
}
