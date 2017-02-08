/*******************************************************************************************
 * Testing great_hall card
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
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
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
   //make the 5th card in the hand great_hall
   test.hand[0][4] = great_hall;
   //copy game state to control game state
   memcpy(&control, &test, sizeof(struct gameState));

   printf("Testing great hall card\n");
   printf("------------------------------------------------------------------\n");

   printf("Test Case: great hall draws from deck\n");
   great_hallCard(&test, 0, 4);
   control.hand[0][4] = copper;
   control.deckCount[0]--;
   control.playedCards[0] = great_hall;
   control.playedCardCount++;
   control.numActions++;
   assertTrue(&test, &control);

   //initialize hand for next 
   memcpy(&test, &G, sizeof(struct gameState));
   test.handCount[0] = 5;
   test.discardCount[0] = 10;
   test.deckCount[0] = 0;
   for(i=0; i<(test.handCount[0]-1); i++)
      test.hand[0][i] = copper;
   for(i=0; i<test.deckCount[0]; i++)
      test.deck[0][i] = copper;
   for(i=0; i<test.discardCount[0]; i++)
      test.discard[0][i] = copper;
   //make the 5th card in the hand smithy
   test.hand[0][4] = great_hall;
   //copy game state to control game state
   memcpy(&control, &test, sizeof(struct gameState));
   
   printf("Test Case: no deck cards to draw from, must shuffle discards\n");
   great_hallCard(&test, 0, 4);
   control.hand[0][4] = copper;
   control.deckCount[0] = 9;
   control.playedCardCount = 1;
   control.playedCards[0] = great_hall;
   control.numActions++;
   assertTrue(&test, &control);

   printf("------------------------------------------------------------------\n");
   printf("Finished testing great hall card\n");
   return 0;
}
