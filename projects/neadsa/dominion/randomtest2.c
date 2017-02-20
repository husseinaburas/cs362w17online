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

int testCardEffectCouncilRoom( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int councilRoomHandPos );

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
		int discardSize;
		int *deck;
		int *hand;
		int *discard;
		int councilRoomPos;
		for( i = 0; i < randomTestAmount; i++ ) {
			deckSize = (rand() % 96) + 4;
			handSize = (rand() % 99) + 1;
			discardSize = rand() % 100;

			deck = (int *) malloc(sizeof(int) * deckSize);
			hand = (int *) malloc(sizeof(int) * handSize);
			discard = (int *) malloc(sizeof(int) * discardSize);

			councilRoomPos = -1;

			for( j = 0; j < deckSize; j++ ) {
				deck[j] = (rand() % (treasure_map+1)) + curse;
			}

			for( j = 0; j < handSize; j++ ) {
				hand[j] = (rand() % (treasure_map+1)) + curse;
				if ( hand[j] == council_room && councilRoomPos == -1 ) {
					councilRoomPos = j;
				}
			}

			for( j = 0; j < discardSize; j++ ) {
				discard[j] = (rand() % (treasure_map+1)) + curse;
			}

			if ( councilRoomPos == -1 ) {
				hand[0] = council_room;
				councilRoomPos = 0;
			}

			testCardEffectCouncilRoom( deck, deckSize, hand, handSize, discard, discardSize, councilRoomPos );

			free(deck);
			free(hand);
			free(discard);
		}
	} else {
		printf( "No random seed specified as parameter\n" );
	}
}

int testCardEffectCouncilRoom( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int councilRoomHandPos )
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
		if ( SHOW_FAILURES ) {
			printf( "TEST FAILED for cardEffectCouncilRoom on player 0 with expected hand size of %d, but new hand size is %d\n", oldState.handCount[player] + 4 - 1, state->handCount[player] );
		}
		free(state);
		return 0;
	} else if ( oldState.numBuys + 1 != state->numBuys ) {
		if ( SHOW_FAILURES ) {
			printf( "TEST FAILED for cardEffectCouncilRoom on player 0 with expected buy of %d, but new buy is %d\n", oldState.numBuys + 1, state->numBuys );
		}
		free(state);
		return 0;
	} else {
		int invalidCount = 0;

		for( player = 1; player < state->numPlayers; player++ ) {
			if ( oldState.handCount[player] + 1 != state->handCount[player] ) {
				if ( SHOW_FAILURES ) {
					printf( "TEST FAILED for cardEffectCouncilRoom on player %d with expected hand size of %d, but new hand size is %d\n", player, oldState.handCount[player] + 1, state->handCount[player] );
				}

				invalidCount = 1;
			}
		}

		if ( invalidCount == 0 ) {
			free(state);
			return 1;
		}
	}

	free(state);
	return 0;
}
