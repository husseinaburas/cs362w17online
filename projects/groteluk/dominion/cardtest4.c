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

   printf("---------------- Council Room Card Test ----------------\n");

   initializeGame(2, k, seed, &G);

   // set player 1 as the player and make the first card in player 1 hand council room
   G.whoseTurn = 0;
   G.hand[0][0] = council_room;

   // save initial state
   memcpy(&copyG, &G, sizeof(struct gameState));

   // confirm council room is in hand
   assert_custom(G.hand[0][0] == council_room, "test council room card is in hand");

   cardEffect(council_room, choice1, choice2, choice3, &G, handPos, &bonus);

   // test player hand card count increases by 3
   int hCntDiff = G.handCount[0] - copyG.handCount[0];
   assert_custom(hCntDiff > 0, "test handCount increased");
   assert_custom(hCntDiff == 3, "test handCount increases by 3");

   // test deckCount decrease for player 1
   int deckCntDiff = G.deckCount[0] - copyG.deckCount[0];
   assert_custom(deckCntDiff < 0, "test deckCount decreased");
   assert_custom(deckCntDiff == -4, "test deckCount decrease by 4 cards for player of card");

   // test deckCount decrease for player 2
   int deckCntDiff1 = G.deckCount[1] - copyG.deckCount[1];
   assert_custom(deckCntDiff1 < 0, "test deckCount decreased");
   assert_custom(deckCntDiff1 == -1, "test deckCount decrease by 1 card for player 2");

   // test numBuys increase by 1
   int numBuysDiff = G.numBuys - copyG.numBuys;
   assert_custom(numBuysDiff > 0, "test numBuys increases");
   assert_custom(numBuysDiff == 1, "test numBuys increases by 1");

   // test discardCount increase
   int disCntDiff = G.discardCount[0] - copyG.discardCount[0];
   assert_custom(disCntDiff > 0, "test discardCount increase");
   assert_custom(disCntDiff == 1, "test discardCount increase by 1 card");

   // test playedCardCount increase
   int playedCardDiff = G.playedCardCount - copyG.playedCardCount;
   assert_custom(playedCardDiff > 0, "test playedCardCount increase");
   assert_custom(playedCardDiff == 1, "test playedCardCount increase by 1 card");

   // test council room removed from hand
   assert_custom(G.hand[0][0] != council_room, "test village is removed from hand");

   printf("---------------- End of Council Room Card Test ----------------\n");
  return 0;
}
