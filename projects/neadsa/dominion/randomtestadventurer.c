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

int testCardEffectAdventurer( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int expectedTreasureCount );

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
		int expectedTreasureCount;
		int discardTreasureCount;
		int returnResult;
		for( i = 0; i < randomTestAmount; i++ ) {
			deckSize = rand() % 100;
			handSize = rand() % 100;
			discardSize = rand() % 100;

			deck = (int *) malloc(sizeof(int) * deckSize);
			hand = (int *) malloc(sizeof(int) * handSize);
			discard = (int *) malloc(sizeof(int) * discardSize);

			expectedTreasureCount = 0;
			discardTreasureCount = 0;

			for( j = 0; j < deckSize; j++ ) {
				deck[j] = (rand() % (treasure_map+1)) + curse;
				if ( deck[j] == copper || deck[j] == silver || deck[j] == gold ) {
					expectedTreasureCount++;
				}
			}

			for( j = 0; j < handSize; j++ ) {
				hand[j] = (rand() % (treasure_map+1)) + curse;
			}

			for( j = 0; j < discardSize; j++ ) {
				discard[j] = (rand() % (treasure_map+1)) + curse;
				if ( discard[j] == copper || discard[j] == silver || discard[j] == gold ) {
					discardTreasureCount++;
				}
			}

			if ( expectedTreasureCount < 2 ) {
				expectedTreasureCount = expectedTreasureCount + discardTreasureCount;
			}

			if ( expectedTreasureCount > 2 ) {
				expectedTreasureCount = 2;
			}

			returnResult = testCardEffectAdventurer( deck, deckSize, hand, handSize, discard, discardSize, expectedTreasureCount );

			if ( returnResult == 0 && SHOW_FAILURES ) {
				printf( "\tExpected Treasures %d\tDeck Size %d\tHand Size %d\tDiscard Size %d\n", expectedTreasureCount, deckSize, handSize, discardSize );
			}

			free(deck);
			free(hand);
			free(discard);
		}
	} else {
		printf( "No random seed specified as parameter\n" );
	}
}

int testCardEffectAdventurer( int *deck, int deckLength, int *hand, int handLength, int *discard, int discardLength, int expectedTreasureCount )
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

	cardEffectAdventurer( player, state );

	if ( oldState.handCount[player] + expectedTreasureCount != state->handCount[player] ) {
		if ( SHOW_FAILURES ) {
			printf( "TEST FAILED for cardEffectAdventurer with expected hand size of %d, but new hand size is %d\n", oldState.handCount[player] + expectedTreasureCount, state->handCount[player] );
		}

		free(state);

		return 0;
	}

	free(state);

	return 1;
}
