#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include <stdbool.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char **argv) {
	printf("Test Great Hall card\n");

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

  Game.phase = 0;
	Game.numActions = Game.numActions > 0 ? Game.numActions : 1;
	Game.handCount[whoseTurn] = Game.handCount[whoseTurn] > 0 ? Game.handCount[whoseTurn] : 1;
	int coins = Game.coins;

	Game.handCount[whoseTurn] = 1;
	Game.handCount[1] = 2;
	Game.hand[whoseTurn][0] = great_hall;
	Game.deckCount[whoseTurn] = 0;
	Game.deckCount[1] = 3;
	Game.supplyCount[whoseTurn] = 5;
	Game.supplyCount[1] = 5;
	Game.discardCount[whoseTurn] = 0;
	Game.discardCount[1] = 0;
	Game.numActions = 2;
	Game.supplyCount[curse] = 4;
	Game.supplyCount[estate] = 4;
	Game.supplyCount[duchy] = 4;
	Game.supplyCount[province] = 4;

  result = playCard(0, 0, 0, 0, &Game);
	assert(result == 0);

	assert(whoseTurn == Game.whoseTurn);
	assert(Game.handCount[whoseTurn] == 1);
	assert(Game.handCount[1] == 2);
	assert(Game.deckCount[whoseTurn] == 0);
	assert(Game.deckCount[1] == 3);
	assert(Game.discardCount[whoseTurn] == 0);
	assert(Game.discardCount[1] == 0);
	assert(Game.supplyCount[whoseTurn] == 6);
	assert(Game.supplyCount[1] == 5);
	assert(Game.numActions == 3);
	assert(Game.supplyCount[curse] == 4);
	assert(Game.supplyCount[estate] == 4);
	assert(Game.supplyCount[duchy] == 4);
	assert(Game.supplyCount[province] == 4);

	Game.handCount[whoseTurn] = 1;
	Game.handCount[1] = 2;
	Game.hand[whoseTurn][0] = great_hall;
	Game.deckCount[whoseTurn] = 3;
	Game.deckCount[1] = 3;
	Game.supplyCount[whoseTurn] = 5;
	Game.supplyCount[1] = 5;
	Game.discardCount[whoseTurn] = 0;
	Game.discardCount[1] = 0;
	Game.numActions = 2;
	Game.supplyCount[curse] = 4;
	Game.supplyCount[estate] = 4;
	Game.supplyCount[duchy] = 4;
	Game.supplyCount[province] = 4;

	result = playCard(0, 0, 0, 0, &Game);
	assert(result == 0);

	assert(whoseTurn == Game.whoseTurn);
	assert(Game.handCount[whoseTurn] == 2);
	assert(Game.handCount[1] == 2);
	assert(Game.deckCount[whoseTurn] == 2);
	assert(Game.deckCount[1] == 3);
	assert(Game.discardCount[whoseTurn] == 0);
	assert(Game.discardCount[1] == 0);
	assert(Game.supplyCount[whoseTurn] == 6);
	assert(Game.supplyCount[1] == 5);
	assert(Game.numActions == 3);
	assert(Game.supplyCount[curse] == 4);
	assert(Game.supplyCount[estate] == 4);
	assert(Game.supplyCount[duchy] == 4);
	assert(Game.supplyCount[province] == 4);

	return 0;
}