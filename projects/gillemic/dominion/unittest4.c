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

   printf("\nUNIT TEST 4: handCard()\n");

   initializeGame(2, k, seed, &G);

   //player 1 gets copper and treasure map
   G.handCount[0] = 2;
   G.hand[0][0] = silver;
   G.hand[0][1] = baron;

   //player 2 gets curse
   G.handCount[1] = 1;
   G.hand[1][0] = estate;

   G.whoseTurn = 0;

   //assert hand position 1 of player 1
   printf("CHECKING FOR SILVER CARD AS FIRST CARD OF PLAYER 1");
   Assert(handCard(0, &G) == silver, 1);
   
   printf("CHECKING THAT SILVER HAS VALUE 5 IN DEX");
   Assert(handCard(0, &G) == 5, 2);

   //assert hand position 2 of player 1
   printf("CHECKING FOR BARON CARD AS SECOND CARD OF PLAYER 1");
   Assert(handCard(1, &G) == baron, 3);

   printf("CHECKING THAT BARON HAS VALUE 15 IN DEX");
   Assert(handCard(1, &G) == 15, 4);

   G.whoseTurn = 1;

   //assert hand position 1 of player 2
   printf("CHECKING FOR ESTATE CARD AS FIRST CARD OF PLAYER 2");
   Assert(handCard(0, &G) == estate, 5);
   printf("CHECKING THAT ESTATE HAS VALUE 1 IN DEX");
   Assert(handCard(0, &G) == 1, 6);

   printf("\nEND OF UNIT TEST 4\n");

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
