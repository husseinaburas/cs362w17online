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

   int realCost[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4, -1};

   printf("UNIT TEST 3- getCost()\n");
   for (i = curse; i <= treasure_map+1; i++)
   {
      int cost = getCost(i);
      Assert(realCost[i] == cost, i);
   }


   printf("UNIT TEST 3 COMPLETE\n");

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
