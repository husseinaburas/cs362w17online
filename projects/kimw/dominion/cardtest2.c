#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
	printf("------  adventurer unit test ------\n");
	
	//initialize game
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	struct gameState G, oG;
	r = initializeGame(2, k, 1, &G);

	int temphand[MAX_HAND];
	int drawntreasure=0;
	int cardDrawn;
	int z = 0;

	//Place adventure card in Players 1 hand
	G.hand[0][0] = k[0];

	// save initial state
	memcpy(&oG, &G, sizeof(struct gameState));

	printf("Player 1 plays adventurer card\n");
	adventurerCard(0, &G, cardDrawn, drawntreasure, temphand, z);

	printf("Card count increased by 2\n");
	int cardCount = G.handCount[0] - oG.handCount[0];
	asserttrue(cardCount == 2);

	printf("Discard count increased\n");
	int discardCount = G.discardCount[0] - oG.discardCount[0];
	asserttrue(discardCount >= 0);

	printf("Deck count decreased\n");
	int deckCount = G.deckCount[0] - oG.deckCount[0];
	asserttrue(deckCount < 0);

	printf("Make sure the same all drawn/discarded cards are accounted for\n");
	int difference = cardCount + discardCount + deckCount;
	asserttrue(difference == 0);

	printf("--------------- end --------------\n");
	return 0;
}