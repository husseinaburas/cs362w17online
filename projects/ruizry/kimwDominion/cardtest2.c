/*
cardtest2.c Testing Village Card
*/
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

void assertTrue(int predicate, char *message)
{
	printf("%s: ", message);
	if(predicate)
		printf("PASSED\n");
	else
		printf("FAILED\n");
}

int main (int argc, char** argv) {
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           council_room, tribute, smithy};


  printf ("Starting Village Tests...\n\n");

/* TEST 1 Starts HERE ******************/
  initializeGame(2, k, 3, &G);

  int money = 0;
  int villagePos[5] = {-1, -1, -1, -1, -1};
  int i=0, j=0;
  int deckVillages = 0;
  int handVillages = 0;
  int oldHandCount = 0;
  int handNotSet = 0;
  int lastDeckCard = 0;

  while(handNotSet == 0) {
    money = 0;
    villagePos[0] = -1;
    villagePos[1] = -1;
    villagePos[2] = -1;
    villagePos[3] = -1;
    villagePos[4] = -1;
    handVillages = 0;


    for (i = 0; i < numHandCards(&G); i++) {
      if (handCard(i, &G) == copper) {
        playCard(i, -1, -1, -1, &G);
        money++;
      }
      else if (handCard(i, &G) == silver) {
        playCard(i, -1, -1, -1, &G);
        money += 2;
      }
      else if (handCard(i, &G) == gold) {
        playCard(i, -1, -1, -1, &G);
        money += 3;
      }
      else if (handCard(i, &G) == village) {
        villagePos[handVillages] = i;
        handVillages++;
      }

    }

    if (handVillages > 0) {

        if (handVillages == 1) {
            oldHandCount = G.handCount[whoseTurn(&G)];

            /* Add 10 cards to deck */
            lastDeckCard = G.deckCount[whoseTurn(&G)];
            G.deckCount[whoseTurn(&G)] = lastDeckCard + 10;
            for(i = 0; i < 10; i++) {
              G.deck[whoseTurn(&G)][lastDeckCard + i] = copper;
            }

            playCard(villagePos[0], -1, -1, -1, &G);
            assertTrue(oldHandCount == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 1 village played in a turn");
            assertTrue(G.numActions == 2, "Testing if remaining action count is correct after 1 village played in a turn");
            handNotSet = 1;
        }

    }

    if ((money >= 4) && (deckVillages < 4)) {
        buyCard(village, &G);
        deckVillages++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 1 ENDS HERE ******************/

/* TEST 2 Starts HERE ******************/

  initializeGame(2, k, 5, &G);

  i=0;
  deckVillages = 0;
  oldHandCount = 0;
  handNotSet = 0;

  while(handNotSet == 0) {
    money = 0;
    villagePos[0] = -1;
    villagePos[1] = -1;
    villagePos[2] = -1;
    villagePos[3] = -1;
    villagePos[4] = -1;
    handVillages = 0;

    for (i = 0; i < numHandCards(&G); i++) {
      if (handCard(i, &G) == copper) {
        playCard(i, -1, -1, -1, &G);
        money++;
      }
      else if (handCard(i, &G) == silver) {
        playCard(i, -1, -1, -1, &G);
        money += 2;
      }
      else if (handCard(i, &G) == gold) {
        playCard(i, -1, -1, -1, &G);
        money += 3;
      }
      else if (handCard(i, &G) == village) {
        villagePos[handVillages] = i;
        handVillages++;
      }

    }

    if (handVillages > 0) {

        if (handVillages == 2) {
            oldHandCount = G.handCount[whoseTurn(&G)];
            G.numActions = 2;

            /* Add 10 cards to deck */
            lastDeckCard = G.deckCount[whoseTurn(&G)];
            G.deckCount[whoseTurn(&G)] = lastDeckCard + 10;
            for(i = 0; i < 10; i++) {
              G.deck[whoseTurn(&G)][lastDeckCard + i] = copper;
            }

            playCard(villagePos[0], -1, -1, -1, &G);
            playCard(villagePos[1], -1, -1, -1, &G);

            assertTrue(oldHandCount == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 2 villages played in the same turn");
            assertTrue(G.numActions == 4, "Testing if remaining action count is correct after 2 villages played in the same turn");
            handNotSet = 1;
        }
    }

    if ((money >= 4) && (deckVillages < 4)) {
        buyCard(village, &G);
        deckVillages++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 2 ENDS HERE */

/* TEST 3 Starts HERE ******************/

  initializeGame(2, k, 5, &G);

  i=0;
  deckVillages = 0;
  oldHandCount = 0;
  handNotSet = 0;

  while(handNotSet == 0) {
    money = 0;
    villagePos[0] = -1;
    villagePos[1] = -1;
    villagePos[2] = -1;
    villagePos[3] = -1;
    villagePos[4] = -1;
    handVillages = 0;

    for (i = 0; i < numHandCards(&G); i++) {
      if (handCard(i, &G) == copper) {
        playCard(i, -1, -1, -1, &G);
        money++;
      }
      else if (handCard(i, &G) == silver) {
        playCard(i, -1, -1, -1, &G);
        money += 2;
      }
      else if (handCard(i, &G) == gold) {
        playCard(i, -1, -1, -1, &G);
        money += 3;
      }
      else if (handCard(i, &G) == village) {
        villagePos[handVillages] = i;
        handVillages++;
      }

    }

    if (handVillages > 0) {

        if (handVillages > 2) {
            oldHandCount = G.handCount[whoseTurn(&G)];
            G.numActions = 3;

            /* Add 10 cards to deck */
            lastDeckCard = G.deckCount[whoseTurn(&G)];
            G.deckCount[whoseTurn(&G)] = lastDeckCard + 10;
            for(i = 0; i < 10; i++) {
              G.deck[whoseTurn(&G)][lastDeckCard + i] = copper;
            }

            playCard(villagePos[0], -1, -1, -1, &G);
            playCard(villagePos[1], -1, -1, -1, &G);
            playCard(villagePos[2], -1, -1, -1, &G);

            assertTrue(oldHandCount == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 3 villages played in the same turn");
            assertTrue(G.numActions == 6, "Testing if remaining action count is correct after 3 villages played in the same turn");
            handNotSet = 1;
        }
    }

    if ((money >= 4) && (deckVillages < 4)) {
        buyCard(village, &G);
        deckVillages++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 3 ENDS HERE */

/* TEST 4 Starts HERE ******************/

  printf ("\nTesting for village Card Being Played on Consecutive Turns\n\n");

  initializeGame(4, k, 5, &G);

  i=0;
  oldHandCount = 0;

  for(i = 0; i < 4; i++) {
    G.hand[i][0] = village;
    oldHandCount = G.handCount[whoseTurn(&G)];

    /* Add 10 cards to deck */
    lastDeckCard = G.deckCount[whoseTurn(&G)];
    G.deckCount[whoseTurn(&G)] = lastDeckCard + 10;
    for(j = 0; j < 10; j++) {
        G.deck[whoseTurn(&G)][lastDeckCard + j] = copper;
    }

    playCard(0, -1, -1, -1, &G);
    printf("Player %d check: ", i);
    assertTrue(oldHandCount == G.handCount[whoseTurn(&G)], "Testing if current player hand count is correct after 1 village played");
    assertTrue(G.numActions == 2, "Testing if remaining action count is correct after village played");
    endTurn(&G);
  }

/* TEST 4 ENDS HERE */

  printf ("\nVillage Tests Complete\n\n");

  return 0;

}
