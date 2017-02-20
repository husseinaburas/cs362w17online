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


int testSmithy() {
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
    int discardSize;

    

    printf ("Number of players: %d\n\n", numPlayers);

    for (int currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++) {
      deckSize = rand() % DECKSIZE;
      handSize = rand() % HANDSIZE;
      discardSize = rand() % DECKSIZE;

      //set player's deck and hand size
      G.deckCount[currentPlayer] = deckSize;
      G.handCount[currentPlayer] = handSize;
      G.discardCount[currentPlayer] = discardSize;


      int deckCount = G.deckCount[currentPlayer];
      int handCount = G.handCount[currentPlayer];
      int discardCount = G.discardCount[currentPlayer];
      
      printf ("Player #%d deckCount = %d, handCount = %d, discardCount = %d\n", currentPlayer+1, deckCount, handCount, discardCount);
      
      //run Adventurer code
      printf("PLAYING SMITHY ON PLAYER %d\n", currentPlayer+1);
      runSmithy(&G, currentPlayer);

      int deckCountAfter = G.deckCount[currentPlayer];
      int handCountAfter = G.handCount[currentPlayer];
      int discardCountAfter = G.discardCount[currentPlayer];
      printf ("Player #%d deckCount = %d, handCount = %d, discardCount = %d\n\n", currentPlayer+1, deckCountAfter, handCountAfter, discardCountAfter);
      if (deckCount >= 3) {
        asserttrue(handCountAfter == handCount+3, "Should have drawn three cards\n");
      }
      else if ((deckCount == 2 && discardCount < 1) || (deckCount == 0 && discardCount == 2)) {
        asserttrue(handCountAfter == handCount+2, "Should have drawn two cards\n");
      }
      else if ((deckCount == 1 && discardCount < 2) || (deckCount == 0 && discardCount == 1)) {
        asserttrue(handCountAfter == handCount+1, "Should have drawn one card\n");
      }
      else if (deckCount == 0 && discardCount == 0) {
        asserttrue(handCountAfter == handCount, "Should have drawn no cards\n");
      }
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
  testSmithy();
  return 0;
}