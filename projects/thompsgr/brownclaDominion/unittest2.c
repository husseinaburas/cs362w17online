/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 3
 *
 * Testing function: discardCard
 *
 * makefile:
 *  unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
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

 /*
 discardCard parameters:
    int handPos - position of card in player's hand
    int currentPlayer
    struct gameState state - initialized game
    int trashFlag - whether the card is to be discarded or trashed
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

//function to check the state of the game after calling the discardCard function
int checkDiscardCard(int handPos, int p, struct gameState *post, int trashFlag) {
  //make a copy of the inital game state before discarding card
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  //discard a card
  int r;
  r = discardCard(handPos, p, post, trashFlag);

  //if trash card is not set, handCount should be decremented by one
  // and discardCount should be incremented by one.
  if (trashFlag != 1) {
    //played card should be in playedCards array
    pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];
    pre.playedCardCount++;
    pre.hand[p][handPos] = pre.hand[p][pre.handCount[p]-1]; //put last card in the discarded card's spot
    pre.hand[p][pre.handCount[p]-1] = -1;
    pre.handCount[p]--; //decrement player's hand count
  } else {
    //trash flag is set, card should not be in discard pile
    pre.hand[p][handPos] = pre.hand[p][pre.handCount[p]-1]; //put last card in the discarded card's spot
    pre.hand[p][pre.handCount[p]-1] = -1; //set to invalid
    pre.handCount[p]--; //decrement player's hand count
  }
  //check that the discardCard function did not return an error
  if (r != 0) {
    printf("\tError calling discardCard\n");
    return 1;
  }
  #if (PRINT_TEST == 1)
    printf("Actual State after discardCard: \n");
    printState(post);
    printf("\n");
    printf("Expected State after discardCard: \n");
    printState(&pre);
/*    printf("\tHandCount: Expected: %d, Actual: %d\n", pre.handCount[p], post->handCount[p]);
    printf("\tDiscardCount: Expected: %d, Actual: %d\n", pre.discardCount[p], post->discardCount[p]);
    printf("\tPlayedCardCount: Expected: %d, Actual: %d\n", pre.playedCardCount, post->playedCardCount);
    printf("\tPlayed Card: Expected: %d, Actual: %d\n", pre.playedCards[pre.playedCardCount - 1], post->playedCards[post->playedCardCount-1]);
    printf("\tHandPos Value: Expected: %d, Actual: %d\n\n", pre.hand[p][handPos], post->hand[p][handPos]);
    */
  #endif
  //check that the state of the game after running discardCard is the same
  //as the expected state.
  if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
    #if (PRINT_TEST)
      printf("\tTest Failed\n");
    #endif
    return 1;
  } else {
    #if (PRINT_TEST)
      printf("\tTest Passed\n");
    #endif
  }

  return 0;
}

int main() {
  printf("\nTESTING FUNCTION: discardCard:\n");

  int p, r, i, handCount, handPos;
  int allPassed = 0;
  int failed = 0; //initialized to false

  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
                village, baron, great_hall};
  struct gameState G;

  printf("\tTEST: discard a card without trash flag set:\n");
  //check for discarding cards when at varying handCount and handPos
  //check with player 0
  int deckCount = 5;
  int discardCount = 0;
  int maxDiscardCount = 10;
  int result;
  //test discardCard without trash flag set
  p = 0;
  //a precondition is that the player has at least one card in their hand to discard
  for (handCount = 1; handCount < 6; handCount++) {
    for (handPos = 0; handPos < handCount; handPos++) {
      #if (PRINT_TEST)
        printf("\tTesting discard card with handCount: %d and handPos: %d\n", handCount, handPos);
      #endif
      //initialize game with static 5 cards in deck and discard piles
      memset(&G, 23, sizeof(struct gameState));
      r = initializeGame(2, k, 1, &G);
      G.deckCount[p] = deckCount;
      memset(G.deck[p], 0, sizeof(int) * deckCount);
      //set deck to all coppers
      for (i = 0; i < G.deckCount[p]; i++) {
        G.deck[p][i] = copper;
      }
      G.discardCount[p] = discardCount;
      memset(G.discard[p], 0, sizeof(int) * maxDiscardCount);
      //set discard to all silver
      for (i = 0; i < G.discardCount[p]; i++) {
        G.discard[p][i] = silver;
      }
      G.handCount[p] = handCount;
      memset(G.hand[p], 0, sizeof(int) * handCount);
      //set hand to all gold
      for (i = 0; i < G.handCount[p]; i++) {
        G.hand[p][i] = gold;
      }
      //allocate memory for played card pile to hold cards
      G.playedCardCount = 0;
      #if (PRINT_TEST)
        printf("INITIAL STATE: \n");
        printState(&G);
      #endif
      //test discardCard without trash flag set
      result = checkDiscardCard(handPos, p, &G, 0);
      if (result != 0) {
        allPassed = 1;
        failed = 1;
      }
    }
  }
  if (failed == 1) {
    printf("\tTest Failed\n");
  }
  //test with trash flag set
  printf("\tTEST: discard a card with trash flag set:\n");
  failed = 0; //reset failed signal
  p = 0;
  //a precondition is that the player has at least one card in their hand to discard
  for (handCount = 1; handCount < 6; handCount++) {
    for (handPos = 0; handPos < handCount; handPos++) {
      #if (PRINT_TEST)
        printf("\tTesting discard card (trash set) with handCount: %d and handPos: %d\n", handCount, handPos);
      #endif
      //initialize game with static 5 cards in deck and discard piles
      memset(&G, 23, sizeof(struct gameState));
      r = initializeGame(2, k, 1, &G);
      G.deckCount[p] = deckCount;
      memset(G.deck[p], 0, sizeof(int) * deckCount);
      //set deck to all coppers
      for (i = 0; i < G.deckCount[p]; i++) {
        G.deck[p][i] = copper;
      }
      G.discardCount[p] = discardCount;
      memset(G.discard[p], 0, sizeof(int) * discardCount);
      //set discard to all silvers
      for (i = 0; i < G.discardCount[p]; i++) {
        G.discard[p][i] = silver;
      }
      G.handCount[p] = handCount;
      memset(G.hand[p], 0, sizeof(int) * handCount);
      //set hand to all gold
      for (i = 0; i < G.handCount[p]; i++) {
        G.hand[p][i] = copper;
      }
      #if (PRINT_TEST)
        printf("INITIAL STATE: \n");
        printState(&G);
      #endif
      //test discardCard with trash flag set
      result = checkDiscardCard(handPos, p, &G, 1);
      if (result != 0) {
        allPassed = 1;
        failed = 1;
      }
    }
  }

  if (failed == 1) {
    printf("\tTest Failed\n");
  }

  if (allPassed == 1) {
    printf("\tFINAL: TESTS DID NOT ALL PASS\n");
  } else {
    printf("\tFINAL: ALL TESTS PASSED\n");
  }

  return 0;
}
