/*******************************************************************************************
 * Testing smithy card
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

   //initialize game
   initializeGame(2, k, 1, &G);

   memcpy(&test, &G, sizeof(struct gameState));
   //create initial deck
   //all cards are the same so that shuffle does not randomize anything
   test.handCount[0] = 5;
   test.discardCount[0] = 10;
   test.deckCount[0] = 10;
   for(i=0; i<(test.handCount[0]-1); i++)
      test.hand[0][i] = copper;
   for(i=0; i<test.deckCount[0]; i++)
      test.deck[0][i] = copper;
   for(i=0; i<test.discardCount[0]; i++)
      test.discard[0][i] = copper;
   //make the 5th card in the hand smithy
   test.hand[0][4] = smithy;
   //copy game state to control game state
   memcpy(&control, &test, sizeof(struct gameState));

   printf("Testing smithy card\n");
   printf("------------------------------------------------------------------\n");

   //test draw when there are at least 3 cards in deck to draw from (no shuffle required)
   printf("Test Case: enough cards in deck to draw from\n");
   smithyCard(&test, 0, 4);
   //add 3 from smithy to hand, minus one for discarding smithy
   control.handCount[0] = control.handCount[0] + 2;
   control.deckCount[0] = control.deckCount[0] - 3;
   control.playedCards[0] = smithy;
   control.playedCardCount++;
   for(i=0; i < control.handCount[0]; i++)
      control.hand[0][i] = copper;
   assertTrue(&test, &control);

   //initialize hand for second test
   memcpy(&test, &G, sizeof(struct gameState));
   test.handCount[0] = 5;
   test.discardCount[0] = 10;
   test.deckCount[0] = 1;
   for(i=0; i<(test.handCount[0]-1); i++)
      test.hand[0][i] = copper;
   for(i=0; i<test.deckCount[0]; i++)
      test.deck[0][i] = copper;
   for(i=0; i<test.discardCount[0]; i++)
      test.discard[0][i] = copper;
   test.hand[0][4] = smithy;
   memcpy(&control, &test, sizeof(struct gameState));

   //test when there is 1 card in deck, must shuffle discard
   printf("Test Case: not enough cards in deck, must use discard pile\n");
   smithyCard(&test, 0, 4);
   control.handCount[0] = control.handCount[0] + 2;
   control.playedCardCount = 1;
   control.playedCards[0] = smithy;
   control.deckCount[0] = 8;
   for(i=0; i<control.handCount[0]; i++)
      control.hand[0][i] = copper;
   assertTrue(&test, &control);

   //initialize hand for third test
   memcpy(&test, &G, sizeof(struct gameState));
   test.handCount[0] = 5;
   test.discardCount[0] = 0;
   test.deckCount[0] = 1;
   for(i=0; i<(test.handCount[0]-1); i++)
      test.hand[0][i] = copper;
   for(i=0; i<test.deckCount[0]; i++)
      test.deck[0][i] = copper;
   test.hand[0][4] = smithy;
   memcpy(&control, &test, sizeof(struct gameState));

   //test when there is 1 card deck, no discards (ie, smithy can only draw 1)
   printf("Test Case: one card in deck, no cards in discard pile\n");
   smithyCard(&test, 0, 4);
   control.playedCardCount = 1;
   control.playedCards[0] = smithy;
   control.deckCount[0] = 0;
   for(i=0; i < control.handCount[0]; i++)
      control.hand[0][i] = copper;
   assertTrue(&test, &control);

   printf("------------------------------------------------------------------\n");
   printf("Finished testing smithy card\n");
   return 0;
}
