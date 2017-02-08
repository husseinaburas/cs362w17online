/*test function int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    struct gameState G;
    int seed = 1000;
	int numPlayers = 0;
	int count;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    printf ("-----------------TESTING fullDeckCount():-----------------\n");
    G.deckCount[0] = 3;
    G.handCount[0] = 3;
    G.discardCount[0] = 2;

	G.hand[0][0] = copper;
    G.hand[0][1] = village;
    G.hand[0][2] = village;
	G.deck[0][0] = village;
    G.deck[0][1] = estate;
    G.deck[0][1] = estate;
	G.discard[0][0] = smithy;
	G.discard[0][1] = smithy;

    printf("Test adding count on deck, hand, discard\n");
    count = fullDeckCount(0, copper, &G);
    printf("expected=%d,fullDeckCount=%d\n",1,count);

    count = fullDeckCount(0, smithy, &G);
    printf("expected=%d,fullDeckCount=%d\n",2,count);

    count = fullDeckCount(0, adventurer, &G);
    printf("expected=%d,fullDeckCount=%d\n",0,count);
    printf ("-----------------TESTING fullDeckCount(): END-----------------\n");
}
