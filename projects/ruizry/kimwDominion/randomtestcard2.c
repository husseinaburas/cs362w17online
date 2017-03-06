/*
randomtestcard2.c - Random tester for Smithy card in dominion program
Author: Ryan Ruiz - ruizry
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

int checkSmithy(int personplayed, int numplayers, int inhand, int indeck, int indiscard, struct gameState *post) {
  int check;

  check = playCard(0, -1, -1, -1, post);


  if (check != 0) {
    printf("Failed: Player %d out of %d, %d smithyCards in hand, %d smithyCards in deck, %d smithyCards in discard\n", personplayed, numplayers, inhand, indeck, indiscard);
  }

  return 0;
}

int main (int argc, char** argv) {

  int i, n, p, totalplayers, advhand, advdeck, advdiscard;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Smithy Card.\n");

  printf ("RANDOM TESTS.\n");

  /*srand(time(NULL)); */
  srand(atoi(argv[1]));

  for (n = 0; n < 20; n++) {
  totalplayers = (rand() % 3) + 2;

  initializeGame(totalplayers, k, atoi(argv[1]), &G);
  /*initializeGame(totalplayers, k, 3, &G); */

    p = rand() % totalplayers;

    advhand = (rand() % 3) + 1;
    if(G.handCount[p] < advhand)
        G.handCount[p] = advhand;
    for(i = 0; i < advhand; i++) {
        G.hand[p][i] = smithy;
    }

    advdeck = rand() % 4;
    if(G.deckCount[p] < advdeck)
        G.deckCount[p] = advdeck;
    for(i = 0; i < advdeck; i++) {
        G.deck[p][i] = smithy;
    }

    advdiscard = rand() % 4;
    if(G.discardCount[p] < advdiscard)
        G.discardCount[p] = advdiscard;
    for(i = 0; i < advdiscard; i++) {
        G.discard[p][i] = smithy;
    }

    checkSmithy(p, totalplayers, advhand, advdeck, advdiscard, &G);
  }

  printf ("TESTS FINISHED.\n");

  return 0;
}