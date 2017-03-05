/* 
 * Name: Thomas Adamcewicz
 * Due Date: 2/7/17
 * Function: endTurn(struct gameState *state)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


 //assertTrue function in place of assert
 void assertTrue(int val) {
	if (val){
		printf("TEST PASSED\n");
	}
	else{
		printf("TEST FAILED\n");
	}
}


int main() {

    printf("\n**** endTurn() TESTING BEGINNING ****\n");

	int i;
	int tFlag = 0;
    int seed = 1000;
    int numPlayers = 2;
    int p1 = 0;
    int p2 = 1;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
    struct gameState G;
    //int maxHandCount = 5;
    int initialSupplyCount[treasure_map + 1];

    //start game
    initializeGame(numPlayers, cards, seed, &G);

    int initCoinCount = G.coins;

    //TEST-1: Test endTurn() after game initialized
    printf("TEST-1\n **GAME INITIALIZED CALLING endTurn() AND CHECKING CHANGED VARS**\n");
    endTurn(&G);
    printf("Checking p1 handCount == 0: ");
    assertTrue(G.handCount[p1] == 0);
    printf("Checking p1 discardCount == 5 (original size of hand): ");
    assertTrue(G.discardCount[p1] == 5);
    printf("Checking whoseTurn == p2: ");
    assertTrue(G.whoseTurn == p2);
    printf("Checking p2 handCount == 5: ");
    assertTrue(G.handCount[p2] == 5);
    int coinCount = 0;
    for (i = 0; i < G.handCount[p2]; i++) {
        if (G.hand[p2][i] == copper) coinCount++;
        if (G.hand[p2][i] == silver) coinCount += 2;
        if (G.hand[p2][i] == gold) coinCount += 3;
    }
    printf("Checking G.coins == manual count of p2 coins: ");
    assertTrue(G.coins == coinCount);
    //TEST-2: Test endTurn() 2nd change
    printf("TEST-2\n **GAME CALLING endTurn() AND CHECKING CHANGED VARS**\n");
    endTurn(&G);
    printf("Checking p2 handCount == 0: ");
    assertTrue(G.handCount[p2] == 0);
    printf("Checking p2 discardCount == 5 (original size of hand): ");
    assertTrue(G.discardCount[p2] == 5);
    printf("Checking whoseTurn == p1: ");
    assertTrue(G.whoseTurn == p1);
    printf("Checking p1 handCount == 5: ");
    assertTrue(G.handCount[p1] == 5);
    coinCount = 0;
    for (i = 0; i < G.handCount[p1]; i++) {
        if (G.hand[p1][i] == copper) coinCount++;
        if (G.hand[p1][i] == silver) coinCount += 2;
        if (G.hand[p1][i] == gold) coinCount += 3;
    }
    printf("Checking G.coins == manual count of p1 coins: ");
    assertTrue(G.coins == coinCount);

    //TEST-3: Test endTurn() 3rd change
    printf("TEST-3\n **GAME CALLING endTurn() 3RD TIME AND CHECKING CHANGED VARS**\n");
    endTurn(&G);
    printf("Checking p1 handCount == 0: ");
    assertTrue(G.handCount[p1] == 0);
    printf("Checking p1 discardCount == 10 (original size of hand + last turn): ");
    assertTrue(G.discardCount[p1] == 10);
    printf("Checking whoseTurn == p2: ");
    assertTrue(G.whoseTurn == p2);
    printf("Checking p2 handCount == 5: ");
    assertTrue(G.handCount[p2] == 5);
    printf("Checking p2 discardCount == 5 (original size of hand): ");
    assertTrue(G.discardCount[p2] == 5);
    coinCount = 0;
    for (i = 0; i < G.handCount[p2]; i++) {
        if (G.hand[p2][i] == copper) coinCount++;
        if (G.hand[p2][i] == silver) coinCount += 2;
        if (G.hand[p2][i] == gold) coinCount += 3;
    }
    printf("Checking G.coins == manual count of p2 coins: ");
    assertTrue(G.coins == coinCount);

    printf("\n**** endTurn() TESTING COMPLETE ****\n");

    return 0;
}
