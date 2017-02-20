#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void Assert(_Bool result, int testnumber);

int main() {
   int i;
   struct gameState G;

   int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
   int seed = 75;

   printf("\nUNIT TEST 2- isGameOver()\n\n");
   
   initializeGame(2, k, seed, &G);

   printf("TESTING ISGAMEOVER WITH NO EMPTY SUPPLIES");

   for (i =0; i <= treasure_map; i++) {
      G.supplyCount[i] = 1;
   }

   int result = isGameOver(&G);
   Assert(result == 0, 1);

   printf("TESTING ISGAMEOVER WITH TWO EMPTY SUPPLIES (NOT PROVINCE)");
   for (i=0; i < treasure_map-1; i++) {
      G.supplyCount[i] = 1;
   }
   G.supplyCount[treasure_map-1] = 0;
   G.supplyCount[treasure_map] = 0;
   result = isGameOver(&G);

   Assert(result == 0, 2);

   printf("TESTING ISGAMEOVER WITH PROVINCE SUPPLY EMPTY");
   G.supplyCount[province] = 0;
   result = isGameOver(&G);
   Assert(result == 1, 3);

   printf("TESTING ISGAMEOVER WITH 3 SUPPLIES EMPTY");
   G.supplyCount[province] = 1;
   G.supplyCount[gold] = 0;
   G.supplyCount[copper] = 0;
   G.supplyCount[curse] = 0;
   G.supplyCount[treasure_map] = 0;

   result = isGameOver(&G);
   Assert(result == 1, 4);

   printf("UNIT TEST 2 COMPLETE\n\n");

   return 0;
}

void Assert(_Bool result, int testnumber) {
   //printf("Function whoseTurn()- ");
   printf(" - ");
   if (result)
      printf("TEST %d SUCCESSFUL\n", testnumber);
   else
      printf("TEST %d FAILED\n", testnumber);
}
