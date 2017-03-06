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

int testCardEffectSmithy( int *deck, int deckLength, int *hand, int handLength, int smithyHandPos );

int SHOW_FAILURES = 1;

int main( int argc, char** argv )
{
	if ( argc > 2 ) {
		SHOW_FAILURES = 0;
	}
	if ( argc >= 2 ) {
		int seed = 0;
		sscanf( argv[1], "%d", &seed );
		srand(seed);

		int randomTestAmount = 1000000;

		int i;
		int j;
		int deckSize;
		int handSize;
		int *deck;
		int *hand;
		int smithyPos;
		for( i = 0; i < randomTestAmount; i++ ) {
			deckSize = rand() % 100;
			handSize = (rand() % 99) + 1;

			deck = (int *) malloc(sizeof(int) * deckSize);
			hand = (int *) malloc(sizeof(int) * handSize);

			smithyPos = -1;

			for( j = 0; j < deckSize; j++ ) {
				deck[j] = (rand() % (treasure_map+1)) + curse;
			}

			for( j = 0; j < handSize; j++ ) {
				hand[j] = (rand() % (treasure_map+1)) + curse;
				if ( hand[j] == smithy && smithyPos == -1 ) {
					smithyPos = j;
				}
			}

			if ( smithyPos == -1 ) {
				hand[0] = smithy;
				smithyPos = 0;
			}

			testCardEffectSmithy( deck, deckSize, hand, handSize, smithyPos );

			free(deck);
			free(hand);
		}
	} else {
		printf( "No random seed specified as parameter\n" );
	}

	return 0;
}

int testCardEffectSmithy( int *deck, int deckLength, int *hand, int handLength, int smithyHandPos )
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

	int expected = 3;

	if ( deckLength < expected ) {
		expected = deckLength;
	}

	if ( oldState.handCount[player] + expected - 1 != state->handCount[player] ) {
		if ( SHOW_FAILURES ) {
			printf( "TEST FAILED for cardEffectSmithy with expected hand size of %d, but new hand size is %d\n", oldState.handCount[player] + 3 - 1, state->handCount[player] );
			printf( "\tOld Hand Size %d\tNew Hand Size %d\tOld Deck Size %d\tNew Deck Size %d\n", oldState.handCount[player], state->handCount[player], oldState.deckCount[player], state->deckCount[player] );
		}

		free(state);

		return 0;
	}

	free(state);

	return 1;
}
