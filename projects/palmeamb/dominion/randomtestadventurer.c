/****************************************
Ambrelle Palmer
randomtestcard1.c
Random Test Generator for Adventurer card

randomTestAdventurer: adventurer
	./randomtestadventurer &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

*****************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*
Functionality to test for:
     •Cards are drawn until 2 treasure cards are added to player's hand from their deck
     •All other cards drawn are discarded (handCount only increased by 2)
     •No state change for other players 
     •No state change for victory or kingdom card files
     •adventurer card is discarded
*/

#define NOISY_TEST 1

int main(){

     int i, j, deckCount, handCount, discardCount, numPlayer;
	int handCountErrors, handCountPassed, deckCountErrors, deckCountPassed = 0;
	int  k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	struct gameState G;

	srand(time(NULL));	

     printf("Random Testing Adventurer Card");

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

		cardEffect(adventurer, 1, 1, 1, &G);

		newHandCount = G.handCount[numPlayer];
		newDeckCount = G.deckCount[numPlayer];
		newDiscardCount = G.discardCount[numPlayer];

		if((handCount + 2) != newHandCount){
			printf("hand count = %d, expected hand count = %d\n", newHandCount, handCount +2);
			handCountErrors ++;
		} 

		else
		{
			handCountPassed++;
		}

		if((deckCount) != newDeckCount){
			printf("deck count = %d, expected deck count = %d\n", newDeckCount, deckCount);
			deckCountError++;
		}
		else
		{
			deckCountPassed++;
		}	

     free(G);
	}

	printf("\n RANDOM TESTING OF ADVENTURER CARD COMPLETED\n");

     return 0;
}

