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
   int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

   printf("\nCARD TEST 1: Adventurer\n");

   initializeGame(2, k, seed, &G);

   //give player 1 advennturer card
   G.whoseTurn = 0;
   G.hand[0][0] = adventurer;

   memcpy(&testG, &G, sizeof(struct gameState));

   //assert hand position 1 of player 1
   printf("CHECKING FOR ADVENTURER CARD AS FIRST CARD OF PLAYER 1");
   Assert(G.hand[0][0] == adventurer, 1);

   cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
   
   printf("CHECKING THAT PLAYER HAND HAS INCREASED");

   int handDiff = G.handCount[0] - testG.handCount[0];
   Assert(handDiff > 0 && handDiff == 2, 2);

   int discardDiff = G.discardCount[0] - testG.discardCount[0];
   printf("CHECKING FOR DISCARD COUNT INCRE %d ASE", discardDiff);
   Assert(discardDiff > 0, 3);

   int cardCountDiff = G.playedCardCount - testG.playedCardCount;
   printf("CHECKING FOR PLAYED CARD COUNT INCRE %d ASE", cardCountDiff);

   Assert(cardCountDiff > 0, 4);

   int deckCountDiff = G.deckCount[0] - testG.deckCount[0];
   printf("CHECKING FOR DECK COUNT DECREASE");
   Assert(deckCountDiff < 0, 5);

   printf("\nEND OF CARD TEST 1\n");

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
