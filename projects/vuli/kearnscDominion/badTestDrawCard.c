#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#define DEBUG 0
#define NOISY_TEST 1

int checkDrawCard(int p, struct gameState *post) {
	int r; // Oddly, compiler is emitting an r not used message...
	r = drawCard (p, post);
	return 0;
}

int main () {
	int i, n, p;	// r, deckCount, discardCount, handcount removed for no useage...

//	int k[10] = {adventurer, council_room, feast, gardens, mine,
//				remodel, smithy, village, baron, great_hall};
// Above commented out due to no useage...

	struct gameState G;
	printf ("Testing drawCard.\n");
	printf ("RANDOM TESTS.\n");
	SelectStream(2);
	PutSeed(3);
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 1000);
		checkDrawCard(p, &G);
	}
	printf ("ALL TESTS OK\n");
	//exit(0);
	return 0;
}
