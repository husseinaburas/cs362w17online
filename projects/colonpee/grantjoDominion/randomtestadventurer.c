#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define NUMTESTS 100
#define MAXPLAYERS 4
#define MINPLAYERS 2
#define DECKSIZE 10

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


int testAdventurer() {
  printf ("TESTING Adventurer card!\n\n");

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

    int deckSize = rand() % DECKSIZE;
    int discardCount = 1 + rand() % DECKSIZE;

    //set player's deck
    for (int i = 0; i < numPlayers; i++) {
      G.deckCount[i] = deckSize;
      for (int j = 0; j < deckSize-1; j++) {
        G.deck[i][j] = copper;
      }
      G.deck[i][deckSize-1] = estate;
      if (deckSize < 5) {
        G.discardCount[i] = discardCount;
        for (int k = 0; k < discardCount; k++) {
          G.discard[i][k] = copper;
        }
      }
    }

    printf ("Number of players: %d\n\n", numPlayers);

    for (int currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++) {
      int deckCount = G.deckCount[currentPlayer];
      int handCount = G.handCount[currentPlayer];
      
      printf ("Player #%d deckCount = %d, handCount = %d\n\n", currentPlayer+1, deckCount, handCount);

      //Coins before playing adventurer
      updateCoins(currentPlayer, &G, 0);
      printf ("Coins before playing Adventurer: %d\n", G.coins);
      
      //run Adventurer code
      printf("PLAYING ADVENTURER ON PLAYER %d\n", currentPlayer+1);
      playAdventurer(&G);
      
      //Coins after playing adventurer
      updateCoins(currentPlayer, &G, 0);
      printf ("Coins after playing Adventurer: %d\n\n", G.coins);

      int deckCountAfter = G.deckCount[currentPlayer];
      int handCountAfter = G.handCount[currentPlayer];
      printf ("Player #%d deckCount = %d, handCount = %d\n", currentPlayer+1, deckCountAfter, handCountAfter);
      asserttrue(handCountAfter == handCount+2, "Should have drawn two treasure cards\n");
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
  testAdventurer();
  return 0;
}