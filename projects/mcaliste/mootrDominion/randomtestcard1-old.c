/**
 * Title:	Random tester for playSmithy() card function
 * Author: Richard Moot
 * Description:	Automatically runs through a series of randomized tests
 * 	to test the playSmithy() card function.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int logFailureState(struct gameState failState, int iteration) {
  printf("Iteration %d failed. Game state= \n", iteration + 1);
  int k;
  for (k = 0; k < failState.numPlayers; k++) {
    printf(
        "\tPlayer: %d, whoseTurn: %d, Hand Count: %d, Deck Count: %d, "
        "Played Card "
        "Count: "
        "%d\n",
        k, failState.whoseTurn, failState.handCount[k], failState.deckCount[k],
        failState.playedCardCount);
  };

  return 0;
}

int main(int argc, char** argv) {
  struct gameState G, copyG;
  int i, j, players, randomSeed, currentPlayer, iterationFailed, randHandPos;
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  int numOfTestCycles = 2000;
  int failedTests = 0;
  int failedIterations = 0;

  // Double check we have the right number of arguments here
  if (argc < 2) {
    printf("You must provide a random seed number. Setting to 3.\n");
    randomSeed = 3;
  } else {
    randomSeed = atoi(argv[argc - 1]);
  };

  // Announce beginning of random testing
  printf("\t=======\tBegin Random Testing of playSmithy\t=======\n");

  // Running Random Tests
  for (i = 0; i < numOfTestCycles; i++) {
    iterationFailed = 0;                   // Reset iteration fail flag
    players = (rand() % MAX_PLAYERS) + 1;  // Setting random number of players
    initializeGame(players, k, randomSeed, &G);  // Initializing game
    currentPlayer = (rand() % players);  // Set current player in players range
    G.whoseTurn = currentPlayer;         // Setting state variables for testing
    G.handCount[currentPlayer] = (rand() % MAX_HAND) + 1;
    G.deckCount[currentPlayer] = (rand() % MAX_DECK) + 1;
    G.numActions = (rand() % 5) + 1;
    G.playedCardCount = rand() % 20;

    // Setting random hand position for player to smithy card
    randHandPos = rand() % G.handCount[currentPlayer];
    G.hand[currentPlayer][randHandPos] = smithy;

    // Copying state to compare to for testing
    memcpy(&copyG, &G, sizeof(struct gameState));

    // Playing smithy card
    playSmithy(&G, randHandPos);

    // Testing proper behavior of smithy

    // Checking discard count to ensure the card was not discarded
    if (G.discardCount[currentPlayer] != 0) {
      iterationFailed = 1;
      failedTests += 1;
    }
    // Testing deck count has changed
    if (G.deckCount[currentPlayer] != copyG.deckCount[currentPlayer]) {
      iterationFailed = 1;
      failedTests += 1;
    }
    // Testing player's hand count increased by 2 (3 from drawing, played 1)
    if (G.handCount[currentPlayer] != copyG.handCount[currentPlayer] + 2) {
      iterationFailed = 1;
      failedTests += 1;
    }
    // Testing card is in played cards deck
    if (G.playedCards[G.playedCardCount - 1] != smithy) {
      iterationFailed = 1;
      failedTests += 1;
    }
    // Deck has decreased by 3 cards
    if (G.deckCount[currentPlayer] == copyG.deckCount[currentPlayer] - 3) {
      iterationFailed = 1;
      failedTests += 1;
    }
    // Check other player's state has not changed
    for (j = 0; j < players; j++) {
      if (j == currentPlayer) {
        continue;
      } else {
        if (G.deckCount[j] != copyG.deckCount[j]) {
          iterationFailed = 1;
          failedTests += 1;
        }
        if (G.handCount[j] != copyG.handCount[j]) {
          iterationFailed = 1;
          failedTests += 1;
        }
      }
    }
    // Check province supply count has not changed
    if (G.supplyCount[province] != copyG.supplyCount[province]) {
      iterationFailed = 1;
      failedTests += 1;
    }

    // Check if iteration has failed
    if (iterationFailed > 0) {
      failedIterations += 1;
      logFailureState(G, i);
    }
  };
  printf("\t%d Tests failed, %d/%d Iterations Failed\n", failedTests,
         failedIterations, numOfTestCycles);

  // Announce end of random testing
  printf("\t=======\tEnd Random Testing of playSmithy\t=======\n");

  return 0;
};
