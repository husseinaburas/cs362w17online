/*
 File Name: cardtest2.c
 unit test for the adventurer card

 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main (){

    struct gameState testCardEffect;
	struct gameState C;

	//give to pass the initializeGame()
	int numPlayer = 2;
	int kCards[10] = {adventurer, smithy, embargo, village, minion, mine, cutpurse, sea_hag, tribute, council_room};
    int seed = 2000;

    //give to pass the playCard when the initializeGame called the playCard function
    int currentPlayer = 0;
    int otherPlayer = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int drawNewCards = 2;

   	//init the gameState and playCard
	initializeGame (numPlayer,kCards, seed, &C);
	printf("--------------------------------------------------------------------- \n");
	printf("Testing adventurer Card: \n");
    //make a copy of the game state
    memcpy(&testCardEffect, &C, sizeof(struct gameState));


    /*----------------------------------Play Card Effect----------------------------------------*/
    // pass to: int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
    cardEffect(adventurer, choice1, choice2, choice3, &testCardEffect, handpos, &bonus);

    /*--------------------Output Result: check player's hand count and deck count---------------*/
    printf("Test result: current player status:\n");
    printf("Hand Count = %d, Expected = %d\n", testCardEffect.handCount[currentPlayer], C.handCount[currentPlayer] + drawNewCards-1);
    printf("Deck Count = %d, Expected = %d\n", testCardEffect.deckCount[currentPlayer], C.deckCount[currentPlayer] - drawNewCards);
    printf("Test result: another player status:\n");
    printf("Hand Count = %d, Expected = %d\n", testCardEffect.handCount[otherPlayer], C.handCount[otherPlayer]);
    printf("Deck Count = %d, Expected = %d\n", testCardEffect.deckCount[otherPlayer], C.deckCount[otherPlayer]);

    return 0;
}
