#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include <stdbool.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char **argv) {
	printf("Test Adventurer card\n");

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
	Game.hand[whoseTurn][0] = adventurer;
	Game.deckCount[whoseTurn] = 0;
	Game.deckCount[1] = 3;
	Game.supplyCount[curse] = 4;
	Game.supplyCount[estate] = 4;
	Game.supplyCount[duchy] = 4;
	Game.supplyCount[province] = 4;
	Game.discard[whoseTurn][0] = estate;
	Game.discard[whoseTurn][1] = copper;
	Game.discard[whoseTurn][2] = copper;
	Game.discard[whoseTurn][3] = curse;
	Game.deck[whoseTurn][0] = estate;
	Game.deck[whoseTurn][1] = duchy;

  result = playCard(0, 0, 0, 0, &Game);
	assert(result == 0);

  assert(whoseTurn == Game.whoseTurn);
	assert(coins + 2 == Game.coins);
	assert(Game.handCount[whoseTurn] == 3);
	assert(Game.handCount[1] == 2);
	assert(Game.deckCount[whoseTurn] == 0);
	assert(Game.deckCount[1] == 3);
	assert(Game.discardCount[whoseTurn] == 0);
	assert(Game.discardCount[1] == 0);
	assert(Game.supplyCount[curse] == 4);
	assert(Game.supplyCount[estate] == 4);
	assert(Game.supplyCount[duchy] == 4);
	assert(Game.supplyCount[province] == 4);

	struct gameState treasureGame;
	result = initializeGame(2, k, randNum, &treasureGame);
	whoseTurn = treasureGame.whoseTurn;
	treasureGame.phase = 0;
	treasureGame.numActions = treasureGame.numActions > 0 ? treasureGame.numActions : 1;
	treasureGame.handCount[whoseTurn] = treasureGame.handCount[whoseTurn] > 0 ? treasureGame.handCount[whoseTurn] : 1;
	coins = treasureGame.coins;

	treasureGame.hand[whoseTurn][0] = adventurer;
	treasureGame.deck[whoseTurn][0] = copper;
	treasureGame.deck[whoseTurn][1] = copper;
	treasureGame.deck[whoseTurn][2] = estate;
	treasureGame.deck[whoseTurn][3] = curse;
	treasureGame.handCount[whoseTurn] = 1;
	treasureGame.deckCount[whoseTurn] = 4;
	treasureGame.handCount[1] = 2;
	treasureGame.deckCount[1] = 3;
	treasureGame.supplyCount[curse] = 4;
	treasureGame.supplyCount[estate] = 4;
	treasureGame.supplyCount[duchy] = 4;
	treasureGame.supplyCount[province] = 4;

  result = playCard(0, 0, 0, 0, &treasureGame);
	assert(result == 0);

	assert(whoseTurn == treasureGame.whoseTurn);
	assert(coins + 2 == treasureGame.coins);
	assert(treasureGame.handCount[whoseTurn] == 1);
	assert(treasureGame.handCount[1] == 2);
	assert(treasureGame.deckCount[whoseTurn] == 2);
	assert(treasureGame.deckCount[1] == 3);
	assert(treasureGame.discardCount[whoseTurn] == 2);
	assert(treasureGame.discardCount[1] == 0);
	assert(treasureGame.supplyCount[curse] == 4);
	assert(treasureGame.supplyCount[estate] == 4);
	assert(treasureGame.supplyCount[duchy] == 4);
	assert(treasureGame.supplyCount[province] == 4);

	Game.hand[whoseTurn][0] = adventurer;
	Game.deck[whoseTurn][0] = estate;
	Game.deck[whoseTurn][1] = curse;
	Game.deck[whoseTurn][2] = copper;
	Game.deck[whoseTurn][3] = copper;
	Game.handCount[whoseTurn] = 1;
	Game.deckCount[whoseTurn] = 4;
	Game.handCount[1] = 2;
	Game.deckCount[1] = 3;
	Game.supplyCount[curse] = 4;
	Game.supplyCount[estate] = 4;
	Game.supplyCount[duchy] = 4;
	Game.supplyCount[province] = 4;

  result = playCard(0, 0, 0, 0, &Game);
	assert(result == 0);

	assert(whoseTurn == Game.whoseTurn);
	assert(coins + 2 == Game.coins);
	assert(Game.handCount[whoseTurn] == 1);
	assert(Game.handCount[1] == 2);
	assert(Game.deckCount[whoseTurn] == 0);
	assert(Game.deckCount[1] == 3);
	assert(Game.discardCount[whoseTurn] == 4);
	assert(Game.discardCount[1] == 0);
	assert(Game.supplyCount[curse] == 4);
	assert(Game.supplyCount[estate] == 4);
	assert(Game.supplyCount[duchy] == 4);
	assert(Game.supplyCount[province] == 4);

	Game.hand[whoseTurn][0] = adventurer;
	Game.deck[whoseTurn][0] = estate;
	Game.deck[whoseTurn][1] = copper;
	Game.deck[whoseTurn][2] = copper;
	Game.deck[whoseTurn][3] = curse;
	Game.handCount[whoseTurn] = 1;
	Game.deckCount[whoseTurn] = 4;
	Game.handCount[1] = 2;
	Game.deckCount[1] = 3;
	Game.supplyCount[curse] = 4;
	Game.supplyCount[estate] = 4;
	Game.supplyCount[duchy] = 4;
	Game.supplyCount[province] = 4;

  result = playCard(0, 0, 0, 0, &Game);
	assert(result == 0);

	assert(whoseTurn == Game.whoseTurn);
	assert(coins + 2 == Game.coins);
	assert(Game.handCount[whoseTurn] == 1);
	assert(Game.handCount[1] == 2);
	assert(Game.deckCount[whoseTurn] == 1);
	assert(Game.deckCount[1] == 3);
	assert(Game.discardCount[whoseTurn] == 3);
	assert(Game.discardCount[1] == 0);
	assert(Game.supplyCount[curse] == 4);
	assert(Game.supplyCount[estate] == 4);
	assert(Game.supplyCount[duchy] == 4);
	assert(Game.supplyCount[province] == 4);

	Game.hand[whoseTurn][0] = adventurer;
	Game.deck[whoseTurn][0] = copper;
	Game.deck[whoseTurn][1] = curse;
	Game.deck[whoseTurn][2] = estate;
	Game.deck[whoseTurn][3] = copper;
	Game.handCount[whoseTurn] = 1;
	Game.deckCount[whoseTurn] = 4;
	Game.handCount[1] = 2;
	Game.deckCount[1] = 3;
	Game.supplyCount[curse] = 4;
	Game.supplyCount[estate] = 4;
	Game.supplyCount[duchy] = 4;
	Game.supplyCount[province] = 4;

  result = playCard(0, 0, 0, 0, &Game);
	assert(result == 0);

	assert(whoseTurn == Game.whoseTurn);
	assert(coins + 2 == Game.coins);
	assert(Game.handCount[whoseTurn] == 1);
	assert(Game.handCount[1] == 2);
	assert(Game.deckCount[whoseTurn] == 0);
	assert(Game.deckCount[1] == 3);
	assert(Game.discardCount[whoseTurn] == 4);
	assert(Game.discardCount[1] == 0);
	assert(Game.supplyCount[curse] == 4);
	assert(Game.supplyCount[estate] == 4);
	assert(Game.supplyCount[duchy] == 4);
	assert(Game.supplyCount[province] == 4);

	Game.hand[whoseTurn][0] = adventurer;
	Game.deck[whoseTurn][0] = copper;
	Game.deck[whoseTurn][1] = curse;
	Game.deck[whoseTurn][2] = estate;
	Game.deck[whoseTurn][3] = copper;
	Game.deck[whoseTurn][4] = copper;
	Game.handCount[whoseTurn] = 1;
	Game.deckCount[whoseTurn] = 5;
	Game.handCount[1] = 2;
	Game.deckCount[1] = 3;
	Game.supplyCount[curse] = 4;
	Game.supplyCount[estate] = 4;
	Game.supplyCount[duchy] = 4;
	Game.supplyCount[province] = 4;

	result = playCard(0, 0, 0, 0, &Game);
	assert(result == 0);

	assert(whoseTurn == Game.whoseTurn);
	assert(coins + 2 == Game.coins);
	assert(Game.handCount[whoseTurn] == 1);
	assert(Game.handCount[1] == 2);
	assert(Game.deckCount[whoseTurn] == 1);
	assert(Game.deckCount[1] == 3);
	assert(Game.discardCount[whoseTurn] == 4);
	assert(Game.discardCount[1] == 0);
	assert(Game.supplyCount[curse] == 4);
	assert(Game.supplyCount[estate] == 4);
	assert(Game.supplyCount[duchy] == 4);
	assert(Game.supplyCount[province] == 4);

	return 0;
}
