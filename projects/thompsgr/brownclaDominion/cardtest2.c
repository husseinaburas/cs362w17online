/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 3
 *
 * Testing card: Adventurer
 *
 * makefile:
 *  cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
 *
 */

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include "rngs.h"

 // set PRINT_TEST to 0 to remove print statements from output, 1 to show
 #define PRINT_TEST 1

 /* Adventurer testing check:
 *
 *  playing this card:
 *    If the player has no Actions left, an error message should be returned.
 *    If successful:
 *      The player should have 2 additional Treasure cards in their hand.
 *      The player's deck should be decremented by at least 2 cards (possibly more)
 *      The player's discard should have zero or more cards added
 *      The total number of cards taken from the deck should equal ([cards added to discard] + 2)
 *      The adventurer card should be in the player's discard pile.
 *      No other player states should change.
 *      No supply states should change.
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

 int checkPlayAdventurer(int handPos, int p, struct gameState *post, int expDeckLoss, int expDiscardInc) {
   struct gameState pre;
   int r;
   //make copy of state before playing card
   memcpy(&pre, post, sizeof(struct gameState));
   r = playCard(handPos, -1, -1, -1, post);

   //if player has no more actions, an error should be returned
   if (pre.numActions < 1) {
     if (assertTrue((r == -1), "Adventurer with no actions left") == 0) {
       printf("\tTest Passed\n");
       return 0;
     } else {
       printf("\tTest Failed\n");
       return 1;
     }
   }
   #if (PRINT_TEST)
    printf("\nActual Game state after playing Adventurer:\n");
    printState(post);
    printf("\n");
   #endif

   int treasure = 0;
   int idx = pre.deckCount[p]-1;
   while (treasure < 2 && idx >= 0) {
     if (pre.deck[p][idx] >= copper && pre.deck[p][idx] <= gold) {
       //add treasure card to hand
       pre.hand[p][pre.handCount[p]] = pre.deck[p][idx];
       pre.handCount[p]++;
       treasure++;
     } else {
       //add non-treasure card to discard pile
       pre.discard[p][pre.discardCount[p]] = pre.deck[p][idx];
       pre.discardCount[p]++;
     }
     //move to next card in deck
     pre.deckCount[p]--;
     idx--;
   }
   //remove adventurer card from hand, add to discard pile
   pre.discard[p][pre.discardCount[p]] = adventurer;
   pre.discardCount[p]++;
   //replace discarded card with last card in hand
   pre.hand[p][handPos] = pre.hand[p][pre.handCount[p]-1];
   //set last card position to -1
   pre.hand[p][pre.handCount[p]-1] = -1;
   //update hand count and add smithy card to discard pile
   pre.handCount[p]--;

   //decrement action count
   pre.numActions--;
   updateCoins(p, &pre, 0);

   #if (PRINT_TEST)
    printf("\nExpected Game state after playing Adventurer:\n");
    printState(&pre);
    printf("\n");
   #endif

   //compare states, if the same, test passes
   if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
     printf("\tTest Failed\n");
     return 1;
   }
   printf("\tTest Passed\n");
   return 0;
 }

 int main() {
   printf("\nTESTING CARD: Adventurer\n");
   int allPassed = 0; //init to true, determines if all tests passed.
   int p, r;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                village, baron, great_hall};
   struct gameState G;

   printf("\tTEST: successfully play Adventurer card\n");
   p = 0; //test on first player
   memset(&G, 23, sizeof(struct gameState));
   //initialize game
   r = initializeGame(2, k, 3, &G);
   //place Adventurer card in player's hand, at position 0
   G.hand[p][0] = adventurer;
   //preset cards in discard pile so first two are not Treasure cards
   //this means to pass, all three non-treasure cards should end up in the discard pile.
   G.deckCount[p] = 5;
   G.deck[p][0] = copper;
   G.deck[p][1] = copper;
   G.deck[p][2] = smithy;
   G.deck[p][3] = copper;
   G.deck[p][4] = estate;
   //update coin count
   updateCoins(p, &G, 0);
   #if (PRINT_TEST)
    printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
    printState(&G);
   #endif
   //expecting 4 cards drawn, 2 added to hand, 2 added to discard
   if (checkPlayAdventurer(0, p, &G, 4, 2) == 1) {
     allPassed = 1;
   }

   printf("\tTEST: attempt to play Adventurer with no Actions left\n");
   p = 0; //test on first player
   memset(&G, 23, sizeof(struct gameState));
   //initialize game
   r = initializeGame(2, k, 3, &G);
   //place Adventurer card in player's hand, at position 0
   G.hand[p][0] = adventurer;
   G.numActions = 0;
   #if (PRINT_TEST)
    printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
    printState(&G);
   #endif
   //expecting a return error that the card cannot be played
   if (checkPlayAdventurer(0, p, &G, 0, 0) == 1) {
     allPassed = 1;
   }

   if (allPassed == 0) {
     printf("\tFINAL RESULT: ALL TESTS PASSED\n");
   } else {
     printf("\tFINAL RESULT: NOT ALL TESTS PASSED\n");
   }

   return 0;
 }
