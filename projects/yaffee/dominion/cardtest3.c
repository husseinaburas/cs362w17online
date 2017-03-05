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
   int failFound = 0;
   if(control->handCount[0] != test->handCount[0]) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Hand Count\n");
   }
   if(control->playedCards[0] != test->playedCards[0]) {
      failFound = 1;
      printf("Test Case Failed: Played Card Incorrect\n");
   }
   if(control->playedCards[1] != test->playedCards[1]) {
      failFound = 1;
      printf("Test Case Failed: Played Card Incorrect\n");
   }
   if(control->playedCardCount != test->playedCardCount) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Played Card Count\n");
   }
   if(failFound == 0){
      printf("No Errors Found\n");
   }
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
   test.outpostPlayed = 0;
   test.playedCardCount = 0;
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
   control.handCount[0] = 4;
   control.outpostPlayed = 1;
   control.playedCards[0] = outpost;
   control.playedCardCount = 1;
   assertTrue(&test, &control);

   printf("Test Case: outpost is played twice in one turn\n");

   memcpy(&test, &G, sizeof(struct gameState));
   test.handCount[0] = 5;
   test.discardCount[0] = 10;
   test.deckCount[0] = 10;
   test.outpostPlayed = 0;
   test.playedCardCount = 0;
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
   outpostCard(&test, 0, 3);
   control.handCount[0] = 3;
   control.outpostPlayed = 2;
   control.playedCards[0] = outpost;
   control.playedCards[1] = outpost;
   control.playedCardCount = 2;
   assertTrue(&test, &control);

   printf("------------------------------------------------------------------\n");
   printf("Finished testing outpost card\n");
   return 0;
}
