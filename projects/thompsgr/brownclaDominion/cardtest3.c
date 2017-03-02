/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 3
 *
 * Testing card: Council Room
 *
 * makefile:
 *  cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
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

 /* Council Room testing check:
 *
 *  playing this card:
 *    If the player has no Actions left, an error message should be returned.
 *    If successful:
 *      The current player should have 4 additional cards in their hand.
 *      The current player's deck should have decreased by 4.
 *      The current player's numBuys should be incremented by 1.
 *      Every other player should have 1 additional card in their hand.
 *      Every other player's deck should be decremented by 1.
 *        Every other player's drawn card should come from their own deck.
 *      No supply pile should be changed.
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

 int checkPlayCouncilRoom(int handPos, int p, struct gameState *post) {
   struct gameState pre;
   int r, i;

   memcpy(&pre, post, sizeof(struct gameState));

   r = playCard(handPos, -1, -1, -1, post);

   //if player has no more actions, an error should be returned
   if (pre.numActions < 1) {
     if (assertTrue((r == -1), "council_room with no actions left") == 0) {
       printf("\tTest Passed\n");
       return 0;
     } else {
       printf("\tTest Failed\n");
       return 1;
     }
   }

   #if (PRINT_TEST)
    printf("\nActual Game state after playing Council_Room:\n");
    printState(post);
    printf("\n");
   #endif

   //if current player's deck is empty:
   if (pre.deckCount[p] <= 0) {
     //move discard to deck, and shuffle
     for (i = 0; i < pre.discardCount[p]; i++) {
       pre.deck[p][i] = pre.discard[p][i];
       pre.discard[p][i] = -1;
     }
     pre.deckCount[p] = pre.discardCount[p]; //deck has all discard now
     pre.discardCount[p] = 0; //discard pile now empty
     //shuffle the deck (might complicate testing process)
     shuffle(p, &pre);
   }

   //current player should have 4 additional cards in their hand, taken from their deck
   for (i = 0; i < 4; i++) {
     //take card from end of deck, add to hand
     pre.hand[p][pre.handCount[p]] = pre.deck[p][pre.deckCount[p]-1];
     pre.handCount[p]++;
     pre.deck[p][pre.deckCount[p]-1] = -1;
     pre.deckCount[p]--;
   }
   //council_room card should be placed in player's discard pile
   pre.discard[p][pre.discardCount[p]] = pre.hand[p][handPos];
   pre.discardCount[p]++;
   //council_room card position should be replaced by last card in hand
   pre.hand[p][handPos] = pre.hand[p][pre.handCount[p]-1];
   pre.hand[p][pre.handCount[p]-1] = -1; //set last card to -1.
   pre.handCount[p]--;

   //update coin count
   updateCoins(p, &pre, 0);

   //for every other player in the game, add one card from their deck to their hand
   for (i = 0; i < pre.numPlayers; i++) {
     //if not current player, draw a card
     if (i != p) {
       pre.hand[i][pre.handCount[i]] = pre.deck[i][pre.deckCount[i]-1];
       pre.handCount[i]++;
       pre.deck[i][pre.deckCount[i]-1] = -1;
       pre.deckCount[i]--;
     }
   }
   //decrease player's Action count
   pre.numActions--;
   //increase player's Buy count by 1
   pre.numBuys++;

   #if (PRINT_TEST)
    printf("\nExpected Game state after playing Council_Room:\n");
    printState(&pre);
    printf("\n");
   #endif

   //if deck was empty shuffle was used so we can't directly compare the states
   //since the ordering of the cards will be randomized.
   int failed = 0;

   //compare counts for each player's hand
   for (i = 0; i < pre.numPlayers; i++) {
     if (pre.handCount[i] != post->handCount[i]) {
       printf("\tHand count for player %d did not match\n", i);
       failed = 1;
     }
     if (pre.deckCount[i] != post->deckCount[i]) {
       printf("\tDeck count for player %d did not match\n", i);
       failed = 1;
     }
     if (pre.discardCount[i] != post->discardCount[i]) {
       printf("\tDiscard count for player %d did not match\n", i);
       failed = 1;
     }
   }
   if (pre.numActions != post->numActions) {
     printf("\tNumActions count for player %d did not match\n", i);
     failed = 1;
   }
   if (pre.numBuys != post->numBuys) {
     printf("\tNumBuys count for player %d did not match\n", i);
     failed = 1;
   }

   if (failed == 1) {
     printf("\tTest failed\n");
     return 1;
   } else {
     printf("\tTest passed\n");
     return 0;
   }
 }


 int main() {
   printf("\nTESTING CARD: Council_Room\n");

   int allPassed = 0; //init to true, checks if all tests passed.

   int p, r, i;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
             village, baron, great_hall};
   struct gameState G;

   printf("\tTEST: successfully play Council_Room\n");
   //test with player 0, with 3 players total
   p = 0;
   for(i = 0; i < 5; i++) { //default 5 cards in hand
     #if (PRINT_TEST)
      printf("\tPlay card in hand position %d\n", i);
     #endif
     memset(&G, 23, sizeof(struct gameState));
     r = initializeGame(4, k, 1, &G); //init game with three players
     //place Council_Room card in player's hand, at varying positions.
     G.hand[p][i] = council_room;
     updateCoins(p, &G, 0); //update coin count to account for change
     #if (PRINT_TEST)
        printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
        printState(&G);
     #endif
     if (checkPlayCouncilRoom(i, p, &G) == 1) {
       allPassed = 1;
     }
   }

   printf("\tTEST: successfully play Council_Room when deck is empty\n");
   memset(&G, 23, sizeof(struct gameState));
   r = initializeGame(2, k, 2, &G); //init game with two players this time
   //place council_room in hand
   G.hand[p][0] = council_room;
   updateCoins(p, &G, 0); //update coin count to account for change
   //G.discardCount[p] = G.deckCount[p];
   //add all deck cards to discard pile
   for (i = 0; i < G.deckCount[p]; i++) {
     G.discard[p][i] = G.deck[p][i];
     G.discardCount[p]++;
   }
   //set deck as empty
   for (i = 0; i < G.deckCount[p]; i++) {
     G.deck[p][i] = -1;
   }
   G.deckCount[p] = 0;
   #if (PRINT_TEST)
      printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
      printState(&G);
   #endif
   if (checkPlayCouncilRoom(0, p, &G) == 1) {
     allPassed = 1;
   }


   printf("\tTEST: attempt to play card when player has no Actions left\n");
   p = 0; //test on first player
   memset(&G, 23, sizeof(struct gameState)); //reset game
   r = initializeGame(2, k, 3, &G); //init game with two players this time
   //place Council_Room card in players hand
   G.hand[p][0] = council_room;
   G.numActions = 0; //set Actions to zero
   #if (PRINT_TEST)
      printf("\nINITIAL STATE FOR PLAYER %d:\n", p);
      printState(&G);
   #endif
   if (checkPlayCouncilRoom(0, p, &G) == 1) {
     allPassed = 1;
   }

   if (allPassed == 0) {
     printf("\tFINAL: ALL TESTS PASSED\n");
   } else {
     printf("\tFINAL: TESTS DID NOT ALL PASS\n");
   }

   return 0;
 }
