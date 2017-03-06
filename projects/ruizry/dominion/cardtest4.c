/*
cardtest4.c Testing Adventurer Card
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


  printf ("Starting Adventurer Tests...\n\n");

/* TEST 1 Starts HERE ******************/
  initializeGame(2, k, 3, &G);

  int money = 0;
  int adventurerPos[5] = {-1, -1, -1, -1, -1};
  int i=0;
  int deckAdventurers = 0;
  int handAdventurers = 0;
  int handNotSet = 0;

  while(handNotSet == 0) {
    money = 6;
    G.coins = 6;
    adventurerPos[0] = -1;
    adventurerPos[1] = -1;
    adventurerPos[2] = -1;
    adventurerPos[3] = -1;
    adventurerPos[4] = -1;
    handAdventurers = 0;


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
      else if (handCard(i, &G) == adventurer) {
        adventurerPos[handAdventurers] = i;
        handAdventurers++;
      }

    }

    if (handAdventurers > 0) {

        if (handAdventurers == 1) {
            playCard(adventurerPos[0], -1, -1, -1, &G);
            assertTrue(G.coins >= 2, "Testing if current player has enough treasure cards after 1 adventurer card played");
            handNotSet = 1;
        }

    }

    if ((money >= 6) && (deckAdventurers < 4)) {
        buyCard(adventurer, &G);
        deckAdventurers++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 1 ENDS HERE ******************/

/* TEST 2 Starts HERE ******************/

  initializeGame(2, k, 5, &G);

  i=0;
  deckAdventurers = 0;
  handNotSet = 0;

  while(handNotSet == 0) {
    money = 6;
    G.coins = 6;
    adventurerPos[0] = -1;
    adventurerPos[1] = -1;
    adventurerPos[2] = -1;
    adventurerPos[3] = -1;
    adventurerPos[4] = -1;
    handAdventurers = 0;

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
      else if (handCard(i, &G) == adventurer) {
        adventurerPos[handAdventurers] = i;
        handAdventurers++;
      }

    }

    if (handAdventurers > 0) {

        if (handAdventurers == 2) {
            G.numActions = 2;

            playCard(adventurerPos[0], -1, -1, -1, &G);
            playCard(adventurerPos[1], -1, -1, -1, &G);

            assertTrue(G.coins >= 4, "Testing if current player has enough treasure cards after 3 adventurer cards played");
            handNotSet = 1;
        }
    }

    if ((money >= 6) && (deckAdventurers < 4)) {
        buyCard(adventurer, &G);
        deckAdventurers++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 2 ENDS HERE */

/* TEST 3 Starts HERE ******************/

  initializeGame(2, k, 5, &G);

  i=0;
  deckAdventurers = 0;
  handNotSet = 0;

  while(handNotSet == 0) {
    money = 6;
    G.coins = 6;
    adventurerPos[0] = -1;
    adventurerPos[1] = -1;
    adventurerPos[2] = -1;
    adventurerPos[3] = -1;
    adventurerPos[4] = -1;
    handAdventurers = 0;

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
      else if (handCard(i, &G) == adventurer) {
        adventurerPos[handAdventurers] = i;
        handAdventurers++;
      }

    }

    if (handAdventurers > 0) {

        if (handAdventurers > 2) {
            G.numActions = 3;

            playCard(adventurerPos[0], -1, -1, -1, &G);
            playCard(adventurerPos[1], -1, -1, -1, &G);
            playCard(adventurerPos[2], -1, -1, -1, &G);

            assertTrue(G.coins >= 6, "Testing if current player has enough treasure cards after 3 adventurer cards played");
            handNotSet = 1;
        }
    }

    if ((money >= 6) && (deckAdventurers < 4)) {
        buyCard(adventurer, &G);
        deckAdventurers++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 3 ENDS HERE */

/* TEST 4 Starts HERE ******************/

  printf ("\nTesting for adventurer Card Being Played on Consecutive Turns\n\n");

  initializeGame(4, k, 5, &G);

  i=0;

  for(i = 0; i < 4; i++) {
    G.hand[i][0] = adventurer;
    playCard(0, -1, -1, -1, &G);
    printf("Player %d check: ", i);
    assertTrue(G.coins >= 2, "Testing if current player has enough treasure cards after adventurer played");
    endTurn(&G);
  }

/* TEST 4 ENDS HERE */

  printf ("\nAdventurer Tests Complete\n\n");

  return 0;

}
