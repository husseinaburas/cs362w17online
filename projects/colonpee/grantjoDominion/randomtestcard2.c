#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define NUMTESTS 200
#define MAXPLAYERS 4
#define MINPLAYERS 2
#define DECKSIZE 100
#define HANDSIZE 100

//Assert true returns error message if condition fails
int asserttrue (int condition, char* message) {
  if (condition) {
    return 0;
  }
  else {
    printf("TEST FAILED: %s\n", message);
    return 1;
  }
}


int testGardens() {
  printf ("TESTING Smithy card!\n\n");

  // Create gamestate
  struct gameState G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

  int r = rand();

  for (int x = 0; x < NUMTESTS; x++) {
    int numPlayers = 1 + rand() % MAXPLAYERS;
    if (numPlayers < MINPLAYERS) {
      numPlayers++;
    }

    initializeGame(numPlayers, k, r, &G);

    int deckSize;
    int handSize;
    int gardenSize;
    int discardSize;

    

    printf ("Number of players: %d\n\n", numPlayers);

    for (int currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++) {
      deckSize = rand() % DECKSIZE;
      handSize = rand() % HANDSIZE;
      gardenSize = rand() % DECKSIZE;
      discardSize = rand() % DECKSIZE;

      //set player's deck and hand size
      G.deckCount[currentPlayer] = deckSize;
      G.handCount[currentPlayer] = handSize;
      G.discardCount[currentPlayer] = discardSize;


      // int deckCount = G.deckCount[currentPlayer];
      // int handCount = G.handCount[currentPlayer];
      // int discardCount = G.discardCount[currentPlayer];

      //adding estates to deck
      for (int l = 0; l < deckSize; l++) {
        G.deck[currentPlayer][l] = estate;
      }

      //adding some estates to hand
      for (int l = 0; l < handSize; l++) {
        G.hand[currentPlayer][l] = estate;
      }

      //making the discardPile worthless cards
      for (int g = 0; g <discardSize; g++) {
        G.discard[currentPlayer][g] = -1;
      }

      int score = scoreFor(currentPlayer, &G);

      printf ("Player #%d deckCount = %d, handCount = %d, discardCount = %d\n", currentPlayer+1, G.deckCount[currentPlayer], G.handCount[currentPlayer], G.discardCount[currentPlayer]);
      printf ("Current Score = %d\n", score);
      char correctScore[100];
      int firstScore = G.deckCount[currentPlayer] + G.handCount[currentPlayer];
      snprintf(correctScore, 100, "Score should be %d", firstScore);
      asserttrue(score == firstScore, correctScore);

      //add gardens to deck
      for (int x = 0; x < gardenSize; x++) {
        G.deck[currentPlayer][G.deckCount[currentPlayer]] = gardens;
        G.deckCount[currentPlayer]++;
      }
      
      
      printf ("\nAdded %d gardens to deck...\n\n", gardenSize);

      printf ("Player #%d deckCount = %d, handCount = %d, discardCount = %d\n", currentPlayer+1, G.deckCount[currentPlayer], G.handCount[currentPlayer], G.discardCount[currentPlayer]);

      //Check score
      printf("CHECKING SCORE FOR PLAYER %d\n", currentPlayer+1);
      int scoreAfter = scoreFor(currentPlayer, &G);

      printf ("Current Score = %d\n\n", scoreAfter);
      int fullCount = G.deckCount[currentPlayer] + G.handCount[currentPlayer] + G.discardCount[currentPlayer];
      snprintf(correctScore, 100, "Score should be %d", (firstScore + fullCount/10));
      asserttrue(scoreAfter == (firstScore + (gardenSize * (fullCount/10))), correctScore);

    }
  }

  return 0;
}

int main(int argc, char** argv) {

  //verify that there is an command line argument
  if (argc < 2) {
    printf("Correct Usage: %s [seedNumber]\n", argv[0]);
    printf("Using 10 as seed for now..\n");
    srand (10);
  }
  else {
    srand(atoi(argv[1]));
  }
  testGardens();
  return 0;
}