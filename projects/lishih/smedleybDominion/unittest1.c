/*
File Name : unittest1.c
purpose : test playCard function
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main()
{
	//access struct variable for initializeGame & test the playCard function
	struct gameState testPlayCard;
	struct gameState playC;

	//give to pass the initializeGame()
	int numPlayer = 2;
	int kCards[10] = {adventurer, council_room, copper, silver, gold, remodel, smithy, village, baron, great_hall};
    int seed = 2000;

    //give to pass the playCard when the initializeGame called the playCard function
    int currentPlayer = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    int result;

	//init the gameState and playCard
	initializeGame (numPlayer,kCards, seed, &playC);

    printf("--------------------------------------------------------------------- \n");
	printf("Testing playCard()\n");

	//copy memory from playC to testPlayCard and give size of the struct gameState
	memcpy(&testPlayCard, &playC, sizeof(struct gameState));

    //test the playCard when phase =0
	testPlayCard.phase =0;
	result = playCard(handpos, choice1, choice2, choice3, &testPlayCard);
    printf("phase = 0 , test result should return to -1.\n");
	printf("result = %d\n\n", result);

	//test numberAction=0 in playCard ()
	memcpy(&testPlayCard, &playC, sizeof(struct gameState));
	testPlayCard.numActions =0;
    result = playCard(handpos, choice1, choice2, choice3, &testPlayCard);
    printf("numAction = 0 , test result should return to -1.\n");
	printf("result = %d\n\n", result);

	return 0;
}
