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

   printf("\nCARD TEST 4: Council Room\n");

   initializeGame(2, k, seed, &G);

   memcpy(&testG, &G, sizeof(struct gameState));

   G.hand[0][0] = council_room;

   //assert hand position 1 of player 1
   printf("CHECKING FOR COUNCIL ROOM CARD AS FIRST CARD OF PLAYER 1");
   Assert(G.hand[0][0] == council_room, 1);

   playCouncil_Room(&G, handPos);
   //cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
   
   printf("CHECKING THAT PLAYER HAND HAS INCREASED");
   Assert(G.handCount - testG.handCount != 0, 2);

   int deckCountDiff = G.deckCount[0] - testG.deckCount[0];
   printf("CHECKING FOR DECK COUNT DECREASE");
   Assert(deckCountDiff < 0, 3);

   printf("CHECKING PLAYED PILE INCREASE");
   Assert(G.playedCardCount > 0, 4);

   printf("CHECKING OTHER PLAYERS HAND COUNT");
   Assert(G.handCount[1] != testG.handCount[1], 5);

   printf("CHECKING OTHER PLAYERS DECK COUNT");
   Assert(G.deckCount[1] != testG.deckCount[1], 6);

   printf("\nEND OF CARD TEST 4\n");

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
