#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "assert_custom.h"
#include "string.h"

int main (int argc, char** argv) {
   struct gameState G, copyG;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
   int seed = 738;
   int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

   printf("---------------- Smithy Card Test ----------------\n");

   initializeGame(2, k, seed, &G);

   // set player 1 as the player and make the first card in player 1 hand smithy
   G.whoseTurn = 0;
   G.hand[0][0] = smithy;

   // save initial state
   memcpy(&copyG, &G, sizeof(struct gameState));

   // confirm smithy is in hand
   assert_custom(G.hand[0][0] == smithy, "test smithy card is in hand");

   cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);

   // test player hand card count increase
   int hCntDiff = G.handCount[0] - copyG.handCount[0];
   assert_custom(hCntDiff > 0, "test handCount increased");
   assert_custom(hCntDiff == 2, "test handCount increase by 2 cards");

   // test deckCount decrease
   int deckCntDiff = G.deckCount[0] - copyG.deckCount[0];
   assert_custom(deckCntDiff < 0, "test deckCount decreased");
   assert_custom(deckCntDiff == -3, "test deckCount decrease by 3 cards");

   // test discardCount increase
   int disCntDiff = G.discardCount[0] - copyG.discardCount[0];
   assert_custom(disCntDiff > 0, "test discardCount increase");
   assert_custom(disCntDiff == 1, "test discardCount increase by 1 card");
    
   // test playedCardCount increase
   int playedCardDiff = G.playedCardCount - copyG.playedCardCount;
   assert_custom(playedCardDiff > 0, "test playedCardCount increase");
   assert_custom(playedCardDiff == 1, "test playedCardCount increase by 1 card");

   // test smithy removed from hand
   assert_custom(G.hand[0][0] != smithy, "test smithy is removed from hand");

   printf("---------------- End of Smithy Card Test ----------------\n");
  return 0;
}
