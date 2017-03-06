#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "fullDeckCount"

int main(){
	int i;
	int numPlayers = 2;
	int seed = 1000;
	int player1 = 0;
	int deckCount, handCount, discardCount;
	int count;
	struct gameState g, test_g;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			smithy, village, baron, great_hall};

	printf("--------------- Testing Card: %s ---------------\n", TESTCARD);
	
	// Initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &g);
	// Copy game state
	memcpy(&test_g, &g, sizeof(struct gameState));

	// Case 1: player has empty deck, hand, & discard piles
	deckCount = 0;
	handCount = 0;
	discardCount = 0;
	test_g.deckCount[player1] = deckCount;
	test_g.handCount[player1] = handCount;
	test_g.discardCount[player1] = discardCount;
	count = fullDeckCount(player1, smithy, &test_g);
	asserttrue("smithy count with empty deck, hand, & discard piles", count, 0);
	
	// Case 2: player has 3 in deck, empty hand & discard piles
	deckCount = 3;
	test_g.deckCount[player1] = deckCount;
	for(i = 0; i < deckCount; i++){
		test_g.deck[player1][i] = adventurer;
	}
	// Count for card not contained in deck
	count = fullDeckCount(player1, smithy, &test_g);
	asserttrue("non-matching cards in deck, empty hand & discard", count, 0);
	// Count for card contained in deck
	count = fullDeckCount(player1, adventurer, &test_g);
	asserttrue("matching cards in deck, empty hand & discard", count, deckCount);
	
	// Case 3: player has 3 in deck & hand, empty discard pile
	handCount = 3;
	test_g.handCount[player1] = handCount;
	for(i = 0; i < handCount; i++){
		test_g.hand[player1][i] = adventurer;
	}
	// Count for card not contained in deck or hand
	count = fullDeckCount(player1, silver, &test_g);
	asserttrue("non-matching cards in deck & hand, empty discard", count, 0);
	// Count for card contained in deck and hand
	count = fullDeckCount(player1, adventurer, &test_g);
	asserttrue("matching cards in deck & hand, empty discard", count, deckCount + handCount);
	// Count for card contained in hand only
	for(i = 0; i < handCount; i++){
		test_g.hand[player1][i] = mine;
	}
	count = fullDeckCount(player1, mine, &test_g);
	asserttrue("matching in hand, non-matching in deck, empty discard", count, handCount);
	
	// Case 4: player has 3 in deck, hand, & discard piles
	discardCount = 3;
	test_g.discardCount[player1] = discardCount;
	for(i = 0; i < discardCount; i++){
		test_g.discard[player1][i] = feast;
	}
	// Count for 3 cards matching in discard pile, non-matching in other piles
	count = fullDeckCount(player1, feast, &test_g);
	asserttrue("matching in discard, non-matching in other 2 piles", count, discardCount);
	// Count for matching in all three piles
	for(i = 0; i < handCount; i++){
		test_g.deck[player1][i] = feast;
		test_g.hand[player1][i] = feast;
	}
	count = fullDeckCount(player1, feast, &test_g);
	asserttrue("matching in all 3 piles", count, deckCount + handCount + discardCount);
	// Count for non-matching in all three piles
	count = fullDeckCount(player1, great_hall, &test_g);
	asserttrue("non-matching in all 3 piles", count, 0);
	
	printf("--------------- Completed Card: %s ---------------\n", TESTCARD);
	return 0;
}