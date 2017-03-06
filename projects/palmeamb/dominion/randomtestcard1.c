/****************************************
Ambrelle Palmer
randomtestcard.c
Random Test for Smithy card

randomTest1: randomtestcard1
	./randomtestcard1.c &> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
*****************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*****************
Functionality to test for:
     •Current player draws exactly 3 cards from their deck
     •Player has one less action to play
     •No state change for other players (not sure how to implement)
     •No state change in victory or kingdom card files
     •Smithy card is discarded
*******************/

#define NOISY_TEST 1
#define MAX_TESTS 2000

int main(){

	 int i, j, deckCount, handCount, discardCount, numPlayer;
     int handCountErrors, handCountPassed, deckCountErrors, deckCountPassed = 0;
     int  k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
     struct gameState G;

     srand(time(NULL));

     printf("Random Testing Smithy Card");

     for(i = 0; i < MAX_TESTS; i++){

          numPlayer = rand() % 4;
          seed = rand();

          initializeGame(numPlayer, k, seed, &G);


          G.deckCount[numPlayer] = rand() % MAX_DECK;
          G.discardCount[numPlayer] = rand() % MAX_DECK;
          G.handCount[numPlayer] = rand() % MAX_HAND;

          handCount = G.handCount[numPlayer];
          deckCount = G.deckCount[numPlayer];
          discardCount = G.discardCount[numPlayer];

          cardEffect(smithy, 1, 1, 1, &G);

          newHandCount = G.handCount[numPlayer];
          newDeckCount = G.deckCount[numPlayer];
          newDiscardCount = G.discardCount[numPlayer];

		if((handCount + 3) != newHandCount){
               printf("hand count = %d, expected hand count = %d\n", newHandCount, handCount +3);
               handCountErrors ++;
          }

          else
          {
               handCountPassed++;
          }

          if((deckCount-3) != newDeckCount){
               printf("deck count = %d, expected deck count = %d\n", newDeckCount, deckCount-3);
               deckCountError++;
          }
          else
          {
               deckCountPassed++;
          }

		if ((discardCount+1) != newDiscardCount){
			printf("discard count = %d, expected discard count = %d\n", newDiscardCount, discardCount+1);
			discardCountError++;
		}
		else
		{
			discardCountPassed++;
		}

     free(G);
     }

     printf("\n RANDOM TESTING OF SMITHY CARD COMPLETED\n");

     return 0;
}




