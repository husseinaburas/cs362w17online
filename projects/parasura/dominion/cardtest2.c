#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include <stdbool.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char **argv) {
	printf("Test Smithy card\n");

  struct gameState Game;
  int result, randNum;
  int k[10] = {adventurer,
    smithy,
    council_room,
    feast,
    gardens,
    village,
    mine,
    remodel,
    baron,
    great_hall};
	randNum = rand() % 10;
	result = initializeGame(2, k, randNum, &Game);
  int whoseTurn = Game.whoseTurn;

	Game.handCount[whoseTurn] = 1;
	Game.hand[whoseTurn][0] = smithy;
	Game.handCount[1] = 2;
	Game.deckCount[whoseTurn] = 7;
	Game.deckCount[1] = 8;
	Game.supplyCount[curse] = 4;
	Game.supplyCount[estate] = 4;
	Game.supplyCount[duchy] = 4;
	Game.supplyCount[province] = 4;

	result = playCard(0, 0, 0, 0, &Game);
	assert(result == 0);

	assert(whoseTurn == Game.whoseTurn);
	assert(Game.handCount[whoseTurn] == 3);
	assert(Game.handCount[1] == 2);
	assert(Game.deckCount[whoseTurn] == 4);
	assert(Game.deckCount[1] == 8);
	assert(Game.supplyCount[curse] == 4);
	assert(Game.supplyCount[estate] == 4);
	assert(Game.supplyCount[duchy] == 4);
	assert(Game.supplyCount[province] == 4);

	Game.handCount[whoseTurn] = 1;
	Game.hand[whoseTurn][0] = smithy;
	Game.handCount[1] = 2;
	Game.deckCount[whoseTurn] = 2;
	Game.deckCount[1] = 8;
	Game.supplyCount[curse] = 4;
	Game.supplyCount[estate] = 4;
	Game.supplyCount[duchy] = 4;
	Game.supplyCount[province] = 4;

	result = playCard(0, 0, 0, 0, &Game);
	assert(result == -1);

	assert(whoseTurn == Game.whoseTurn);
	assert(Game.handCount[whoseTurn] == 1);
	assert(Game.handCount[1] == 2);
	assert(Game.deckCount[whoseTurn] == 2);
	assert(Game.deckCount[1] == 8);
	assert(Game.supplyCount[curse] == 4);
	assert(Game.supplyCount[estate] == 4);
	assert(Game.supplyCount[duchy] == 4);
	assert(Game.supplyCount[province] == 4);

	return 0;
}
