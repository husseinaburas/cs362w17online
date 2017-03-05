#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "assert_custom.h"

int main (int argc, char** argv) {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    int seed = 738;

   printf("---------------- Unit Test 2 updateCoins() ----------------\n");

   initializeGame(2, k, seed, &G);
    
   // setup player 1 hand with 1 copper, 1 silver, and 2 gold cards coin value of 9
   G.handCount[0] = 4;
   G.hand[0][0] = copper;
   G.hand[0][1] = silver;
   G.hand[0][2] = gold;
   G.hand[0][3] = gold;

   // setup player 2 hand with 2 copper and 3 gold cards coin value of 11
   G.handCount[1] = 5;
   G.hand[1][0] = copper;
   G.hand[1][1] = copper;
   G.hand[1][2] = gold;
   G.hand[1][3] = gold;
   G.hand[1][4] = gold;

   // set coins game state to 0
   G.coins = 0;

   // updateCoins for player 1 with no bonus, coin value should be 9
   updateCoins(0, &G, 0);
   assert_custom(G.coins == 9, "Player 1 update coins no bonus");

   // updateCoins for player 2 with bonus of 10, coin value should be 21
   updateCoins(1, &G, 10);
   assert_custom(G.coins == 21, "Player 2 update coins with bonus");

   printf("---------------- End of Unit Test 2 updateCoins() ----------------\n");
  return 0;
   }
