/*
unittest1.c Testing Shuffle Function
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


  printf ("Starting Shuffle Units Tests...\n\n");

  printf ("\nTesting for Shuffle Being Used by Consecutive Players\n\n");

  initializeGame(4, k, 5, &G);

  int i=0;
  int j=0;
  int shufReturn = 0;

  for(i = 0; i < 4; i++) {
    drawCard(i, &G);
    drawCard(i, &G);
    drawCard(i, &G);
    drawCard(i, &G);
    drawCard(i, &G);


    printf("Player %d\n", i);
    printf("Testing Shuffled with 10 cards in hand\n");

    shufReturn = shuffle(i, &G);
    assertTrue(shufReturn == 0, "Testing if shuffle recognized cards");
    assertTrue(G.handCount[i] == 10, "Testing if hand amount is correct");

    for(j = 0; j < 10; j++)
        discardCard(j, i, &G, 0);

    printf("Testing Shuffled with 0 cards in hand\n");

    shufReturn = shuffle(i, &G);

    assertTrue(shufReturn == -1, "Testing if shuffle recognized no cards");
    assertTrue(G.handCount[i] == 0, "Testing if hand amount is correct");

    endTurn(&G);
    printf("\n");
  }

  printf ("\nShuffle Unit Tests Complete\n\n");

  return 0;

}
