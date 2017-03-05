/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 4
 *
 * Random Testing for Card: Council Room
 *
 * makefile:
 *  randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *	   gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 *
 */

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include <time.h>
 #include "rngs.h"

 // set PRINT_TEST to 0 to remove print statements from output
 #define PRINT_TEST 0

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

 int checkPlayCouncilRoom(int handPos, int p, struct gameState *post) {
   struct gameState pre;
   int r, i;
   //make a copy of the game state before playing the card
   memcpy(&pre, post, sizeof(struct gameState));
   r = playCard(handPos, -1, -1, -1, post);

   //If player has no more actions, an error should be returned.
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
   //Player should have 4 additional cards in their hand, and minus the Council Room card (so 3 added total)
   if(post->handCount[p] != pre.handCount[p] + 3) {
     #if (PRINT_TEST)
      printf("Test Failed: Expected Hand Count: %i, Actual Hand Count: %i\n", pre.handCount[p]+3, post->handCount[p]);
     #endif
   }
   //Council Room card should be in player's discard pile, discard should be incremented by 1
   //If player originally had 0 - 3 cards in their deck, and needed to shuffle the discard pile
   if (pre.deckCount[p] < 4) {
     //discard pile should be set to 0, and deck should now have all of those cards
     pre.discardCount[p] = 0;
   }
   //discard pile should have Council Room card in it now
   if (post->discardCount[p] != pre.discardCount[p] + 1) {
     #if (PRINT_TEST)
        printf("Test Failed: Expected Discard Count: %i, Actual Discard Count: %i\n", pre.discardCount[p]+1, post->discardCount[p]);
     #endif
     return 1;
   }
   //Main player should have one less action
   if(post->numActions != pre.numActions - 1) {
     #if (PRINT_TEST)
      printf("Test Failed: Expected Action count: %i, Actual Action Count: %i\n", pre.numActions - 1, post->numActions);
     #endif
     return 1;
   }
   //Main player should have one additional Buy
   if(post->numBuys != pre.numBuys + 1) {
     #if (PRINT_TEST)
      printf("Test Failed: Expected Buy count: %i, Actual Buy Count: %i\n", pre.numBuys + 1, post->numBuys);
     #endif
     return 1;
   }
   //Every other player should have one additional card in their hand
   for (i = 0; i < post->numPlayers; i++) {
     if (i != p) {
       //if not the current player, check the deck, hand, and discard pile counts
       //player should have one additional card in their hand
       if(post->handCount[i] != pre.handCount[i] + 1) {
         #if (PRINT_TEST)
            printf("Test Failed: Player %i Expected Hand Count: %i, Actual Hand Count: %i\n", i, pre.handCount[i]+1, post->handCount[i]);
         #endif
         return 1;
       }
       //if player's deck was originally empty, switch out to discard pile
       if (pre.deckCount[i] < 1) {
         pre.deckCount[i] = pre.discardCount[i];
         pre.discardCount[i] = 0; //no more cards in discard if all have been moved to deck
         //draw card
         pre.deckCount[i]--;
       } else {
         pre.deckCount[i]--; //decrement player deck by 1
       }
       //Player's deck should be decremented by one
       if (post->deckCount[i] != pre.deckCount[i]) {
         #if (PRINT_TEST)
            printf("Test Failed: Player %i Expected Deck Count: %i, Actual Deck Count: %i\n", i, pre.deckCount[i], post->deckCount[i]);
         #endif
         return 1;
       }
       //Player's discard pile should match expected count
       if (post->discardCount[i] != pre.discardCount[i]) {
         #if (PRINT_TEST)
            printf("Test Failed: Player %i Expected Discard Count: %i, Actual Discard Count: %i\n", i, pre.discardCount[i], post->discardCount[i]);
         #endif
         return 1;
       }
     }
   }
   //Every other player should have one less card in their deck
   return 0; //test passed
 }


int main() {
  int n, i, p, r, numPlayers, handPos, numActions, numBuys;
  int result = 0;
  int passed = 0;
  int failed = 0;
  time_t t;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int allCards[17] = {curse, estate, duchy, province, copper, silver, gold,
         adventurer, council_room, feast, gardens, mine, remodel, smithy,
         village, baron, great_hall};
  struct gameState *G;

  printf("\nRANDOM TESTING: council_room\n");

  srand((unsigned) time(&t)); //initialize the random number generator
  //allocate memory for the gameState
  G = (struct gameState *)malloc(sizeof(struct gameState));
  //run 2000 tests
  for (n = 0; n < 2000; n++) {
    //Randomly determine the number of players
    numPlayers = (rand() % 3) + 2; //No less than 2 players, no more than 4.
    //Initialize the game with that many players
    r = initializeGame(numPlayers, k, 2, G);
    if (r < 0) {
      printf("Failed to Initialize Game.\n");
      exit(2);
    }
    //For each player, randomly generate their hand, discard, and deck
    for (p = 0; p < numPlayers; p++) {
      //determine number of deck cards, and randomly fill deck
      G->deckCount[p] = rand() % MAX_DECK;
      for (i = 0; i < G->deckCount[p]; i++) {
        G->deck[p][i] = allCards[rand() % 17]; //17 valid cards to choose from
      }
      //determine number of discard cards, and randomly fill discard
      G->discardCount[p] = rand() % MAX_DECK;
      for (i = 0; i < G->discardCount[p]; i++) {
        G->discard[p][i] = allCards[rand() % 17];
      }
      //determine number of cards, and randomly fill hand
      G->handCount[p] = rand() % MAX_HAND;
      for (i = 0; i < G->handCount[p]; i++) {
        G->hand[p][i] = allCards[rand() % 17];
      }
    }
    //For first player, if the player has zero cards in hand, add one (council_room)
    if(G->handCount[0] < 1) {
      G->handCount[0]++;
    }
    //place council_room in random position in first player's hand
    handPos = rand() % G->handCount[0];
    G->hand[0][handPos] = council_room;
    updateCoins(0, G, 0); //update Coin count for player
    //determine random number of actions (between 0 and 5)
    numActions = rand() % 6;
    G->numActions = numActions;
    //determine random number of buys (between 0 and 5)
    numBuys = rand() % 6;
    G->numBuys = numBuys;
    //test Council Room
    //printState(G);
    result = checkPlayCouncilRoom(handPos, 0, G);
    //check result, add to count accordingly
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
