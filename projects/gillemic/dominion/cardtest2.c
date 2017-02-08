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

   printf("\nCARD TEST 2: Great Hall\n");

   initializeGame(2, k, seed, &G);

   memcpy(&testG, &G, sizeof(struct gameState));

   G.hand[0][0] = great_hall;

   //assert hand position 1 of player 1
   printf("CHECKING FOR GREAT HALL CARD AS FIRST CARD OF PLAYER 1");
   Assert(G.hand[0][0] == great_hall, 1);

   playGreat_Hall(0, &G, handPos);
   //cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
   
   printf("CHECKING THAT PLAYER HAND HAS CHANGED");
   Assert(G.hand[0][0] != testG.hand[0][0], 2);

   int deckCountDiff = G.deckCount[0] - testG.deckCount[0];
   printf("CHECKING FOR DECK COUNT DECREASE");
   Assert(deckCountDiff < 0, 3);

   printf("CHECKING FOR INCREASED ACTIONS");
   Assert(G.numActions != testG.numActions, 4);

   printf("CHECKING THAT IT IS PLAYER 2'S TURN NOW");
   Assert(G.whoseTurn == 1, 5);

   printf("\nEND OF CARD TEST 2\n");

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
