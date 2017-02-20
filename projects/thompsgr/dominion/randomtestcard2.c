/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 4
 *
 * Random Testing for Card: Smithy
 *
 * makefile:
 *  randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *	   gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
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

  int randomCheckPlaySmithy(int handPos, int p, int trashFlag, struct gameState *post) {
    struct gameState pre;
    int r;
    //make copy of state before playing Smithy card
    memcpy(&pre, post, sizeof(struct gameState));
    //play Smithy card
    r = playCard(handPos, -1, -1, -1, post);
    //If player had no more Actions to play, error should be returned
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
    //The player should have 2 additional cards in their hand, if Smithy card has been discarded
    if (post->handCount[p] != pre.handCount[p] + 2) {
      #if (PRINT_TEST)
        printf("Test Failed: Expected Hand Count: %i, Actual Hand Count: %i\n", pre.handCount[p]+1, post->handCount[p]);
      #endif
      return 1;
    }
    //If the trashFlag is set, the discard count should not change.
    if (trashFlag == 1) {
      if (post->discardCount[p] != pre.discardCount[p]) {
        #if (PRINT_TEST)
          printf("Test Failed: Expected Discard Count: %i, Actual Discard Count: %i\n", pre.discardCount[p], post->discardCount[p]);
        #endif
        return 1;
      }
    }
    //If the trashFlag is not set, the discard count should increment by 1.
    else if (trashFlag == 0) {
      if (post->discardCount[p] != pre.discardCount[p] + 1) {
        #if (PRINT_TEST)
          printf("Test Failed: Expected Discard Count: %i, Actual Discard Count: %i\n", pre.discardCount[p]+1, post->discardCount[p]);
        #endif
        return 1;
      }
    }
    //Player should have one less Action than before.
    if (post->numActions != pre.numActions - 1) {
       #if (PRINT_TEST)
        printf("Test Failed: Expected Action count: %i, Actual Action Count: %i\n", pre.numActions - 1, post->numActions);
       #endif
       return 1;
    }

    return 0; //the test passed
  }

  int main() {
    int n, i, p, r, handPos, numActions, numBuys, result;
    int trashFlag = 0;
    int passed = 0;
    int failed = 0;
    time_t t;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int allCards[17] = {curse, estate, duchy, province, copper, silver, gold,
         adventurer, council_room, feast, gardens, mine, remodel, smithy,
         village, baron, great_hall};
    struct gameState *G;

    printf("\nRANDOM TESTING: Smithy\n");

    srand((unsigned) time(&t)); //Initialize random number generator

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
      G->hand[p][handPos] = smithy;
      //randomly determine trash flag set or not
      trashFlag = rand() % 2; //0 for not set, 1 for set
      updateCoins(p, G, 0); //update the coin count to what the player now has in their hand
      //randomly determine the number of Actions the player has (between 0 and 5)
      numActions = rand() % 6;
      G->numActions = numActions;
      //randomly determine the number of Buys the player has (between 0 and 5)
      numBuys = rand() % 6;
      G->numBuys = numBuys;
      //test the Smithy card with the current gameState
      result = randomCheckPlaySmithy(handPos, p, trashFlag, G);
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
