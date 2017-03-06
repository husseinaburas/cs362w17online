/*******************************************************************************************
 * Testing updateCoins function
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
   int i;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;
   //initialize game
   initializeGame(2, k, 1, &G);

   printf("Testing updateCoins function\n");
   printf("----------------------------------------------------------------\n");

   //test number of coins when no cards in hand
   printf("Test Case: No cards in hand\n");
   G.handCount[0] = 0;
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 0);

   //test number of coin with max hand size, no coins
   printf("Test Case: Max hand size, no coins in hand\n");
   G.handCount[0] = MAX_HAND;
   for(i=0; i<MAX_HAND; i++) {
      G.hand[0][i] = duchy;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 0);

   //test number of coin with max hand size, no coins, 5 coin bonus
   printf("Test Case: Max hand size, no coins in hand, 5 coin bonus\n");
   G.handCount[0] = MAX_HAND;
   for(i=0; i<MAX_HAND; i++) {
      G.hand[0][i] = duchy;
   }
   updateCoins(0, &G, 5);
   assertTrue(G.coins, 5);

   //test max hand with all copper
   printf("Test Case: Max hand size, all copper\n");
   G.handCount[0] = MAX_HAND;
   for(i=0; i<MAX_HAND; i++) {
      G.hand[0][i] = copper;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 500);

   //test max hand with all silver
   printf("Test Case: Max hand size, all silver\n");
   G.handCount[0] = MAX_HAND;
   for(i=0; i<MAX_HAND; i++) {
      G.hand[0][i] = silver;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 1000);

   //test max hand with all gold
   printf("Test Case: Max hand size, all gold\n");
   G.handCount[0] = MAX_HAND;
   for(i=0; i<MAX_HAND; i++) {
      G.hand[0][i] = gold;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 1500);

   //test max hand with mix of coins
   printf("Test case: Max hand size, mix of coins\n");
   G.handCount[0] = MAX_HAND;
   for(i=0; i<MAX_HAND; i++) {
      if(i%3 == 0)
         G.hand[0][i] = copper;
      else if (i%3 == 1)
         G.hand[0][i] = silver;
      else
         G.hand[0][i] = gold;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 999);

   //test max hand with mix of coins and a bonus
   printf("Test case: Max hand size, mix of coins, 5 coin bonus\n");
   G.handCount[0] = MAX_HAND;
   for(i=0; i<MAX_HAND; i++) {
      if(i%3 == 0)
         G.hand[0][i] = copper;
      else if (i%3 == 1)
         G.hand[0][i] = silver;
      else
         G.hand[0][i] = gold;
   }
   updateCoins(0, &G, 5);
   assertTrue(G.coins, 1004);
   
   //test max hand with mix of coins and other cards
   printf("Test case: Max hand size, mix of coins and other cards\n");
   G.handCount[0] = MAX_HAND;
   for(i=0; i<MAX_HAND; i++) {
      if(i%5 == 0)
         G.hand[0][i] = copper;
      else if (i%5 == 1)
         G.hand[0][i] = silver;
      else if (i%5 == 2)
         G.hand[0][i] = gold;
      else if (i%5 == 3)
         G.hand[0][i] = duchy;
      else 
         G.hand[0][i] = estate;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 600);

   //test 5 card hand with no coins
   printf("Test Case: 5 card hand, no coins in hand\n");
   G.handCount[0] = 5;
   for(i=0; i<5; i++) {
      G.hand[0][i] = estate;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 0);
   
   //test number of coin with 5 card hand, no coins, 5 coin bonus
   printf("Test Case: 5 card hand, no coins in hand, 5 coin bonus\n");
   G.handCount[0] = 5;
   for(i=0; i<5; i++) {
      G.hand[0][i] = duchy;
   }
   updateCoins(0, &G, 5);
   assertTrue(G.coins, 5);

   //test 5 card hand with all copper
   printf("Test Case: 5 card hand, all copper\n");
   G.handCount[0] = 5;
   for(i=0; i<5; i++) {
      G.hand[0][i] = copper;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 5);
   
   //test 5 card hand with all silver
   printf("Test Case: 5 card hand, all silver\n");
   G.handCount[0] = 5;
   for(i=0; i<5; i++) {
      G.hand[0][i] = silver;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 10);
   
   //test 5 card hand with all gold
   printf("Test Case: 5 card hand, all gold\n");
   G.handCount[0] = 5;
   for(i=0; i<5; i++) {
      G.hand[0][i] = gold;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 15);
   
   //test 5 card hand with mix of coins
   printf("Test case: 5 card hand, mix of coins\n");
   G.handCount[0] = 5;
   for(i=0; i<5; i++) {
      if(i%3 == 0)
         G.hand[0][i] = copper;
      else if (i%3 == 1)
         G.hand[0][i] = silver;
      else
         G.hand[0][i] = gold;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 9);
   
   //test 5 card hand with mix of coins and a bonus
   printf("Test case: 5 card hand, mix of coins, 5 coin bonus\n");
   G.handCount[0] = 5;
   for(i=0; i<5; i++) {
      if(i%3 == 0)
         G.hand[0][i] = copper;
      else if (i%3 == 1)
         G.hand[0][i] = silver;
      else
         G.hand[0][i] = gold;
   }
   updateCoins(0, &G, 5);
   assertTrue(G.coins, 14);
   
   //test 5 card hand with mix of coins and other cards
   printf("Test case: 5 card hand, mix of coins and other cards\n");
   G.handCount[0] = 5;
   for(i=0; i<5; i++) {
      if(i%5 == 0)
         G.hand[0][i] = copper;
      else if (i%5 == 1)
         G.hand[0][i] = silver;
      else if (i%5 == 2)
         G.hand[0][i] = gold;
      else if (i%5 == 3)
         G.hand[0][i] = duchy;
      else 
         G.hand[0][i] = estate;
   }
   updateCoins(0, &G, 0);
   assertTrue(G.coins, 6);

   printf("----------------------------------------------------------------\n");
   printf("Finished testing updateCoins function\n");
   return 0;
}
