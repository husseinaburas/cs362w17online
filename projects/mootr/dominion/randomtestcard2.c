/**
 * Title:	Random tester for playFeast() card function
 * Author: Richard Moot
 * Description:	Automatically runs through a series of randomized tests
 * 	to test the playFeast() card function.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"



int main(int argv, char** argc) {
  struct gameState G;
  int i, j, l, handCount, deckCount, discardCount, failedTests, players;
  int k[10] = {adventurer, council_room, feast,   gardens, mine,
               remodel,    smithy,       village, baron,   great_hall};
  int numOfTests = 5000;

  if(argv < 2){
    printf("You must provide a random seed number.\n");
    return 1;
  } else {
    int randomSeed = atoi(argc[1]);
  };



  for(i = 0; i < numOfTests; i ++){

  }

  return 0;
};
