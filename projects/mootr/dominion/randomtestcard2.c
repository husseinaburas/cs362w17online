/**
 * Title:	Random tester for playFeast() card function
 * Author: Richard Moot
 * Description:	Automatically runs through a series of randomized tests
 * 	to test the playFeast() card function.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define UNIT_ASSERT(conditional, message) \
  if (!conditional) {                     \
    printf("%s FAIL\n", message);         \
  } else {                                \
    printf("%s PASS\n", message);         \
  }

int main(int argv, char** argc) {
  struct gameState G;
  int i, j, l, handCount, deckCount, discardCount, failedTests, players,
      randomSeed, currentPlayer;
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  int numOfTests = 5000;

  // Double check we have the right number of arguments here
  if (argv < 2) {
    printf("You must provide a random seed number.\n");
    return 1;
  } else {
    randomSeed = atoi(argc[1]);
  };

  // Announce beginning of random testing
  printf("\t=======\tBegin Random Testing\t=======\n");

  // Running Random Tests
  for (i = 0; i < numOfTests; i++) {
    players = (rand() % MAX_PLAYERS) + 1;
    initializeGame(players, k, randomSeed, &G);
    currentPlayer = (rand() % players);

    G.whoseTurn = currentPlayer;
    G.handCount[currentPlayer] =
        (rand() % MAX_HAND) + 1;  // Setting a random hand size
    G.deckCount[currentPlayer] = (rand() % MAX_DECK) + 1;
    G.numActions = (rand() % 5) + 1;
    G.playedCardCount = rand() % 20;


  }

  // Announce end of random testing
  printf("\t=======\tEnd Random Testing\t=======\n");


  return 0;
};
