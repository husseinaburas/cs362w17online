#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char **argv) {
  printf("Test shuffle() \n");

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

  Game.deckCount[1] = 1;
  result = shuffle(1, &Game);
  assert(result == 0);

  Game.deckCount[1] = -1;
  result = shuffle(1, &Game);
  assert(result == -1);

  Game.deckCount[1] = 0;
  result = shuffle(1, &Game);
  assert(result == -1);

  return 0;
}
