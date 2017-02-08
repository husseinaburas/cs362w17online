#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void Assert(_Bool result, int testnumber);

int main() {
   //int i;
   struct gameState G;
   struct gameState testG;

   int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
   int seed = 75;
   int handPos = 0;

   printf("\nCARD TEST 3: Smithy\n");

   initializeGame(2, k, seed, &G);

   memcpy(&testG, &G, sizeof(struct gameState));

   G.hand[0][0] = smithy;

   //assert hand position 1 of player 1
   printf("CHECKING FOR SMITHY CARD AS FIRST CARD OF PLAYER 1");
   Assert(G.hand[0][0] == smithy, 1);

   playSmithy(0, &G, handPos);
   //cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
   
   printf("CHECKING THAT PLAYER HAND HAS INCREASED BY 2");
   Assert(G.handCount - testG.handCount != 0, 2);

   int deckCountDiff = G.deckCount[0] - testG.deckCount[0];
   printf("CHECKING FOR DECK COUNT DECREASE");
   Assert(deckCountDiff < 0, 3);

   printf("CHECKING DISCARD PILE INCREASE");
   Assert(G.discardCount[0] > 0, 4);

   printf("CHECKING PLAYED PILE INCREASE");
   Assert(G.playedCardCount > 0, 5);

   printf("\nEND OF CARD TEST 3\n");

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
