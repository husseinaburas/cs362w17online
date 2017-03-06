/*
cardtest1.c
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

//  printf ("Starting game.\n");

  printf ("Starting Smithy Tests...\n\n");

/* TEST 1 Starts HERE ******************/
  initializeGame(2, k, 3, &G);

  int money = 0;
  int smithyPos[5] = {-1, -1, -1, -1, -1};
  int i=0, j=0;
  int deckSmithies = 0;
  int handSmithies = 0;
//  int fullDeckCount = 0;
  int oldHandCount = 0;
  int handNotSet = 0;
  int lastDeckCard = 0;

  while(handNotSet == 0) {
    money = 0;
    smithyPos[0] = -1;
    smithyPos[1] = -1;
    smithyPos[2] = -1;
    smithyPos[3] = -1;
    smithyPos[4] = -1;
    handSmithies = 0;

//    fullDeckCount = G.handCount[whoseTurn(&G)] + G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)];

    //printf("Full deck count: %d\n", fullDeckCount);

    //printf ("Player %d cards in hand: ", whoseTurn(&G));

    for (i = 0; i < numHandCards(&G); i++) {
      //printf("card%d, ", handCard(i, &G));
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
      else if (handCard(i, &G) == smithy) {
        smithyPos[handSmithies] = i;
        handSmithies++;
      }

    }

/*
    printf("\nGold in Hand: %d\n", money);
    printf ("Player %d has %d coins credited for purchasing\n", whoseTurn(&G), G.coins);
    printf ("Player %d has %d actions left\n", whoseTurn(&G), G.numActions);
    printf("Number of Smithies in Hand: %d\n", handSmithies);
*/

    if (handSmithies > 0) {
        /*for(j = 0; j < handSmithies; j++) {
            printf("Smithy in position %d \n", smithyPos[j]);
            printf("Card in position %d: %d\n", smithyPos[j], handCard(smithyPos[j], &G));
        }*/

        if (handSmithies == 1) {
            oldHandCount = G.handCount[whoseTurn(&G)];

            /* Add 10 cards to deck */
            lastDeckCard = G.deckCount[whoseTurn(&G)];
            G.deckCount[whoseTurn(&G)] = lastDeckCard + 10;
            for(i = 0; i < 10; i++) {
              G.deck[whoseTurn(&G)][lastDeckCard + i] = copper;
            }

            //printf("Playing Smithy Card:\n");
            playCard(smithyPos[0], -1, -1, -1, &G);
            /*
            printf("Player %d cards in hand: ", whoseTurn(&G));
            for (i = 0; i < numHandCards(&G); i++) {
                printf("card%d, ", handCard(i, &G));
            }
            printf("\n");
            printf ("Player %d has %d actions left\n", whoseTurn(&G), G.numActions);
            */

            assertTrue((oldHandCount + 2) == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 1 smithy played in a turn");
            handNotSet = 1;
        }

/*
        if (handSmithies == 2) {
            oldHandCount = G.handCount[whoseTurn(&G)];
            G.numActions = 2;
            //printf ("Player %d has %d actions left\n", whoseTurn(&G), G.numActions);
            //printf("Playing 2 Smithy Cards:\n");
            playCard(smithyPos[0], -1, -1, -1, &G);
            playCard(smithyPos[1], -1, -1, -1, &G);

            printf("Player %d cards in hand: ", whoseTurn(&G));
            for (i = 0; i < numHandCards(&G); i++) {
                printf("card%d, ", handCard(i, &G));
            }
            printf("\n");
            printf ("Player %d has %d actions left\n", whoseTurn(&G), G.numActions);

            assertTrue((oldHandCount + 4) == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 2 smithies played in the same turn");
            handNotSet = 1;
        }

        if (handSmithies >= 2) {
            oldHandCount = G.handCount[whoseTurn(&G)];
            G.numActions = 3;
            //printf ("Player %d has %d actions left\n", whoseTurn(&G), G.numActions);
            //printf("Playing 3 Smithy Cards:\n");
            playCard(smithyPos[0], -1, -1, -1, &G);
            playCard(smithyPos[1], -1, -1, -1, &G);
            playCard(smithyPos[2], -1, -1, -1, &G);

            printf("Player %d cards in hand: ", whoseTurn(&G));
            for (i = 0; i < numHandCards(&G); i++) {
                printf("card%d, ", handCard(i, &G));
            }
            printf("\n");
            printf ("Player %d has %d actions left\n", whoseTurn(&G), G.numActions);

            assertTrue((oldHandCount + 6) == G.handCount[whoseTurn(&G)], "Test hand count is correct after 3 smithies played in the same turn");
            handNotSet = 1;
        }
*/
    }

    if ((money >= 4) && (deckSmithies < 4)) {
        //printf("Bought smithy\n");
        buyCard(smithy, &G);
        deckSmithies++;
    }

    //printf("End turn and skip next player\n\n");
    endTurn(&G);
    endTurn(&G);
  }

/*
  printf ("Test game finished.\n");
  printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, &G), scoreFor(1, &G));
*/

/* TEST 1 ENDS HERE ******************/

/* TEST 2 Starts HERE ******************/

  initializeGame(2, k, 5, &G);

  i=0;
  deckSmithies = 0;
  oldHandCount = 0;
  handNotSet = 0;

  while(handNotSet == 0) {
    money = 0;
    smithyPos[0] = -1;
    smithyPos[1] = -1;
    smithyPos[2] = -1;
    smithyPos[3] = -1;
    smithyPos[4] = -1;
    handSmithies = 0;

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
      else if (handCard(i, &G) == smithy) {
        smithyPos[handSmithies] = i;
        handSmithies++;
      }

    }

    if (handSmithies > 0) {

        if (handSmithies == 2) {
            oldHandCount = G.handCount[whoseTurn(&G)];
            G.numActions = 2;

            /* Add 10 cards to deck */
            lastDeckCard = G.deckCount[whoseTurn(&G)];
            G.deckCount[whoseTurn(&G)] = lastDeckCard + 10;
            for(i = 0; i < 10; i++) {
              G.deck[whoseTurn(&G)][lastDeckCard + i] = copper;
            }

            playCard(smithyPos[0], -1, -1, -1, &G);
            playCard(smithyPos[1], -1, -1, -1, &G);

            assertTrue((oldHandCount + 4) == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 2 smithies played in the same turn");
            handNotSet = 1;
        }
    }

    if ((money >= 4) && (deckSmithies < 4)) {
        buyCard(smithy, &G);
        deckSmithies++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 2 ENDS HERE */

/* TEST 3 Starts HERE ******************/

  initializeGame(2, k, 5, &G);

  i=0;
  deckSmithies = 0;
  oldHandCount = 0;
  handNotSet = 0;

  while(handNotSet == 0) {
    money = 0;
    smithyPos[0] = -1;
    smithyPos[1] = -1;
    smithyPos[2] = -1;
    smithyPos[3] = -1;
    smithyPos[4] = -1;
    handSmithies = 0;

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
      else if (handCard(i, &G) == smithy) {
        smithyPos[handSmithies] = i;
        handSmithies++;
      }

    }

    if (handSmithies > 0) {

        if (handSmithies > 2) {
            oldHandCount = G.handCount[whoseTurn(&G)];
            G.numActions = 3;

            /* Add 10 cards to deck */
            lastDeckCard = G.deckCount[whoseTurn(&G)];
            G.deckCount[whoseTurn(&G)] = lastDeckCard + 10;
            for(i = 0; i < 10; i++) {
              G.deck[whoseTurn(&G)][lastDeckCard + i] = copper;
            }

            playCard(smithyPos[0], -1, -1, -1, &G);
            playCard(smithyPos[1], -1, -1, -1, &G);
            playCard(smithyPos[2], -1, -1, -1, &G);

            assertTrue((oldHandCount + 6) == G.handCount[whoseTurn(&G)], "Testing if hand count is correct after 3 smithies played in the same turn");
            handNotSet = 1;
        }
    }

    if ((money >= 4) && (deckSmithies < 4)) {
        buyCard(smithy, &G);
        deckSmithies++;
    }

    endTurn(&G);
    endTurn(&G);
  }

/* TEST 3 ENDS HERE */

/* TEST 4 Starts HERE ******************/

  printf ("\nTesting for Smithy Card Being Played on Consecutive Turns\n\n");

  initializeGame(4, k, 5, &G);

  i=0;
  oldHandCount = 0;


  for(i = 0; i < 4; i++) {
    G.hand[i][0] = smithy;
    oldHandCount = G.handCount[whoseTurn(&G)];

    /* Add 10 cards to deck */
    lastDeckCard = G.deckCount[whoseTurn(&G)];
    G.deckCount[whoseTurn(&G)] = lastDeckCard + 10;
    for(j = 0; j < 10; j++) {
        G.deck[whoseTurn(&G)][lastDeckCard + j] = copper;
    }

    playCard(0, -1, -1, -1, &G);
    printf("Player %d check: ", i);
    assertTrue((oldHandCount + 2) == G.handCount[whoseTurn(&G)], "Testing if current player hand count is correct after 1 smithy played");
    endTurn(&G);
  }

/* TEST 4 ENDS HERE */

  printf ("\nSmithy Tests Complete\n\n");

  return 0;

}
