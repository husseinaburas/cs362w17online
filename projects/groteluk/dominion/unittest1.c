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

   printf("---------------- Unit Test 1 whoseTurn() ----------------\n");

   // set gamestate whoseTurn value directly to 6 and check with getter function
   G.whoseTurn = 6;
   assert_custom(whoseTurn(&G) == 6, "get whoseTurn value after setting directly to 6 prior to initializing game");

   initializeGame(2, k, seed, &G);

   // use whoseTurn getter function to test state change and getting function after game initialized
   assert_custom(whoseTurn(&G) == 0, "get whoseTurn value after initializing game");

   // end turn change to player 2
   endTurn(&G);

   // check whoseTurn reads next player after player change
   assert_custom(whoseTurn(&G) == 1, "get whoseTurn value after ending turn");

   printf("---------------- End of Unit Test 1 whoseTurn() ----------------\n");
  return 0;
}
