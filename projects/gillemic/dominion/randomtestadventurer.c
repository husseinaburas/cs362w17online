#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[]) {
   if (argc != 2 || argv[1] < 0) {
      printf("Error! Usage: randomtestadventurer [positive integer]\n");
      exit(0);
   }

   int temphand[MAX_HAND];

   int randomSeed = atoi(argv[1]);
   srand(randomSeed);

   int i, p;
   int passed, failed = 0;

   for (i = 0; i < 1000; i++) {
      printf("Random Test %d\n", i+1);
      struct gameState testG, G;

      int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, village, adventurer, council_room};

      int playerCount = rand() % 3 + 2;
      int currentPlayer = rand() % playerCount;

      int treasureCount[playerCount];
      for (p = 0; p < playerCount; p++)
	 treasureCount[p] = 0;

      initializeGame(playerCount, k, (rand() % 1000 + 1), &G);

      memcpy(&testG, &G, sizeof(struct gameState));

      testG.whoseTurn = currentPlayer;
      printf("Current Player: %d      Number of Players: %d\n\n", currentPlayer+1, playerCount);

      testG.hand[currentPlayer][testG.handCount[currentPlayer]] = adventurer;
      testG.handCount[currentPlayer]++;

      if (G.handCount[currentPlayer] + 1 != testG.handCount[currentPlayer]) {
	 printf("Adding adventurer card to hand: FAILED\n");
	 failed++;
	 continue;
      }

      playAdventurer(&testG, currentPlayer, 0, 0, temphand, 0);

      int j, drawn;

      for (j = 0; j < testG.handCount[currentPlayer]; j++)
      {
	 drawn = testG.hand[currentPlayer][j];
	 if (drawn == copper || drawn == silver || drawn == gold)
	 {
	    treasureCount[currentPlayer] += 1;
	 }
      }

      if (treasureCount[currentPlayer] != 2)
      {
	 printf("Adding 2 treasures to hand: FAILED\n");
	 failed++;
	 continue;
      }

      passed++;
      printf("ADVENTURER RANDOM TEST: PASSED\n");
      //free(&G);
      //free(&testG);
   }

   printf("\n\nTESTS PASSED: %d                TESTS FAILED: %d\n", passed, failed);

   return 0;
}
