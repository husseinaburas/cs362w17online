#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char **argv) {
  printf("Test isGameOver() \n");

  struct gameState Game;
  int result, randNum, i;
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

	Game.supplyCount[province] == 5;
	for(i = 0; i < 25; i++) {
    Game.supplyCount[i] = 1;
  }
	result = isGameOver(&Game);
	assert(result == 0);

  Game.supplyCount[province] == 2;
  for (i = 0; i < 25; i++) {
    Game.supplyCount[i] = 0;
  }
  result = isGameOver(&Game);
  assert(result == 1);

	Game.supplyCount[province] == 0;
	for(i = 0; i < 25; i++) {
    Game.supplyCount[i] = 1;
  }
	result = isGameOver(&Game);
	assert(result == 1);

	Game.supplyCount[province] == 0;
	for(i = 0; i < 25; i++) {
    Game.supplyCount[i] = 0;
  }
	result = isGameOver(&Game);
	assert(result == 1);

	return 0;
}
