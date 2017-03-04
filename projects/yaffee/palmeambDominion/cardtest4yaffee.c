/*******************************************************************************************
 * Testing adventurer card
*******************************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void assertTrue(struct gameState *test, struct gameState *control) {
   int failFound = 0;
   int testTreas = 0;
   int controlTreas = 0;
   int i;
   for(i=0; i < control->handCount[0]; i++) {
      if(control->hand[0][i] == copper)
         controlTreas = controlTreas+1;
   }
   for(i=0; i < test->handCount[0]; i++) {
      if(test->hand[0][i] == copper)
         testTreas = testTreas+1;
   }
   if(control->handCount[0] != test->handCount[0]) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Hand Count\n");
   }
   if(controlTreas != testTreas) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Number of Treasures in Hand\n");
   }
   if(control->playedCards[0] != test->playedCards[0]) {
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
   int temphand[MAX_HAND];
   int cardDrawn;
   int drawntreasure;
   int z;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   struct gameState test;
   struct gameState control;
   
   initializeGame(2, k, 1, &G);
   memcpy(&test, &G, sizeof(struct gameState));

   printf("Testing adventurer card\n");
   printf("------------------------------------------------------------------\n");

   printf("Test Case: at least two treasures in deck\n");
   test.handCount[0] = 5;
   test.discardCount[0] = 5;
   test.deckCount[0] = 5;
   test.playedCardCount = 0;
   for(i=0; i<(test.handCount[0]-1); i++)
      test.hand[0][i] = copper;
   for(i=0; i<test.deckCount[0]; i++)
      test.deck[0][i] = copper;
   for(i=0; i<test.discardCount[0]; i++)
      test.discard[0][i] = copper;
   test.hand[0][4] = adventurer;
   memcpy(&control, &test, sizeof(struct gameState));
   drawntreasure=0;
   cardDrawn = -1;
   z=0;
   adventurerCard(&test, drawntreasure, 0, temphand, cardDrawn, z);
   control.handCount[0] = 6;
   control.hand[0][4] = copper;
   control.hand[0][5] = copper;
   control.deckCount[0] = control.deckCount[0] - 2;
   control.playedCards[0] = adventurer;
   control.playedCardCount = 1;
   assertTrue(&test, &control);

   printf("Test Case: at least two treasures in discard\n");
   memcpy(&test, &G, sizeof(struct gameState));
   test.handCount[0] = 5;
   test.discardCount[0] = 5;
   test.deckCount[0] = 5;
   test.playedCardCount = 0;
   for(i=0; i<(test.handCount[0]-1); i++)
      test.hand[0][i] = copper;
   for(i=0; i<test.deckCount[0]; i++)
      test.deck[0][i] = estate;
   for(i=0; i<test.discardCount[0]; i++)
      test.discard[0][i] = copper;
   test.hand[0][4] = adventurer;
   memcpy(&control, &test, sizeof(struct gameState));
   drawntreasure=0;
   cardDrawn = -1;
   z=0;
   adventurerCard(&test, drawntreasure, 0, temphand, cardDrawn, z);
   control.handCount[0] = 6;
   control.hand[0][4] = copper;
   control.hand[0][5] = copper;
   control.playedCards[0] = adventurer;
   control.playedCardCount = 1;
   assertTrue(&test, &control);

   printf("Test Case: no treasure available\n");
   memcpy(&test, &G, sizeof(struct gameState));
   test.handCount[0] = 5;
   test.discardCount[0] = 5;
   test.deckCount[0] = 5;
   test.playedCardCount = 0;
   for(i=0; i<(test.handCount[0]-1); i++)
      test.hand[0][i] = duchy;
   for(i=0; i<test.deckCount[0]; i++)
      test.deck[0][i] = estate;
   for(i=0; i<test.discardCount[0]; i++)
      test.discard[0][i] = estate;
   test.hand[0][4] = adventurer;
   memcpy(&control, &test, sizeof(struct gameState));
   drawntreasure=0;
   cardDrawn = -1;
   z=0;
   adventurerCard(&test, drawntreasure, 0, temphand, cardDrawn, z);
   control.handCount[0] = 4;
   control.hand[0][4] = -1;
   control.deckCount[0] = 0;
   control.discardCount[0] = 10;
   for(i=0; i<control.discardCount[0]; i++)
      control.discard[0][i] = estate;
   control.playedCards[0] = adventurer;
   control.playedCardCount = 1;
   assertTrue(&test, &control);

   printf("------------------------------------------------------------------\n");
   printf("Finished testing adventurer card\n");
   return 0;
}



