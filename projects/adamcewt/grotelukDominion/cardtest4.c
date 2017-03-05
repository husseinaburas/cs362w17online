/* 
 * Name: Thomas Adamcewicz
 * Due Date: 3/5/17
 * Function: cardEffect(great_hall, choice1, choice2, choice3, gameState *state, handPos, *bonus)
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

    printf("\n**** playGreat_hall() TESTING BEGINNING ****\n");

	int i;
	int tFlag = 0;
    int seed = 1000;
    int numPlayers = 2;
    int p1 = 0;
    int p2 = 1;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, outpost};
    int z = 0;
    int tempHand[MAX_HAND];
    int cardDrawn;
    struct gameState G;
    //int maxHandCount = 5;
    int initialSupplyCount[treasure_map + 1];
    int choice1, choice2, choice3;
    //int *bonus;

    //start game
    initializeGame(numPlayers, cards, seed, &G);
    int initDeckSizeP1 = G.deckCount[p1];
    int initDiscardSizeP1 = G.discardCount[p1];
    int initDeckSizeP2 = G.deckCount[p2];
    int initDiscardSizeP2 = G.discardCount[p2];
    int initHandSizeP1 = G.handCount[p1];
    int initHandSizeP2 = G.handCount[p2];
    int drawntreasure = 0;
    int initHandTreasure = 0;
    int initActions = G.numActions;

    //put village in p1 hand at first position
    G.hand[p1][0] = great_hall;

    //TEST-1: Test playGreat_hall() after game initialized
    //playGreat_hall(p1, &G, 0);
    cardEffect(great_hall, choice1, choice2, choice3, &G, 0, 0);
    printf("TEST-1\n **GAME INITIALIZED CALLING playGreat_hall() WITH P1 AND CHECKING CHANGED VARS**\n");
    printf("Check p1 handCount == initial handCount (1 card drawn, 1 discarded): ");
    assertTrue(initHandSizeP1 == G.handCount[p1]);
    printf("Check p1 deckCount == initial deckCount - 1: ");
    assertTrue(initDeckSizeP1 - 1 == G.deckCount[p1]);
    printf("Check numActions == 2 (original action + 1) ");
    assertTrue(G.numActions == 2);
    printf("Check numActions > original num actions ");
    assertTrue(G.numActions > initActions);
    printf("Check great_hall was discarded from p1 hand: ");
    int gHFound = 0;
    for (i = 0; i < G.handCount[p1]; i++) {
        if (G.hand[p1][i] == great_hall) gHFound++;
    }
    assertTrue(gHFound == 0);
    printf("Check value of p1 hand at current handCount is == -1 (discard): ");
    assertTrue(G.hand[p1][G.handCount[p1]] == -1);


    //TEST-2: Check deck/discard which shouldn't have changed
    printf("TEST-2\n **AFTER VILLAGE PLAYED, CHECK VARS THAT SHOULDN'T BE EFFECTED**\n");
    printf("Check discardCount is equal to initial discardCount for p1: ");
    assertTrue(G.discardCount[p1] == initDiscardSizeP1);
    printf("Check p2 Deck/Hand/Discard counts are same as initial values: ");
    assertTrue(G.discardCount[p2] == initDiscardSizeP2 && G.deckCount[p2] == initDeckSizeP2 && G.handCount[p2] == initHandSizeP2);

    printf("\n**** playGreat_hall() TESTING COMPLETE ****\n");

    return 0;

}