/*
 * Name: Grace Thompson
 * CS 362 W17 Assignment 3
 *
 * Testing function: gainCard
 *
 * makefile:
 *  unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
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

 /* gainCard testing check:
 *
 *  if the supply pile is empty, an error should be returned.
 *  if the card is to be added to the player's hand,
      the player hand should have one extra card
 *  if the card is to be added to the player's discard pile,
      the player's discard pile should have one extra card
 *  if the card is to be added to the player's deck,
      the player's deck should have one extra card
 *  the card gained should be the one specified, not a different card
 *  the supply for the specified card should be decremented by 1
 *  no other supply states should be changed.
 *  no other player states should be changed.
 */

 //int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);

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

int checkGainCard(int supplyPos, struct gameState *post, int toFlag, int p) {
  struct gameState pre;
  //make copy of state before executing gainCard
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  r = gainCard(supplyPos, post, toFlag, p);

  //if no more of that card in the supply pile, should return an error
  if (supplyCount(supplyPos, &pre) < 1) {
    if (assertTrue((r == -1), "empty supply pile") == 1) {
      return 1;
    }else {
      return 0;
    }
  }
  //if card is to be sent to player hand
  if (toFlag == 2) {
    pre.handCount[p]++;
    pre.hand[p][pre.handCount[p]-1] = supplyPos;
    pre.supplyCount[supplyPos]--; //decrement supply count
  } else if (toFlag == 1) { //if card is to be sent to player deck
    pre.deckCount[p]++;
    pre.deck[p][pre.deckCount[p]-1] = supplyPos;
    pre.supplyCount[supplyPos]--;
  } else { //if card is to be sent to player discard
    pre.discardCount[p]++;
    pre.discard[p][pre.discardCount[p]-1] = supplyPos;
    pre.supplyCount[supplyPos]--;
  }

  //check that the gainCard function did not return an error
  if (r != 0) {
    printf("\tError calling gainCard\n");
    return 1;
  }
  #if (PRINT_TEST == 1)
    printf("\tHand Count: Expected: %d, Actual: %d\n", pre.handCount[p], post->handCount[p]);
    printf("\tDeck Count: Expected: %d, Actual: %d\n", pre.deckCount[p], post->deckCount[p]);
    printf("\tDiscard Count: Expected: %d, Actual: %d\n", pre.discardCount[p], post->discardCount[p]);
    if (toFlag == 2) {
      printf("\tCard Gained: Expected: %d, Actual: %d\n", supplyPos, post->hand[p][post->handCount[p]-1]);
    }
    else if (toFlag == 1) {
      printf("\tCard Gained: Expected: %d, Actual: %d\n", supplyPos, post->deck[p][post->deckCount[p]-1]);
    } else {
      printf("\tCard Gained: Expected: %d, Actual: %d\n\n", supplyPos, post->discard[p][post->discardCount[p]-1]);
    }
  #endif

  //check the state of post and pre, they should be the same if pass
  if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
    #if (PRINT_TEST)
      printf("\tTest Failed\n");
    #endif
    return 1;
  }
  #if (PRINT_TEST)
    printf("\tTest Passed\n");
  #endif
  return 0;
}

