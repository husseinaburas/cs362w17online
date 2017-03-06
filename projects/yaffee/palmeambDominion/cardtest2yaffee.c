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
   int failFound = 0;
   if(control->handCount[0] != test->handCount[0]) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Hand Count\n");
   }
   if(control->hand[0][4] != test->hand[0][4]) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Drawn Card\n");
   }
   if(control->deckCount[0] != test->deckCount[0]) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Deck Count\n");
   }
   if(control->discardCount[0] != test->discardCount[0]) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Discard Count\n");
   }
   if(control->playedCards[0] != test->playedCards[0]) {
      failFound = 1;
      printf("Test Case Failed: Played Card Incorrect\n");
   }
   if(control->playedCardCount != test->playedCardCount) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Played Card Count\n");
   }
   if(control->numActions != test->numActions) {
      failFound = 1;
      printf("Test Case Failed: Incorrect Played Card Count\n");
   }
   if(failFound == 0){
      printf("No Errors Found\n");
   }
}

int main() {
   int i;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   struct gameState test;
   struct gameState control;
   int choice1 = 0;
   int choice2 = 0;
   int choice3 = 0;
   int handpos = 4;
   int bonus = 0;

   initializeGame(2, k, 1, &G);
   memcpy(&test, &G, sizeof(struct gameState));
   test.handCount[0] = 5;
   test.discardCount[0] = 10;
   test.deckCount[0] = 10;
   test.playedCardCount = 0;
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
   cardEffect(great_hall, choice1, choice2, choice3, &test, handpos, &bonus);
   control.hand[0][4] = copper;
   control.deckCount[0] = 9;
   control.playedCards[0] = great_hall;
   control.playedCardCount = 1;
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
   cardEffect(great_hall, choice1, choice2, choice3, &test, handpos, &bonus);
   control.hand[0][4] = copper;
   control.deckCount[0] = 9;
   control.discardCount[0] = 0;
   control.playedCardCount = 1;
   control.playedCards[0] = great_hall;
   control.numActions++;
   assertTrue(&test, &control);

   printf("------------------------------------------------------------------\n");
   printf("Finished testing great hall card\n");
   return 0;
}
