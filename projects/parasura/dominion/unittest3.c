#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char **argv) {
  printf("Test buyCard() \n");

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

  Game.numBuys = 2;
  Game.coins = 10;
  result = buyCard(1, &Game);
  assert(result == 0);

  Game.numBuys = 0;
  Game.coins = 10;
  result = buyCard(1, &Game);
  assert(result == -1);

  Game.numBuys = 1;
  Game.coins = 5;
  for(i = 0; i < 100; i++) {
    Game.supplyCount[i] = 0;
  }
  assert(result == -1);

  Game.numBuys = 1;
  Game.coins = 0;
  result = buyCard(1, &Game);
  assert(result == -1);

  Game.numBuys = 1;
  Game.coins = 2;
  result = buyCard(7, &Game);
  assert(result == -1);

  return 0;
}
