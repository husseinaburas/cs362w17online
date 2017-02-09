/*
cardtest3.c Testing Council Room Card
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


  printf ("Starting Coucil Room Tests...\n\n");

/* TEST 1 Starts HERE ******************/
  initializeGame(2, k, 3, &G);

  int money = 0;
  int council_roomPos[5] = {-1, -1, -1, -1, -1};
  int i=0;
  int deckCouncils = 0;
  int handCouncils = 0;
  int oldHandCount = 0;
  int handNotSet = 0;

  while(handNotSet == 0) {
    money = 5;
    G.coins = 5;
    council_roomPos[0] = -1;
    council_roomPos[1] = -1;
    council_roomPos[2] = -1;
    council_roomPos[3] = -1;
    council_roomPos[4] = -1;
    handCouncils = 0;


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
      else if (handCard(i, &G) == council_room) {
        council_roomPos[handCouncils] = i;
        handCouncils++;
      }

    }

    if (handCouncils > 0) {

        if (handCouncils == 1) {
            oldHandCount = G.handCount[whoseTurn(&G)];
            playCard(council_roomPos[0], -1, -1, -1, &G);
            assertTrue((oldHandCount + 3) == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 1 council_room played in the same turn");
            handNotSet = 1;
        }

    }

    if ((money >= 5) && (deckCouncils < 4)) {
        buyCard(council_room, &G);
        deckCouncils++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 1 ENDS HERE ******************/

/* TEST 2 Starts HERE ******************/

  initializeGame(2, k, 5, &G);

  i=0;
  deckCouncils = 0;
  oldHandCount = 0;
  handNotSet = 0;

  while(handNotSet == 0) {
    money = 5;
    G.coins = 5;
    council_roomPos[0] = -1;
    council_roomPos[1] = -1;
    council_roomPos[2] = -1;
    council_roomPos[3] = -1;
    council_roomPos[4] = -1;
    handCouncils = 0;

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
      else if (handCard(i, &G) == council_room) {
        council_roomPos[handCouncils] = i;
        handCouncils++;
      }

    }

    if (handCouncils > 0) {

        if (handCouncils == 2) {
            oldHandCount = G.handCount[whoseTurn(&G)];
            G.numActions = 2;

            playCard(council_roomPos[0], -1, -1, -1, &G);
            playCard(council_roomPos[1], -1, -1, -1, &G);

            assertTrue((oldHandCount + 6) == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 2 Councils played in the same turn");
            handNotSet = 1;
        }
    }

    if ((money >= 4) && (deckCouncils < 4)) {
        buyCard(council_room, &G);
        deckCouncils++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 2 ENDS HERE */

/* TEST 3 Starts HERE ******************/

  initializeGame(2, k, 5, &G);

  i=0;
  deckCouncils = 0;
  oldHandCount = 0;
  handNotSet = 0;

  while(handNotSet == 0) {
    money = 5;
    G.coins = 5;
    council_roomPos[0] = -1;
    council_roomPos[1] = -1;
    council_roomPos[2] = -1;
    council_roomPos[3] = -1;
    council_roomPos[4] = -1;
    handCouncils = 0;

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
      else if (handCard(i, &G) == council_room) {
        council_roomPos[handCouncils] = i;
        handCouncils++;
      }

    }

    if (handCouncils > 0) {

        if (handCouncils > 2) {
            oldHandCount = G.handCount[whoseTurn(&G)];
            G.numActions = 3;

            playCard(council_roomPos[0], -1, -1, -1, &G);
            playCard(council_roomPos[1], -1, -1, -1, &G);
            playCard(council_roomPos[2], -1, -1, -1, &G);

            assertTrue((oldHandCount + 9) == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 3 Councils played in the same turn");
            handNotSet = 1;
        }
    }

    if ((money >= 4) && (deckCouncils < 4)) {
        buyCard(council_room, &G);
        deckCouncils++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 3 ENDS HERE */

/* TEST 4 Starts HERE ******************/

  printf ("\nTesting for council_room Card Being Played on Consecutive Turns\n\n");

  initializeGame(4, k, 5, &G);

  i=0;
  oldHandCount = 0;

  for(i = 0; i < 4; i++) {
    if (i == 0) {
    G.hand[i][0] = council_room;
    playCard(0, -1, -1, -1, &G);
    printf("Player %d check:\n", i);
    assertTrue(G.handCount[whoseTurn(&G)] == 8, "Testing if current player hand count is correct after 1 council_room played");
    assertTrue(G.numBuys == 2, "Testing if remaining buy count is correct after council_room played");
    endTurn(&G);
    }
    else {
    G.hand[i][0] = council_room;
    playCard(0, -1, -1, -1, &G);
    printf("Player %d check:\n", i);
    printf("Hand count: %d\n", G.handCount[whoseTurn(&G)]);
    assertTrue(G.handCount[whoseTurn(&G)] == (8 + i), "Testing hand count after current and previous player used council_room");
    assertTrue(G.numBuys == 2, "Testing if remaining buy count is correct after council_room played");
    endTurn(&G);
    }
  }

/* TEST 4 ENDS HERE */

  printf ("\nCouncil Room Tests Complete\n\n");

  return 0;

}
