#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {


   if (argc != 2 || argv[1] < 0) {
      printf("USAGE: ./randomtest1 [positive integer]\n");
      exit(0);
   }


   int randomSeed = atoi(argv[1]);
   srand(randomSeed);

   int i;
   int passed, failed = 0;

   for (i = 0; i < 1000; i++) {
      printf("\nRandom Test %d\n", i+1);

      struct gameState G, testG;

      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

      int playerCount = rand() % 3 + 2; //2 to 4 players
      int currentPlayer = rand() % playerCount;

      initializeGame(playerCount, k, (rand() % 1000 + 1), &G);

      memcpy(&testG, &G, sizeof(struct gameState));

      testG.whoseTurn = currentPlayer;
      printf("Current Player: %d        Number of Players: %d\n\n", currentPlayer+1, playerCount);

      testG.hand[currentPlayer][testG.handCount[currentPlayer]] = smithy;
      testG.handCount[currentPlayer]++;

      if (G.handCount[currentPlayer] + 1 != testG.handCount[currentPlayer]) {
	 printf("Adding Smithy card to hand: FAILED\n");
	 failed++;
	 continue;
      }

      playSmithy(&testG, 0);

      if (testG.handCount[currentPlayer] != G.handCount[currentPlayer] + 2) {
	 printf("Checking if currentPlayer has 2 more cards: FAILED\n");
	 failed++;
	 continue;
      }

      if (testG.deckCount[0] - G.deckCount[0] == 0) {
	 printf("Checking that the deck count has changed: FAILED\n");
	 failed++;
	 continue;
      }

      passed++;
      printf("Smithy Random Test: PASSED\n");
   }

   printf("\n\nTESTS PASSED: %d                TESTS FAILED: %d\n", passed, failed);

   return 0;
}