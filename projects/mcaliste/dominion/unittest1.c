// test for supplyCount()
#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "rngs.c"
#include <stdlib.h>
#include <math.h>
#include "assertresult.h"

int main() {
  struct gameState state;
  int seed = 667;
  int numPlayers = 2;
  int kingdom[10] = {adventurer, council_room, feast, gardens, mine, remodel,
    smithy, village, baron, great_hall};

  initializeGame(numPlayers, kingdom, seed, &state);

  // test initial card numbers, for two player game:
  // 10 of each kingdom card, 8 of each victory card
  // great hall and gardens are special victory kingdom cards:
  // 8 of each for 2 player game, and 12 of each for 3+ players
  // 30 gold treasure cards, 40 silver treasure cards
  // 60 copper treasure cards, where each player gets 7 to start
  // any cards not in play are set to -1

  printf("Unit testing supplyCount(), initial state:\n");
  // sum of all cards available in this implementation of the game is 27
  //for (int i = 0; i < 26; i++) {
    //printf("Card %d count: %d \n", i+1, supplyCount(i, &state));
  //}

  for (int j = 0; j < 27; j++) {
    if (numPlayers == 2) {
      // test number of victory cards for 2 players
      if (j == estate || j == duchy || j == province) {
        printf("Unit testing supplyCount(), 2p victory cards:\n");
         assertResult(supplyCount(j, &state) == 8);
      }
      // test number of curse cards for 2 players
      if (j == curse) {
        printf("Unit testing supplyCount(), 2p curse cards:\n");
        assertResult(supplyCount(j, &state) == 10);
      }
    }
      // 3 or more players
      // test number of curse cards for 3 players
    else if (numPlayers == 3) {
      if (j == curse) {
        printf("Unit testing supplyCount(), 3p curse cards:\n");
        assertResult(supplyCount(j, &state) == 20);
      }
    }
    // test number of curse cards for more than 3 players
    else {
      if (j == curse) {
        printf("Unit testing supplyCount(), 3p+ curse cards:\n");
        assertResult(supplyCount(j, &state) == 30);
      }
    // test number of victory cards for 3 or more players
      if (j == estate || j == duchy || j == province) {
        printf("Unit testing supplyCount(), 3p+ victory cards:\n");
        assertResult(supplyCount(j, &state) == 12);
      }
    }
    // test number of treasure cards for any number of players
    // 60 copper treasure cards to start, minus 7 for each player deck
    if (j == copper) {
      printf("Unit testing supplyCount(), copper treasure cards:\n");
      assertResult(supplyCount(j, &state) == (60 - (7 * numPlayers)));
    }
    // 40 silver treasure cards to start
    else if (j == silver) {
      printf("Unit testing supplyCount(), silver treasure cards:\n");
      assertResult(supplyCount(j, &state) == 40);
    }
    // 30 gold treasure cards to start
    else if (j == gold) {
      printf("Unit testing supplyCount(), gold treasure cards:\n");
      assertResult(supplyCount(j, &state) == 30);
    }
      // all remaining cards are kingdom cards
    else if (j > 6) {
      for (int k = 0; k < 10; k++) {
        // check that this supply card exists in the drawn kingdom cards
        if (kingdom[k] == j) {
          // gardens and great hall are special kingdom victory cards
          if ((j == gardens) || (j == great_hall)) {
            printf("Unit testing supplyCount(), kingdom victory cards:\n");
            assertResult(supplyCount(j, &state) == 8);
          }
          else {
            printf("Unit testing supplyCount(), kingdom cards:\n");
            assertResult(supplyCount(j, &state) == 10);
          }
          break;
        }
        //kingdom card is not in drawn supply
        // there's not any other way to know whether the card is unused
        else if (kingdom[k] != j && state.supplyCount[j] == -1) {
          printf("Unit testing supplyCount(), unused kingdom cards:\n");
          assertResult(supplyCount(j, &state) == -1);
          break;
        }
      }
    }
  }

  /*
  printf("Unit testing supplyCount() for adventurer:\n");
  assertResult(supplyCount(adventurer, &state) == 10);
  printf("Unit testing supplyCount() for council room:\n");
  assertResult(supplyCount(council_room, &state) == 10);
  printf("Unit testing supplyCount() for feast:\n");
  assertResult(supplyCount(feast, &state) == 10);
  printf("Unit testing supplyCount() for gardens:\n");
  assertResult(supplyCount(gardens, &state) == 8);
  printf("Unit testing supplyCount() for mine:\n");
  assertResult(supplyCount(mine, &state) == 10);
  printf("Unit testing supplyCount() for remodel:\n");
  assertResult(supplyCount(remodel, &state) == 10);
  printf("Unit testing supplyCount() for smithy:\n");
  assertResult(supplyCount(smithy, &state) == 10);
  printf("Unit testing supplyCount() for village:\n");
  assertResult(supplyCount(village, &state) == 10);
  printf("Unit testing supplyCount() for baron:\n");
  assertResult(supplyCount(baron, &state) == 10);
  printf("Unit testing supplyCount() for great hall:\n");
  assertResult(supplyCount(great_hall, &state) == 8);
  */
  return 0;
}
