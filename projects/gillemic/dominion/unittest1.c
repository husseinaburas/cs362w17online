#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void Assert(_Bool result, int testnumber);

int main() {
   //int i;
   struct gameState G;

   int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
   int seed = 75;

   /* Unit Test 1: Whoseturn() test*/
   printf("\nUNIT TEST 1 - whoseTurn()\n\n");
   G.whoseTurn = 5;

   printf("CHECKING WHOSETURN FUNCTION ASSIGNED A VALUE");
   Assert(whoseTurn(&G) == 5, 1);

   initializeGame(2, k, seed, &G);

   printf("CHECKING WHOSETURN FUNCTION AFTER INITIALIZING GAME");
   Assert(whoseTurn(&G) == 0, 2);

   endTurn(&G);

   printf("CHECKING WHOSETURN FUNCTION AFTER ENDING PLAYER 1'S TURN");
   Assert(whoseTurn(&G) == 1, 3);

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
