/*
File Name : unittest4.c
purpose : test buyCard function
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main() {

    //access struct variable for initializeGame & test the playCard function
	struct gameState testBuyCard;
	struct gameState buyC;

	//give to pass the initializeGame()
	int numPlayer = 2;
	int kCards[10] = {adventurer, council_room, copper, silver, gold, remodel, smithy, village, baron, great_hall};
    int seed = 2000;

    int result;

   // initialize the game state and player cards
   initializeGame(numPlayer, kCards, seed, &buyC);

   printf("--------------------------------------------------------------------- \n");
   printf("Testing buyCard()\n");

   printf("testBuyCard.numBuys = 0, supplyPos = 1,  return -1 \n");
   memcpy(&testBuyCard, &buyC, sizeof(struct gameState));
   // testBuyCard.phase = 0 should return -1
   testBuyCard.numBuys = 0;
   result =  buyCard(1 , &testBuyCard);
   printf("expected = -1\n");
   printf("result = %d\n\n", result);
   printf("testBuyCard.numBuys = 1, supplyPos = 1,  return 0 \n");
   memcpy(&testBuyCard, &buyC, sizeof(struct gameState));
   // testBuyCard.phase = 0 should return -1
   testBuyCard.numBuys = 1;
   result =  buyCard(1 , &testBuyCard);
   printf("expected = 0\n");
   printf("result = %d\n\n", result);
   return 0;
}
