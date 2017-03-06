/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 3
 *
 * Testing card: smithy
 *
 * makefile:
 *  cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
 *
 */

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include "rngs.h"

 // set PRINT_TEST to 0 to remove print statements from output, 1 to show
 #define PRINT_TEST 0

 /* smithy testing check:
 *
 *  playing this card:
 *    player should have 3 additional cards in their hand
 *    smithy card should be in the discard pile
 *      discard pile should be incremented by 1
 *    player's deck should be decremented by 3
 *    hand count should be incremented by 2 (-1 for smithy card, + 3 cards)
 *    no other player's state should be changed
 *    no supply pile should be changed
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

 void printState(struct gameState *G) {
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                village, baron, great_hall};
   printf("GAME STATE:\n");
   printf("numPlayers: %d\n", G->numPlayers);
   printf("Kingdom cards supplyCount:\n");
   int i, p, c;
   for (i = 0; i < 10; i++) {
     printf("\t%d: %d \n", k[i], G->supplyCount[k[i]]);
   }
   printf("Treasure cards supplyCount:\n");
   printf("\tCopper: %d\n", G->supplyCount[copper]);
   printf("\tSilver: %d\n", G->supplyCount[silver]);
   printf("\tGold: %d\n", G->supplyCount[gold]);
   printf("Victory cards supplyCount:\n");
   printf("\tEstate: %d\n", G->supplyCount[estate]);
   printf("\tDuchy: %d\n", G->supplyCount[duchy]);
   printf("\tProvince: %d\n", G->supplyCount[province]);
   printf("Curse card supplyCount: %d\n", G->supplyCount[curse]);
   printf("\n");
   printf("Whose Turn: %d\n", G->whoseTurn);
   printf("Phase: %d\n", G->phase);
   printf("PLAYER STATE:\n");
   printf("\tnumActions: %d\n", G->numActions);
   printf("\tnumBuys: %d\n", G->numBuys);
   printf("\tcoins: %d\n", G->coins);
   for (p = 0; p < G->numPlayers; p++) {
     printf("Player %d:\n", p);
     printf("\tHand Count: %d \n", G->handCount[p]);
     for (c = 0; c < G->handCount[p]; c++) {
       //show all cards in hand
       printf("\t\t card %d\n", G->hand[p][c]);
     }
     printf("\tDeck Count: %d \n", G->deckCount[p]);
     for (c = 0; c < G->deckCount[p]; c++) {
       //show all cards in deck
       printf("\t\t card %d\n", G->deck[p][c]);
     }
     printf("\tDiscard Count: %d \n", G->discardCount[p]);
     for (c = 0; c < G->discardCount[p]; c++) {
       //show all cards in discard pile
       printf("\t\t card %d\n", G->discard[p][c]);
     }
   }
   printf("PLAYED CARDS:\n");
   printf("\tPlayed Card Count: %d\n", G->playedCardCount);
   for (c = 0; c < G->playedCardCount; c++) {
     //show all cards in played card pile
     printf("\t\t card %d\n", G->playedCards[c]);
   }
 }

 int checkPlaySmithy(int handPos, int p, int trashFlag, struct gameState *post) {
   struct gameState pre;
   int r, i;

   //make copy of state before playing card
   memcpy(&pre, post, sizeof(struct gameState));

   r = playCard(handPos, -1, -1, -1, post);

   //if player has no more actions, an error should be returned
   if (pre.numActions < 1) {
     if (assertTrue((r == -1), "smithy with no actions left") == 0) {
       printf("\tTest Passed\n");
       return 0;
     } else {
       printf("\tTest Failed\n");
       return 1;
     }
   }

   #if (PRINT_TEST)
    printf("\nActual Game state after playing Smithy:\n");
    printState(post);
    printf("\n");
   #endif

   //setup expected state
   //draw three cards from the deck
   for (i = 0; i < 3; i++) {
     drawCard(p, &pre);
   }
   //replace discarded card with last card in hand
   pre.hand[p][handPos] = pre.hand[p][pre.handCount[p]-1];
   //set last card position to -1
   pre.hand[p][pre.handCount[p]-1] = -1;
   //update hand count and add smithy card to discard pile
   pre.handCount[p]--;
   if (trashFlag == 0) {
     pre.discardCount[p]++; //smithy card should be in discard pile
     pre.discard[p][pre.discardCount[p]-1] = smithy; //add smithy to end of discard pile
   }
   //pre.handCount[p] = pre.handCount[p] + 2; //lose one card, gain three
   //pre.deckCount[p] = pre.deckCount[p] - 3; //decrement player's pile by 3
   pre.numActions--; //used one action to play the card
   updateCoins(p, &pre, 0);
   #if (PRINT_TEST)
    printf("\nExpected Game state after playing Smithy:\n");
    printState(&pre);
    printf("\n");
   #endif

   //compare game states, if same, pass
   if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
     printf("\tTest Failed\n");
     return 1;
   }
   printf("\tTest Passed\n");
   return 0;
 }

 int main() {
   printf("\nTESTING CARD: Smithy\n");

   int allPassed = 0; //init to true, will change to false if any of the tests fail.
   int p, r, i;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                village, baron, great_hall};
   struct gameState G;


   printf("\tTEST: play Smithy card without trash flag set\n");
   //test on player 0
   p = 0;
   memset(&G, 23, sizeof(struct gameState));
   r = initializeGame(2, k, 1, &G); //init game with two players (min)
   //printState(&G);
   G.whoseTurn = p;
   //place smithy card in player's hand, at position 0
   G.hand[p][0] = smithy;
   updateCoins(p, &G, 0);
   #if (PRINT_TEST)
    printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
    printState(&G);
   #endif
   if (checkPlaySmithy(0, p, 0, &G) == 1) {
     allPassed = 1;
   }


   printf("\tTEST: play Smithy card with trash flag set\n");
   //test on player 0
   p = 0;
   memset(&G, 23, sizeof(struct gameState));
   r = initializeGame(2, k, 1, &G); //init game with two players (min)
   //printState(&G);
   G.whoseTurn = p;
   //place smithy card in player's hand, at varying position 0
   G.hand[p][0] = smithy;
   updateCoins(p, &G, 0);
   #if (PRINT_TEST)
    printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
    printState(&G);
   #endif
   if (checkPlaySmithy(0, p, 1, &G) == 1) {
     allPassed = 1;
   }

   printf("\tTEST: play Smithy card when deck is empty\n");
   memset(&G, 23, sizeof(struct gameState));
   r = initializeGame(2, k, 1, &G);
   //place smithy card in player's hand, at varying position 0
   G.hand[p][0] = smithy;
   updateCoins(p, &G, 0);
   //add all cards in deck to discard pile
   for (i = 0; i < G.deckCount[p]; i++) {
     G.discard[p][i] = G.deck[p][i];
   }
   G.discardCount[p] = G.deckCount[p];
   //set deck as empty
   for (i = 0; i < G.deckCount[p]; i++) {
     G.deck[p][i] = -1;
   }
   G.deckCount[p] = 0;
   #if (PRINT_TEST)
    printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
    printState(&G);
   #endif
   if (checkPlaySmithy(0, p, 0, &G) == 1) {
     allPassed = 1;
   }




   printf("\tTEST: attempt to play Smithy card when player has no more Actions\n");
   memset(&G, 23, sizeof(struct gameState));
   r = initializeGame(2, k, 1, &G); //init game with two players (min)
   //printState(&G);
   G.numActions = 0;
   //place smithy card in player's hand, at varying position 0
   G.hand[p][0] = smithy;
   updateCoins(p, &G, 0);
   #if (PRINT_TEST)
    printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
    printState(&G);
   #endif
   if (checkPlaySmithy(0, p, 0, &G) == 1) {
     allPassed = 1;
   }

   //if allPassed is still set to 0, all tests passed.
   if(allPassed == 0) {
     printf("\tFINAL: ALL TESTS PASSED\n");
   } else {
     printf("\tFINAL: TESTS DID NOT ALL PASS\n");
   }

   return 0;
 }
