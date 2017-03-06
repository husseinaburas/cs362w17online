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

   printf("---------------- Unit Test 4 supplyCount() ----------------\n");

   initializeGame(2, k, seed, &G);

   // check game initialized curse card to 10 for 2 players
   assert_custom(supplyCount(curse, &G) == 10, "check supply count of curse card is 10");

   // directly change supply of curse cards to 14
   G.supplyCount[curse] = 14;

   // assert supplyCount() gets new supply value of curse cards
   assert_custom(supplyCount(curse, &G) == 14, "check supply count of curse card is 14");

   printf("---------------- End of Unit Test 4 supplyCount() ----------------\n");
  return 0;
}
