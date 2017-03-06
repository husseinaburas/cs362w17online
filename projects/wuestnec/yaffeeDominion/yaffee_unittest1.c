/*******************************************************************************************
 * Testing isGameOver function
*******************************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//define assert function
void assertTrue(int test1, int test2) {
   if(test1 == test2)
      printf("Test Case PASSED\n");
   else
      printf("Test Case FAILED\n");
}

int main() {
   int returnvalue;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   struct gameState G1;
   struct gameState G2;
   struct gameState G3;
   struct gameState G4;
   struct gameState G5;

   //initialize game
   initializeGame(4, k, 1, &G);

   //copy initial state to all test states
   memcpy(&G1, &G, sizeof(struct gameState));
   memcpy(&G2, &G, sizeof(struct gameState));
   memcpy(&G3, &G, sizeof(struct gameState));
   memcpy(&G4, &G, sizeof(struct gameState));
   memcpy(&G5, &G, sizeof(struct gameState));

   printf("Testing isGameOver function\n");
   printf("-------------------------------------\n");
   //test that the game is not over when no supply cards are out
   printf("Test Case: out of no supply cards\n");
   returnvalue = isGameOver(&G);
   assertTrue(returnvalue, 0);

   //test that game is over when province cards are out
   printf("Test Case: out of province cards\n");
   G1.supplyCount[province] = 0;
   returnvalue = isGameOver(&G1);
   assertTrue(returnvalue, 1);

   //test that game is not over when 1 supply card is out
   printf("Test Case: out of one supply card\n");
   G2.supplyCount[duchy] = 0;
   returnvalue = isGameOver(&G2);
   assertTrue(returnvalue, 0);

   //test that game is not over when 2 supply cards are out
   printf("Test Case: out of two supply cards\n");
   G3.supplyCount[duchy] = 0;
   G3.supplyCount[estate] = 0;
   returnvalue = isGameOver(&G3);
   assertTrue(returnvalue, 0);

   //test that game is over when 3 supply cards are out
   printf("Test Case: out of three supply cards\n");
   G4.supplyCount[duchy] = 0;
   G4.supplyCount[estate] = 0;
   G4.supplyCount[silver] = 0;
   returnvalue = isGameOver(&G4);
   assertTrue(returnvalue, 1);

   //test that game is over when 4 supply cards are out
   //this could happen if a player had multiple buys and bought the
   //last card of two supply piles
   printf("Test Case: out of four supply cards\n");
   G5.supplyCount[duchy] = 0;
   G5.supplyCount[estate] = 0;
   G5.supplyCount[silver] = 0;
   G5.supplyCount[gold] = 0;
   returnvalue = isGameOver(&G5);
   assertTrue(returnvalue, 1);

   printf("-------------------------------------\n");
   printf("Finished testing isGameOver function\n");
   return 0;
}
