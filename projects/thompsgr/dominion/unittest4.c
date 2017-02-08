/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 3
 *
 * Testing function: buyCard
 *
 * makefile:
 *  unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
 *
 */

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include "rngs.h"

 // set PRINT_TEST to 0 to remove print statements from output
 #define PRINT_TEST 0

 /* buyCard testing check:
 *
 *  if the supply pile is empty, an error should be returned.
 *  if the player does not have any Buys left, an error should be returned.
 *  if the player does not have enough coins to purchase, an error should be returned.
 *  if none of the above statements apply, the player should be able to purchase
 *    the specified card, sent to the player's discard pile.
 *  if successful:
 *    the supply pile for the specified card should be decremented by 1.
 *    the player's buy count should be decremented by 1.
 *    the player's coin count should be decremented by the cost of the card.
 *    the player's discard pile contains the specified card, count incremented by 1.
 *    no other player states should be changed.
 *    no state change should happen to any other supply pile.
 */

 //function to check assertion
 int assertTrue(int compare, char* test) {
   if (compare == 1) {
     #if (PRINT_TEST == 1)
       printf("\tTest for %s passed\n", test);
     #endif
     return 0;
   } else {
     #if (PRINT_TEST == 1)
       printf("\tTest for %s failed\n", test);
     #endif
     return 1;
   }
 }

 int checkBuyCard(int p, int card, struct gameState *post) {
   struct gameState pre;
   memcpy (&pre, post, sizeof(struct gameState));
   //try to buy the card
   int r;
   r = buyCard(card, post);

   //if supply pile is empty, should have a -1 response
   if (pre.supplyCount[card] < 1) {
     if (assertTrue((r == -1), "empty supply pile") == 0) {
       return 0;
     } else {
       return 1;
     }
   }
   //if card is too expensive for player
   if (pre.coins < getCost(card)) {
     if (assertTrue((r == -1), "card too expensive") == 0) {
       return 0;
     } else {
       return 1;
     }
   }
   //if player does not have enough buys
   if (pre.numBuys < 1) {
     if (assertTrue((r == -1), "not enough buys") == 0) {
       return 0;
     } else {
       return 1;
     }
   }
   //check if can successfully buy a card
   if (r == -1) {
     printf("\tERROR with buyCard\n");
     return 1;
   }
   pre.coins = pre.coins - getCost(card);
   pre.numBuys--;
   pre.supplyCount[card]--;
   pre.discardCount[p]++; //add card to discard pile
   pre.discard[p][pre.discardCount[p]-1] = card;
   pre.phase = 1; //changes to Buy phase

   #if (PRINT_TEST)
    printf("\tCoin count: Expected: %d, Actual: %d\n", pre.coins, post->coins);
    printf("\tBuy count: Expected: %d, Actual: %d\n", pre.numBuys, post->numBuys);
    printf("\tDiscard count: Expected: %d, Actual: %d\n", pre.discardCount[p], post->discardCount[p]);
    printf("\tCard in discard pile: Expected: %d, Actual: %d\n", pre.discard[p][pre.discardCount[p]-1], post->discard[p][post->discardCount[p]-1]);
    printf("\tHand count: Expected: %d, Actual: %d\n", pre.handCount[p], post->handCount[p]);
    printf("\tDeck count: Expected: %d, Actual: %d\n\n", pre.deckCount[p], post->deckCount[p]);
   #endif
   if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
     //printf("\tTest Failed\n");
     return 1;
   }
   return 0;
 }

 int main() {
   printf("\nTESTING FUNCTION: buyCard:\n");
   int allPassed = 0; //set to true, will change to false if any of the tests fail.
   int p, r, supplyCount, coinCount, buyCount, selectedCard, discardCount, maxDiscardCount;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                village, baron, great_hall};
   struct gameState G;

   //attempt to buy a card whose supply pile is empty
   supplyCount = 0; //empty supply of mine cards
   selectedCard = adventurer; //attempt to buy this card
   coinCount = 6; //just enough coins to buy the card.
   buyCount = 1; //enough actions to buy the card
   discardCount = 0; //initalize discard pile
   maxDiscardCount = 10; //can hold up to 10 cards (more than needed for the tests)


   printf("\tTEST: attempt to buy card from empty supply pile\n");
   //test with player 0
   p = 0;
   memset(&G, 23, sizeof(struct gameState));
   r = initializeGame(2, k, 1, &G); //init game with two players (min)
   G.discardCount[p] = discardCount; //set to 0
   memset(G.discard[p], 0, sizeof(int) * maxDiscardCount);
   //set number of buys for player
   G.supplyCount[selectedCard] = supplyCount; //empty supply pile
   G.numBuys = buyCount;
   G.coins = coinCount;
   if (checkBuyCard(p, selectedCard, &G) != 0) {
     printf("\tTest failed\n");
     allPassed = 1;
   }


   //attempt to buy a card that costs coins than the player has
   //last iteration should have enough coins for the card to be bought
   supplyCount = 10;
   printf("\tTEST: attempt to buy card that is too expensive\n");
   //test with player 0 again
   p = 0;
   for (coinCount = 0; coinCount <= getCost(selectedCard); coinCount++) {
     #if (PRINT_TEST)
      printf("\tBuy card %d, cost: %d, currentCoins: %d\n", selectedCard, getCost(selectedCard), coinCount);
     #endif
     memset(&G, 23, sizeof(struct gameState));
     r = initializeGame(2, k, 1, &G); //init game with two players (min)
     G.discardCount[p] = discardCount; //set to 0
     memset(G.discard[p], 0, sizeof(int) * maxDiscardCount);
     //set number of buys for player
     G.supplyCount[selectedCard] = supplyCount;
     G.numBuys = buyCount;
     G.coins = coinCount;
     if (checkBuyCard(p, selectedCard, &G) != 0) {
       printf("\tTest Failed\n");
       allPassed = 1;
     }
   }

   //attempt to buy a card when the player has no Buys left
   printf("\tTEST: attempt to buy card with 0 Buys left\n");
   coinCount = 10;
   buyCount = 0;
   p = 0;
   memset(&G, 23, sizeof(struct gameState));
   r = initializeGame(2, k, 1, &G); //init game with two players (min)
   G.discardCount[p] = discardCount; //set to 0
   memset(G.discard[p], 0, sizeof(int) * maxDiscardCount);
   //set number of buys for player
   G.supplyCount[selectedCard] = supplyCount;
   G.numBuys = buyCount;
   G.coins = coinCount;
   if (checkBuyCard(p, selectedCard, &G) != 0) {
     printf("\tTest Failed\n");
     allPassed = 1;
   }

   //successfully buy a card
   coinCount = 10;
   buyCount = 2;
   supplyCount = 10;
   printf("\tTEST: successfully buy a card\n");
   for (p = 0; p < 2; p++) {
     memset(&G, 23, sizeof(struct gameState));
     r = initializeGame(2, k, 1, &G); //init game with two players (min)
     G.discardCount[p] = discardCount; //set to 0
     memset(G.discard[p], 0, sizeof(int) * maxDiscardCount);
     //set number of buys for player
     G.supplyCount[selectedCard] = supplyCount;
     G.numBuys = buyCount;
     G.coins = coinCount;
     G.whoseTurn = p; //specify which player's turn it is.
     if (checkBuyCard(p, selectedCard, &G) != 0) {
       printf("\tTest Failed\n");
       allPassed = 1;
     }
   }

   if (allPassed == 0) {
     printf("\tFINAL: ALL TESTS PASSED\n\n");
   } else {
     printf("\tFINAL: TESTS DID NOT ALL PASS\n");
   }

   return 0;
 }
