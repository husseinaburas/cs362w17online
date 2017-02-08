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

void testFullDeckCount( int *deck, int deckLength, int *hand, int handLength, int *discard, int card, int discardLength, int expectedValue );

int main( int argc, char** argv )
{
	int deck[4]	= { baron, copper, copper, gold };
	int hand[4]	= { province, smithy, smithy, gold };
	int discard[4]	= { council_room, gardens, mine, gold };

	// Test finding a card that doesn't exist in the deck/hand/discard
	testFullDeckCount( deck, 4, hand, 4, discard, 4, great_hall, 0 );

	// Test finding a card that doesn't exist in the deck/hand
	testFullDeckCount( deck, 4, hand, 4, discard, 4, council_room, 1 );

	// Test finding a card that doesn't exist in the deck/discard
	testFullDeckCount( deck, 4, hand, 4, discard, 4, province, 1 );

	// Test finding a card that doesn't exist in the hand/discard
	testFullDeckCount( deck, 4, hand, 4, discard, 4, baron, 1 );

	// Test finding a card that exists in deck/hand/discard
	testFullDeckCount( deck, 4, hand, 4, discard, 4, gold, 3 );

	return 0;
}

void testFullDeckCount( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int card, int expectedValue )
{
	struct gameState *state = newGame();
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

	for( i = 0; i < deckLength; i++ ) {
		state->discard[player][i] = discard[i];
	}

	int output = fullDeckCount( player, card, state );

	if ( output != expectedValue ) {
		printf( "TEST FAILED for fullDeckCount with expected value of %d, but fullDeckCount returned %d\n\tDeck(", expectedValue, output );

		for( i = 0; i < deckLength; i++ ) {
			printf( "%s", cardNames[deck[i]] );

			if ( i != deckLength - 1 ) {
				printf( ", " );
			}
		}

		printf(")\n\tHand(");

		for( i = 0; i < handLength; i++ ) {
			printf( "%s", cardNames[hand[i]] );

			if ( i != handLength - 1 ) {
				printf( ", " );
			}
		}

		printf(")\n\tDiscard(");

		for( i = 0; i < discardLength; i++ ) {
			printf( "%s", cardNames[discard[i]] );

			if ( i != discardLength - 1 ) {
				printf( ", " );
			}
		}

		printf(")\n");
	} else {
		printf( "TEST PASSED for fullDeckCount with expected value of %d\n\tDeck(", expectedValue );

		for( i = 0; i < deckLength; i++ ) {
			printf( "%s", cardNames[deck[i]] );

			if ( i != deckLength - 1 ) {
				printf( ", " );
			}
		}

		printf(")\n\tHand(");

		for( i = 0; i < handLength; i++ ) {
			printf( "%s", cardNames[hand[i]] );

			if ( i != handLength - 1 ) {
				printf( ", " );
			}
		}

		printf(")\n\tDiscard(");

		for( i = 0; i < discardLength; i++ ) {
			printf( "%s", cardNames[discard[i]] );

			if ( i != discardLength - 1 ) {
				printf( ", " );
			}
		}

		printf(")\n");
	}

	free(state);
}
