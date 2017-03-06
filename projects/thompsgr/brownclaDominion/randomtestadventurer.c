/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 4
 *
 * Random Testing for Card: Adventurer
 *
 * makefile:
 *  randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *	   gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 *
 */

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include <time.h>
 #include "rngs.h"

 // set PRINT_TEST to 0 to remove print statements from output, 1 to show.
 #define PRINT_TEST 0

 /* Adventurer testing check:
  *
  * Playing this card:
  *   If the player has no Actions left, an error message should be returned.
  *   If successful:
  *     The player should have 2 additional Treasure cards in their hand.
 *      The player's deck should be decremented by at least 2 cards (possibly more)
 *      The player's discard should have zero or more cards added
 *      The total number of cards taken from the deck should equal ([cards added to discard] + 2)
 *      The adventurer card should be in the player's discard pile.
 *      No other player states should change.
 *      No supply states should change.
 */

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
     printf("\tDeck Count: %d \n", G->deckCount[p]);
     printf("\tDiscard Count: %d \n", G->discardCount[p]);
   }
   printf("PLAYED CARDS:\n");
   printf("\tPlayed Card Count: %d\n", G->playedCardCount);
   for (c = 0; c < G->playedCardCount; c++) {
     //show all cards in played card pile
     printf("\t\t card %d\n", G->playedCards[c]);
   }
 }

 int checkPlayAdventurer(int handPos, int p, struct gameState *post) {
   struct gameState pre;
   int r;
   memcpy(&pre, post, sizeof(struct gameState)); //make a copy of the game before playing the card
   //play the Adventurer card
   r = playCard(handPos, -1, -1, -1, post);
   //If player had no more actions to play, error should be returned
   if (pre.numActions < 1) {
     if (r != -1) {
       #if (PRINT_TEST)
        printf("Test Failed: Expected an Error\n");
       #endif
       return 1;
     } else {
       #if (PRINT_TEST)
        printf("Test Passed\n");
       #endif
       return 0;
     }
   }
   //The player should have 1 additional cards in their hand, if Adventurer is discarded from hand
   if (post->handCount[p] != pre.handCount[p] + 1) {
     #if (PRINT_TEST)
      printf("Test Failed: Expected Hand Count: %i, Actual Hand Count: %i\n", pre.handCount[p]+1, post->handCount[p]);
     #endif
     return 1;
   }
   //coin count for player should be at least 2 more than before (2 copper), but no more than 6 (two gold)
   if (post->coins < pre.coins + 2 || post->coins > pre.coins + 6) {
     #if (PRINT_TEST)
      printf("Test Failed: Coin count was either too low or too high\n");
     #endif
     return 1;
   }
   //The adventurer card should be in the discard pile, as the last card to be discarded
   if (post->discard[p][post->discardCount[p]-1] != adventurer) {
     #if (PRINT_TEST)
      printf("Test Failed: Expected Adventurer in last position of Discard pile.\n");
     #endif
     return 1;
   }
   //The player should have one less Actions than before
   if (post->numActions != pre.numActions - 1) {
     #if (PRINT_TEST)
      printf("Test Failed: Expected Action count: %i, Actual Action Count: %i\n", pre.numActions - 1, post->numActions);
     #endif
     return 1;
   }


   return 0;
 }

int main() {
  int n, i, p, r, handPos, numActions, numBuys, result;
  int passed = 0;
  int failed = 0;
  time_t t;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int allCards[17] = {curse, estate, duchy, province, copper, silver, gold,
         adventurer, council_room, feast, gardens, mine, remodel, smithy,
         village, baron, great_hall};
  struct gameState *G;

  printf("\nRANDOM TESTING: Adventurer\n");

  srand((unsigned) time(&t)); //initialize the random number generator
  //allocate memory for the gameState
  G = (struct gameState *)malloc(sizeof(struct gameState));
  //run 2000 tests
  p = 0;
  for (n = 0; n < 2000; n++) {
    //Initialize the game with 4 players
    r = initializeGame(4, k, 2, G);
    if (r < 0) {
      printf("Failed to Initialize Game.\n");
      exit(2);
    }
    //For first player, randomly generate the player state
    G->deckCount[p] = rand() % MAX_DECK;
    //randomly determine the cards in the player's deck
    for (i = 0; i < G->deckCount[p]; i++) {
      //assign a valid value to the position
      G->deck[p][i] = allCards[rand() % 17]; //17 valid cards to choose from
    }
    //randomly determine the cards in the player's discard
    G->discardCount[p] = rand() % MAX_DECK;
    for (i = 0; i < G->discardCount[p]; i++) {
      G->discard[p][i] = allCards[rand() % 17];
    }
    //randomly determine the cards in the player's hand
    G->handCount[p] = rand() % MAX_HAND;
    for (i = 0; i < G->handCount[p]; i++) {
      G->hand[p][i] = allCards[rand() % 17];
    }
    //randomly determine the position of Adventurer in the players hand
    //if player has no cards in hand, update handCount to have one card
    if(G->handCount[p] < 1) {
      G->handCount[p]++;
    }
    handPos = rand() % G->handCount[p];
    G->hand[p][handPos] = adventurer;
    updateCoins(p, G, 0); //update the coin count to what the player now has in their hand
    //randomly determine the number of Actions the player has (between 0 and 5)
    numActions = rand() % 6;
    G->numActions = numActions;
    //randomly determine the number of Buys the player has (between 0 and 5)
    numBuys = rand() % 6;
    G->numBuys = numBuys;
    //printf("ITERATION %i BEFORE STATE:\n", n);
    //printState(&G);
    //printf("\n");
    //test the Adventurer card with the current gameState
    result = checkPlayAdventurer(handPos, p, G);
    if (result == 1) {
      failed++; //add to total failed count
    } else {
      passed++;
    }

  }
  //if failed == 0, all passed!
  if (failed == 0) {
    printf("All Tests Passed!\n");
  } else {
    printf("Tests did not all pass.\n");
    printf("\tTotal Passed: %i\n", passed);
    printf("\tTotal Failed: %i\n", failed);
    printf("\tTotal Tests: %i\n", passed + failed);
    printf("\n");
  }
  free(G);
  return 0;
}
