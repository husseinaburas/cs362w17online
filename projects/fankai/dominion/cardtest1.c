/*int DoSmithy(int currentPlayer, struct gameState *state, int handPos)
{
  //+3 Cards
  int i;
  for (i = 0; i == 3; i++)
  {
    drawCard(currentPlayer, state);
  }

  //discard card from hand
  discardCard(handPos, currentPlayer, state, 1);//?

  return 0;
}
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Smithy"

int main() {
    int handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G,G2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    memcpy(&G2, &G, sizeof(struct gameState));

	printf("----------------- Testing Card: Smithy %s ----------------\n", TESTCARD);
	printf("Testing +3 cards and discard correctly\n");
    DoSmithy(0,&G,handpos);
	printf("hand count = %d, expected = %d\n", G.handCount[0], G2.handCount[0]+3-1);
	printf("deck count = %d, expected = %d\n", G.deckCount[0], G2.deckCount[0]-3);
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


