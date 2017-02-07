#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char **argv) {
  printf("Test whoseTurn() \n");

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

	for (i = 0; i < 5; i++) {
		assert(whoseTurn(&Game) == Game.whoseTurn);
		Game.whoseTurn++;
	}

	return 0;
}
