/*******************************************************************************************
 * Testing isGameOver function
*******************************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void assertTrue(int val1, int val2) {
   if(val1 == val2)
      printf("Test Case PASSED\n");
   else
      printf("Test Case Failed\n");
   return;
}

int main() {
   int count;
   int i;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;

   //initialize game
   initializeGame(2, k, 1, &G);

   //create player's deck, every card is a copper
   G.deckCount[0] = 20;
   G.handCount[0] = 5;
   G.discardCount[0] = 12;

   for(i=0; i < G.deckCount[0]; i++)
      G.deck[0][i] = copper;
   for(i=0; i < G.handCount[0]; i++)
      G.hand[0][i] = copper;
   for(i=0; i < G.discardCount[0]; i++)
      G.discard[0][i] = copper;

   printf("Testing fullDeckCount function\n");
   printf("------------------------------------------------------------------\n");

   //test card not in game
   printf("Test Case: card not in game\n");
   count = fullDeckCount(0, steward, &G);
   assertTrue(count, 0);

   //test card not in player's possession
   printf("Test Case: player does not have card\n");
   count = fullDeckCount(0, silver, &G);
   assertTrue(count, 0);

   //test card only in deck
   printf("Test Case: card only in player's deck\n");
   for(i=0; i < G.deckCount[0]; i++)
      G.deck[0][i] = silver;
   count = fullDeckCount(0, silver, &G);
   assertTrue(count, 20);

   //test card only in hand
   printf("Test Case: card only in player's hand\n");
   for(i=0; i < G.handCount[0]; i++)
      G.hand[0][i] = gold;
   count = fullDeckCount(0, gold, &G);
   assertTrue(count, 5);

   //test card only in discard
   printf("Test Case: card only in player's discard pile\n");
   count = fullDeckCount(0, copper, &G);
   assertTrue(count, 12);
 
   //card is mixed in throughout the full deck 
   printf("Test Case: card distributed throughout player's entire deck\n");
   for(i=1; i <= G.deckCount[0]; i=i*3)
      G.deck[0][i] = province;
   for(i=1; i <= G.handCount[0]; i=i*3)
      G.hand[0][i] = province;
   for(i=1; i <= G.discardCount[0]; i=i*3)
      G.discard[0][i] = province;
   count = fullDeckCount(0, province, &G);
   assertTrue(count, 8);

   printf("------------------------------------------------------------------\n");
   printf("Finished testing fullDeckCount function\n");
   return 0;
}
