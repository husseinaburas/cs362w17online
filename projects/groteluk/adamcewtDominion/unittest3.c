#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "assert_custom.h"

int main (int argc, char** argv) {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    int seed = 738;

   printf("---------------- Unit Test 3 handCard() ----------------\n");

   initializeGame(2, k, seed, &G);
    
   // setup player 1 hand with known cards to test handCard
   G.handCount[0] = 2;
   G.hand[0][0] = curse;
   G.hand[0][1] = treasure_map;
   
   // setup player 2 hand with known cards to test handCard
   G.handCount[1] = 1;
   G.hand[1][0] = copper;


   // set current player to player 1
   G.whoseTurn = 0;

   // check player 1 cards with handCard() against known inputs
   assert_custom(handCard(0, &G) == curse, "Check player 1 card position 0 is curse");
   assert_custom(handCard(0, &G) == 0, "Check player 1 card position 0 enum is 0");
   assert_custom(handCard(1, &G) == treasure_map, "Check player 1 card position 1 is treasure_map");
   assert_custom(handCard(1, &G) == 26, "Check player 1 card position 1 enum is 26");

   // change to player 2 and test handCard()
   G.whoseTurn = 1;
   assert_custom(handCard(0, &G) == copper, "Check player 2 card position 0 is copper");
   assert_custom(handCard(0, &G) == 4, "Check player 2 card position 0 enum is 4");

   printf("---------------- End of Unit Test 3 handCard() ----------------\n");
   return 0;
   }
