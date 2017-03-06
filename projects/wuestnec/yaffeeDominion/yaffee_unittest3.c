
/*******************************************************************************************
 * Testing gainCard function
********************************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void assertTrue(int retval, int rettest, struct gameState *test, struct gameState *control) {
   if(retval != rettest) {
      printf("Test Case FAILED\n");
   }
   else if((memcmp(test, control, sizeof(struct gameState))) != 0){
      printf("Test Case FAILED\n");
   }
   else
      printf("Test Case PASSED\n");
   return;
}

int main() {
//   int i;
   int returnvalue;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   struct gameState test;
   struct gameState control;
   //initialize game
   initializeGame(2, k, 1, &G);

   printf("Testing gainCard function\n");
   printf("----------------------------------------------------------------\n");

   //empties copper pile, tries to draw copper
   printf("Test Case: Chosen supply pile empty\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   test.supplyCount[copper] = 0;
   control.supplyCount[copper] = 0;
   returnvalue = gainCard(copper, &test, 1, 0);
   assertTrue(returnvalue, -1, &test, &control);

   //tries to draw steward when card not in game
   printf("Test Case: Chosen card not in game\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   returnvalue = gainCard(steward, &test, 1, 0);
   assertTrue(returnvalue, -1, &test, &control);

   //gain curse to hand
   printf("Test Case: Gain curse to hand\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   control.hand[0][control.handCount[0]] = curse;
   control.handCount[0]++;
   control.supplyCount[curse]--;
   returnvalue = gainCard(curse, &test, 2, 0);
   assertTrue(returnvalue, 0, &test, &control);

   //gain curse to deck
   printf("Test Case: Gain curse to deck\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   control.deck[0][control.deckCount[0]] = curse;
   control.deckCount[0]++;
   control.supplyCount[curse]--;
   returnvalue = gainCard(curse, &test, 1, 0);
   assertTrue(returnvalue, 0, &test, &control);

   //gain curse to discard
   printf("Test Case: Gain curse to discard\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   control.discard[0][control.discardCount[0]] = curse;
   control.discardCount[0]++;
   control.supplyCount[curse]--;
   returnvalue = gainCard(curse, &test, 0, 0);
   assertTrue(returnvalue, 0, &test, &control);

   //gain silver to hand
   printf("Test Case: Gain silver to hand\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   control.hand[0][control.handCount[0]] = silver;
   control.handCount[0]++;
   control.supplyCount[silver]--;
   returnvalue = gainCard(silver, &test, 2, 0);
   assertTrue(returnvalue, 0, &test, &control);

   //gain silver to deck
   printf("Test Case: Gain silver to deck\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   control.deck[0][control.deckCount[0]] = silver;
   control.deckCount[0]++;
   control.supplyCount[silver]--;
   returnvalue = gainCard(silver, &test, 1, 0);
   assertTrue(returnvalue, 0, &test, &control);

   //gain silver to discard
   printf("Test Case: Gain silver to discard\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   control.discard[0][control.discardCount[0]] = silver;
   control.discardCount[0]++;
   control.supplyCount[silver]--;
   returnvalue = gainCard(silver, &test, 0, 0);
   assertTrue(returnvalue, 0, &test, &control);

   //gain great_hall to hand
   printf("Test Case: Gain Great Hall to hand\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   control.hand[0][control.handCount[0]] = great_hall;
   control.handCount[0]++;
   control.supplyCount[great_hall]--;
   returnvalue = gainCard(great_hall, &test, 2, 0);
   assertTrue(returnvalue, 0, &test, &control);

   //gain great_hall to deck
   printf("Test Case: Gain Great Hall to deck\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   control.deck[0][control.deckCount[0]] = great_hall;
   control.deckCount[0]++;
   control.supplyCount[great_hall]--;
   returnvalue = gainCard(great_hall, &test, 1, 0);
   assertTrue(returnvalue, 0, &test, &control);

   //gain great_hall to discard
   printf("Test Case: Gain Great Hall to discard\n");
   memcpy(&test, &G, sizeof(struct gameState));
   memcpy(&control, &G, sizeof(struct gameState));
   control.discard[0][control.discardCount[0]] = great_hall;
   control.discardCount[0]++;
   control.supplyCount[great_hall]--;
   returnvalue = gainCard(great_hall, &test, 0, 0);
   assertTrue(returnvalue, 0, &test, &control);

   printf("----------------------------------------------------------------\n");
   printf("Finished testing gainCard function\n");

   return 0;
}