int main() {
  printf("\nTESTING FUNCTION: gainCard:\n");

  int i, j, p, r, s, deckCount, discardCount, handCount;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int t[3] = {copper, silver, gold};
  int v[4] = {estate, duchy, province, curse};
  struct gameState G;
  int allPassed = 0;
  //test gain card and add to player's discard (0)
  //test gain card and add to player's deck (1)
  //test gain card and add to player's hand (2)
  deckCount = 5;
  discardCount = 5;
  handCount = 5;
  //test gaining a kingdom card
  printf("\tTEST: Gain a Kingdom Card\n");
  //test for two players
  for (p = 0; p < 2; p++) {
    //this loop sets the toFlag - discard, deck, or hand
    for (i = 0; i < 3; i++) {
      //this loop sets the kingdom card to be gained by the player
      for (j = 0; j < 10; j++) {
        //this loop determines how many of the card is left in the supply
        for (s = 0; s < 5; s++) {
          memset(&G, 23, sizeof(struct gameState));
          r = initializeGame(2, k, 1, &G);
          #if (PRINT_TEST)
            printf("\tTesting gain card: %d, supply: %d, sent to: %d\n", k[j], s, i);
          #endif
          //set deckCount, discardCount, and handCount for player
          G.deckCount[p] = deckCount;
        	memset(G.deck[p], 0, sizeof(int) * deckCount);
        	G.discardCount[p] = discardCount;
          memset(G.discard[p], 0, sizeof(int) * discardCount);
      	  G.handCount[p] = handCount;
      	  memset(G.hand[p], 0, sizeof(int) * handCount);
          G.supplyCount[k[j]] = s;
          //k[j] = kingdom card to be gained
          //&G = initialized gameState
          //i = toFlag (discard, deck, hand)
          //p = currentPlayer
          if (checkGainCard(k[j], &G, i, p) != 0) {
            printf("\tTesting gain card: %d, supply %d, sent to: %d FAILED\n", k[j], s, i);
            allPassed = 1; //not all tests passed
          }
        }
      }
    }
  }
  //test gaining a treasure card
  printf("\tTEST: Gain a Treasure Card\n");
  for (p = 0; p < 2; p++) {
    //this loop sets the toFlag - discard, deck, or hand
    for (i = 0; i < 3; i++) {
      //this loop sets the kingdom card to be gained by the player
      for (j = 0; j < 3; j++) {
        //this loop determines how many of the card is left in the supply
        for (s = 0; s < 5; s++) {
          memset(&G, 23, sizeof(struct gameState));
          r = initializeGame(2, k, 1, &G);
          #if (PRINT_TEST)
            printf("\tTesting gain card: %d, supply: %d, sent to: %d\n", t[j], s, i);
          #endif
          //set deckCount, discardCount, and handCount for player
          G.deckCount[p] = deckCount;
        	memset(G.deck[p], 0, sizeof(int) * deckCount);
        	G.discardCount[p] = discardCount;
          memset(G.discard[p], 0, sizeof(int) * discardCount);
      	  G.handCount[p] = handCount;
      	  memset(G.hand[p], 0, sizeof(int) * handCount);
          G.supplyCount[t[j]] = s;
          //k[j] = kingdom card to be gained
          //&G = initialized gameState
          //i = toFlag (discard, deck, hand)
          //p = currentPlayer
          if (checkGainCard(t[j], &G, i, p) != 0) {
            printf("\tTesting gain card: %d, supply: %d, sent to: %d FAILED\n", t[j], s, i);
            allPassed = 1; //not all tests passed
          }
        }
      }
    }
  }
  //test gaining a Victory or Curse card
  printf("\tTEST: Gain a Victory or Curse card\n");
  for (p = 0; p < 2; p++) {
    //this loop sets the toFlag - discard, deck, or hand
    for (i = 0; i < 3; i++) {
      //this loop sets the kingdom card to be gained by the player
      for (j = 0; j < 4; j++) {
        //this loop determines how many of the card is left in the supply
        for (s = 0; s < 5; s++) {
          memset(&G, 23, sizeof(struct gameState));
          r = initializeGame(2, k, 1, &G);
          #if (PRINT_TEST)
            printf("Testing gain card: %d, supply: %d, sent to: %d\n", v[j], s, i);
          #endif
          //set deckCount, discardCount, and handCount for player
          G.deckCount[p] = deckCount;
        	memset(G.deck[p], 0, sizeof(int) * deckCount);
        	G.discardCount[p] = discardCount;
          memset(G.discard[p], 0, sizeof(int) * discardCount);
      	  G.handCount[p] = handCount;
      	  memset(G.hand[p], 0, sizeof(int) * handCount);
          G.supplyCount[v[j]] = s;
          //k[j] = kingdom card to be gained
          //&G = initialized gameState
          //i = toFlag (discard, deck, hand)
          //p = currentPlayer
          if (checkGainCard(v[j], &G, i, p) != 0) {
            printf("Testing gain card: %d, supply: %d, sent to: %d FAILED\n", v[j], s, i);
            allPassed = 1; //not all tests passed
          }
        }
      }
    }
  }

  if (allPassed == 0) {
    printf("\tFINAL: ALL TESTS PASSED\n");
  } else {
    printf("\tFINAL: TESTS DID NOT ALL PASS\n");
  }

  return 0;
}
