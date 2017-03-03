/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 3
 *
 * Testing card: Feast
 *
 * makefile:
 *  cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
 *
 */

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include "rngs.h"

 // set PRINT_TEST to 0 to remove print statements from output
 #define PRINT_TEST 1

 /* Feast testing check:
 *
 *  playing this card:
 *    If the player has no Actions left, an error message should be returned.
 *    If player requests a card of no more than 5 cost:
 *      The player should have the chosen card added to their discard pile.
 *      The player's discardCount should be incremented by 1.
 *      The Feast card played should be trashed.
 *      The chosen card's supply count should be decremented by 1.
 *      No other supply pile should be changed.
 *    If player requests a card that is more than 5 cost:
 *      An error message should be returned.
 *    If the supply for the requested card is zero:
 *      An error message should be returned.
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
       printf("Test for %s failed\n", test);
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

 int checkPlayFeast(int handPos, int p, int choice, struct gameState *post) {
   struct gameState pre;
   int r;

   memcpy(&pre, post, sizeof(struct gameState)); //make copy of game before playing card
   r = playCard(handPos, choice, -1, -1, post);

   #if (PRINT_TEST)
    printf("\nActual Game state after playing Feast:\n");
    printState(post);
    printf("\n");
   #endif

   //if player has no more actions left to play card
   if (pre.numActions < 1) {
     if (assertTrue((r == -1), "Feast with no actions left") == 0) {
       printf("\tTest Passed\n");
       return 0;
     } else {
       printf("\tTest Failed\n");
       return 1;
     }
   }
   //if supply is empty, an error should be returned
   if (pre.supplyCount[choice] <= 0) {
     if (assertTrue((r == -1), "Feast with no supply left") == 0) {
       printf("\tTest Passed\n");
       return 0;
     } else {
       printf("\tTest Failed\n");
       return 1;
     }
   }
   //if card costs more than 5, an error should be returned
   if (getCost(choice) > 5) {
     if (assertTrue((r == -1), "Feast with too-expensive card") == 0) {
       printf("\tTest Passed\n");
       return 0;
     } else {
       printf("\tTest Failed\n");
       return 1;
     }
   }

   //if card is affordable, add to discard pile, decrement supply pile of that card
   pre.discard[p][pre.discardCount[p]] = choice;
   pre.discardCount[p]++;
   pre.supplyCount[choice]--;
   //remove feast card from player hand, do not add to discard as it is trashed
   pre.hand[p][handPos] = pre.hand[p][pre.handCount[p]-1]; //move last card to where feast was
   pre.hand[p][pre.handCount[p]-1] = -1; //set to emtpy
   pre.handCount[p]--; //decrement hand count

   //decrement action count
   pre.numActions--;

   #if (PRINT_TEST)
    printf("\nExpected Game state after playing Feast:\n");
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
   int p, r, i;
   int allPassed = 0;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
               village, baron, great_hall};
   struct gameState G;

   int affordableCards[13] = {estate, duchy, copper, silver, council_room, feast,
                            gardens, mine, remodel, smithy, village, baron, great_hall};
   int expensiveCards[3] = {province, gold, adventurer};

   printf("\nTESTING CARD: Feast\n");

   printf("\tTEST: successfully play Feast card to obtain cards under 5 coins\n");
   //try to choose each card in the affordableCards list
   p = 0; //test with first player
   for (i = 0; i < 13; i++) {
     printf("\tTesting Feast card with selected card: %d\n", affordableCards[i]);
     memset(&G, 23, sizeof(struct gameState)); //initialize the game
     r = initializeGame(2, k, 1, &G); //with two players
     //place Feast card in player's hand, at position 0
     G.hand[p][0] = feast;
     updateCoins(p, &G, 0); //update coin count for hand
     #if (PRINT_TEST)
      printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
      printState(&G);
     #endif
     //expecting chosen card to end up in player's discard pile, Feast card trashed
     if (checkPlayFeast(0, p, affordableCards[i], &G) == 1) {
       allPassed = 1;
     }
   }

   printf("\tTEST: attempt to buy cards costing more than 5 coins\n");
   for (i = 0; i < 3; i++) {
     printf("\tTesting Feast card with selected card: %d\n", expensiveCards[i]);
     memset(&G, 23, sizeof(struct gameState)); //initialize the game
     r = initializeGame(2, k, 2, &G); //with two players
     //place Feast card in player's hand, at position 0
     G.hand[p][0] = feast;
     updateCoins(p, &G, 0); //update coin count for hand
     #if (PRINT_TEST)
      printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
      printState(&G);
     #endif
     //expecting chosen card to end up in player's discard pile, Feast card trashed
     if (checkPlayFeast(0, p, expensiveCards[i], &G) == 1) {
       allPassed = 1;
     }
   }

   printf("\tTEST: attempt to buy a card from empty supply\n");
   //test on empty card supply (check with every affordable card)
   for (i = 0; i < 13; i++) {
     printf("\tTesting Feast card with empty supply card: %d\n", affordableCards[i]);
     memset(&G, 23, sizeof(struct gameState)); //initialize the game
     r = initializeGame(2, k, 3, &G); //with two players
     //place Feast card in player's hand, at position 0
     G.hand[p][0] = feast;
     updateCoins(p, &G, 0); //update coin count for hand
     G.supplyCount[affordableCards[i]] = 0; //set supply to empty
     #if (PRINT_TEST)
      printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
      printState(&G);
     #endif
     //expecting chosen card to end up in player's discard pile, Feast card trashed
     if (checkPlayFeast(0, p, affordableCards[i], &G) == 1) {
       allPassed = 1;
     }
   }


   printf("\tTEST: attempt to play Feast card with no more Actions left\n");
   memset(&G, 23, sizeof(struct gameState)); //initialize the game
   r = initializeGame(2, k, 4, &G); //with two players
   //place Feast card in player's hand, at position 0
   G.hand[p][0] = feast;
   updateCoins(p, &G, 0); //update coin count for hand
   G.numActions = 0;
   #if (PRINT_TEST)
    printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
    printState(&G);
   #endif
   //expecting chosen card to end up in player's discard pile, Feast card trashed
   if (checkPlayFeast(0, p, silver, &G) == 1) {
     allPassed = 1;
   }

   if (allPassed == 1) {
     printf("\tFINAL: TESTS DID NOT ALL PASS\n");
   } else {
     printf("\tFINAL: ALL TESTS PASSED\n");
   }
   return 0;
 }
