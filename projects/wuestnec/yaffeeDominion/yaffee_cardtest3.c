/*******************************************************************************************
 * Testing outpost card
*******************************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void assertTrue(struct gameState *test, struct gameState *control) {
   if(memcmp(test, control, sizeof(struct gameState)) == 0)
      printf("Test Case PASSED\n");
   else
      printf("Test Case FAILED\n");
   return;
}

int main() {
   int i;
   int k[10] = {adventurer, outpost, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   struct gameState test;
   struct gameState control;

   initializeGame(2, k, 1, &G);

   memcpy(&test, &G, sizeof(struct gameState));
   test.handCount[0] = 5;
   test.discardCount[0] = 10;
   test.deckCount[0] = 10;
   for(i=0; i<(test.handCount[0]-1); i++)
      test.hand[0][i] = copper;
   for(i=0; i<test.deckCount[0]; i++)
      test.deck[0][i] = copper;
   for(i=0; i<test.discardCount[0]; i++)
      test.discard[0][i] = copper;
   //make 5th card in hand outpost
   test.hand[0][4] = outpost;
   memcpy(&control, &test, sizeof(struct gameState));

   printf("Testing outpost card\n");
   printf("------------------------------------------------------------------\n");

   printf("Test Case: outpost is played once\n");
   outpostCard(&test, 0, 4);
   control.handCount[0]--;
   control.hand[0][4] = -1;
   control.outpostPlayed++;
   control.playedCards[0] = outpost;
   control.playedCardCount++;
   assertTrue(&test, &control);

   printf("Test Case: outpost is played twice in one turn\n");

   memcpy(&test, &G, sizeof(struct gameState));
   test.handCount[0] = 5;
   test.discardCount[0] = 10;
   test.deckCount[0] = 10;
   for(i=0; i<(test.handCount[0]-1); i++)
      test.hand[0][i] = copper;
   for(i=0; i<test.deckCount[0]; i++)
      test.deck[0][i] = copper;
   for(i=0; i<test.discardCount[0]; i++)
      test.discard[0][i] = copper;
   test.hand[0][3] = outpost;
   test.hand[0][4] = outpost;
   memcpy(&control, &test, sizeof(struct gameState));
  
   outpostCard(&test, 0, 4);
   control.handCount[0]--;
   control.hand[0][4] = -1;
   control.outpostPlayed++;
   control.playedCards[0] = outpost;
   control.playedCardCount++;
   outpostCard(&test, 0, 3);
   control.handCount[0]--;
   control.hand[0][3] = -1;
   control.outpostPlayed++;
   control.playedCards[1] = outpost;
   control.playedCardCount++;
   control.handCount[0]--;
   assertTrue(&test, &control);

   printf("------------------------------------------------------------------\n");
   printf("Finished testing outpost card\n");
   return 0;
}
