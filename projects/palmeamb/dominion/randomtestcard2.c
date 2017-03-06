/**************************************
Ambrelle Palmer
randomtestcard2.c
Random Test for Village card

randomtestcard2: randomtestcard2
     ./randomtestcard2 &> randomtestcard2.out
     gcov dominion.c >> randomtestcard2.out
     cat dominion.c.gcov >> randomtestcard2.out
*****************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "dominion.c"

/**********************************************
Functionality to test for:
     One card is added to player's hand from their deck
     Player's number of available actions is increased by 2
     Played card is discarded from hand
     No state change for other players
     No state change in victory or kingdom card files
**********************************************/

//#define TESTCARD "village"
#define NOISY_TEST 1

int main(){

int i, j, deckCount, handCount, discardCount, numPlayer;
     int handCountErrors, handCountPassed, deckCountErrors, deckCountPassed = 0;
     int  k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
     struct gameState G;

     srand(time(NULL));

     printf("Random Testing Village Card");

     for(i = 0; i < 2000; i++){

          numPlayer = rand() % 4;
          seed = rand();
    
          initializeGame(numPlayer, k, seed, &G);


          G.deckCount[numPlayer] = rand() % MAX_DECK;
          G.discardCount[numPlayer] = rand() % MAX_DECK;
          G.handCount[numPlayer] = rand() % MAX_HAND;

          handCount = G.handCount[numPlayer];
          deckCount = G.deckCount[numPlayer];
          discardCount = G.discardCount[numPlayer];

          cardEffect(village, 1, 1, 1, &G, 0, 0);

          newHandCount = G.handCount[numPlayer];
          newDeckCount = G.deckCount[numPlayer];
          newDiscardCount = G.discardCount[numPlayer];

		if((handCount + 1) != newHandCount){
               printf("hand count = %d, expected hand count = %d\n", newHandCount, handCount +1);
               handCountErrors ++;
          }

          else
          {
               handCountPassed++;
          }

          if((deckCount-1) != newDeckCount){
               printf("deck count = %d, expected deck count = %d\n", newDeckCount, deckCount-1);
               deckCountError++;
          }
          else
          {
               deckCountPassed++;
          }   
		if((discardCount + 1) != newDiscardCount){
			printf("discard count = %d, expected discard count = %d\n", newDiscardCount, discardCount+1);
		}

     free(G);
     }

     printf("\n RANDOM TESTING OF VILLAGE CARD COMPLETED\n");

     return 0;
}


